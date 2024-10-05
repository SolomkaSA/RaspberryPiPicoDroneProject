#include <stdio.h>
#include <pico/stdlib.h>
#include "ff.h"
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif
#include "hardware/pwm.h"
// #include "../core/Common/Constant.cpp"
// #include <tusb.h> // tud_cdc_connected()
#include "../Core/FlightController.cpp"
#include "../core/FileSystem/SDCard.cpp"

int pico_led_init(void)
{
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on)
{
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main()
{
    stdio_init_all();
    int rc = pico_led_init();
    time_init();
    // if (cyw43_arch_init())
    // {
    //     printf("WiFi init failed");
    //     return -1;
    // }

    // WARNING!!!! ONLY FOR DEBUGGING WITH USB!!!!
    // wait here until the CDC ACM (serial port emulation) is connected
    // while (!tud_cdc_connected())
    // {
    //     sleep_ms(10);
    // }

    pico_set_led(true);
    // const uint led_pin = 25;
    const uint led_pin = PICO_DEFAULT_LED_PIN;

    // Initialize LED pin
    // gpio_init(led_pin);
    // gpio_set_dir(led_pin, GPIO_OUT);
    sleep_ms(30);
    pico_set_led(false);
    sleep_ms(30);
    // gpio_put(led_pin, true);
    pico_set_led(true);
    printf("Initialize FlightController!\r\n");
    FlightController flc;
    printf("Init Sensors!\r\n");
    // gpio_put(led_pin, false);
    pico_set_led(false);
    flc.Init();
    printf("Start Loop!\r\n");
    // Loop forever
    while (true)
    {
        // Blink LED
        // printf("Blinking!\r\n");
        // gpio_put(led_pin, true);
        pico_set_led(true);
        flc.Run();
        sleep_ms(30);
        // gpio_put(led_pin, false);
        pico_set_led(false);
        sleep_ms(30);
    }
}
