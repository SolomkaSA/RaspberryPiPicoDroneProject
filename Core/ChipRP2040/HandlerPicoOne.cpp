#include "../common/Constants.cpp"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"
#include "hardware/pwm.h"

class HandlerPicoOne
{
public:
    void InitBoard()
    {
        // spi_init(spi1, 10000000);
        i2c_init(i2c_default, 400 * 1000);

        // gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
        // gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
        // gpio_pull_up(PICO_DEFAULT_SPI_TX_PIN);
        // gpio_pull_up(PICO_DEFAULT_SPI_RX_PIN);
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
        // bi_decl(bi_2pins_with_func(PICO_DEFAULT_SPI_RX_PIN, PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI));
    }
};