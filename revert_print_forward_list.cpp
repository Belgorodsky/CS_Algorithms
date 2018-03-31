#include <iostream>
#include <sstream>
#include <string>
#include <forward_list>
#include <iterator>

template<class It, class It2>
void revert(It from, It to, It2 &&out)
{
    if (from != to)
    {
        revert(std::next(from), to, out);
        *out = *from;
        ++out;
    }
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::forward_list<int> fl;

    auto it = fl.before_begin();

    for(auto isIt = std::istream_iterator<int>(iss); isIt != std::istream_iterator<int>(); ++isIt)
    {
        it = fl.insert_after(it, *isIt);
    }
    std::cout << "reverted forward list: ";
    revert(fl.cbegin(), fl.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    std::string new_string;

    revert(line.cbegin(), line.cend(), std::back_inserter(new_string));
   
    std::cout << "reverted string: " << new_string << '\n';


    return 0;
}
