// test/test_example.cpp
#include <catch2/catch_test_macros.hpp>
#include "CoffeeScale.hpp"
#include "Helpers.hpp"

using namespace ADC;
using namespace CoffeeScale;

namespace Test::app
{
    TEST_CASE("CoffeeScale basic functionality", "[CoffeeScale]")
    {
        Helpers::MockADC mockADC(0.0_V);
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
}