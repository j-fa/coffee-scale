#pragma once

#include "ADC.hpp"
#include "InterfaceTypes.hpp"


namespace Test::Helpers
{
    class MockADC : public ADC::IADC
    {
    public:
        MockADC(ADC::Voltage voltage) : voltage_(voltage) {}
        ADC::Voltage Read() override
        {
            return voltage_;
        }
        void SetVoltage(ADC::Voltage voltage)
        {
            voltage_ = voltage;
        }

    private:
        ADC::Voltage voltage_;
    };
} // namespace Test::Helpers
