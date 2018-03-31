#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cinttypes>
#include <limits>

using std::vector;
using std::string;
using std::max;
using std::min;

int64_t eval(int64_t a, int64_t b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

int64_t get_maximum_value(const string &exp) {
    //write your code here
    int length = exp.size();
    int numOfnum = (length + 1) / 2;
    vector<vector<int64_t>> minArray(numOfnum, vector<int64_t>(numOfnum, 0));
    vector<vector<int64_t>> maxArray(numOfnum, vector<int64_t>(numOfnum, 0));
    for (int i = 0; i < numOfnum; i++)
    {
        minArray[i][i] = std::stoll(exp.substr(2*i,1));
        maxArray[i][i] = std::stoll(exp.substr(2*i,1));
    }

    for (int s = 0; s < numOfnum - 1; s++)
    {
        for (int i = 0; i < numOfnum - s - 1; i++)
        {
            int j = i + s + 1;
            int64_t minVal = std::numeric_limits<int64_t>::max();
            int64_t maxVal = std::numeric_limits<int64_t>::min();
            for (int k = i; k < j; k++ )
            {
                int64_t a = eval(minArray[i][k], minArray[k + 1][j], exp[2 * k + 1]);
                int64_t b = eval(minArray[i][k], maxArray[k + 1][j], exp[2 * k + 1]);
                int64_t c = eval(maxArray[i][k], minArray[k + 1][j], exp[2 * k + 1]);
                int64_t d = eval(maxArray[i][k], maxArray[k + 1][j], exp[2 * k + 1]);
                minVal = min(minVal, min(a, min(b, min(c, d))));
                maxVal = max(maxVal, max(a, max(b, max(c,d))));
            }

            minArray[i][j] = minVal;
            maxArray[i][j] = maxVal;
        }
    }

    return maxArray[0][numOfnum - 1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
