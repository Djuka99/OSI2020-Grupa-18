#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "HR funkcije.h"

void glavniMeni() {

	system("cls");
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tWELCOME\n");
	printf("----------------------------------------------------------------\n");
	printf("Odaberite opciju:\n");
	printf("1:Dodavanje novog zaposlenog\n");
	printf("2:Pregled prijava radnika\n");
	printf("3:Pretraga po bazi\n");
	printf("0:Za izlazak iz aplikacije\n\n");

}

void meniZaLogovanje() {
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tLOGIN\n");
	printf("----------------------------------------------------------------\n");
	logovanje();
}

void dodavanjeNovogZaposlenog() {
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tDODAVANJE NOVOG ZAPOSLENOG\n");
	printf("----------------------------------------------------------------\n");
	dodavanjeNovog();
}

void pregledPrijavaRadnika() {
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tPREGLED PRIJAVA RADNIKA\n");
	printf("----------------------------------------------------------------\n");
	//pregledPrijava();
}

void pretragaBaze() {
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tPRETRAGA BAZE\n");
	printf("----------------------------------------------------------------\n");
	//pretragaPoBazi();
}

void odabirOpcije() {
	char opcija;

	while (1) {

		opcija = _getch();

		switch (opcija) {
		case '0':
			exit(1);
			break;
		case '1':
			system("cls");
			dodavanjeNovogZaposlenog();
			opcija = _getch();
			while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E') {
				printf("Pogresan unos!\n");
				opcija = _getch();
			}

			if (opcija == 'm' || opcija == 'M')
				glavniMeni();
			else if (opcija == 'e' || opcija == 'E')
				exit(1);
			break;
		case '2':
			system("cls");
			pregledPrijavaRadnika();
			opcija = _getch();
			while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E') {
				printf("Pogresan unos!\n");
				opcija = _getch();
			}

			if (opcija == 'm' || opcija == 'M')
				glavniMeni();
			else if (opcija == 'e' || opcija == 'E')
				exit(1);
			break;
		case '3':
			system("cls");
			pretragaBaze();
			system("cls");
			pretragaBaze();
			opcija = _getch();
			while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E') {
				printf("Pogresan unos!\n");
				opcija = _getch();
			}

			if (opcija == 'm' || opcija == 'M')
				glavniMeni();
			else if (opcija == 'e' || opcija == 'E')
				exit(1);
			break;
		default:
			printf("Nepostojeca opcija!\n");
		}
	}

}