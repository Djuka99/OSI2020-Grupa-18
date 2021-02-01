#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define MAXF 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct datum {
	int dan, mjesec, godina;
}DATUM;

typedef struct korisnik {
	char userName[MAX], password[MAX], ime[MAX], prezime[MAX], radnoMjesto[MAX], sektor[MAX];
	int id, stanje, pin;
	DATUM datum;
}KORISNIK;

typedef struct informacija {
	char ime[MAX], email[MAX], broj[MAX];
}INFO;

typedef struct vrijeme {
	int sati, minute, sekunde, dan, mjesec, godina;
}VRIJEME;

char userName[MAX] = "", password[MAX] = "";

void citanjeInformacije() {
	FILE* informacije;
	INFO info;

	if ((informacije = fopen("../../Datoteke/Informacije.txt", "r")) != NULL)
		fscanf(informacije, "%s %s %s", info.ime, info.email, info.broj);
	else printf("Nije moguce otvoriti Informacije.txt!\n");
	fclose(informacije);
	printf("%s\n%s\n%s\n", info.ime, info.email, info.broj);

}

int unosPodataka() {
	FILE* korisnici;
	char  tmp;
	KORISNIK kracc, temp;

	for (int i = 0; i < MAX; i++)
		kracc.password[i] = 0;
	printf("\nUsername: "); scanf("%s", kracc.userName); strcat(userName, kracc.userName);
	printf("Password: ");
	tmp = _getch();
	int i = 0;
	while (tmp != 13) {
		if (tmp != 8) {
			kracc.password[i] = tmp;
			printf("*");
		}
		tmp = _getch();
		i++;
	}
	strcat(password, kracc.password);
	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF)
			if (strcmp(kracc.userName, temp.userName) == 0 && strcmp(kracc.password, temp.password) == 0 && temp.stanje)
				return 1;
	}
	else
		printf("\nGreska pri otvaranju datoteke!\n");
	fclose(korisnici);
	return 0;
}

void logovanje() {
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

void pretragaInformacija() {
	FILE* krAccount;
	KORISNIK  temp;
	char str[MAX];
	int i = 0;
	if ((krAccount = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(krAccount, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF)
			if (strcmp(temp.userName, userName) == 0 && strcmp(temp.password, password) == 0)
			{
				printf("Ime:               %s\n", temp.ime);
				printf("Prezime:           %s\n", temp.prezime);
				printf("Username:          %s\n", temp.userName);
				printf("Password:          %s\n", temp.password);
				printf("PIN:               %d\n", temp.pin);
				printf("Radno mjesto:      %s\n", temp.radnoMjesto);
				printf("Sektor:            %s\n", temp.sektor);
				printf("Zaposlen od:       %d.%d.%d\n\n", temp.datum.dan, temp.datum.mjesec, temp.datum.godina);
				if (temp.stanje == 0)
					printf("Stanje: Nalog je deaktiviran\n");
				else
					printf("Stanje: Nalog je aktivan\n");
				i++;
			}
		if (i == 0)
			printf("U bazi nema nikoga u tom sektoru!\n");
	}
	else
		printf("Ne moze otvoriti Korisnici.txt za pretragu sektora!\n");
	fclose(krAccount);
}

void pretragaPrijava() {
	FILE* korisnici;
	FILE* prijave;
	KORISNIK temp;
	VRIJEME vrijeme;
	int mjesec, godina, brojac = 0;
	char flag[MAX] = "";
	char txtPrijave[MAXF] = "../../Datoteke/Baza radnika/Prijave radnika/";
	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF)
			if (strcmp(temp.userName, userName) == 0 && strcmp(temp.password, password) == 0) {
				brojac++;

				strcat(txtPrijave, temp.userName);
				strcat(txtPrijave, ".txt");

				printf("Za koji mjesec i godinu zelis izvjestaj?\n");
				printf("Mjesec: "); scanf("%d", &mjesec);
				printf("Godina: "); scanf("%d", &godina);

				if ((prijave = fopen(txtPrijave, "r")) != NULL) {
					while (fscanf(prijave, "%d.%d.%d. %s %d:%d", &vrijeme.dan, &vrijeme.mjesec, &vrijeme.godina, flag, &vrijeme.sati, &vrijeme.minute) != EOF) {
						if (vrijeme.mjesec == mjesec && vrijeme.godina == godina)
							printf("%02d.%02d.%d. %-11s %02d:%02d\n", vrijeme.dan, vrijeme.mjesec, vrijeme.godina, flag, vrijeme.sati, vrijeme.minute);
					}
					fclose(prijave);
				}
				else
					printf("Nije moguce otvoriti datoteku prijave u funkciji za pretrgau prijava!\n");
			}
		fclose(korisnici);
	}
	else printf("Nije moguce otvoriti datoteku korisnici u funkciji za pretragu prijava!\n");
	if (brojac == 0)
		printf("Ne postoji korisnik u bazi!\n");
}

void pretragaSati() {
	FILE* korisnici;
	FILE* sati;
	KORISNIK temp;
	VRIJEME vrijeme;
	int mjesec, godina, brojac = 0, ukupnoSati = 0, ukupnoMinuta = 0;
	char flag[MAX] = "";
	char txtSati[MAXF] = "../../Datoteke/Baza radnika/Sati radnika/";
	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &temp.id, temp.userName, temp.password, &temp.pin, temp.ime, temp.prezime, temp.radnoMjesto, temp.sektor, &temp.datum.dan, &temp.datum.mjesec, &temp.datum.godina, &temp.stanje) != EOF)
			if (strcmp(temp.userName, userName) == 0 && strcmp(temp.password, password) == 0) {
				brojac++;

				strcat(txtSati, temp.userName);
				strcat(txtSati, ".txt");

				printf("Za koji mjesec i godinu zelis izvjestaj?\n");
				printf("Mjesec: "); scanf("%d", &mjesec);
				printf("Godina: "); scanf("%d", &godina);
				if ((sati = fopen(txtSati, "r")) != NULL) {
					while (fscanf(sati, "%d.%d.%d.     %d:%dh", &vrijeme.dan, &vrijeme.mjesec, &vrijeme.godina, &vrijeme.sati, &vrijeme.minute) != EOF) {
						if (vrijeme.mjesec == mjesec && vrijeme.godina == godina) {
							printf("%02d.%02d.%d.     %02d:%02dh\n", vrijeme.dan, vrijeme.mjesec, vrijeme.godina, vrijeme.sati, vrijeme.minute);
							ukupnoSati += vrijeme.sati;
							ukupnoMinuta += vrijeme.minute;
						}
					}
					fclose(sati);
				}
				else
					printf("Nije moguce otvoriti datoteku sati u funkciji za pretrgau prijava!\n");
				while (ukupnoMinuta > 60) {
					ukupnoSati++;
					ukupnoMinuta -= 60;
				}
				printf("----------------------\n");
				printf("UKUPNO:\n");
				printf("ZA %02d.%d.        %dh\n", mjesec, godina, ukupnoSati);
			}
		fclose(korisnici);
	}
	else printf("Nije moguce otvoriti datoteku korisnici u funkciji za pretragu prijava!\n");
	if (brojac == 0)
		printf("Ne postoji korisnik u bazi!\n");
}