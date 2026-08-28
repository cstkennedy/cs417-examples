#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Constants
const double MPH_TO_M_DIV_S = 0.44704;
const double C              = 299791958;  // speed of light (m/s)
const double C_SQUARED      = C * C;

const int DAY_PER_WEEK   = 5;       // Based on 5-day work-week
const int WEEKS_PER_YEAR = 16 * 2;  // Based on fall & spring semesters
const int DRIVE_DURATION = 60;      // length of drive one way in minutes
const int MINUTES_TO_SECONDS = 60;

const std::string DIVIDER(32, '-');
//------------------------------------------------------------------------------

/**
 * Compute gamma and inverse gamma
 *
 * @tparam T precision (float or double).
 *
 * @param speed travel speed in MPH
 */
template<typename T>
std::pair<T, T> compute_gamma(const T speed)
{
     const T gamma     = 1.0 / sqrt(1 - pow((speed / C), 2));
     const T gamma_inv = (C_SQUARED - (0.5 * pow(speed, 2.0))) / C_SQUARED;

     return {gamma, gamma_inv};
}

//------------------------------------------------------------------------------
int main(int argc, char**  argv)
{
    cout.setf(ios::fixed);
    setprecision(32);

    constexpr double time = 2 * DAY_PER_WEEK * WEEKS_PER_YEAR
                          * DRIVE_DURATION * MINUTES_TO_SECONDS;

    for (double speed = 10; speed <= 60; speed += 5)
    {
        const double speed_in_ms = speed * MPH_TO_M_DIV_S;
        const auto& [gamma, gamma_inv] = compute_gamma<double>(speed_in_ms);

        const double proper_time = time / gamma_inv;
        const double diff = time - proper_time;

        cout << "Mph          " << right << setw(19) << speed       << "\n";
        cout << "m/s          " << right << setw(19) << speed_in_ms << "\n";

        cout << DIVIDER << "\n";
        cout << "Gamma        " << right << setw(19) << gamma       << "\n";
        cout << "Gamma inv    " << right << setw(19) << gamma_inv   << "\n";

        cout << DIVIDER << "\n";
        cout << "Time         " << right << setw(19) << time        << "\n";
        cout << "Time(proper) " << right << setw(19) << proper_time << "\n";
        cout << "Difference   " << right << setw(19) << diff        << "\n"
             << "\n";
    }

    return 0;
}
