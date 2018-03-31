#include <iostream>
#include <cinttypes>
#include <cassert>
#include <cmath>
#include <vector>

uint64_t get_fibonacci_huge_naive(uint64_t n, uint64_t m) {
    if (n <= 1)
        return n;

    uint64_t previous = 0;
    uint64_t current  = 1;

    for (uint64_t i = 0; i < n - 1; ++i) {
        uint64_t tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
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

void test_solution() {
    assert(get_fibonacci_huge_fast(1, 239) == 1);
    assert(get_fibonacci_huge_fast(239, 1000) == 161);
    for (size_t n = 0; n < 94; ++n)
    {
        for (size_t m = 2; m < 1000; ++m)
        {
            std::cout << "n " << n << '\n';
            std::cout << "m " << m << '\n';
            uint64_t res_fast = get_fibonacci_huge_fast(n, m);
            uint64_t res_naive = get_fibonacci_huge_naive(n, m);
            std::cout << "res fast: " << res_fast <<
                "\nres naive: " << res_naive << '\n';
            assert(res_fast == res_naive);
            std::cout << "OK\n";
        }
    }
}

int main() {
    uint64_t n, m;
    std::cin >> n >> m;
//    test_solution();
//    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
    std::cout << get_fibonacci_huge_fast(n, m) << '\n';

    return 0;
}
