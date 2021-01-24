#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Admin_funkcije.h"



void glavniMeni() {
	system("cls");
	printf("----------------------------------------------------------------\n");
	printf("\t\t\tWELCOME ADMIN\n");
	printf("----------------------------------------------------------------\n");
	printf("Odaberite opciju:\n");
	printf("1:Kreiranje HR naloga\n");
	printf("2:Deaktiviranje HR naloga\n");
	printf("3:Deaktiviranje korisnickog naloga\n");
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
		default:
			printf("Nepostojeca opcija!\n");
		}
	}
}

void provjeraMenia() {
	if (citanjeFlaga() != 49)
		meniZaAktivaciju();
	else
		meniZaLogovanje();
}
