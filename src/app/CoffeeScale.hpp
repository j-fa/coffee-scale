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
        void Tare();
        Grams GetWeight() {return GetAbsoluteWeight() - tareWeight_;};
        Grams GetAbsoluteWeight();
        Grams GetTareWeight() { return tareWeight_; }

    private:
        LoadCell &loadCell_;
        Grams tareWeight_ = 0.0_g;
    };
} // namespace CoffeeScale
