#include <stdio.h>
#include <pico/stdlib.h>
#include "core/FlightController.cpp"

int main()
{
    FlightController flc;
    stdio_init_all();
    const uint led_pin = 25;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port

    // Initialize chosen serial port
    stdio_init_all();

    flc.Init();
    // Loop forever
    while (true)
    {
        flc.Run();
        // Blink LED
        printf("Blinking!\r\n");
        gpio_put(led_pin, true);
        sleep_ms(500);
        gpio_put(led_pin, false);
        sleep_ms(500);
    }
}