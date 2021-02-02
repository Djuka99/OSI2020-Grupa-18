#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Korisnicka funkcije.h"

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
	printf("\t\t\tWELCOME\n");
	printf("----------------------------------------------------------------\n");
	printf("\nOdaberite opciju:\n");
	printf("1-> Prikaz licnih podataka\n");
	printf("2-> Pregled prijava radnika\n");
	printf("3-> Pregled radnih sati po danima\n\n");
	printf("0-> Za izlazak iz aplikacije\n\n");

}

void meniZaLogovanje() {
	zaglavlje();
	printf("\t\tKORISNICKA APLIKACIJA\n");
	printf("----------------------------------------------------------------\n\n");
	logovanje();
}

void prikazInformacija() {
	zaglavlje();
	printf("\t\tPROFIL\n");
	printf("----------------------------------------------------------------\n\n");
	pretragaInformacija();
	footer();
}

void prikazPrijava() {
	zaglavlje();
	printf("\t\tPREGLED PRIJAVA PO DANIMA\n");
	printf("----------------------------------------------------------------\n\n");
	pretragaPrijava();
	footer();
}

void prikazSati() {
	zaglavlje();
	printf("\t\tPREGLED RADNIH SATI PO DANIMA\n");
	printf("----------------------------------------------------------------\n\n");
	pretragaSati();
	footer();
}

void odabirKorisnika() {
	char opcija;
	opcija = _getch();

	switch (opcija) {
	case'0':
		exit(1);
		break;
	case'1':
		system("cls");
		prikazInformacija();
		opcija = _getch();
		while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E') {
			printf("Pogresan unos!\n");
			opcija = _getch();
		}

		if (opcija == 'm' || opcija == 'M') {
			glavniMeni();
			odabirKorisnika();
		}
		else if (opcija == 'e' || opcija == 'E')
			exit(1);
		break;
	case'2':
		system("cls");
		prikazPrijava();
		opcija = _getch();
		while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E') {
			printf("Pogresan unos!\n");
			opcija = _getch();
		}

		if (opcija == 'm' || opcija == 'M') {
			glavniMeni();
			odabirKorisnika();
		}
		else if (opcija == 'e' || opcija == 'E')
			exit(1);
		break;
	case'3':
		system("cls");
		prikazSati();
		opcija = _getch();
		while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E') {
			printf("Pogresan unos!\n");
			opcija = _getch();
		}

		if (opcija == 'm' || opcija == 'M') {
			glavniMeni();
			odabirKorisnika();
		}
		else if (opcija == 'e' || opcija == 'E')
			exit(1);
		break;
	default:
		printf("Nepostojeca opcija!\n");
	}
}
