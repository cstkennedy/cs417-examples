from typing import Callable


def approach_zero(f: Callable[[float], float]) -> None:
    """
    Evaluate a given function (f) for x values in the range 1 to 2^(-2000)
    where each value is half the previous one (1, 0.5, 0.25, 0.125...)

    Args:
        f: mathematical function to evaluate
    """

    for i in range(0, 2000):
        x = 2**-i
        f_of_x = f(x)

        print(f"2^-{i:} / {x:>24.20e} | {f_of_x:>24.20e}")

def main() -> None:
    def f(x: float):
        return x**2 + 7 * x + 3

    approach_zero(f)


if __name__ == "__main__":
    main()


