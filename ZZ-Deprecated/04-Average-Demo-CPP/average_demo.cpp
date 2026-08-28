#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <iterator>
#include <numeric>
#include <functional>

using namespace std;

/**
 * Output all numbers in a vector.
 */
void output_numbers(const vector<double>& to_prt)
{
    // std::copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, "\n"));
    for (int i = 0; i < to_prt.size(); ++i) {
        cout << to_prt[i] << "\n";
    }
}

/**
 * Compute a naive average.
 */
double naive_average(const vector<double>& to_avg)
{
    double running_sum = 0;
    for (int i = 0; i < to_avg.size(); ++i) {
        running_sum += to_avg[i];
    }

    return running_sum / to_avg.size();
}

/**
 * Compute a stable mean (running average)
 */
double running_average(const vector<double>& to_avg)
{
    double x_bar = to_avg[0];
    for (int i = 1; i < to_avg.size(); ++i) {
        x_bar += (to_avg[i] - x_bar) / (i + 1);
    }

    return x_bar;
}

/**
 * Fill a vector with alternating values (i.e., 1000000000.1 and 1.1).
 */
std::vector<double> fill_demo_data(const int pre_fill_size = 100000)
{
    std::vector<double> numbers(pre_fill_size);

    for (int i = 0; i < numbers.size(); ++i) {
        if (i % 2 == 0) {
            numbers[i] = 1000000000.1;
        }
        else {
            numbers[i] = 1.1;
        }
    }

    return numbers;
}

int main(const int argc, const char* const* argv)
{
    vector<double> numbers = fill_demo_data(atoi(argv[1]));

    const double naive_avg = naive_average(numbers);
    const double stable_mean = running_average(numbers);

    std::sort(begin(numbers), end(numbers));
    const double sorted_avg_asc = naive_average(numbers);
    const double stable_mean_asc = running_average(numbers);

    std::reverse(begin(numbers), end(numbers));
    const double sorted_avg_dsc = naive_average(numbers);
    const double stable_mean_dsc = running_average(numbers);

    cout.precision(20);
    cout.setf(ios::fixed | ios::showpoint);

    cout << "Naive Avg.              : " << naive_avg << "\n";
    cout << "Sorted Avg. (ascending) : " << sorted_avg_asc << "\n";
    cout << "Sorted Avg. (descending): " << sorted_avg_dsc << "\n";

    cout << "Stable Avg.             : " << stable_mean << "\n";
    cout << "Stable Avg. (ascending) : " << stable_mean_asc << "\n";
    cout << "Stable Avg. (descending): " << stable_mean_dsc << "\n";

    return 0;
}
