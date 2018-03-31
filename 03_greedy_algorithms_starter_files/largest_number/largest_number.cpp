#include <algorithm>
//#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

using std::vector;
using std::string;

string largest_number(vector<string> &a)
{
    //write your code here
    //  std::stringstream ret;
    std::string result;

	auto comparatorLess = [](const std::string &lhs, const std::string &rhs)
	{
		if (lhs.length() != rhs.length())
			return lhs + rhs < rhs + lhs;
		else
			return lhs < rhs;
	};

    std::sort(a.begin(), a.end(), comparatorLess);
    for (auto it = a.rbegin(); it != a.rend(); ++it)
    {
        result += *it;
    }
    return result;
}

int main() {
    int n;
    std::cin >> std::skipws >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a) << "\n";
}
