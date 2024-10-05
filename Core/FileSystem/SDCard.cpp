#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "sd_card.h"
#include "ff.h"
#include "rtc.h"
#include "../sd_driver/hw_config.h"
// #include "hw_config.c"
#include "diskio.h" /* Declarations of disk functions */

// static spi_t *p_spi;
sd_card_t *pSD;
// void add_spi(spi_t *const spi);
// void add_sd_card(sd_card_t *const sd_card);

class SDCard
{
    FRESULT fr;
    FATFS fs;
    FIL fil;

public:
    void InitSDInstance()
    {

        pSD = sd_get_by_num(0);
        /* p_spi = new spi_t;
         memset(p_spi, 0, sizeof(spi_t));
         if (!p_spi)
             panic("Out of memory");
         p_spi->hw_inst = spi1; // SPI component
         p_spi->miso_gpio = 12; // GPIO number (not pin number)
         p_spi->mosi_gpio = 11;
         p_spi->sck_gpio = 10;
         */
        /* The choice of SD card matters! SanDisk runs at the highest speed. PNY
         can only mangage 5 MHz. Those are all I've tried. */
        /*
      // p_spi->baud_rate = 12500 * 1000,
      // p_spi->baud_rate = 1000 * 1000;
      p_spi->baud_rate = 10000000; // The limitation here is SPI slew rate.
                                   // p_spi->baud_rate = 6250 * 1000;  // The limitation here is SPI slew rate.
      // p_spi->baud_rate = 25 * 1000 * 1000; // Actual frequency: 20833333. Has
      // worked for me with SanDisk.
      add_spi(p_spi);

      // Hardware Configuration of the SD Card "object"
      sd_card_t *p_sd_card = new sd_card_t;
      if (!p_sd_card)
          panic("Out of memory");
      memset(p_sd_card, 0, sizeof(sd_card_t));
      p_sd_card->pcName = "0:"; // Name used to mount device
      p_sd_card->spi = p_spi;   // Pointer to the SPI driving this card
      p_sd_card->ss_gpio = 13;  // The SPI slave select GPIO for this SD card
      // p_sd_card->card_detect_gpio = 22; // Card detect
      // What the GPIO read returns when a card is
      // present. Use -1 if there is no card detect.
      // p_sd_card->card_detected_true = 1;
      // State attributes:
      // p_sd_card->m_Status = STA_NOINIT;
      p_sd_card->card_detected_true = 1;
      // p_sd_card->sectors = 0;
      // p_sd_card->card_type = 0;
      add_sd_card(p_sd_card);
      */
    }

    void CreateEmptyFile(char filename[])
    {
        int ret;
        // Initialize SD card
        while (!sd_init_driver())
        {
            printf("ERROR: Could not initialize SD card\r\n");
        }
        // Mount drive
        fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
        while (fr != FR_OK)
        {
            printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
            fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
        }

        // Open file for writing ()
        fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
        while (fr != FR_OK)
        {
            printf("ERROR: Could not open file (%d)\r\n", fr);
            fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
        }

        // Close file
        fr = f_close(&fil);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not close file (%d)\r\n", fr);
        }
    }
    void WriteIntoFile(char filename[], char *text)
    {

        int ret;
        // Initialize SD card
        while (!sd_init_driver())
        {
            printf("ERROR: Could not initialize SD card\r\n");
        }
        // Mount drive
        fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
        while (fr != FR_OK)
        {
            printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
            fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
        }

        // Open file for writing ()
        fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
        // fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
        while (fr != FR_OK)
        {
            printf("ERROR: Could not open file (%d)\r\n", fr);
            fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
        }

        // Write something to file
        ret = f_printf(&fil, text);
        if (ret < 0)
        {
            printf("ERROR: Could not write to file (%d)\r\n", ret);
            f_close(&fil);
        }

        // Close file
        fr = f_close(&fil);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not close file (%d)\r\n", fr);
        }
    }

    void ReadFile(char filename[])
    {
        char buf[100];
        // Open file for reading
        fr = f_open(&fil, filename, FA_READ);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not open file (%d)\r\n", fr);
        }

        // Print every line in file over serial
        printf("Reading from file '%s':\r\n", filename);
        printf("---\r\n");
        while (f_gets(buf, sizeof(buf), &fil))
        {
            printf(buf);
        }
        printf("\r\n---\r\n");

        // Close file
        fr = f_close(&fil);
        if (fr != FR_OK)
        {
            printf("ERROR: Could not close file (%d)\r\n", fr);
        }
    }

    void UnmountSDCard()
    {
        // Unmount drive
        f_unmount(pSD->pcName);
    }
};