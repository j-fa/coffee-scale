#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hx711_read.pio.h"
#include <iostream>

#define HX711_DATA_PIN 26
#define HX711_CLOCK_PIN 27

// Initialize the PIO program for HX711
int hx711_program_init(PIO pio, uint sm, uint offset, uint data_pin, uint clock_pin)
{
    int error = PICO_OK;
    pio_gpio_init(pio, data_pin);                                            // Initialize the data pin
    pio_gpio_init(pio, clock_pin);                                           // Initialize the clock pin
    if (error = pio_sm_set_consecutive_pindirs(pio, sm, data_pin, 1, false)) // Set data pin as input
    {
        return error;
    }
    if (error = pio_sm_set_consecutive_pindirs(pio, sm, clock_pin, 1, true)) // Set clock pin as output
    {
        return error;
    }
    pio_sm_config c = hx711_read_program_get_default_config(offset); // Get default config
    sm_config_set_clkdiv(&c, 125.0);                                 // f_clk = 1 MHz
    sm_config_set_in_shift(&c, false, false, 0);                     // Shift ISR to the left
    sm_config_set_in_pins(&c, data_pin);                             // Set data pin for input
    sm_config_set_sideset_pins(&c, clock_pin);                       // Set clock pin for sideset
    if (error = pio_sm_init(pio, sm, offset, &c))                    // Initialize the state machine with the config
    {
        return error;
    }
    pio_sm_set_enabled(pio, sm, true); // Enable the state machine
    return error;
}

int main()
{
    stdio_init_all();                                                                    // Initialize standard I/O
    PIO pio = pio0;                                                                      // Use PIO instance 0
    uint sm = 0;                                                                         // Use state machine 0
    uint offset = pio_add_program(pio, &hx711_read_program);                             // Load the PIO program
    if (hx711_program_init(pio, sm, offset, HX711_DATA_PIN, HX711_CLOCK_PIN) != PICO_OK) // Initialize the HX711 program
    {
        exit(EXIT_FAILURE);
    }

    std::cout << "Starting HX711 read loop" << std::endl;
    while (true)
    {
        uint32_t data = pio_sm_get_blocking(pio, sm); // Read data from the state machine
        // std::cout << "0x" << std::hex << data << std::endl;
        // std::cout << "ADC Value: " << data * 100.0 / 0x7FFFFF << " %" << std::endl;
        std::cout << data << std::endl;

        sleep_ms(100); // Adjust the delay as needed
    }
}
