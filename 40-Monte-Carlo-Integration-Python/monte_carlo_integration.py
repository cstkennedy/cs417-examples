#! /usr/bin/env python3

import random
import sys
import time
from typing import Callable, Generator

import numpy as np

Point = tuple[float, float]

def simple_timer(function):
    """
    This is a simple timer meant to be used as a decorator.
    """

    def wrapper():
        start_time = time.perf_counter_ns()

        function()

        end_time = time.perf_counter_ns()
        time_in_sec = (end_time - start_time) / 10**9

        print(f"Total Time: {time_in_sec:>4.2f}")

    return wrapper


def generate_random_points(f: Callable[[float], float],
                           lower_limit: float,
                           upper_limit: float,
                           n: int) -> Generator[Point, None, None]:
    """
    Generate a sequence of random x values and plug them into f(x).

    Args:
        f: mathematical function
        lower_limit: 'a' the lower bound
        upper_bound: 'b' the upper bound
        n: number of points to generate

    Yields:
        A sequence of points in the form (x, f(x))
    """

    for _ in range(0, n):
        x = random.uniform(lower_limit, upper_limit)
        y = f(x)

        yield (x, y)


def __parse_cmd_line_args() -> tuple[int, float, float, int | None]:
    """
    This is a helper/utility function to parse command line arguments, 3 of
    which are common between the examnple main functions
    """

    num_points = int(sys.argv[1])
    limit_a = float(sys.argv[2])
    limit_b = float(sys.argv[3])

    max_magnitude = int(sys.argv[4]) if len(sys.argv) >= 5 else None

    return (num_points, limit_a, limit_b, max_magnitude)


def naive_main():
    """
    This is a "naive" main function used to demonstrate the basic premise
    behind Monte Carlo integration.
    """

    num_points, limit_a, limit_b, _ = __parse_cmd_line_args()

    math_f = lambda x: x**2
    #  math_f = lambda x: cos(x)

    print("{:-^80}".format("Points"), file=sys.stderr)

    temp_sum = 0.0
    for i, point in enumerate(generate_random_points(math_f, limit_a, limit_b, num_points)):
        print(f"{i:5d} - ({point[0]:>12.8f}, {point[1]:>12.8f})", file=sys.stderr)

        temp_sum += point[1]

    integral_result = (limit_b - limit_a) / float(num_points) * temp_sum

    print(f"{integral_result:16.8f}")


@simple_timer
def not_so_naive_main():
    """
    This main function demonstrates the more "Pythonic" approach
    """

    num_points, limit_a, limit_b, _ = __parse_cmd_line_args()

    math_f = lambda x: x**2
    #  math_f = lambda x: cos(x)

    point_sequence = generate_random_points(math_f, limit_a, limit_b, num_points)
    f_of_x_values = (y for x, y in point_sequence)

    integral_result = ((limit_b - limit_a) /
                       float(num_points) *
                       sum(f_of_x_values))

    print(f"{integral_result:16.8f}")

@simple_timer
def main_without_a_table_flip():
    """
    This main demonstrates the impact of the number of points on Monte Carlo
    integration
    """

    _, limit_a, limit_b, max_magnitude = __parse_cmd_line_args()

    if not max_magnitude:
        raise ValueError("No 'max_magnitude' was provided")

    math_f = lambda x: x**2

    print("| {:^16} | {:^20} |".format("# Points", "Est. f(x)"))

    max_num_points = 2 ** max_magnitude
    point_sequence = generate_random_points(math_f, limit_a, limit_b, max_num_points)
    all_y_values = list((y for x, y in point_sequence))

    for magnitude in range(0, max_magnitude + 1):
        num_points = 2 ** magnitude

        f_of_x_values = all_y_values[:num_points]

        integral_result = ((limit_b - limit_a) /
                           float(num_points) *
                           sum(f_of_x_values))

        print(f"| {num_points:>16} | {integral_result:^20.8f} |")


@simple_timer
def main_with_numpy():
    """
    This main demonstrates the impact of the number of points on Monte Carlo
    integration
    """

    _, limit_a, limit_b, max_magnitude = __parse_cmd_line_args()

    if not max_magnitude:
        raise ValueError("No 'max_magnitude' was provided")

    math_f = lambda x: x**2

    print("| {:^16} | {:^20} |".format("# Points", "Est. f(x)"))

    max_num_points = 2 ** max_magnitude
    all_x_values = np.random.uniform(low=limit_a, high=limit_b, size=max_num_points)
    all_y_values = math_f(all_x_values)

    for magnitude in range(0, max_magnitude + 1):
        num_points = 2 ** magnitude

        f_of_x_values = all_y_values[:num_points]

        integral_result = ((limit_b - limit_a) /
                           float(num_points) *
                           sum(f_of_x_values))

        print(f"| {num_points:>16} | {integral_result:^20.8f} |")


#  @simple_timer
def main_with_numpy_better():
    """
    This main demonstrates the impact of the number of points on Monte Carlo
    integration
    """

    _, limit_a, limit_b, max_magnitude = __parse_cmd_line_args()

    if not max_magnitude:
        raise ValueError("No 'max_magnitude' was provided")

    math_f = lambda x: x**2

    print("| {:^16} | {:^20} |".format("# Points", "Est. f(x)"))

    max_num_points = 2 ** max_magnitude
    all_x_values = np.random.uniform(low=limit_a, high=limit_b, size=max_num_points)
    all_y_values = math_f(all_x_values)

    for magnitude in range(0, max_magnitude + 1):
        num_points = 2 ** magnitude

        f_of_x_values = all_y_values[:num_points]

        integral_result = ((limit_b - limit_a) /
                           float(num_points) *
                           f_of_x_values.sum())

        print(f"| {num_points:>16} | {integral_result:^20.8f} |")


if __name__ == "__main__":
    #  naive_main()
    #  not_so_naive_main()
    #  main_without_a_table_flip()
    #  main_with_numpy()
    main_with_numpy_better()
