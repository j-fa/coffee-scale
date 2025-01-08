#include "HX711.hpp"
#include "hx711_read.pio.h"

namespace ADC
{
    HX711::HX711(Voltage referenceVoltage, PIO pio, uint pioStateMachine, uint dataPin, uint clockPin, Voltage zeroOffset = 0.0)
        : referenceVoltage_(referenceVoltage), zeroOffsetVoltage_(zeroOffset), pio_(pio), pioStateMachine_(pioStateMachine)
    {
        pioOffset_ = pio_add_program(pio, &hx711_read_program);
        assert(InitPIOProgram(pio_, pioStateMachine_, pioOffset_, dataPin, clockPin) == PICO_OK);
    }

    HX711::~HX711()
    {
        pio_remove_program_and_unclaim_sm(&hx711_read_program, pio_, pioStateMachine_, pioOffset_);
    }

    Voltage HX711::Read()
    {
        Voltage maxOutputLsb = (1 << 24) - 1;
        auto sample = pio_sm_get_blocking(pio_, pioStateMachine_);
        return sample * referenceVoltage_ / maxOutputLsb - zeroOffsetVoltage_;
    }

    int HX711::InitPIOProgram(PIO pio, uint sm, uint offset, uint data_pin, uint clock_pin)
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
} // namespace ADC
