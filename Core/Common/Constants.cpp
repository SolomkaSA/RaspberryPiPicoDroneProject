#define IS_PICO_W_BOARD 1 // 0 is Pico and 1 is PicoW

#define I2C_DEFAULT_BLOCK 0
// #define PICO_DEFAULT_SPI 0

#define I2C_SDA_PIN 4 // it is a GP ports not a pin!
#define I2C_SCL_PIN 5

#define BUZZER_SOUND_PIN 29

#define MOTOR_LEFT_UP_PIN 21
#define MOTOR_LEFT_DOWN_PIN 20
#define MOTOR_RIGHT_UP_PIN 6
#define MOTOR_RIGHT_DOWN_PIN 7

#define SDCARD_SPIx_SCK_PIN 14
#define SDCARD_SPIx_TX_MOSI_PIN 15
#define SDCARD_SPIx_RX_MISO_PIN 16
#define SDCARD_SPIx_CSn_PIN 17

#define PICO_DEFAULT_LED_PIN 25

#define NRF24_CE_GPIO 9
#define NRF24_CSN_GPIO 14

// #define CE_PIN 8
// #define CSN_PIN 9