#include <iostream>
#include <array>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <vector>

uint64_t fibonacci_sum_naive(uint64_t n) {
    if (n <= 1)
        return n;

    uint64_t previous = 0;
    uint64_t current  = 1;
    uint64_t sum      = 1;

    for (uint64_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

uint64_t get_fibonacci_huge_fast(uint64_t n, uint64_t m)
{
    if (1 < n)
    {
        auto get_pisano_period = [](uint64_t m)->uint64_t
        {
            uint64_t a = 0, b = 1, c = a + b;
            for (uint64_t i = 0; i < m * m; i++) {
                c = (a + b) % m;
                a = b;
                b = c;
                if (a == 0 && b == 1) return i + 1;
            }

            return m;
        };

        uint64_t per = get_pisano_period(m);
//        std::cout << "per " << per << "\n";
        uint64_t remainder = n % per;
        std::vector<uint64_t> table = { 0, 1 };
        for(int i = 2; i <= remainder; ++i)
        {
            auto &v = table;
            v.push_back((v[v.size() - 1] + v[v.size() - 2]) % m);
        }

        return table[remainder];
    }

    return n;
}


uint64_t fibonacci_sum_fast(uint64_t n)
{
    return (get_fibonacci_huge_fast(n + 2,10) + 9) % 10 ; 
}

void test_solution()
{
    assert(fibonacci_sum_fast(3) == 4);
    assert(fibonacci_sum_fast(100) == 5);
    for (size_t n = 0; n < 10000000; ++n)
    {
        std::cout << "n " << n << '\n';
        uint64_t res_fast = fibonacci_sum_fast(n);
        uint64_t res_naive = fibonacci_sum_naive(n);
        std::cout << "res fast: " << res_fast <<
            "\nres naive: " << res_naive << '\n';
        assert(res_fast == res_naive);
        std::cout << "OK\n";
    }
}

int main()
{
//    test_solution();
    uint64_t n = 0;
    std::cin >> n;
//    std::cout << fibonacci_sum_naive(n);
    std::cout << fibonacci_sum_fast(n);

    return 0;
}
