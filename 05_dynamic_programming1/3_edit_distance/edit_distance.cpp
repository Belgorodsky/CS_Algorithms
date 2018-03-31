#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

int edit_distance(const string &str1, const string &str2) {
    //write your code here

    auto &&n = str1.length();
    auto &&m = str2.length();
    vector<vector<size_t>> dp(1 + m, vector<size_t>(1 + n));


    for (size_t i = 0u; i <= m; ++i)
        for (size_t j = 0u; j <= n; ++j)
        {
            if (0 == i) 
                dp[i][j] = j;
            else if (0 == j) 
                dp[i][j] = i;
            else if (str1[j-1] == str2[i-1])
                dp[i][j] = dp[i-1][j-1];
            else 
                dp[i][j] = 1 + std::min(dp[i][j-1], std::min(dp[i-1][j], dp[i-1][j-1]));
        }

    return dp[m][n];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;
    return 0;
}
