#include <cassert>
#include <iostream>
#include <array>
#include <cstdint>


template<std::size_t maxIndex>
class FibonacciLastDigit final
{
	public:

		static int get(int n)
		{
			assert(n <= maxIndex);
			assert(n >= 0);
			
			if (1 < n)
			{
				table[0] = 0;
				table[1] = 1;
				for(int i = 2; i <= n; ++i)
				{
					uint64_t new_one = (table[0] + table[1]) % 10;
					table[0] = table[1];
					table[1] = new_one;
				}
				return table[1];
			}

			return n;
		}
	private:
		static std::array<uint64_t, 2> table;
};


template<std::size_t maxIndex>
std::array<uint64_t, 2> FibonacciLastDigit<maxIndex> ::table = {};

template<>
class FibonacciLastDigit<0> final
{
		static int get(int n)
		{
			assert(!n);
			return 0;
		}
};

template<>
class FibonacciLastDigit<1> final
{
		static int get(int n)
		{
			assert(n <= 1);
			assert(n >= 0);
			return n;
		}
};

int main(void) {
	int n;
	std::cin >> n;
	std::cout << FibonacciLastDigit<10000000>::get(n) << std::endl;
	return 0;
}
