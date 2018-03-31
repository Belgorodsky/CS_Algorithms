#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <iterator>

using std::pair;
using std::vector;

pair<vector<int>,vector<int>> merge_count(pair<vector<int>,vector<int>> &left_half, pair<vector<int>,vector<int>> &right_half);
pair<vector<int>,vector<int>> chunk_process(vector<int> &majors, vector<int> &eles);
pair<vector<int>,vector<int>> get_majority_element_routine(const vector<int> &a, int left, int right);

int get_majority_element(vector<int> &a, int left, int right)
{
    std::sort(a.begin(), a.end());
    
    auto &&res = get_majority_element_routine(a, left, right);
    auto &&majors = std::get<0>(res);

    return !majors.empty() && a.size() / 2 < majors.size() ? majors[0] : -1;
}

pair<vector<int>, vector<int>> get_majority_element_routine(const vector<int> &a, int left, int right)
{
    if (left == right) return { {}, {} };
    if (left + 1 == right) return { {a[left]} , {} };

    int mid = left + (right - left) / 2;

    auto &&left_half = get_majority_element_routine(a, left, mid);
    auto &&right_half = get_majority_element_routine(a, mid, right);

    return merge_count(left_half, right_half);
}

pair<vector<int>,vector<int>> merge_count(pair<vector<int>,vector<int>> &left_half, pair<vector<int>,vector<int>> &right_half)
{
    auto &&chunk1 = chunk_process(std::get<0>(left_half), std::get<1>(right_half));
    auto &&chunk2 = chunk_process(std::get<0>(right_half), std::get<1>(left_half));

    auto &&left_majors = std::get<0>(chunk1);
    auto &&right_minors = std::get<1>(chunk1);
    auto &&right_majors = std::get<0>(chunk2);
    auto &&left_minors = std::get<1>(chunk2);

    if (!left_majors.empty() && !right_majors.empty() && left_majors[0] == right_majors[0])
    {
        auto &&result_majors = left_majors;
        auto &&result_minors = left_minors;
        
        std::move(right_majors.begin(), right_majors.end(), std::back_inserter(result_majors));
        std::move(right_minors.begin(), right_minors.end(), std::back_inserter(result_minors));

        return { std::move(result_majors), std::move(result_minors) };
    }
    else if (right_majors.size() < left_majors.size())
    {
        auto &&result_majors = left_majors;
        auto &&result_minors = right_majors;

        std::move(left_minors.begin(), left_minors.end(), std::back_inserter(result_minors));
        std::move(right_minors.begin(), right_minors.end(), std::back_inserter(result_minors));

        return { std::move(result_majors), std::move(result_minors) };
    }
    else
    {
        auto &&result_majors = right_majors;
        auto &&result_minors = left_majors;

        std::move(right_minors.begin(), right_minors.end(), std::back_inserter(result_minors));
        std::move(left_minors.begin(), left_minors.end(), std::back_inserter(result_minors));

        return { std::move(result_majors), std::move(result_minors) };
    }
}

pair<vector<int>,vector<int>> chunk_process(vector<int> &majors, vector<int> &eles)
{
    vector<int> left;

    if (!majors.empty())
    {
        for(auto &&ele : eles)
        {
            if (majors[0] == ele)
                majors.emplace_back(std::move(ele));
            else
                left.emplace_back(std::move(ele));
        }
    }
    else
    {
        left = std::move(eles);
    }

    return { std::move(majors), std::move(left) };
}


int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
