#include "catch2/catch_test_macros.hpp"
#include "LoadCell.hpp"
#include "Helpers.hpp"

using namespace ADC;
using namespace CoffeeScale;

namespace Test::app
{
    TEST_CASE("Calibration struct", "[LoadCell]")
    {
        CoffeeScale::Calibration calibration;
        SECTION("Default values")
        {
            REQUIRE(calibration.referenceWeight_ == 0.0_g);
            REQUIRE(calibration.voltageAtReferenceWeight_ == 0.0);
            REQUIRE(calibration.voltageAtZeroWeight_ == 0.0_V);
        }

        SECTION("IsValid checks")
        {
            REQUIRE_FALSE(calibration.IsValid());
            calibration.referenceWeight_ = 500.0_g;
            REQUIRE_FALSE(calibration.IsValid());
            calibration.voltageAtReferenceWeight_ = 2.0_V;
            REQUIRE(calibration.IsValid());
            calibration.voltageAtZeroWeight_ = 1.0_V;
            REQUIRE(calibration.IsValid());
            calibration.voltageAtReferenceWeight_ = 1.0_V;
            REQUIRE_FALSE(calibration.IsValid());
        }
    }

    TEST_CASE("LoadCell Calibration", "[LoadCell]")
    {
        Helpers::MockADC mockADC(0.0_V);
        CoffeeScale::LoadCell loadCell(mockADC);

        SECTION("Default calibration")
        {
            REQUIRE_FALSE(loadCell.GetCalibration().IsValid());
            auto weight = loadCell.ReadWeight();
            REQUIRE(weight == 0.0_g);
        }

        SECTION("Set and Get Calibration")
        {
            CoffeeScale::Calibration calibration = {
                .referenceWeight_ = 1000.0_g,
                .voltageAtReferenceWeight_ = 3.0_V,
                .voltageAtZeroWeight_ = 0.5_V
            };
            loadCell.SetCalibration(calibration);
            auto retrievedCalibration = loadCell.GetCalibration();
            REQUIRE(retrievedCalibration.referenceWeight_ == 1000.0_g);
            REQUIRE(retrievedCalibration.voltageAtReferenceWeight_ == 3.0_V);
            REQUIRE(retrievedCalibration.voltageAtZeroWeight_ == 0.5_V);

            mockADC.SetVoltage(3.0_V);
            REQUIRE(loadCell.ReadWeight() == 1000.0_g);
            mockADC.SetVoltage(0.5_V);
            REQUIRE(loadCell.ReadWeight() == 0.0_g);
        }
    }

    TEST_CASE("LoadCell ReadWeight", "[LoadCell]")
    {
        Helpers::MockADC mockADC(0.0_V);
        CoffeeScale::LoadCell loadCell(mockADC);

        CoffeeScale::Calibration calibration = {
            .referenceWeight_ = 500.0_g,
            .voltageAtReferenceWeight_ = 2.0_V,
            .voltageAtZeroWeight_ = 0.5_V
        };
        loadCell.SetCalibration(calibration);

        SECTION("Below zero weight voltage")
        {
            mockADC.SetVoltage(0.3_V);
            REQUIRE(loadCell.ReadWeight() == 0.0_g);
        }

        SECTION("At zero weight voltage")
        {
            mockADC.SetVoltage(0.5_V);
            REQUIRE(loadCell.ReadWeight() == 0.0_g);
        }

        SECTION("At reference weight voltage")
        {
            mockADC.SetVoltage(2.0_V);
            REQUIRE(loadCell.ReadWeight() == 500.0_g);
        }

        SECTION("Midpoint voltage")
        {
            mockADC.SetVoltage(1.25_V); // Midpoint between 0.5V and 2.0V
            REQUIRE(loadCell.ReadWeight() == 250.0_g);
        }
    }
}