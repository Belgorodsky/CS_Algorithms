#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    //write your code here
    int term = 1;
    while (term < n - term)
    {
        summands.emplace_back(term);
        n -= term++;
    }

    if(n)
        summands.emplace_back(n);

    return summands;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
