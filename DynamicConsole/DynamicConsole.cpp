
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;
typedef void ForeignFunction(const char *, const char*);
int main()
{
    string localString = "stringbefore";
    int IsFinished = 0;
    HMODULE dll = 0;
    while (!IsFinished)
    {
        cout << localString.c_str() << endl;
        char tmp = _getch();
        switch (tmp) {
        case 'r':
           
            if ((dll = LoadLibrary(L"MainDll.dll"))) {
                ForeignFunction* FuncBuf;
                FuncBuf = (ForeignFunction*)GetProcAddress(dll, "Replace");
                FuncBuf("stringbefore", "stringafter");
                FreeLibrary(dll);
            }
            else
                cout<<"Can't load library";
            break;
        case 'e':
            IsFinished = 1;
            break;
        default:
            break;
        }
    }

}
