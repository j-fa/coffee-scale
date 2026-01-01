#include <iostream>

#include "HX711.hpp"
#include "CoffeeScale.hpp"

using namespace ADC;
using namespace CoffeeScale;

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
    .referenceVoltage_ = 3.3_V, // Use ADC::Voltage literal
    .hx711DataPin_ = 26,
    .hx711ClockPin_ = 27,
};

CoffeeScale::Calibration dummyCalibration = {
    .referenceWeight_ = 750.0_g,
    .voltageAtReferenceWeight_ = 2.0,
};

int main()
{
    ADC::HX711 adc = ADC::HX711(hwConfig.referenceVoltage_, hwConfig.pioInstance_, hwConfig.pioStateMachine_, hwConfig.hx711DataPin_, hwConfig.hx711ClockPin_);
    LoadCell loadCell = LoadCell(dynamic_cast<ADC::IADC &>(adc));
    loadCell.SetCalibration(dummyCalibration);

    CoffeeScale::CoffeeScale scale = CoffeeScale::CoffeeScale(loadCell);
    scale.Zero();

    auto weight = scale.GetWeight();
}