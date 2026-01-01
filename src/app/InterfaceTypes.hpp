#pragma once

namespace CoffeeScale
{
    using Grams = double;

    constexpr Grams operator"" _g(long double val)
    {
        return static_cast<Grams>(val);
    }
}
