#include <iostream>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>

using std::pair;
using std::vector;

pair<uint64_t, vector<int>> inversion_n_sort(vector<int> &a, size_t left, size_t right); 
pair<uint64_t, vector<int>> merge(pair<uint64_t, vector<int>> &left, pair<uint64_t, vector<int>> &right);

uint64_t get_number_of_inversions(const vector<int> &a, size_t left, size_t right)
{
	auto b = a;
	return std::get<0>(inversion_n_sort(b, left, right));
}

pair<uint64_t, vector<int>> inversion_n_sort(vector<int> &a, size_t left, size_t right) 
{
	if (1 == right - left)
	{
		return { 0,  { std::move(a[left]) } };
	}

	size_t ave = left + (right - left) / 2;
	auto  &&left_res = inversion_n_sort(a, left, ave);
	auto &&right_res = inversion_n_sort(a, ave, right);
	
	return merge(left_res, right_res);
}

pair<uint64_t, vector<int>> merge(pair<uint64_t, vector<int>> &left, pair<uint64_t, vector<int>> &right)
{
	uint64_t count_inversions = std::get<0>(left) + std::get<0>(right);

	auto&& left_array = std::get<1>(left);
	auto&& right_array = std::get<1>(right);

	auto l_it = left_array.begin();
	auto r_it = right_array.begin();

	vector<int> result;

	while (l_it != left_array.end() && r_it != right_array.end())
	{
		if (*r_it < *l_it)
		{
			result.emplace_back(std::move(*l_it));
			// l_it value moves  [r_it,right_array.end()) times
			count_inversions += std::distance(r_it, right_array.end());
			++l_it;
		}
		else
		{
			result.emplace_back(std::move(*r_it));
			++r_it;
		}
	}

	std::move(l_it, left_array.end(), std::back_inserter(result));
	std::move(r_it, right_array.end(), std::back_inserter(result));

	return { count_inversions, result };
}



int main() {
	int n;
	std::cin >> n;
	vector<int> a(n);
	for (size_t i = 0; i < a.size(); i++) {
		std::cin >> a[i];
	}
	std::cout << get_number_of_inversions(a, 0, a.size()) << '\n';
}
