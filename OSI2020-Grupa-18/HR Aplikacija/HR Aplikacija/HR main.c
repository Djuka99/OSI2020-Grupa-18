#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "HR funkcije.h"
#include "HR meni.h"


int main() {

	system("title Human Resources");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 450, TRUE);
	system("color 0b");
	meniZaLogovanje();
	glavniMeni();
	odabirOpcije();
	return 0;
}