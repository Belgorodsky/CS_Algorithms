#include <iostream>
#include <array>
#include <unordered_map>
#include <limits>
#include <cinttypes>

int get_change(int money) {
    //write your code here
    constexpr std::array<int, 3u> denominations = { 1, 3, 4 };// must be ordered
    std::unordered_map<int, size_t> minNumCoins;
    minNumCoins[0] = 0;

    for (int m = 1; m <= money; ++m)
    {
        minNumCoins[m] = std::numeric_limits<size_t>::max();
        for (auto&& coin :  denominations)
        {
            if (coin <= m)
            {
                auto numCoins = minNumCoins[m-coin] + 1;
                if (numCoins < minNumCoins[m])
                {
                    minNumCoins[m] = numCoins;
                }
            }
        }
    }

    return minNumCoins[money];
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
