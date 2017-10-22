#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>


int main()
{
	size_t den_count;
	std::cout << "input denominations count\n";

	std::cin >>  den_count;

	std::set<int> denominations;
	std::cout << "input space separated denominations \n";

	while(den_count--)
	{
		int tmp;
		std::cin >> tmp;
		denominations.emplace(tmp);
	}

	
	std::cout << "input change\n";
	int n;
	std::cin >> n;

	std::vector<int> result;

	while(n)
	{
		for ( auto rit = denominations.rbegin(); rit != denominations.rend(); ++rit)
		{
			auto &denomination = *rit;

			if (!(n % denomination))
			{
				n -= denomination;
				result.emplace_back(denomination);
				break;
			}
		}
	}
	
	std::cout << "result is: ";
	std::copy(result.begin(), std::prev(result.end()), std::ostream_iterator<int>(std::cout, " + "));
	std::cout << result.back() << std::endl;

	return 0;
}
