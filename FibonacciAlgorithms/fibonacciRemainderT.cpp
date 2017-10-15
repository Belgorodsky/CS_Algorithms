#include <cassert>
#include <iostream>
#include <array>
#include <cstdint>
#include <vector>

template<std::size_t maxIndex>
class FibonacciRemainder final
{
	public:

		static int get(size_t n, int m)
		{
			assert(n <= maxIndex);
			assert(n > 0);
			assert(m >= 2);
			assert(m <= 100000);
			static_assert(maxIndex, "FibonacciRemainder<0> is undefined");
			
			if (1 < n)
			{
				static size_t previous_index = 1;
				static size_t previous_m = 0;
				static size_t pisano_period = 0;
				if (previous_index < n || m != previous_m)
				{
					pisano_period = get_pisano_period(m);
				}
				return table[n % pisano_period];
			}

			return n;
		}

	private:
		static size_t get_pisano_period(size_t m)
		{
			table.resize(2);
			auto &v = table;
			do 
			{
				v.push_back((v[v.size() - 1] + v[v.size() - 2]) % m);
			}
			while ( v.back() || !std::equal(v.begin(), v.begin() + v.size() / 2,
							v.begin() + v.size() / 2));
			table.resize(table.size() / 2);

			return table.size();
		}
	private:
		static std::vector<size_t> table;
};


template<std::size_t maxIndex>
std::vector<size_t> FibonacciRemainder<maxIndex>::table = { 0, 1};

template<>
class FibonacciRemainder<1> final
{
		static int get(size_t n, int m)
		{
			assert(n <= 1);
			assert(n > 0);
			assert(m >= 2);
			return n;
		}
};

int main(void) {
	size_t n;
	int m;
	std::cin >> n >> m;
	std::cout << FibonacciRemainder<1000000000000000000>::get(n, m) << std::endl;
	return 0;
}
