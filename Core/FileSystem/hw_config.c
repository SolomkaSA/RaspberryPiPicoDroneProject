#include <string.h>
//
#include "my_debug.h"
//
#include "../sd_driver/hw_config.h"
//
#include "ff.h" /* Obtains integer types */
//
#include "diskio.h" /* Declarations of disk functions */

void spi0_dma_isr();

// Hardware Configuration of SPI "objects"
// Note: multiple SD cards can be driven by one SPI if they use different slave
// selects.
static spi_t spis[] = { // One for each SPI.
    {
        .hw_inst = spi1, // SPI component
        .miso_gpio = 12, // GPIO number (not pin number)
        .mosi_gpio = 11,
        .sck_gpio = 10,
        /* The choice of SD card matters! SanDisk runs at the highest speed. PNY
           can only mangage 5 MHz. Those are all I've tried. */
        //.baud_rate = 1000 * 1000,
        .baud_rate = 6250 * 1000, // The limitation here is SPI slew rate.
        //.baud_rate = 6250 * 1000,  // The limitation here is SPI slew rate.
        //.baud_rate = 25 * 1000 * 1000, // Actual frequency: 20833333. Has
        // worked for me with SanDisk.

        .dma_isr = spi0_dma_isr}};

// Hardware Configuration of the SD Card "objects"
static sd_card_t sd_cards[] = { // One for each SD card
    {
        .pcName = "0:",  // Name used to mount device
        .spi = &spis[0], // Pointer to the SPI driving this card
        .ss_gpio = 13,   // The SPI slave select GPIO for this SD card
        .m_Status = STA_NOINIT,
    }};

void spi0_dma_isr() { spi_irq_handler(&spis[0]); }

/* ********************************************************************** */
size_t sd_get_num() { return count_of(sd_cards); }
sd_card_t *sd_get_by_num(size_t num)
{
    if (num <= sd_get_num())
    {
        return &sd_cards[num];
    }
    else
    {
        return NULL;
    }
}
size_t spi_get_num() { return count_of(spis); }
spi_t *spi_get_by_num(size_t num)
{
    if (num <= sd_get_num())
    {
        return &spis[num];
    }
    else
    {
        return NULL;
    }
}

/* [] END OF FILE */