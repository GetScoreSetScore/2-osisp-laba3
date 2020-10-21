#include <windows.h>
#include <tchar.h>
#include <wingdi.h>
#include <vector>
#include <processthreadsapi.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>
using namespace std;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex; HWND hWnd; MSG msg;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = _T("HelloWorldClass");
	wcex.hIconSm = wcex.hIcon;
	RegisterClassEx(&wcex);
	hWnd = CreateWindow(_T("HelloWorldClass"), _T("Hello, World!"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
HBITMAP hBitmap = NULL;
HBITMAP Mask = NULL; 
#define TIMER1 1001
int length = 0;
int N = 5;
int M = 3;
int CellWidth = 0;
int CellHeight = 0;

int nPos=0;
void Replace(const char* data, const char* replacement)
{
	HANDLE process = GetCurrentProcess();
	size_t len = strlen(data);
	size_t replacementLength = strlen(replacement);

	if (process)
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		MEMORY_BASIC_INFORMATION info;
		std::vector<char> chunk;
		char* p = 0;
		while (p < si.lpMaximumApplicationAddress)
		{
			if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
			{
				if (info.State == MEM_COMMIT && info.AllocationProtect == PAGE_READWRITE)
				{
					p = (char*)info.BaseAddress;
					chunk.resize(info.RegionSize);
					SIZE_T bytesRead;

					try {
						if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
						{
							for (size_t i = 0; i < (bytesRead - len); ++i)
							{
								if (memcmp(data, &chunk[i], len) == 0)
								{
									char* ref = (char*)p + i;
									for (int j = 0; j < replacementLength; j++) {
										ref[j] = replacement[j];
									}
									ref[replacementLength] = 0;
								}
							}
						}
					}
					catch (std::bad_alloc& e) {
					}
				}
				p += info.RegionSize;
			}
		}
	}
}
char* FindWord(DWORD pid, const char* data, size_t len)
{
	HANDLE process = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (process)
	{
		SYSTEM_INFO si;
		GetSystemInfo(&si);

		MEMORY_BASIC_INFORMATION info;
		std::vector<char> chunk;
		char* p = 0;
		while (p < si.lpMaximumApplicationAddress)
		{
			if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
			{
				p = (char*)info.BaseAddress;
				chunk.resize(info.RegionSize);
				SIZE_T bytesRead;
				if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
				{
					for (size_t i = 0; i < (bytesRead - len); ++i)
					{
						if (memcmp(data, &chunk[i], len) == 0)
						{
							chunk[i] = 'w';
							BOOL tmp;
							PDWORD lpflOldProtect=NULL;
							tmp=VirtualProtectEx(process, (LPVOID)(p+i), 256, PAGE_EXECUTE_READWRITE, lpflOldProtect);
							DWORD tmp1 = GetLastError();
							 tmp =WriteProcessMemory(process, (char*)(p+i), &chunk[i], len, NULL);
							  tmp1 = GetLastError();
							return (char*)p + i;
						}
					}
				}
				p += info.RegionSize;
			}
		}
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDC;
	PAINTSTRUCT ps;
	static RECT rect;
	RECT tmp;
	char* tmp1;
	wchar_t tmp2;
	wchar_t* tmp3;
	string text = "helmew";
	switch (message)
	{
	case WM_CHAR:
		GetClientRect(hWnd, &tmp);
		InvalidateRect(hWnd, &tmp, FALSE);
		switch (wParam)
		{
		case 'w':
			Replace("helmew", "wick");
			tmp.left = tmp.left;
			break;
		case 's':

			//MessageBox(NULL, L"e", L"e", MB_OK);
			break;
		}
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}