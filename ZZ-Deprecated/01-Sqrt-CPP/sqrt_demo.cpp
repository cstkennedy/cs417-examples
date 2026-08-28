#include <iostream>
#include <iomanip>

#include <cmath>


void sqrt_demo()
{
    for (int power = 0; power < 20; ++power) {
        const double result = std::sqrt(1.0 + pow(10.0, -power));
        std::cout << " sqrt(1 + 10^" << std::setw(2) << -power
                  << " = "
                  << result << '\n';
    }
}

int main()
{
    std::cout.precision(50);
    std::cout.setf(std::ios::fixed);
    sqrt_demo();

    return 0;
}
