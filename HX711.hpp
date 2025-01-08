#include "hardware/pio.h"
#include "ADC.hpp"

namespace ADC
{
    class HX711 : IADC
    {
    public:
        HX711(Voltage referenceVoltage, PIO pio, uint stateMachine, uint dataPin, uint clockPin, Voltage zeroOffset = 0.0);
        ~HX711();
        Voltage Read() override;

    private:
        int InitPIOProgram(PIO pio, uint sm, uint offset, uint data_pin, uint clock_pin);

        Voltage referenceVoltage_;
        Voltage zeroOffsetVoltage_;
        PIO pio_;
        uint pioStateMachine_;
        uint pioOffset_;
    };
} // namespace ADC
