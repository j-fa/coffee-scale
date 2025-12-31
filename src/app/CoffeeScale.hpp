#pragma once

#include "ADC.hpp"
#include "LoadCell.hpp"
#include "InterfaceTypes.hpp"

namespace CoffeeScale
{
    class CoffeeScale
    {
    public:
        CoffeeScale(LoadCell &loadCell) : loadCell_(loadCell) {};
        void Zero();
        Grams GetWeight();
        Grams GetAbsoluteWeight();
        Grams GetZeroWeight() { return zeroWeight_; }

    private:
        LoadCell &loadCell_;
        Grams zeroWeight_ = 0;
    };
} // namespace CoffeeScale
