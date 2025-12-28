// test/test_example.cpp
#include <catch2/catch_test_macros.hpp>
#include "CoffeeScale.hpp"

using namespace ADC;

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
    CoffeeScale::CoffeeScale scale(&mockADC);
    scale.Zero();
}