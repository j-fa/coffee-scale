#include "CoffeeScale.hpp"

namespace CoffeeScale
{
    void CoffeeScale::Zero()
    {
        zeroWeight_ = GetAbsoluteWeight();
    }

    Grams CoffeeScale::GetWeight()
    {
        return GetAbsoluteWeight() - zeroWeight_;
    }
}