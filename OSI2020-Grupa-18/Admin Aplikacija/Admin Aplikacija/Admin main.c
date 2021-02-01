#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "Admin funkcije.h"
#include "Admin meni.h"

int main() {

	system("title Admin");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 450, TRUE);
	system("color 0c");
	provjeraMenia();
	odabirOpcije();
	return 0;

}
