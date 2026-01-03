#include "LoadCell.hpp"

namespace CoffeeScale
{
    Grams CoffeeScale::LoadCell::ReadWeight()
    {
        if (!calibration_.IsValid())
        {
            return 0.0_g;
        }

        ADC::Voltage currentVoltage = adc_.Read();

        if (currentVoltage <= calibration_.voltageAtZeroWeight_)
        {
            return 0.0_g;
        }

        ADC::Voltage voltageDifference = currentVoltage - calibration_.voltageAtZeroWeight_;
        ADC::Voltage referenceVoltageDifference = calibration_.voltageAtReferenceWeight_ - calibration_.voltageAtZeroWeight_;

        double weightRatio = voltageDifference / referenceVoltageDifference;
        Grams weight = calibration_.referenceWeight_ * weightRatio;

        return weight;
    }
} // namespace CoffeeScale
