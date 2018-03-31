#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>

struct VpW
{
    VpW(int v, int w) : value(v), weight(w) {}
    long double value;
    int weight;

    bool operator>(const VpW &rhs) const
    {
        return value / weight > rhs.value / rhs.weight;
    }
};

double get_optimal_value(int capacity, const std::vector<int> &weights, const std::vector<int> &values)
{
    // write your code here
    double retVal = 0.0;
    std::multiset<VpW, std::greater<VpW>> vpw;

    for(int i = 0; i != weights.size(); ++i)
    {
        vpw.emplace(values[i], weights[i]);
    }

    for(auto it = vpw.begin(); capacity && it != vpw.end(); ++it)
    {
        int value = it->value;
        int weight = it->weight;
        int count = std::min(weight, capacity);
        retVal += double(count) * value / weight;
        capacity -= count;
    }

    return retVal;
}

int main() {
    int n;
    int capacity;
    std::cin >> n >> capacity;
    std::vector<int> values(n);
    std::vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
