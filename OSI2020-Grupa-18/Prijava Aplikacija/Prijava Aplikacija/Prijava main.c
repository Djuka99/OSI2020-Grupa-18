#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "Prijava meni.h"
#include "Prijava funkcije.h"


int main() {

	system("title PIN aplikacija");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 450, TRUE);
	system("color 0a");
	//while(1)
		glavniMeni();
}