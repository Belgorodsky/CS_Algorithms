#include <iostream>
#include <vector>
#include <array>
#include <cassert>

using std::vector;

uint64_t get_fibonacci_partial_sum_naive(uint64_t from, uint64_t to) {
    uint64_t sum = 0;

    uint64_t current = 0;
    uint64_t next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
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

uint64_t get_fibonacci_partial_sum_fast(uint64_t from, uint64_t to)
{
    uint64_t sum_to = get_fibonacci_huge_fast(to + 2, 10);
    uint64_t sum_from = get_fibonacci_huge_fast(from + 1, 10);

    uint64_t res = 
        (10 + sum_to - sum_from) % 10;

//    std::cout << "sum to " <<  sum_to << " sum_from " << sum_from << " res " << res << "\n";
    return res; 
}


void test_solution() {
    assert(get_fibonacci_partial_sum_fast(3, 7) == 1);
    assert(get_fibonacci_partial_sum_fast(10, 10) == 5);
    assert(get_fibonacci_partial_sum_fast(10, 200) == 2);
    for (size_t f = 0; f < 93; ++f)
    {
        for (size_t t = 0; t < 93; ++t)
        {
            std::cout << "f " << f << '\n';
            std::cout << "t " << t << '\n';
            uint64_t res_fast = get_fibonacci_partial_sum_fast(f, t);
            uint64_t res_naive = get_fibonacci_partial_sum_naive(f, t);
            std::cout << "res fast: " << res_fast <<
                "\nres naive: " << res_naive << '\n';
            assert(res_fast == res_naive);
            std::cout << "OK\n";
        }
    }
}

int main() {
//    test_solution();
    uint64_t from, to;
    std::cin >> from >> to;
//    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
}
