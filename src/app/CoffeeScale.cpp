#include "CoffeeScale.hpp"

namespace CoffeeScale
{
    CoffeeScale::CoffeeScale(ADC::IADC *adc) : adc_(adc)
    {
    }

    void CoffeeScale::Zero()
    {
        zeroWeight_ = GetAbsoluteWeight();
    }

    Grams CoffeeScale::GetAbsoluteWeight()
    {
        auto voltage = adc_->Read();
        Grams weight = voltage * calibration_.referenceWeight_ / calibration_.voltageAtReferenceWeight_;
        return weight;
    }

    Grams CoffeeScale::GetWeight()
    {
        return GetAbsoluteWeight() - zeroWeight_;
    }

    Calibration CoffeeScale::Calibrate(Grams referenceWeight)
    {
        calibration_.voltageAtReferenceWeight_ = adc_->Read();
        calibration_.referenceWeight_ = referenceWeight;
        return calibration_;
    }

}