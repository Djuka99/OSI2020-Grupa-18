#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define MAXF 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

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

typedef struct vrijeme {
	int sati, minute, sekunde, dan, mjesec, godina;
}VRIJEME;

void upisPrijave(int pin);
void logovanje();
void citanjeInformacije();
int unosPina();

void citanjeInformacije() {
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
	char ime[MAX];

	printf("Unesi PIN: "); scanf("%d", &temp);

	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &korisnik.id, korisnik.userName, korisnik.password, &korisnik.pin, korisnik.ime, korisnik.prezime, korisnik.radnoMjesto, korisnik.sektor, &korisnik.datum.dan, &korisnik.datum.mjesec, &korisnik.datum.godina, &korisnik.stanje) != EOF)
			if (temp - korisnik.pin == 0) {
				upisPrijave(temp);
				return 1;

			}

	}
	else
		printf("Nije moguce otvoriti Korisnici.txt za provjeru PIN-a!\n");


	return 0;
}

void logovanje() {
	char c;
	int brPokusaja = 5;
	while (brPokusaja && !unosPina()) {
		--brPokusaja;
		printf("\nPOGRESAN PIN KOD\nPokusaj ponovo (T) ili izadji iz aplikacije (E)!\n");
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

VRIJEME trenutnoVrijeme() {
	VRIJEME t;
	time_t vrijeme;
	time(&vrijeme);

	struct tm* local = localtime(&vrijeme);

	t.sati = local->tm_hour;
	t.minute = local->tm_min;
	t.sekunde = local->tm_sec;
	t.dan = local->tm_mday;
	t.mjesec = local->tm_mon + 1;
	t.godina = local->tm_year + 1900;

	return t;
}

int zamjena(char* fname, int brLinije, char* novaLinija)							                                         // Funkcija koja ce mijenjati stanje radnika
{
	FILE* fptr1, * fptr2;
	int  linectr = 0;
	char str[MAXF];
	char temp[] = "temp1.txt";
	fptr1 = fopen(fname, "r");
	if (!fptr1)
	{
		printf("Nije moguce otvaranje datoteke za citanje!!\n");
		return 0;
	}
	fptr2 = fopen(temp, "w");
	if (!fptr2)
	{
		printf("Nije moguce otvaranje datoteke za pisanje!!\n");
		fclose(fptr1);
		return 0;
	}

	while (!feof(fptr1))
	{
		strcpy(str, "\0");
		fgets(str, MAXF, fptr1);
		linectr++;
		if (linectr != brLinije)
		{
			fprintf(fptr2, "%s", str);
		}
		else
		{
			fprintf(fptr2, "%s", novaLinija);
			printf("ISPISO ZAMJENU\n");
		}
	}
	fclose(fptr1);
	fclose(fptr2);
	remove(fname);
	rename(temp, fname);
	return 0;
}

void upisPrijave(int pin) {
	char c = "prijavljen", flag[MAX] = "", novaLinija[MAXF] = "";
	char txtPrijave[MAXF] = "../../Datoteke/Baza radnika/Prijave radnika/";
	char txtSati[MAXF] = "../../Datoteke/Baza radnika/Sati radnika/";
	char charDan[MAX], charMjesec[MAX], charGodina[MAX], charSat[MAX], charMinute[MAX];
	int tempMinute, tempSati, brLinija = 0, x, y;
	KORISNIK krAccount;
	VRIJEME vrijeme, vrijeme2, temp = trenutnoVrijeme();
	FILE* korisnici;
	FILE* prijava;
	FILE* upisPrijave;
	FILE* upisSata;


	//TRAZIM ZADNJU LINIJU (PRIJAVLJEN ili ODJAVLJEN)
	if ((korisnici = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL) {
		while (fscanf(korisnici, "%d %s %s %d %s %s %s %s %d %d %d %d", &krAccount.id, krAccount.userName, krAccount.password, &krAccount.pin, krAccount.ime, krAccount.prezime, krAccount.radnoMjesto, krAccount.sektor, &krAccount.datum.dan, &krAccount.datum.mjesec, &krAccount.datum.godina, &krAccount.stanje) != EOF)
			if (pin == krAccount.pin) {
				strcat(txtPrijave, krAccount.userName);
				strcat(txtPrijave, ".txt");
				strcat(txtSati, krAccount.userName);
				strcat(txtSati, ".txt");
				if ((prijava = fopen(txtPrijave, "r")) != NULL)
					while (!feof(prijava))
					{
						fscanf(prijava, "%d.%d.%d. %s %d:%d", &vrijeme.dan, &vrijeme.mjesec, &vrijeme.godina, flag, &vrijeme.sati, &vrijeme.minute);
					}
			}
	}
	else
		printf("Nije moguce otvoriti Prijave radnika.txt\n");
	fclose(korisnici);

	//PROVJERAVAM ZADNJU LINIJU
	if (strcmp(flag, "odjavljen") == 0) {
		//AKO JE ODJAVLJEN UPISACU SAMO PRIJAVU
		if ((upisPrijave = fopen(txtPrijave, "a")) != NULL)
			fprintf(upisPrijave, "%02d.%02d.%d. %-11s %02d:%02d\n", temp.dan, temp.mjesec, temp.godina, "prijavljen", temp.sati, temp.minute);
		else
			printf("Nije moguce otvoriti Prijava radnika.txt datoteku\n");
		fclose(upisPrijave);
	}
	else {
		//AKO JE PRIJAVLJEN UPISACU ODJAVU I RACUNAM RAZLIKU VREMENA
		if ((upisPrijave = fopen(txtPrijave, "a")) != NULL) {

			fprintf(upisPrijave, "%02d.%02d.%d. %-11s %02d:%02d\n", temp.dan, temp.mjesec, temp.godina, "odjavljen", temp.sati, temp.minute);
			tempSati = temp.sati - vrijeme.sati;
			tempMinute = temp.minute - vrijeme.minute;

			//CITAM ZADNJU LINIJU IZ DATOTEKE UPIS SATI I BROJIM KOLIKO IMA LINIJA
			if ((upisSata = fopen(txtSati, "r")) != NULL)
				while (!feof(upisSata)) {
					fscanf(upisSata, "%02d.%02d.%d.     %02d:%02dh", &vrijeme2.dan, &vrijeme2.mjesec, &vrijeme2.godina, &vrijeme2.sati, &vrijeme2.minute);
					brLinija++;

				}
			brLinija--;
			fclose(upisSata);
			printf("%02d.%02d.%d.     %02d:%02dh", vrijeme2.dan, vrijeme2.mjesec, vrijeme2.godina, vrijeme2.sati, vrijeme2.minute);
			//PROVJERAVAM DA LI JE DATUM JOS VAZECI
			if (temp.dan == vrijeme2.dan && temp.mjesec == vrijeme2.mjesec && temp.godina == vrijeme2.godina) {
				//AKO JE DATUM ISTI DODAJ NOVE SATE U ISTU LINIJU
				x = tempSati + vrijeme2.sati;
				y = tempMinute + vrijeme2.minute;

				//PRAVIM ZAMJENSKU LINIJU
				_itoa(vrijeme2.dan, charDan, 10);
				_itoa(vrijeme2.mjesec, charMjesec, 10);
				_itoa(vrijeme2.godina, charGodina, 10);
				_itoa(x, charSat, 10);
				_itoa(y, charMinute, 10);

				strcat(novaLinija, charDan);
				strcat(novaLinija, ".");
				strcat(novaLinija, charMjesec);
				strcat(novaLinija, ".");
				strcat(novaLinija, charGodina);
				strcat(novaLinija, ".");
				strcat(novaLinija, "     ");
				if (x < 10)
					strcat(novaLinija, "0");
				strcat(novaLinija, charSat);
				strcat(novaLinija, ":");
				if (y < 10)
					strcat(novaLinija, "0");
				strcat(novaLinija, charMinute);
				strcat(novaLinija, "h");
				printf("\n%d\n", brLinija);
				zamjena(txtSati, brLinija, novaLinija);
			}
			else
				//AKO JE DATUM RAZLICIT SAMO DODAJ NOVU LINIJU SA NOVIM SATOM
				fprintf(upisSata, "\n%02d.%02d.%d.     %02d:%02dh", temp.dan, temp.mjesec, temp.godina, tempSati, tempMinute);
		}
		else printf("NE OTVARA\n");
		fclose(upisPrijave);
	}
}