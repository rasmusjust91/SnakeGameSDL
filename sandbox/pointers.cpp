#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{

    int i;
    int *p_i = &i;
    i = 1;
    *p_i = 4;
    cout << i << " asd ";
    return 0;
}
