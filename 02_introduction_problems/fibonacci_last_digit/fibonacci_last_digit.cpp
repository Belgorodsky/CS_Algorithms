#include <iostream>
#include <cassert>
#include <cstdint>
#include <array>

uint64_t get_fibonacci_last_digit_naive(size_t n) {
    if (n <= 1)
        return n;

    uint64_t previous = 0;
    uint64_t current  = 1;

    for (uint64_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

uint64_t get_fibonacci_last_digit_fast(size_t n)
{
    std::array<uint64_t, 2> table;
    if (1 < n)
    {
        table[0] = 0;
        table[1] = 1;
        for(int i = 2; i <= n; ++i)
        {
            uint64_t new_one = (table[0] + table[1]) % 10;
            table[0] = table[1];
            table[1] = new_one;
        }
        return table[1];
    }

    return n;
}

void test_solution() {
    assert(get_fibonacci_last_digit_fast(3) == 2);
    assert(get_fibonacci_last_digit_fast(331) == 9);
    for (size_t n = 0; n < 10000000; ++n)
    {
        std::cout << "n " << n << '\n';
        uint64_t res_fast = get_fibonacci_last_digit_fast(n);
        uint64_t res_naive = get_fibonacci_last_digit_naive(n);
        std::cout << "res fast: " << res_fast <<
            "\nres naive: " << res_naive << '\n';
        assert(res_fast == res_naive);
        std::cout << "OK\n";
    }
}

int main() {
//    test_solution();
    int n;
    std::cin >> n;
//    int c = get_fibonacci_last_digit_naive(n);
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
}
