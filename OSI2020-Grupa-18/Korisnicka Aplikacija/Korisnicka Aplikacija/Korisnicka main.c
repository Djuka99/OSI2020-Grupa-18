#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "Korisnicka funkcije.h"
#include "Korisnicka meni.h"


int main() {

	system("title Korisnici info");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 450, TRUE);
	system("color 0e");
	meniZaLogovanje();
	glavniMeni();
	odabirKorisnika();
	return 0;
}