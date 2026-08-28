import math

def main() -> None:
    for power in range(0, 20):
        result = math.sqrt(1 + 10 ** -power)
        print(f" sqrt(1 + 10^-{power:<2d}) = {result:>50.50f}")

if __name__ == "__main__":
    main()


