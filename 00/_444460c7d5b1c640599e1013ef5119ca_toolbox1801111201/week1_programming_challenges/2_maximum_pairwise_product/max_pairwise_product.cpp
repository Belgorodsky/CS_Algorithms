#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

uint64_t MaxPairwiseProduct(const vector<int>& numbers) {
  uint64_t result = 0;
  
  if (1 < numbers.size())
  {
    auto vec = numbers;
    std::sort(vec.begin(), vec.end());
    return uint64_t(vec[numbers.size()-2]) * vec[numbers.size()-1];
  }
  return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    uint64_t result = MaxPairwiseProduct(numbers);
    cout << result << "\n";
    return 0;
}
