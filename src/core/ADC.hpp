#pragma once

namespace ADC
{
    using Voltage = double;
    constexpr Voltage operator"" _V(long double val)
    {
        return static_cast<Voltage>(val);
    }

    class IADC
    {
    public:
        virtual Voltage Read() = 0;
    };
} // namespace ADC
