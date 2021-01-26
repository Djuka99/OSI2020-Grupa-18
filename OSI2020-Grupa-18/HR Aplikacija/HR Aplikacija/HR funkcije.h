#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define MAXF 1000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct HR {
	char userName[MAX], password[MAX];
	int id, stanje;
}HR;

typedef struct datum {
	int dan, mjesec, godina;
}DATUM;

typedef struct korisnik {
	char userName[MAX], password[MAX], ime[MAX], prezime[MAX], radnoMjesto[MAX], sektor[MAX];
	int id, stanje, pin;
	DATUM datum;
}KORISNIK;




int unosPodataka() {
	FILE* hr;
	char username_temp[MAX], password_temp[MAX], temp;
	int id_temp, status_temp, test;
	HR hracc;

	for (int i = 0; i < MAX; i++)
		hracc.password[i] = 0;
	do {
		printf("\nUsername: "); scanf("%s", hracc.userName);
		printf("Password: ");
		temp = _getch();
		int i = 0;
		while (temp != 13) {
			if (temp != 8) {
				hracc.password[i] = temp;
				printf("*");
			}
			temp = _getch();
			i++;
		}
		if ((hr = fopen("../../Datoteke/HR.txt", "r")) != NULL) {
			while (fscanf(hr, "%d %s %s %d\n", &id_temp, username_temp, password_temp, &status_temp) != EOF)
				if (strcmp(hracc.userName, username_temp) == 0 && strcmp(hracc.password, password_temp) == 0 && status_temp) {
					if (status_temp == 0) {
						printf("\nNalog je deaktiviran!\n");
						return 2;
					}
					else
						return 1;
				}
		}
		else
			printf("\nGreska pri otvaranju datoteke!\n");
	} while (status_temp==0);
	fclose(hr);
	return 0;
}




int logovanje() {
	char c;
	int brPokusaja = 5;

	while (brPokusaja && !unosPodataka()) {
		--brPokusaja;
		printf("\nAkaunt ne postoji ili je deaktiviran!\nPokusaj ponovo (T) ili izadji iz aplikacije (E)!\n");
		c = _getch();

		while (c != 't' && c != 'T' && c != 'e' && c != 'E')
		{
			printf("Nepostojeca opcija!\nUnesite 'e' ili 'p': ");
			c = _getch();
		}
		if (c == 'e' || c == 'E')
			exit(1);
		else if (c == 't' || c == 'T') {
			printf("Ostalo je jos %d pokusaja!", brPokusaja);
			continue;
		}
	}
	if (brPokusaja == 0) {
		printf("Nalog je blokiran sat vremena!");
		do {
			printf("Pritisni E za izlazak iz aplikacije!");
			c = _getch();
		} while (c != 'e' && c != 'E');
	}
}

int brojacNaloga(char* imeFajla) {																									     // Funkcija koja broji naloge                                                                                             
	FILE* datoteka;
	int brojac = 1;
	char c;
	if ((datoteka = fopen(imeFajla, "r")) != NULL) {
		for (c = getc(datoteka); c != EOF; c = getc(datoteka))
			if (c == '\n')
				brojac++;

	}
	else printf("Greska pri otvaranju datoteke tokom brojanja!\n");
	fclose(datoteka);
	return brojac;
}

int dodavanjeNovog() {
	FILE* korisnici;
	KORISNIK krAccount, temp;
	int b = brojacNaloga("../../Datoteke/Korisnici.txt");
	int stanjeRadnika = 1;                                                                                                   // Promjenljiva koja reprezentuje stanje radnika:
	                                                                                                                         // 1 za aktivan nalog i 0 za neaktivan
	for (int i = 0; i < MAX; i++)
		krAccount.password[i] = 0;

	do {

		printf("Unesi ime novog korisnika: "); scanf("%s", krAccount.ime);
		printf("Unesi prezime novog korisnika: "); scanf("%s", krAccount.prezime);
		printf("Unesi username novog korisnika: "); scanf("%s", krAccount.userName);
		printf("Unesi sifru novog korisnika: "); scanf("%s", krAccount.password);
		printf("Unesi radno mjesto novog korisnika: "); scanf("%s", krAccount.radnoMjesto);
		printf("Unesi sektor novog korisnika: "); scanf("%s", krAccount.sektor);
		printf("Unesi datum zaposlenja novog korisnika (dan mjesec godina): "); scanf("%d %d %d", &krAccount.datum.dan, &krAccount.datum.mjesec, &krAccount.datum.godina);
		krAccount.pin = rand() % 9000 + 1000;
		if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL)
			while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF) {
				if ((strcmp(krAccount.userName, temp.userName) == 0)) {
					printf("Vec postoji nalog sa tim imenom!\n");
					break;
				}
			}
	} while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF);
	fclose(korisnici);
	do {

		if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL)
			while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF) {
				if ((krAccount.pin - temp.pin) == 0) {
					krAccount.pin = rand() % 9000 + 1000;
					break;
				}
			}


	} while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF);
	fclose(korisnici);
	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "a")) != NULL)
		fprintf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d\n", b, krAccount.userName, krAccount.password, krAccount.pin, krAccount.ime, krAccount.prezime, krAccount.radnoMjesto, krAccount.sektor, krAccount.datum.dan, krAccount.datum.mjesec, krAccount.datum.godina, stanjeRadnika);
	else
		printf("Nije moguce otvoriti HR datoteku!\n");
	fclose(korisnici);
}

int pretragaRadnogMjesta() {
	FILE* krAccount;
	KORISNIK korisnik, temp;
	char str[MAX];
	int i = 0;
	printf("Unesi ime radnog mjesta: "); scanf("%s", korisnik.radnoMjesto);

	if ((krAccount = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(krAccount, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF)
			if (strcmp(temp.radnoMjesto, korisnik.radnoMjesto) == 0)
			{
				printf("%d %-10s %-10s %-8s\n", i + 1, temp.ime, temp.prezime, temp.userName);
				i++;
			}
		if (i == 0)
			printf("U bazi nema nikoga na tom radnom mjestu!\n");
	}
	else printf("Ne moze otvoriti Korisnici.txt za pretragu radnog mjesta!\n");
	fclose(krAccount);
}


int pretragaSektora() {
	FILE* krAccount;
	KORISNIK korisnik, temp;
	char str[MAX];
	int i = 0;
	printf("Unesi ime sektora: "); scanf("%s", korisnik.sektor);

	if ((krAccount = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(krAccount, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF)
			if (strcmp(temp.sektor, korisnik.sektor) == 0)
			{
				printf("%d %s %s ( %s )\n", i + 1, temp.ime, temp.prezime, temp.userName);
				i++;
			}
		if (i == 0)
			printf("U bazi nema nikoga u tom sektoru!\n");
	}
	else
		printf("Ne moze otvoriti Korisnici.txt za pretragu sektora!\n");
	fclose(krAccount);
}

int pretragaPoBazi() {
	char c;
	
	c = _getch();
	while (c != '1' && c != '2') {
		printf("Nepostojeca opcija!\n");
		c = _getch();
	}

	if (c == '1')
		pretragaRadnogMjesta();
	else
		pretragaSektora();

}