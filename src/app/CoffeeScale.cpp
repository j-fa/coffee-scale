#include "CoffeeScale.hpp"

namespace CoffeeScale
{
    void CoffeeScale::Tare()
    {
        tareWeight_ = GetAbsoluteWeight();
    }

    Grams CoffeeScale::GetAbsoluteWeight()
    {
        return loadCell_.ReadWeight();
    }
}