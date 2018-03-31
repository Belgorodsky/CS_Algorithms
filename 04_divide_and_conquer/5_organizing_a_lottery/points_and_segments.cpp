#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <tuple>
#include <cassert>

using std::pair;
using std::vector;

int compare_routine(const vector< int> &numbers, int key)
{
    int left = 0, right = numbers.size() - 1, mid;

    while (left <= right)
    {
        mid = (int) ((left + right) / 2);
        if (key == numbers[mid])
            break;
        else if (key > numbers[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }

    return mid;
}

vector<int> fast_count_segments(
	const vector<int> &starts,
	const vector<int> &ends,
	const vector<int> &points
)
{
    vector<int> left_points(starts.begin(), starts.end());
    std::sort(left_points.begin(), left_points.end());

    vector<int> right_points(ends.begin(), ends.end());
    std::sort(right_points.begin(), right_points.end());

    vector<int> ret_val;

    for (auto &&point : points)
    {
        int less = compare_routine(left_points, point);
        while ( !(left_points[less] <= point) )
        {
            less--;
            if (less == -1) break;
        }
        if (less != -1)
        {
            assert(left_points[less] <= point);
            while (less + 1 < left_points.size() && left_points[less + 1] <= point) less++;
        }

        int less_or_eq = compare_routine(right_points, point);
        while ( !(right_points[less_or_eq] < point) )
        {
            less_or_eq--;
            if (less_or_eq == -1) break;
        }

        if (less_or_eq != -1)
        {
            assert(right_points[less_or_eq] < point);
            while (less_or_eq + 1 < right_points.size() && right_points[less_or_eq + 1] < point) less_or_eq++;
        }
        ret_val.push_back(std::labs(less - less_or_eq));
    }

    return ret_val;
}


vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
	vector<int> cnt(points.size());
	for (size_t i = 0; i < points.size(); i++) {
		for (size_t j = 0; j < starts.size(); j++) {
			cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
		}
	}
	return cnt;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<int> starts(n), ends(n);
	for (size_t i = 0; i < starts.size(); i++) {
		std::cin >> starts[i] >> ends[i];
	}
	vector<int> points(m);
	for (size_t i = 0; i < points.size(); i++) {
		std::cin >> points[i];
	}
	//use fast_count_segments
	vector<int> cnt = fast_count_segments(starts, ends, points);
	for (size_t i = 0; i < cnt.size(); i++) {
		std::cout << cnt[i] << ' ';
	}
}
