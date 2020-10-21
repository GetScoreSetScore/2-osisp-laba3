// InjectedConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;
typedef void ForeignFunction(const char*, const char*);
int main()
{
    string localString = "stringbefore";
    int IsFinished = 0;
    while (!IsFinished)
    {
        cout <<"PID: "<< GetCurrentProcessId() <<"  "<< localString.c_str() << endl;
        char tmp = _getch();
        switch (tmp) {
        case 'e':
            IsFinished = 1;
            break;
        default:
            break;
        }
    }

}