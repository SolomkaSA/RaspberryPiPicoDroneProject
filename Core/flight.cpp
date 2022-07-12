#include "Sensors/AccelGyro-GY-521-MPU6050.cpp"
#include "Sensors/Barometer-GY-BM-280.cpp"
void Flight_Init()
{ // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
}
void Run()
{
    /*MPU5060*/
    mpu6050_reset();
    AccellGyroStruct AccellGyro;
    bmp280_init();
    struct bmp280_calib_param params;
    bmp280_get_calib_params(&params);
    float Temperature = 0, Pressure = 0;
    Run_BMP280(&Temperature, &Pressure, &params);

    Run_MPU5060(&AccellGyro);
}