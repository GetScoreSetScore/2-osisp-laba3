// MathClient.cpp : Client app for MathLibrary DLL.
// #include "pch.h" Uncomment for Visual Studio 2017 and earlier
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <tlhelp32.h>
#include "DllSource.h"
using namespace std;

typedef int Func(int, int);
int main()
{
    // Initialize a Fibonacci relation sequence.
    fibonacci_init(1, 1);
    // Write out the sequence values until overflow.
    do {
        std::cout << fibonacci_index() << ": "
            << fibonacci_current() << std::endl;
    } while (fibonacci_next());
    // Report count of values written before overflow.
    std::cout << fibonacci_index() + 1 <<
        " Fibonacci sequence values fit in an " <<
        "unsigned 64-bit integer." << std::endl;
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