#include<iostream>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
void SendMsg(HWND hWnd, const CHAR *msg)
{
	UINT _length = strlen(msg);
	for (UINT i = 0; i < _length; i++)
	{
		if (msg[i] < 0)
		{
			WPARAM wChar = (BYTE)msg[i];
			wChar <<= 8;
			wChar |= (BYTE)msg[++i];
			SendMessageA(hWnd, WM_IME_CHAR, wChar, NULL);
		}
		else
		{
			WPARAM wChar = (BYTE)msg[i];
			SendMessageA(hWnd, WM_IME_CHAR, wChar, NULL);
		}
	}
	Sleep(10);
}

int main()
{
	HWND hwnd;
	wchar_t w[256];	cout << "title(english please,no space):"; wcin >> w;
	int counts;
	cout << "counts:"; cin >> counts;
	hwnd = FindWindowW(NULL, w);
	cout << "please change config.txt file.\n";
	cout << "input the words that you want to say.\n";
	string temp;
	vector<string> contents;
	if (hwnd == 0x00000000)
	{
		cout << "window is not found!\n";
		_getch();
		return 0;
	}
	ifstream file;
	file.open("config.txt");
	while (!file.eof())
	{
		file >> temp;
		contents.push_back(temp);
	}
	file.close();
	SetForegroundWindow(hwnd);
	MoveWindow(hwnd, 500, 500, 634, 505, 0);
	POINT pos;
	pos.x = 25;
	pos.y = 423;
	ClientToScreen(hwnd, &pos);
	SetCursorPos(pos.x, pos.y);
	SendMessage(hwnd, MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0);
	Sleep(20);
	for (int i2 = 0; i2 < counts; i2++)
	{
		for (int i = 0; i < contents.size(); i++)
		{
			SendMsg(hwnd, contents[i].c_str());
			SendMessage(hwnd, WM_KEYDOWN, VK_RETURN, 0);
			Sleep(10);
			SendMessage(hwnd, WM_KEYUP, VK_RETURN, 0);
		}
	}
	cout << "Complete!\n";
	fflush(stdin);
	_getch();
	return 0;
}