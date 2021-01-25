#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Admin funkcije.h"



void glavniMeni() {
	system("cls");
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tWELCOME ADMIN\n");
	printf("----------------------------------------------------------------\n");
	printf("Odaberite opciju:\n");
	printf("1:Kreiranje HR naloga\n");
	printf("2:Deaktiviranje HR naloga\n");
	printf("3:Deaktiviranje korisnickog naloga\n");
	printf("4:Sta se dobija u punoj verziji?\n\n");
	printf("0:Za izlazak iz aplikacije\n\n");
}

void meniZaLogovanje() {
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tLOGIN\n");
	printf("----------------------------------------------------------------\n");
	logovanje();
}

void meniKreiranjeHR() {
	printf("----------------------------------------------------------------\n");
	printf("\t\tKREIRANJE HR NALOGA\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	kreiranjeHR();

}

void meniZaDeaktiviranjeHR() {
	printf("----------------------------------------------------------------\n");
	printf("\t\tDEAKTIVIRANJE HR NALOGA\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	deaktiviranjeHR();
}

void meniZaDeaktiviranjeKN() {
	printf("----------------------------------------------------------------\n");
	printf("\t\tDEAKTIVIRANJE KORISNICKOG NALOGA\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	deaktiviranjeKR();
}

void meniZaAktivaciju() {
	printf("----------------------------------------------------------------\n");
	printf("\t\tOTKLJUCAVANJE APLIKACIJE\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	unosKoda();

}

void meniInfo() {
	printf("----------------------------------------------------------------\n");
	printf("\t\tINFO\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	printf("U otkljucanoj verziji korisniku su omogucene iduce izmjene:\n");
	printf(" - Prikaz imena kompanije\n");
	printf(" - Prikaz broja telefona \n");
	printf(" - Prikaz mail-a\n");
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
		case '4':
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
	char c;
	if (strcmp(citanjeFlaga(), "zakljucano") == 0) {
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\tAplikacija nije otkljucana\n");
		printf("------------------------------------------------------------------------------------------------------------------------\n");
		printf("Da li zelite otkljucati aplikaciju ili nastaviti sa besplatnom verzijom?\n(Y)-> za unos koda\n(N)-> za besplatnu verziju.\n");
		c = _getch();
		while (c != 'Y' && c != 'y' && c != 'N' & c != 'n') {
			printf("Nepostojeca opcija!\n");
			c = _getch();
		}
		if (c == 'Y' || c == 'y') {
			system("cls");
			meniZaAktivaciju();
		}
		else if (c == 'N' || c == 'n') {
			system("cls");
			meniZaLogovanje();
		}
	}
	else
		meniZaLogovanje();
		
}
