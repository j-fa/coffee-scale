#include <iostream>

#include "HX711.hpp"
#include "CoffeeScale.hpp"

struct HardwareConfiguration
{
public:
    PIO pioInstance_;
    uint pioStateMachine_;
    ADC::Voltage referenceVoltage_;
    uint hx711DataPin_;
    uint hx711ClockPin_;

    // HardwareConfiguration(PIO pioInstance, uint pioStateMachine, ADC::Voltage referenceVoltage)
    //     : pioInstance_(pioInstance), pioStateMachine_(pioStateMachine), referenceVoltage_(referenceVoltage)
    // {
    // }
};

HardwareConfiguration hwConfig = {
    .pioInstance_ = pio0,
    .pioStateMachine_ = 0,
    .referenceVoltage_ = 3.3,
    .hx711DataPin_ = 26,
    .hx711ClockPin_ = 27,
};

CoffeeScale::Calibration dummyCalibration = {
    .referenceWeight_ = 750,
    .voltageAtReferenceWeight_ = 2.0,
};

int main()
{
    ADC::HX711 adc = ADC::HX711(hwConfig.referenceVoltage_, hwConfig.pioInstance_, hwConfig.pioStateMachine_, hwConfig.hx711DataPin_, hwConfig.hx711ClockPin_);
    CoffeeScale::CoffeeScale scale = CoffeeScale::CoffeeScale(dynamic_cast<ADC::IADC *>(&adc));

    scale.SetCalibration(dummyCalibration);
    scale.Zero();

    auto weight = scale.GetWeight();
}