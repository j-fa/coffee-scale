#pragma once

#include "ADC.hpp"

namespace CoffeeScale
{
    using Grams = double;

    constexpr Grams operator"" _g(long double val)
    {
        return static_cast<Grams>(val);
    }

    struct Calibration
    {
        Grams referenceWeight_;
        ADC::Voltage voltageAtReferenceWeight_;
    };

    class CoffeeScale
    {
    public:
        CoffeeScale(ADC::IADC *adc);
        Calibration Calibrate(Grams ReferenceWeight);
        void Zero();
        Grams GetWeight();
        Grams GetAbsoluteWeight();
        Grams GetZeroWeight() { return zeroWeight_; }
        Calibration GetCalibration() { return calibration_; }
        void SetCalibration(Calibration calibration) { calibration_ = calibration; }

    private:
        ADC::IADC *adc_;
        Calibration calibration_ = {0};
        Grams zeroWeight_ = 0;
    };
} // namespace CoffeeScale
