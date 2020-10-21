// DynamicConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;
typedef int Func(int, int);
int main()
{
    HMODULE dll = 0;
    if ((dll = LoadLibrary(L"ReplaceDll.dll"))) {
        Func* _Sum, * _Sub;
        _Sum = (Func*)GetProcAddress(dll, "Sum");
        _Sub = (Func*)GetProcAddress(dll, "Sub");
        cout << "Dynamic Include: " << endl << "8 * 5 = " << _Sum(8, 5) << endl << "7 % 3 = " << _Sub(7, 3) << endl;
        FreeLibrary(dll);
    }
    else
        printf("Cant load Dll");
}
