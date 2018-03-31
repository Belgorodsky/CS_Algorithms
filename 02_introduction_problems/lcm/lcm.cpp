#include <iostream>
#include <cstdint>

uint64_t lcm_naive(int a, int b) {
    for (uint64_t l = 1; l <= (uint64_t) a * b; ++l)
        if (l % a == 0 && l % b == 0)
            return l;

    return (uint64_t) a * b;
}

uint64_t lcm_fast(int a, int b)
{
    uint64_t mul = (uint64_t) a * b;
    while (0 < b)
    {
        a %= b;
        std::swap(a, b);
    }
    return mul / a;
}


int main() {
    int a, b;
#if 0
    while(true)
    {
        a = rand() % 50000;
        b = rand() % 50000;
        std::cout << "a " << a << "\n" << "b " << b << "\n";
        int res_fast = lcm_fast(a, b);
        int res_naive = lcm_naive(a, b);
        std::cout << "res_fast " << res_fast << " res_naive " << res_naive << "\n";
        if (res_fast != res_naive)
            break;
        std::cout << "OK\n";
    }
#endif
    std::cin >> a >> b;
//    std::cout << lcm_naive(a, b) << std::endl;
    std::cout << lcm_fast(a, b) << std::endl;
    return 0;
}
