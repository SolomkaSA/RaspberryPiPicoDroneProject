#include <stdio.h>
#include <pico/stdlib.h>
#include "core/FlightController.cpp"
#include "core/FileSystem/SDCard.cpp"
int main()
{
    stdio_init_all();
    const uint led_pin = 25;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    sleep_ms(5000);
    gpio_put(led_pin, true);
    printf("Initialize FlightController!\r\n");
    FlightController flc;
    printf("Init Sensors!\r\n");
    flc.Init();
    gpio_put(led_pin, false);
    printf("Start Loop!\r\n");
    // Loop forever
    while (true)
    {
        // Blink LED
        // printf("Blinking!\r\n");
        gpio_put(led_pin, true);
        flc.Run();
        gpio_put(led_pin, false);
    }
}