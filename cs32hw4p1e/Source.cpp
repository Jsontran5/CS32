#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int MAGIC = 11223344;

void test()
{
  

    bool allValid = true;
    vector<int> v2(5, MAGIC);
    int k = 0;
    for (vector<int>::iterator p = v2.begin(); p != v2.end(); p++, k++)
    {
        if (k >= 20)  // prevent infinite loop
            break;
        if (*p != MAGIC)
        {
            cout << "Item# " << k << " is " << *p << ", not " << MAGIC << "!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                v2.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        cout << "Passed test 3" << endl;
    else
        cout << "Failed test 3" << endl;
}

int main()
{
    test();
}