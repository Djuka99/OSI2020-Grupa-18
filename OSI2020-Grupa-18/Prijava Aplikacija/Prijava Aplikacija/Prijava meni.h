#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Prijava funkcije.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void zaglavlje() {
	printf("----------------------------------------------------------------\n");
	citanjeInformacije();
	printf("----------------------------------------------------------------\n");
}

void footer() {
	printf("\n\n----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
}

void glavniMeni() {

	system("cls");
	zaglavlje();
	printf("\t\tPRIJAVA NA POSAO\n");
	printf("----------------------------------------------------------------\n");
	logovanje();
	footer();
}
