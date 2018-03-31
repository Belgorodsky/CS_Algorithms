#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using std::vector;

decltype(auto) min_ops(int n)
{
    vector<int> result(n+1, 0);

    for(int i = 2; i <= n; ++i)
    {
        auto min1 = result[i-1];
        auto min2 = std::numeric_limits<decltype(min1)>::max();
        auto min3 = std::numeric_limits<decltype(min1)>::max();
        if (0 == i % 2)
            min2 = result[i / 2];
        if (0 == i % 3)
            min3 = result[i / 3];
        auto minOp = std::min(min1, std::min(min2, min3));

        result[i] = minOp + 1;
    }

    return result;
}

decltype(auto) construct_min(int n, decltype(min_ops(0)) &ops)
{
    decltype(min_ops(0)) sequence;
    sequence.reserve(n);

    while (0 < n)
    {
        sequence.push_back(n);
        if (n % 2 != 0 && n % 3 != 0)
        {
            --n;
        }
        else if (0 == n % 2 && 0 == n % 3)
        {
            n /= 3;
        }
        else if (0 == n % 2)
        {
            if (n && ops[n - 1] < ops[n / 2])
                --n;
            else
                n /= 2;
        }
        else if (0 == n % 3)
        {
            if (n && ops[n - 1] < ops[n / 3])
                --n;
            else
                n /= 3;
        }
    }

    return decltype(min_ops(0))(sequence.rbegin(), sequence.rend());
}


vector<int> optimal_sequence(int n) {
    if (1 == n)
        return { { 1 }, };

    auto ops = min_ops(n);
    return construct_min(n, ops);
}




int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
}
