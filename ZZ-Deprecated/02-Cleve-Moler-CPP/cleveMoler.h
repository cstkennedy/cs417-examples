#ifndef CLEVE_MOLER_H
#define CLEVE_MOLER_H

#include <cmath>
#include <cfloat>

// Use Boost float128
#include <boost/multiprecision/float128.hpp>

using namespace boost::multiprecision;

namespace std {
    /**
     * Compute the abs of a float128 argument. Due to the quirks around
     * float128 (even with Boost), there is no proper std::abs call
     */
    inline
    float128 abs(float128 x)
    {
        return signbit(x) ? changesign(x) : x;
    }
}

/**
 * Estimate floating point precision using the method attributed
 * to Cleve Moler.
 */
template<typename T>
T estimatePrecision()
{
    T a = (4.0 / 3.0);
    T b = a - 1.0;
    T c = b + b + b;

    return std::abs(c - 1.0);
}

/**
 * Estimate floating point precision using the method attributed
 * to Cleve Moler.
 *
 * The "float128" type provided by boost requires some bodges
 */
template<>
float128 estimatePrecision<float128>()
{
    using T = float128;

    T ONE = float128{1.0};

    T a = T{4.0} / T{3.0};
    T b = a - ONE;
    T c = b + b + b;

    return std::abs(c - ONE);
}

#endif
