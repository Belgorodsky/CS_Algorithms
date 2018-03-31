#include <iostream>
#include <vector>

using std::vector;

size_t lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    //write your code here
    auto &&m = a.size();
    auto &&n = b.size();
    auto &&k = c.size();
    vector<vector<vector<size_t>>> cp(1 + m, vector<vector<size_t>>(1 + n, vector<size_t>(1 + k)));


    for (size_t i = 0u; i <= m; ++i)
        for (size_t j = 0u; j <= n; ++j)
            for(size_t l = 0u; l <= k; ++l)
            {
                if (0 == i || 0 == j || 0 == l) 
                    cp[i][j][l] = 0;
                else if (a[i-1] == b[j-1] && b[j-1] == c[l-1])
                    cp[i][j][l] = cp[i-1][j-1][l-1] + 1;
                else 
                    cp[i][j][l] = std::max(cp[i-1][j][l], std::max(cp[i][j-1][l], cp[i][j][l-1]));
            }

    return cp[m][n][k];
}

int main() {
    size_t an;
    std::cin >> an;
    vector<int> a(an);
    for (size_t i = 0; i < an; i++) {
        std::cin >> a[i];
    }
    size_t bn;
    std::cin >> bn;
    vector<int> b(bn);
    for (size_t i = 0; i < bn; i++) {
        std::cin >> b[i];
    }
    size_t cn;
    std::cin >> cn;
    vector<int> c(cn);
    for (size_t i = 0; i < cn; i++) {
        std::cin >> c[i];
    }
    std::cout << lcs3(a, b, c) << std::endl;
}
