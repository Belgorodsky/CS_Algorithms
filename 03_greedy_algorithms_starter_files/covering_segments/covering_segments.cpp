#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <limits>

using std::vector;

struct Segment {
    int start, end;

    bool operator<(const Segment &rhs) const
    {
        return end < rhs.end;
    }
};

vector<int> optimal_points(vector<Segment> &segments) {
    std::sort(segments.begin(), segments.end());
    int lastPoint;
    vector<int> points;
    //write your code here
    for (auto &&seg : segments)
    {
        auto &&left = seg.start;
        auto &&right = seg.end;
        bool inRange = false;
        if(points.size())
        {
            auto last = points.back();
            inRange = left <= last && last <= right;
        }

        if (!inRange)
            points.push_back(right);
    }
    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        std::cin >> segments[i].start >> segments[i].end;
    }
    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
