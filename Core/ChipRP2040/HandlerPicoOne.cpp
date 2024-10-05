#include "../common/Constants.cpp"
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

class HandlerPicoOne
{
public:
    void InitBoard()
    {
        set_sys_clock_khz(133000, false);
        spi_init(spi1, 40 * 1000000);
        // spi_init(spi0, 10000000);
        i2c_init(i2c_default, 400 * 1000);
        // PUBLIC PICO_DEFAULT_SPI_SCK_PIN=10 # depends on which SPI bus (0 or 1) is being used
        // PUBLIC PICO_DEFAULT_SPI_TX_PIN=11  # depends on which SPI bus (0 or 1) is being used
        // PUBLIC PICO_DEFAULT_SPI_RX_PIN=12 # depends on which SPI bus (0 or 1) is being used

        // gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
        // gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
        // gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
        // gpio_set_function(14, GPIO_FUNC_SPI);
        // gpio_set_function(9, GPIO_FUNC_SPI);

        // gpio_pull_up(PICO_DEFAULT_SPI_TX_PIN);
        // gpio_pull_up(PICO_DEFAULT_SPI_RX_PIN);
        // gpio_pull_up(PICO_DEFAULT_SPI_SCK_PIN);
        // gpio_pull_up(14);
        // gpio_pull_up(9);
        // gpio_init(9);
        // gpio_init(14);
        // gpio_set_dir(9, 1);
        // gpio_set_dir(14, 1);

        gpio_set_function(MOTOR_LEFT_UP_PIN, GPIO_FUNC_PWM);
        gpio_set_function(MOTOR_LEFT_DOWN_PIN, GPIO_FUNC_PWM);
        gpio_set_function(MOTOR_RIGHT_UP_PIN, GPIO_FUNC_PWM);
        gpio_set_function(MOTOR_RIGHT_DOWN_PIN, GPIO_FUNC_PWM);

        gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(I2C_SDA_PIN);
        gpio_pull_up(I2C_SCL_PIN);
        // Make the I2C pins available to picotool
        bi_decl(bi_2pins_with_func(I2C_SDA_PIN, I2C_SCL_PIN, GPIO_FUNC_I2C));
        // bi_decl(bi_3pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI));
    }
};