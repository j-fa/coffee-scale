#pragma once

#include "ADC.hpp"
#include "InterfaceTypes.hpp"

using namespace ADC;

namespace CoffeeScale
{
    struct Calibration
    {
        Grams referenceWeight_ = 0.0_g;
        ADC::Voltage voltageAtReferenceWeight_ = 0.0_V;
        ADC::Voltage voltageAtZeroWeight_ = 0.0_V;

        bool IsValid() const
        {
            return referenceWeight_ > 0 && voltageAtReferenceWeight_ > voltageAtZeroWeight_;
        }
    };

    class LoadCell
    {
    public:
        LoadCell(IADC &adc) : adc_(adc) {};

        Grams ReadWeight();
        void Calibrate(Grams referenceWeight);
        void SetCalibration(const Calibration &calibration) { calibration_ = calibration; };
        const Calibration &GetCalibration() const { return calibration_; };

    private:
        IADC &adc_;
        Calibration calibration_;
    };
} // namespace CoffeeScale