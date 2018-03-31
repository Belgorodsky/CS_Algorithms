#include <iostream>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <utility>

using std::pair;
using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
	int x = a[l];
	int j = l;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= x) {
			j++;
			swap(a[i], a[j]);
		}
	}
	swap(a[l], a[j]);
	return j;
}

pair<int,int> partition3(vector<int> &a, int l, int r) {
	int x = a[l];
	int begin = l + 1;
	int end = l;

	for (int i = l + 1; i != r + 1; ++i)
	{
		if (a[i] <= x)
		{
			++end;
			std::swap(a[i], a[end]);
			if (a[end] < x)
			{
				std::swap(a[begin], a[end]);
				++begin;
			}
		}
	}

	std::swap(a[l], a[begin-1]);

	return { begin, end };
}


void randomized_quick_sort(vector<int> &a, int l, int r) {
	if (l >= r) {
		return;
	}

	int k = l + rand() % (r - l + 1);
	swap(a[l], a[k]);
	int m1,m2;
	std::tie(m1,m2) = partition3(a, l, r);

	randomized_quick_sort(a, l, m1 - 1);
	randomized_quick_sort(a, m2 + 1, r);
}

int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cin >> a[i];
	}
	randomized_quick_sort(a, 0, a.size() - 1);
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << ' ';
	}
}
