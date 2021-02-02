#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "HR funkcije.h"

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
	printf("1-> Dodavanje novog zaposlenog\n");
	printf("2-> Pregled prijava radnika\n");
	printf("3-> Pretraga po bazi\n\n");
	printf("0-> Za izlazak iz aplikacije\n\n");

}

void meniZaLogovanje() {
	zaglavlje();
	printf("\t\t\tHR APLIKACIJA\n");
	printf("----------------------------------------------------------------\n\n");
	logovanje();
}

void dodavanjeNovogZaposlenog() {
	zaglavlje();
	printf("\t\t\tDODAVANJE NOVOG ZAPOSLENOG\n");
	printf("----------------------------------------------------------------\n\n");
	dodavanjeNovog();
	footer();
}

void pregledPrijavaRadnika() {
	zaglavlje();
	printf("\t\t\tPREGLED PRIJAVA RADNIKA\n");
	printf("----------------------------------------------------------------\n");
	printf("Unesi M za povratak na glavni meni ili E za izlazak iz programa!\n");
	printf("----------------------------------------------------------------\n\n");
	printf("Izaberi opciju:\n");
	printf("1-> Prikaz izvjestaja o ukupnpnom radnom vremenu po danima\n");
	printf("2-> Prikaz pristupa radnika po danima\n");
}

void pretragaBaze() {
	zaglavlje();
	printf("\t\t\tPRETRAGA BAZE\n");
	printf("----------------------------------------------------------------\n\n");
	printf("Izaberi opciju:\n");
	printf("1-> Prikaz radnika po radnom mjestu\n");
	printf("2-> Prikaz radnika po sektoru\n");
	printf("3-> Prikaz radnika po imenu i prezimenu\n");
}

void pretragaBazePoRM() {
	zaglavlje();
	printf("\t\tPRETRAGA BAZE PO RADNOM MJESTU\n");
	printf("----------------------------------------------------------------\n\n");
	pretragaRadnogMjesta();
	footer();
}

void pretragaBazePoSE() {
	zaglavlje();
	printf("\t\tPRETRAGA BAZE PO SEKTORU\n");
	printf("----------------------------------------------------------------\n\n");
	pretragaSektora();
	footer();
}

void pretragaBazePoIme() {
	zaglavlje();
	printf("\t\tPRETRAGA BAZE PO IMENU\n");
	printf("----------------------------------------------------------------\n\n");
	pretragaImena();
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
			while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2') {
				printf("Pogresan unos!\n");
				opcija = _getch();
			}

			if (opcija == 'm' || opcija == 'M')
				glavniMeni();
			else if (opcija == 'e' || opcija == 'E')
				exit(1);
			else if (opcija != '1') {
				system("cls");
				prikazSati();
				opcija = _getch();
				while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'm' || opcija == 'M')
					glavniMeni();
				else if (opcija == 'e' || opcija == 'E')
					exit(1);
			}
			else if (opcija != '2') {
				system("cls");
				prikazPrijava();
				opcija = _getch();
				while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'm' || opcija == 'M')
					glavniMeni();
				else if (opcija == 'e' || opcija == 'E')
					exit(1);
			}
			break;
		case '3':
			system("cls");
			pretragaBaze();
			opcija = _getch();
			while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2' && opcija != '3') {
				printf("Pogresan unos!\n");
				opcija = _getch();
			}

			if (opcija == 'm' || opcija == 'M')
				glavniMeni();
			else if (opcija == 'e' || opcija == 'E')
				exit(1);
			else if (opcija == '1') {
				system("cls");
				pretragaBazePoRM();
				opcija = _getch();
				while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2' && opcija != '3') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'm' || opcija == 'M')
					glavniMeni();
				else if (opcija == 'e' || opcija == 'E')
					exit(1);
			}
			else if (opcija == '2') {
				system("cls");
				pretragaBazePoSE();
				opcija = _getch();
				while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2' && opcija != '3') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'm' || opcija == 'M')
					glavniMeni();
				else if (opcija == 'e' || opcija == 'E')
					exit(1);
			}
			else if (opcija == '3') {
				system("cls");
				pretragaBazePoIme();
				opcija = _getch();
				while (opcija != 'm' && opcija != 'M' && opcija != 'e' && opcija != 'E' && opcija != '1' && opcija != '2' && opcija != '3') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'm' || opcija == 'M')
					glavniMeni();
				else if (opcija == 'e' || opcija == 'E')
					exit(1);
			}

			break;
		default:
			printf("Nepostojeca opcija!\n");
		}
	}

}