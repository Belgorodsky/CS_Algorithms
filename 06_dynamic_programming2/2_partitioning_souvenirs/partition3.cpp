#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

bool partition3(vector<int> &A) {
    //write your code here
    auto n = A.size();
    int sum = std::accumulate(A.cbegin(),A.cend(), 0);
    int i, j;

    if (sum % 3 != 0)  
        return false;

    vector<vector<bool>> part(sum / 3 + 1, vector<bool>(n + 1, false));

    for (i = 0; i <= n; ++i)
        part[0][i] = true;

    for (i = 1; i <= sum / 3; ++i)
        part[i][0] = false;     

    for (i = 1; i <= sum / 3; ++i)  
    {
        for (j = 1; j <= n; ++j)  
        {
            part[i][j] = part[i][j - 1];
            if (A[j - 1] <= i)
                part[i][j] = part[i][j] || part[i - A[j - 1]][j - 1];
        }        
    }    

    return part[sum / 3][n];
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}
