#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>
#include <iterator>
#include <limits>

using std::vector;
using std::string;
using std::pair;
using std::min;

double distance(pair<int,int> &p1, pair<int,int> &p2)
{
	double dx = (std::get<0>(p1) - std::get<0>(p2));
	double dy = (std::get<1>(p1) - std::get<1>(p2));
	return std::sqrt(dx * dx + dy *dy);
}

vector<pair<int,int>> merge2points(vector<int> &x, vector<int> &y)
{
	vector<pair<int,int>> points;
	points.reserve(x.size());

	for (size_t i = 0; i != x.size(); ++i)
		points.emplace_back(std::move(x[i]), std::move(y[i]));
	
	return points;
}

double compute_hybrid_min(
	vector<pair<int,int>> &left_x,
	vector<pair<int,int>> &right_x,
	double line_l,
	double wide
)
{
	vector<pair<int,int>> left;

	for(size_t i = 0; i != left_x.size(); ++i)
	{
		if(std::abs(std::get<0>(left_x[i]) - line_l) <= wide)
		{
			left.emplace_back(left_x[i]);
		}
	}

	vector<pair<int,int>> right;

	for(size_t i = 0; i != right_x.size(); ++i)
	{
		if(std::abs(std::get<0>(right_x[i]) - line_l) <= wide)
		{
			right.emplace_back(right_x[i]);
		}
	}

	vector<pair<int,int>> total = std::move(left);
	std::move(right.begin(), right.end(), std::back_inserter(total)); 

	std::sort(
		total.begin(),
		total.end(),
		[](auto&& lhs, auto &&rhs) { return std::get<1>(lhs) < std::get<1>(rhs); }
	);

	auto result = wide;

	for(size_t i = 0; i != total.size(); ++i)
	{
		for(size_t j = i + 1; j != std::min(i + 8, total.size()); ++j)
		{
			if (std::abs(std::get<1>(total[i]) - std::get<1>(total[j])) <= wide)
				result = std::min(result, distance(total[i], total[j]));
		}
	}

	return result;
}

double small_size_min_distance(vector<pair<int,int>> &points_by_x)
{
	double result = std::numeric_limits<double>::max();

	for(size_t i = 0; i != points_by_x.size(); ++i)
	{
		for(size_t j = i + 1; j != points_by_x.size(); ++j)
		{
			result = std::min(result, distance(points_by_x[i], points_by_x[j]));
		}
	}

	return result;
}

double large_size_min_distance(vector<pair<int,int>> &points_by_x)
{
	size_t size = points_by_x.size(); 
	size_t half_size = size / 2;

	if (3 < size)
	{
		vector<pair<int,int>> left_p_x;
		vector<pair<int,int>> right_p_x;

		left_p_x.reserve(half_size);
		right_p_x.reserve(size - half_size);

		std::copy(
			points_by_x.begin(),
			points_by_x.begin() + half_size,
			std::back_inserter(left_p_x)
		);

		std::copy(
			points_by_x.begin() + half_size,
			points_by_x.end(),
			std::back_inserter(right_p_x)
		);

		auto &&left_min = large_size_min_distance(left_p_x);
		auto &&right_min = large_size_min_distance(right_p_x);

		auto &&separated_min = std::min(left_min, right_min);

		auto line_l = (
			std::get<0>(left_p_x.back()) + std::get<0>(right_p_x.front())
		) / 2.0;

		auto &&hybrid_min = compute_hybrid_min(left_p_x, right_p_x, line_l, separated_min);

		return std::min(hybrid_min, separated_min);
	}
	else
	{
		return small_size_min_distance(points_by_x);
	}
}

double minimal_distance(vector<int> x, vector<int> y) {
	auto points = merge2points(x, y);

	std::sort(
		points.begin(),
		points.end(),
		[](auto&&lhs, auto&&rhs) {return std::get<0>(lhs) < std::get<0>(rhs); }
	);

	return large_size_min_distance(points);
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(10) << minimal_distance(x, y) << "\n";
}
