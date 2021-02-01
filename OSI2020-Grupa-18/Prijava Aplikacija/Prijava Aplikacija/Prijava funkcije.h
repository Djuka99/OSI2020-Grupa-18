#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define MAXF 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct informacija {
	char ime[MAX], email[MAX], broj[MAX];
}INFO;

typedef struct datum {
	int dan, mjesec, godina;
}DATUM;

typedef struct korisnik {
	char userName[MAX], password[MAX], ime[MAX], prezime[MAX], radnoMjesto[MAX], sektor[MAX];
	int id, stanje, pin;
	DATUM datum;
}KORISNIK;

int logovanje();
int citanjeInformacije();
int unosPina();

int citanjeInformacije() {
	FILE* informacije;
	INFO info;

	if ((informacije = fopen("../../Datoteke/Informacije.txt", "r")) != NULL)
		fscanf(informacije, "%s %s %s", info.ime, info.email, info.broj);
	else printf("Nije moguce otvoriti Informacije.txt!\n");
	fclose(informacije);
	printf("%s\n%s\n%s\n", info.ime, info.email, info.broj);
}

int unosPina() {
	FILE* korisnici;
	KORISNIK korisnik;
	int temp;

	printf("Unesi PIN: "); scanf("%d", &temp);

	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &korisnik.id, korisnik.userName, korisnik.password, &korisnik.pin, korisnik.ime, korisnik.prezime, korisnik.radnoMjesto, korisnik.sektor, &korisnik.datum.dan, &korisnik.datum.mjesec, &korisnik.datum.godina, &korisnik.stanje) != EOF)
			if (temp - korisnik.pin == 0)
				return 1;
	}
	else
		printf("Nije moguce otvoriti Korisnici.txt za provjeru PIN-a!\n");
	return 0;
}

int logovanje() {
	char c;
	int brPokusaja = 5;

	while (brPokusaja && !unosPina()) {
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
			printf("Ostalo je jos %d pokusaja!\n", brPokusaja);
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