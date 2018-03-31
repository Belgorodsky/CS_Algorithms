#include <iostream>
#include <vector>

using std::vector;

size_t lcs2(vector<int> &a, vector<int> &b) {
    //write your code here
    auto &&m = a.size();
    auto &&n = b.size();
    vector<vector<size_t>> cp(1 + m, vector<size_t>(1 + n));


    for (size_t i = 0u; i <= m; ++i)
        for (size_t j = 0u; j <= n; ++j)
        {
            if (0 == i || 0 == j) 
                cp[i][j] = 0;
            else if (a[i-1] == b[j-1])
                cp[i][j] = cp[i-1][j-1] + 1;
            else 
                cp[i][j] = std::max(cp[i-1][j], cp[i][j-1]);
        }

    return cp[m][n];
}


int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    std::cout << lcs2(a, b) << std::endl;
}
