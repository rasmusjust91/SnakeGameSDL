#include <iostream>
#include <vector>
using namespace std;

vector<int> vec;

int main()
{
    int prev_, prev;
    int head = 1;

    vec.push_back(5);
    vec.push_back(6);
    vec.push_back(7);
    vec.push_back(78);
    vec.push_back(79);
    vec.push_back(7);

    for (vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
    {
        if (i == vec.begin())
        {
            prev = *i.base();
            *i.base() = head;
        }
        else
        {
            prev_ = *i.base();
            *i.base() = prev;
            prev = prev_;
        }
    }

    // PRINT
    for (vector<int>::iterator i = vec.begin(); i != vec.end(); i++)
    {
        cout << *i.base() << '\n';
    }
    return 0;
}
