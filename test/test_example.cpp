// test/test_example.cpp
#include <catch2/catch_test_macros.hpp>
#include "CoffeeScale.hpp"

using namespace ADC;
using namespace CoffeeScale;

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

TEST_CASE("CoffeeScale basic functionality", "[CoffeeScale]")
{
    MockADC mockADC(0.0_V);
    CoffeeScale::LoadCell loadCell(mockADC);
    CoffeeScale::Calibration dummyCalibration = {
        .referenceWeight_ = 750.0_g,
        .voltageAtReferenceWeight_ = 2.0,
    };
    loadCell.SetCalibration(dummyCalibration);
    CoffeeScale::CoffeeScale scale(loadCell);
    mockADC.SetVoltage(1.0_V);

    REQUIRE(scale.GetWeight() == 375.0_g);
}