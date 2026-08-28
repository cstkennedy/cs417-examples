#include <cmath>
#include <random>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <functional>
#include <tuple>

using namespace std;

/**
 * Generate a random number in a specified range, using the "old-school"
 * uniform RNG approach.
 *
 * @tparam T numeric precision (float or double)
 *
 * @param lower_bound smallest allowed random number
 * @param upper_bound largest allowed random number
 *
 * @return random number in the range [lower, upper)
 */
template<class T>
T generateRandom(const T lower_bound, const T upper_bound)
{
    const T difference = upper_bound - lower_bound;
    const double x = static_cast<T>(rand()) / RAND_MAX;

    return lower_bound + (x * difference);
}

using ArgumentList = tuple<int, int, int>;

/**
 * Parse command line arguments in the form of tuple.
 *
 * @param argc number of command line arguments
 * @param argv command line arguments to parse
 *
 * @return tuple in the form (error_code, parsed_arg_1, parsed_arg_2) where
 *         error_code is 0 if everything was parsed without issue
 */
ArgumentList parseArgs(const int argc, char const* const* argv)
{
    // Not enough arguments
    if (argc < 2) {
        return {1, -1, -1};
    }

    const int the_seed = atoi(argv[1]);

    if (argc == 3) {
        const int the_precision = atoi(argv[2]);

        return {0, the_seed, the_precision};
    }

    return {0, the_seed, -1};
}

template<class T1, class T2>
void doTheWorkSmarter(const int lower=1, const int upper=100)
{
    for (int i = 0; i < 10; ++i) {
        T1 random_t1 = generateRandom<T1>(lower, upper);
        T2 t1_as_t2 = random_t1;

        cout << random_t1 << '\n'
             << t1_as_t2 << '\n';

        cout << '\n';
    }
}

void demonstrateUnderflow()
{
    double x = 4.62;

    for (int i = 0; i < 100; ++i) {
        x /= 10;
        cout << "i: " << i << " - x: " << x << '\n';
    }
}

void demonstrateOverflow()
{
    double x = 4.62;

    for (int i = 0; i < 100; ++i) {
        x *= 1000000;
        cout << "i: " << i << " - x: " << x << '\n';
    }
}

//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    const auto [error_code, the_seed, the_precision] = parseArgs(argc, argv);

    if (error_code == 1) {
        std::cerr << "Usage: " << argv[0] << " seed" << "\n";
        return 1;
    }

    srand(the_seed);

    cout.setf(ios::fixed | ios::showpoint);
    cout.precision(the_precision != -1 ? the_precision : 16);

    //--------------------------------------------------------------------------
    cout << "---------------------------------------------------------------\n";
    cout << " Demonstrate \"float\" to \"double\"\n";
    cout << "---------------------------------------------------------------\n";
    /*
    for (int i = 0; i < 10; ++i) {
        float random_flt = generateRandom<float>(1, 100);
        double flt_as_dbl = random_flt;

        cout << random_flt << '\n'
             << flt_as_dbl << '\n';

        cout << '\n';
    }
    */
    doTheWorkSmarter<float, double>();

    cout << "---------------------------------------------------------------\n";
    cout << " Demonstrate \"double\" to \"float\"\n";
    cout << "---------------------------------------------------------------\n";
    /*
    for (int i = 0; i < 10; ++i) {
        double random_dbl = generateRandom<double>(1, 100);
        float dbl_as_flt = random_dbl;

        cout << random_dbl << '\n'
             << dbl_as_flt << '\n';

        cout << '\n';
    }
    */
    doTheWorkSmarter<double, float>();

    cout << "---------------------------------------------------------------\n";
    cout << " Demonstrate Underflow\n";
    cout << "---------------------------------------------------------------\n";
    demonstrateUnderflow();

    cout << "---------------------------------------------------------------\n";
    cout << " Demonstrate Overflow\n";
    cout << "---------------------------------------------------------------\n";
    demonstrateOverflow();

    return 0;
}
