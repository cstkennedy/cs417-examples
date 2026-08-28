#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <memory>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cmath>


/**
 * Evaluate a given function (f) for x values in the range 1 to 2^(-2000)
 * where each value is have the previous one (1, 0.5, 0.25, 0.125...)
 *
 * @tparam F any function or function-like (i.e., callable) type that takes a
 *           single double and returns a single double
 *
 * @param f mathematical function to evaluate
 */
template<typename F>
void approach_zero(const F f)
{
    for (int i = 0; i < 2000; ++i) {
        const double x = std::pow(2, -i);
        const double f_of_x = f(x);

        std::cout.setf(std::ios::showpoint | std::ios::scientific);
        std::cout.precision(20);

        std::cout << "2^-" << i << " / "
                  << std::right << std::setw(24) << x << " | "
                  << std::right << std::setw(24) << f_of_x << '\n';
    }
}


/**
 * An example function used to demonstrate templates.
 */
constexpr double g(const double x)
{
    return (x * x) + (3 * x);
}


//------------------------------------------------------------------------------
int main([[maybe_unused]] const int argc, [[maybe_unused]] const char* const* argv)
{
    auto f = [] (const double x) -> double {
        return sin(x);
    };

    approach_zero(g);

    return 0;
}

