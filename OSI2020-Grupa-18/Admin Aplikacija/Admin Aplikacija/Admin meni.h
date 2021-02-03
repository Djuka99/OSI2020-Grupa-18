#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Admin funkcije.h"
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
	printf("\t\t\tWELCOME ADMIN\n");
	printf("----------------------------------------------------------------\n");
	printf("Odaberite opciju:\n");
	printf("1:Kreiranje HR naloga\n");
	printf("2:Deaktiviranje HR naloga\n");
	printf("3:Deaktiviranje korisnickog naloga\n");
	printf("4:Izmijeni informacije\n");
	printf("5:Sta se dobija u punoj verziji?\n\n");
	printf("0:Za izlazak iz aplikacije\n\n");
}

void meniZaLogovanje() {
	zaglavlje();
	printf("\t\t\tLOGIN\n");
	printf("----------------------------------------------------------------\n");
	logovanje();
}

void meniKreiranjeHR() {
	zaglavlje();
	printf("\t\tKREIRANJE HR NALOGA\n");
	printf("----------------------------------------------------------------\n");
	kreiranjeHR();
	footer();

}

void meniZaDeaktiviranjeHR() {
	zaglavlje();
	printf("\t\tDEAKTIVIRANJE HR NALOGA\n");
	printf("----------------------------------------------------------------\n");
	deaktiviranjeHR();
}

void meniZaDeaktiviranjeKN() {
	zaglavlje();
	printf("\t\tDEAKTIVIRANJE KORISNICKOG NALOGA\n");
	printf("----------------------------------------------------------------\n");
	deaktiviranjeKR();
}

void meniZaAktivaciju() {
	zaglavlje();
	printf("\t\tOTKLJUCAVANJE APLIKACIJE\n");
	printf("----------------------------------------------------------------\n");
	unosKoda();

}

void meniInfo() {
	zaglavlje();
	printf("\t\tINFO\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	printf("U otkljucanoj verziji korisniku su omogucene iduce izmjene:\n");
	printf(" - Prikaz imena kompanije\n");
	printf(" - Prikaz broja telefona \n");
	printf(" - Prikaz mail-a\n");
}

void meniZaOtkljucavanje() {
	zaglavlje();
	printf("\t\tAplikacija nije otkljucana\n");
	printf("----------------------------------------------------------------\n");
	printf("Da li zelite otkljucati aplikaciju?\n(Y)-> za unos koda\n(N)-> za besplatnu verziju.\n");
}

void meniZaIzmjenuInformacija() {
	zaglavlje();
	printf("\t\tIzmjena informacija\n");
	printf("----------------------------------------------------------------\n");
	
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
			meniKreiranjeHR();
			footer();
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
			meniZaDeaktiviranjeHR();
			footer();
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
			meniZaDeaktiviranjeKN();
			footer();
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
		case '4': {
			system("cls");
			meniZaIzmjenuInformacija(); 
			if (strcmp(citanjeFlaga(), "zakljucano") == 0) {
				printf("Ova opcija je dostupna samo za placenu aplikaciju!\n\n");
				footer();
				opcija = _getch();
				while (opcija != 'M' && opcija != 'm' && opcija != 'N' && opcija != 'n') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'M' || opcija == 'm') {
					system("cls");
					glavniMeni();
				}

				else if (opcija == 'N' || opcija == 'n')
					exit(1);
			}
			else {
				upisInformacija();
				printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
				opcija = _getch();
				while (opcija != 'M' && opcija != 'm' && opcija != 'N' && opcija != 'n') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'M' || opcija == 'm')
					glavniMeni();
				else if (opcija == 'N' || opcija == 'n')
					exit(1);
			}
		}
			break;
		case '5':
			system("cls");
			meniInfo();
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

void provjeraMenia() {
	char c, a;
	if (strcmp(citanjeFlaga(), "zakljucano") == 0) {
		restartInformacija();
		meniZaOtkljucavanje();
		c = _getch();
		while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
			printf("Nepostojeca opcija!\n");
			c = _getch();
		}
		if (c == 'Y' || c == 'y') {
			system("cls");
			meniZaAktivaciju();
			printf("\n\nPritisni (Y) za logovanje ili (N) za izlazak iz aplikacije!\n ");
			c = _getch();
			while (c != 'Y' && c != 'y' && c != 'N' && c != 'n') {
				printf("Nepostojeca opcija!\n");
				c = _getch();
			}
			if (c == 'Y' || c == 'y') {
				system("cls");
				meniZaLogovanje();
				glavniMeni();
			}
			else
				exit(1);
		}
		else {
			system("cls");
			meniZaLogovanje();
			glavniMeni();
		}
	}
	else {
		meniZaLogovanje();
		glavniMeni();
	}

}


