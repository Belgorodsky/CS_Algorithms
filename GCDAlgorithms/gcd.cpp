#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>

template <class Int>
Int gcd(Int a, Int b)
{
	static_assert(std::is_integral<Int>::value, "a and b must be integral");

	Int current_gcd = 1;

	while (0 < b)
	{
		a %= b;
		std::swap(a, b);
	}
	return a;
#if 0
	while (0 < a && 0 < b)
	{
		if ( a <= b )
		{
			b %= a;
		}
		else
		{
			a %= b;
		}
	}

	return !a ? b : a;
#endif
#if 0
	if (!a)
		current_gcd = b;
	else if (!b)
		current_gcd = a;
	else if (a <= b)
		current_gcd = gcd(a, b % a);
	else
		current_gcd = gcd(a % b, b);

	return current_gcd;
#endif
}

int main(void)
{
	std::int64_t a, b;
	std::cin >> a >> b;
	std::cout << gcd(a, b) << std::endl;
	return 0;
}
