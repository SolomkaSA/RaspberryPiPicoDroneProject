#include "../common/Constants.cpp"
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

class HandlerPicoOne
{
public:
    void InitBoard()
    {
        i2c_init(I2C_DEFAULT_BLOCK, 400 * 1000);
        gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(I2C_SDA_PIN);
        gpio_pull_up(I2C_SCL_PIN);
        // Make the I2C pins available to picotool
        bi_decl(bi_2pins_with_func(I2C_SDA_PIN, I2C_SCL_PIN, GPIO_FUNC_I2C));
    }
};