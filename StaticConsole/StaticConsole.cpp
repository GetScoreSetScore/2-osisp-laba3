using namespace std;
#include <iostream>
#include <conio.h>
#include "DllSource.h"
int main()
{
    string localString = "stringbefore";
    int IsFinished = 0;
    while (!IsFinished)
    {
        cout << localString.c_str() << endl;
        char tmp =_getch();
        switch (tmp) {
        case 'r':
            Replace("stringbefore", "stringafter");
            break;
        case 'e':
            IsFinished = 1;
            break;
        default:
            break;
        }
    }
}
