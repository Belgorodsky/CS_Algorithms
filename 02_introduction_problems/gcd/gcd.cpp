#include <iostream>
#include <cstdlib>

int gcd_naive(int a, int b) {
    int current_gcd = 1;
    for (int d = 2; d <= a && d <= b; d++) {
        if (a % d == 0 && b % d == 0) {
            if (d > current_gcd) {
                current_gcd = d;
            }
        }
    }
    return current_gcd;
}

int gcd_fast(int a, int b)
{
    while (0 < b)
    {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

int main() {
    int a, b;
#if 0
    while(true)
    {
        a = rand();
        b = rand();
        std::cout << "a " << a << "\n" << "b " << b << "\n";
        int res_fast = gcd_fast(a, b);
        int res_naive = gcd_naive(a, b);
        std::cout << "res_fast " << res_fast << " res_naive " << res_naive << "\n";
        if (res_fast != res_naive)
            break;
        std::cout << "OK\n";
    }
#endif
    std::cin >> a >> b;
    std::cout << gcd_fast(a, b) << std::endl;
    //  std::cout << gcd_naive(a, b) << std::endl;
    return 0;
}
