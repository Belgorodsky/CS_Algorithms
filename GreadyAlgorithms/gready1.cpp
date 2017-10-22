#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>

template<class IterIn>
void algo(IterIn from, IterIn to, std::set<typename IterIn::value_type::second_type>& setOut)
{
	setOut.clear();
	for(auto it = from; it != to;++it)
	{
		auto &left  = it->second;
		auto &right  = it->first;
		auto lastSetIt = setOut.crbegin();
		bool inRange = false;
		if (setOut.crend() != lastSetIt)
		{
			inRange = left <= *lastSetIt && *lastSetIt <= right;
		}

		if (!inRange)
			setOut.emplace(right);
	}
}


int main()
{
	std::multimap<int,int> ranges;
	std::set<int> points;
	size_t ranges_count;
	std::cin >> ranges_count;
	
	for (size_t i = 0; i < ranges_count; ++i)
	{
		int left, right;
		std::cin >> left;
		std::cin >> right;
		ranges.emplace(std::make_pair(right,left));
	}

	algo(ranges.begin(), ranges.end(), points);

	std::cout << points.size() << std::endl;
	std::copy( points.cbegin(), points.cend(), std::ostream_iterator<int>(std::cout, " ") );
	std::cout << std::endl;


	return 0;
}
