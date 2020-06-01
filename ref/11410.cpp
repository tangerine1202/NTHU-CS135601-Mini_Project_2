#include <cstdlib>
#include <iostream>
#include <string>
// #include "function.h"
#include "11410.h"

namespace oj
{
// data_t *Vector::begin() const
// {
//     return begin_;
// }
// data_t *Vector::end() const
// {
//     return end_;
// }
// data_t *Vector::last() const
// {
//     return last_;
// }

std::ostream &operator<<(std::ostream &os, const Vector &vec)
{

    // os << "begin: " << vec.begin() << '\n';
    // os << "end  : " << vec.end() << '\n';
    // os << "last : " << vec.last() << '\n';

    for (std::size_t i(0); i != vec.size(); ++i)
        os
            << vec[i] << ' ';
    return os;
}
} // namespace oj

int main()
{
    using namespace std;
    {
        oj::Vector v;
        string command;

        for (oj::data_t n; cin >> command;)
        {
            if (command == "pop_back")
            {
                v.pop_back();
                cout << v << endl;
            }
            else if (command == "push_back")
            {
                cin >> n;
                v.push_back(n);
                cout << v << endl;
            }
            else if (command == "insert")
            {
                size_t pos, count;
                cin >> pos >> count >> n;
                v.insert(pos, count, n);
                cout << v << endl;
            }
            else if (command == "capacity")
                cout << v.capacity() << endl;
            else if (command == "size")
                cout << v.size() << endl;
            else if (command == "reserve")
            {
                cin >> n;
                v.reserve(n);
                cout << v << endl;
            }
            else if (command == "resize")
            {
                cin >> n;
                v.resize(n);
                cout << v << endl;
            }
        }
        cout << v << endl;
    }
}