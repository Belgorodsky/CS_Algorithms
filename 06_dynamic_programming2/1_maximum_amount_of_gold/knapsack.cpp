#include <iostream>
#include <vector>

using std::vector;

int optimal_weight(int W, const vector<int> &w) 
{
    //write your code here
    auto n = w.size();
    std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(W + 1, 0));
    
    for (auto i = 1u; i <= n; ++i)
        for(auto weight= 1u; weight <= W; ++weight)
        {
            dp[i][weight] = dp[i - 1][weight];
            if (w[i - 1] <= weight)
            {
                auto &&val = dp[i - 1][weight - w[i - 1]] + w[i - 1];
                if (dp[i][weight] < val)
                    dp[i][weight] = val;
            }
        }

    return dp.back().back();
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
