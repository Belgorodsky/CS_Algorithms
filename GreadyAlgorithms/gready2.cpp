#include <iostream>
#include <map>
#include <iomanip>

struct Goods
{
	long double price;
	uint64_t vol;
};

template<class IterIn, class RealNum >
void algo(IterIn from, IterIn to, uint64_t  maxVol,  RealNum &priceOut)
{
	priceOut = 0;
	size_t currentVol = 0;
	for(auto it = from; it != to; ++it)
	{
		
		auto &kvp = *it;
		auto &pricePerVol = kvp.first;
		auto &one = kvp.second;
		
		while (true)
		{
			if (currentVol < maxVol && one.vol)
			{
				++currentVol;
				priceOut += pricePerVol;
				one.price -= pricePerVol;
				--one.vol;
			}
			else
			{
				break;
			}
		}

	}
}


int main()
{
	size_t goodsCount;
	size_t backpackVol;

	long double bestPrice;

	std::multimap<long double, Goods>  goods;

	std::cin >> goodsCount >> backpackVol;

	for (size_t i = 0; i < goodsCount; ++i )
	{
		Goods one;
		auto  &price = one.price;
		auto &vol = one.vol;

		std::cin >> price >> vol;
		long double key = price / vol;

		goods.emplace(std::make_pair(key, one ));
	}

	algo(goods.rbegin(), goods.rend(), backpackVol, bestPrice);

	std::cout << std::fixed << std::setprecision(3) << bestPrice << std::endl;

	return 0;
}
