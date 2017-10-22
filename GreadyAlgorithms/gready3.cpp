#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

template<class T>
void algo(T n, std::set<T> &kset)
{
	kset.clear();

	if (1 == n || 2 == n)
	{
		kset.emplace(n);
		return;
	}

	for(T i = 1; 0 < n; ++i )
	{
		if (0 < n - i)
		{
			kset.emplace(i);
			n -= i;
		}
		else
		{
			kset.erase(i-n);

			kset.emplace(i);
			n -= i;
		}
	}
}


int main()
{
	int n;

	std::set<int> kset;

	std::cin >> n;
	
	algo(n, kset);

	std::cout << kset.size() << std::endl;
	std::copy(kset.begin(), kset.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;


	return 0;
}
