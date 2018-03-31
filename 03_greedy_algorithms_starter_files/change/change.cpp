#include <iostream>
#include <array>
#include <cassert>
#include <cstdlib>
#include <limits>

int get_change(int m) {
    //write your code here

    // denominations in order to decrease
    std::array<int, 3> denominations = { 10, 5, 1};

    int retVal = 0;

    for(int i = 0; i < denominations.size(); ++i)
    {
        if ( i != (denominations.size() - 1))
        {
            int _tmp = m / denominations[i];
            retVal += _tmp;
            m -= _tmp * denominations[i];
        }
        else
        {
            retVal += m % denominations[i - 1];
        }
    }
    
    return retVal;
}

int get_change_naive(int m)
{

    // denominations in order to decrease
    std::array<int, 3> denominations = { 10, 5, 1 };

    int retVal = 0;

    while(m)
    {
        for (auto &&denomination : denominations)
        {
            if (!(m % denomination))
            {
                m -= denomination;
                ++retVal;
                break;
            }
        }
    }
    
    return retVal;
}

void test_solution()
{
    assert(2 == get_change(2));
    assert(6 == get_change(28));
    for( int val = 0; val < std::numeric_limits<int>::max() ; ++val)
    {
        int res1 = get_change(val);
        int res2 = get_change_naive(val);
        if ( res1 != res2 )
        {
            std::cerr << "val " << val << "\nres1" << res1 << "\nres2" << res2 << "\n";
            std::cerr << "fails\n";
        }
        std::cout << "OK\n";
    }
}

int main() {
//    test_solution();
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
