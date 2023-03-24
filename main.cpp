#include <stdio.h>
#include <pico/stdlib.h>
#include "pico/cyw43_arch.h"
#include "core/FlightController.cpp"
#include "core/FileSystem/SDCard.cpp"
int main()
{
    stdio_init_all();
    if (cyw43_arch_init())
    {
        printf("WiFi init failed");
        return -1;
    }
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    // const uint led_pin = 25;
    const uint led_pin = PICO_DEFAULT_LED_PIN;

    // Initialize LED pin
    // gpio_init(led_pin);
    // gpio_set_dir(led_pin, GPIO_OUT);
    sleep_ms(5000);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(500);
    // gpio_put(led_pin, true);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    printf("Initialize FlightController!\r\n");
    FlightController flc;
    printf("Init Sensors!\r\n");
    flc.Init();
    // gpio_put(led_pin, false);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    printf("Start Loop!\r\n");
    // Loop forever
    while (true)
    {
        // Blink LED
        // printf("Blinking!\r\n");
        // gpio_put(led_pin, true);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        flc.Run();

        // gpio_put(led_pin, false);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }
}