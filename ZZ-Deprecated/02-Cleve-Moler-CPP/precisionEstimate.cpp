#include <cmath>
#include <iostream>
#include <iomanip>
#include <functional>

#include "cleveMoler.h"

using namespace std;

/**
 * Run an arbitrary 0-argument function a predefined number of times.
 *
 * @param f function to run
 * @param numExecs number of function executions
 *
 * @return total execution time
 */
template<typename T>
long performExecs(T (*f)(), const long numExecs)
{
    const long start = time(NULL);

    for (long i = 0; i < numExecs; i++) {
        const T p = f();
    }

    const long stop = time(NULL);

    return stop - start;
}

/**
 * Run the cleveMoler estimatePeceision function a predefined number of times.
 *
 * @param numExecs number of function executions
 *
 * @return total execution time
 */
template<typename T>
long performCleveMoler(const long numExecs)
{
	return performExecs(estimatePrecision<T>, numExecs);
}

//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " numExecs" << "\n";
        return 1;
    }

    long numExecs = -1;

    // Argument parsing & validation
    try {
        numExecs = std::stol(argv[1]);

        if (numExecs <= 0) {
            throw std::domain_error(
				"\"" + string(argv[1]) + "\" is not > 0"
				+ " and <= "
			  	+ to_string(std::numeric_limits<long>::max())
			);
        }
    }
    catch (const std::invalid_argument& e) {
        cout << "ERROR: \"" << argv[1] << "\" is not a valid number" << "\n";
        cout << e.what() << "\n";

        return 1;
    }
    catch (const std::domain_error& e) {
        cout << "ERROR: \"" << argv[1] << "\" is not a valid number" << "\n";
        cout << e.what() << "\n";

        return 2;
    }

    // Perform Cleve Moler precision estimates
    const float    sp = estimatePrecision<float>();
    const double   dp = estimatePrecision<double>();
    const float128 qp = estimatePrecision<float128>();

    // Repeat Cleve Moler precision estimates for benchmarks
    long totalTime = performCleveMoler<float>(numExecs);
    cout << right << setw(4) <<  totalTime << " secs | " << sp << "\n";

    totalTime = performCleveMoler<double>(numExecs);
    cout << right << setw(4) <<  totalTime << " secs | " << dp << "\n";

    totalTime = performCleveMoler<float128>(numExecs);
    cout << right << setw(4) <<  totalTime << " secs | " << qp << "\n";

    return 0;
}
