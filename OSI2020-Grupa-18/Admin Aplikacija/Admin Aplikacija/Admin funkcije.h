#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define MAXF 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct admin {
	char userName[MAX], password[MAX];
}ADMIN;

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

typedef struct informacija {
	char ime[MAX], email[MAX], broj[MAX];
}INFO;



void upisInformacija();
void citanjeInformacije();
char* citanjeFlaga();
void upisFlaga(char* flag);
int unosKoda();
int unosPodataka();
int logovanje();
int kreiranjeHR();
int deaktiviranjeHR();
int deaktiviranjeKR();
int provjeraPostojanja();
int informacije();
void restartInformacija();


int unosPodataka() {
	FILE* admini;
	char username_temp[MAX], password_temp[MAX], temp;
	ADMIN admin;
	
	for (int i = 0; i < MAX; i++)
		admin.password[i] = 0;

	printf("\nUsername: "); scanf("%s", admin.userName);
	printf("Password: ");
	int i = 0;
	temp = _getch();
	while (temp != 13) {
		if (temp != 8) {
			admin.password[i] = temp;
			printf("*");
			i++;
		}
		else {
			admin.password[i - 1] = "";
			printf("\b \b");
			i--;
		}
		temp = _getch();
		
	}

	

	if ((admini = fopen("../../Datoteke/Admini.txt", "r")) != NULL) {
		while (fscanf(admini, "%s %s\n", username_temp, password_temp) != EOF)
			if (strcmp(admin.userName, username_temp) == 0 && strcmp(admin.password, password_temp) == 0)
				return 1;
	}
	else
		printf("\nGreska pri otvaranju datoteke!\n");
	fclose(admini);
	return 0;
}

int logovanje() {
	char c;
	int brPokusaja = 3;

	while (brPokusaja && !unosPodataka()) {
		--brPokusaja;

		printf("\nPogresan unos podataka! Pokusaj ponovo (T) ili izadji iz aplikacije (E)!\n");
		c = _getch();

		while (c != 't' && c != 'T' && c != 'e' && c != 'E')
		{
			printf("\nNepostojeca opcija!\nUnesite 'T' ili 'E': ");
			c = _getch();
		}
		if (c == 'e' || c == 'E')
			exit(1);
		else if (c == 't' || c == 'T') {
			if (brPokusaja == 0)
				break;
			else {
				printf("Ostalo je jos %d pokusaja!", brPokusaja);
				continue;
			}
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

int brojacNaloga(char* imeFajla) {																					         // Funkcija koja broji naloge                                                                                             
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

int kreiranjeHR() {
	FILE* hr;
	HR hrAccount, temp;
	int b = brojacNaloga("../../Datoteke/HR.txt");

	//Stanje radnika je aktivno po kreiranju HR naloga
	int stanjeRadnika = 1;

	for (int i = 0; i < MAX; i++)
		hrAccount.password[i] = 0;

	do {

		printf("Unesi ime: "); scanf("%s", hrAccount.userName);
		printf("Unesi sifru: "); scanf("%s", hrAccount.password);

		if ((hr = fopen("../../Datoteke/HR.txt", "r")) != NULL)
			while (fscanf(hr, "%d %s %s %d", &temp.id, temp.userName, temp.password, &temp.stanje) != EOF) {
				if (strcmp(hrAccount.userName, temp.userName) != 0) {
					continue;
				}
				else {
					printf("Vec postoji nalog sa tim imenom!\n");
					fclose(hr);
					break;
				}
			}
		fclose(hr);
	} while (fscanf(hr, "%d %s %s %d", &temp.id, temp.userName, temp.password, &temp.stanje) != EOF);
	if ((hr = fopen("../../Datoteke/HR.txt", "a")) != NULL)
		fprintf(hr, "\n%d %s %s %d", temp.id + 1, hrAccount.userName, hrAccount.password, stanjeRadnika);
	else
		printf("Nije moguce otvoriti HR datoteku!\n");
	fclose(hr);

}

// Funkcija koja ce mijenjati stanje radnika
int zamjena(char* fname, int brLinije, char* novaLinija)
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
		}
	}
	fclose(fptr1);
	fclose(fptr2);
	remove(fname);
	rename(temp, fname);
	printf("Nalog radnika je deaktiviran !\n");
	return 0;
}

int deaktiviranjeHR() {
	FILE* hr, * hr_temp;
	HR hrAccount;
	char temp_u[MAX], idChar[MAX], stanjeChar[MAX], linija[MAXF] = "";
	int brLinija = 0, br = 0;
	printf("Unesi username HR korisnika kome zelis promjeniti stanje naloga!\n");
	scanf("%s", temp_u);
	if ((hr = fopen("../../Datoteke/HR.txt", "r")) != NULL)
		while (fscanf(hr, "%d %s %s %d", &hrAccount.id, hrAccount.userName, hrAccount.password, &hrAccount.stanje) != EOF)
		{
			brLinija++;
			if (strcmp(hrAccount.userName, temp_u) == 0) {
				br++;
				if (hrAccount.stanje) {

					hrAccount.stanje = 0;

					// Konverujem int u string i spajam sve u jedan string
					_itoa(hrAccount.id, idChar, 10);
					_itoa(hrAccount.stanje, stanjeChar, 10);
					strcat(linija, idChar);
					strcat(linija, " ");
					strcat(linija, hrAccount.userName);
					strcat(linija, " ");
					strcat(linija, hrAccount.password);
					strcat(linija, " ");
					strcat(linija, stanjeChar);
					strcat(linija, "\n");
					fclose(hr);
					zamjena("../../Datoteke/HR.txt", brLinija, linija);
					break;
				}
				else
					printf("Nalog radnika je vec neaktivan!\n");
			}
		}
	if (br == 0)
		printf("Ne postoji username u bazi!\n");
	fclose(hr);
}

int deaktiviranjeKR() {
	FILE* kr, * kr_temp;
	KORISNIK krAccount;
	char temp_u[MAX], idChar[MAX], stanjeChar[MAX], danChar[MAX], mjesecChar[MAX], godinaChar[MAX], pinChar[MAX], linija[MAXF] = "";
	char opcija;
	int brLinija = 0, br = 0;
	printf("Unesi username radnika kome zelis promjeniti stanje naloga!\n");
	scanf("%s", temp_u);
	if ((kr = fopen("../../Datoteke/Korisnici.txt", "r")) != NULL)
		while (fscanf(kr, "%d %s %s %d %s %s %s %s %d %d %d %d", &krAccount.id, krAccount.userName, krAccount.password, &krAccount.pin, krAccount.ime, krAccount.prezime, krAccount.radnoMjesto, krAccount.sektor, &krAccount.datum.dan, &krAccount.datum.mjesec, &krAccount.datum.godina, &krAccount.stanje) != EOF)
		{
			brLinija++;
			if (strcmp(krAccount.userName, temp_u) == 0) {
				br++;
				if (krAccount.stanje) {
					krAccount.stanje = 0;

					// Konvertujem int u string i spajam sve u jedan string
					_itoa(krAccount.id, idChar, 10);
					_itoa(krAccount.stanje, stanjeChar, 10);
					_itoa(krAccount.datum.dan, danChar, 10);
					_itoa(krAccount.datum.mjesec, mjesecChar, 10);
					_itoa(krAccount.datum.godina, godinaChar, 10);
					_itoa(krAccount.pin, pinChar, 10);
					strcat(linija, idChar);
					strcat(linija, " ");
					strcat(linija, krAccount.userName);
					strcat(linija, " ");
					strcat(linija, krAccount.password);
					strcat(linija, " ");
					strcat(linija, pinChar);
					strcat(linija, " ");
					strcat(linija, krAccount.ime);
					strcat(linija, " ");
					strcat(linija, krAccount.prezime);
					strcat(linija, " ");
					strcat(linija, krAccount.radnoMjesto);
					strcat(linija, " ");
					strcat(linija, krAccount.sektor);
					strcat(linija, " ");
					strcat(linija, danChar);
					strcat(linija, " ");
					strcat(linija, mjesecChar);
					strcat(linija, " ");
					strcat(linija, godinaChar);
					strcat(linija, " ");
					strcat(linija, stanjeChar);
					strcat(linija, "\n");
					fclose(kr);
					zamjena("../../Datoteke/Korisnici.txt", brLinija, linija);
					break;
				}
				else
					printf("Nalog radnika je vec neaktivan!\n");
			}
		}
	if (br == 0)
		printf("Ne postoji username u bazi!\n");
	fclose(kr);
}

//Funkcija kojom u datoteku Validnost kljuca.txt upisujem flag (zakljucano ili otkljucano)
void upisFlaga(char* flag) {
	FILE* Validnost_kljuca;
	if (Validnost_kljuca = fopen("../../Datoteke/Validnost kljuca.txt", "w"))
		fprintf(Validnost_kljuca, "%s", flag);
	else
		printf("Nije moguce otvoriti fajl Validnost kljuca!\n");
	fclose(Validnost_kljuca);

}

//Citam iz datoteke Validnost kljuca.txt flag
char* citanjeFlaga() {
	FILE* Validnost_kljuca;
	char flag[MAX], flag_temp[MAX];
	if (Validnost_kljuca = fopen("../../Datoteke/Validnost kljuca.txt", "r"))
		while (fscanf(Validnost_kljuca, "%s", flag) != EOF)
		{
			strcpy(flag_temp, flag);
		}
	else
		printf("Nije moguce otvoriti fajl Validnost kljuca!\n");
	fclose(Validnost_kljuca);
	return flag_temp;
}

//Funkcija kojom unosim kljuc 
int unosKoda() {
	char kod[50], temp_kod[50], opcija, flag;
	int  opcija2 = 0, opcija3 = 0;
	FILE* aktivacija;

	printf("Napomena:\nKljuc mora biti unijet u formatu: XXX-XXX-XXX\n\n\n\n");
	do {
		printf("Unesi kljuc: "); scanf("%s", temp_kod);
		if ((aktivacija = fopen("../../Datoteke/Aktivacioni kod.txt", "r")) != NULL) {
			fgets(kod, 50, aktivacija);
			if (strcmp(kod, temp_kod) == 0) {
				printf("Program je otkljucan!\n");
				upisFlaga("otkljucano");
				opcija2 = 1;
				opcija3 = 1;
			}
			else {
				printf("Kljuc je netacan! Ponovite unos (Y) ili zatvorite aplikaciju (N)\n");
				opcija = _getch();
				while (opcija != 'y' && opcija != 'Y' && opcija != 'n' && opcija != 'N') {
					printf("Pogresan unos!\n");
					opcija = _getch();
				}

				if (opcija == 'y' || opcija == 'Y')
					opcija2 = 0;
				else if (opcija == 'n' || opcija == 'N')
					exit(1);
			}
		}
		else {
			printf("Nije moguce otvoriti datoteku za citanje kljuca!\n");
			opcija2 = 1;
		}
	} while (opcija2 != 1);
	fclose(aktivacija);
	return opcija3;
}

void citanjeInformacije() {
	FILE* informacije;
	INFO info;

	if ((informacije = fopen("../../Datoteke/Informacije.txt", "r")) != NULL)
		fscanf(informacije, "%s %s %s", info.ime, info.email, info.broj);
	else printf("Nije moguce otvoriti Informacije.txt!\n");
	fclose(informacije);
	printf("\t\t\t                 ___ ___ _  _  ___  ___\n");
	printf("%-20s", info.ime); printf("\t\t\t| _ \\_ _| \\| |/ __|/ _ \\ \n");
	printf("%-20s", info.email); printf("\t\t\t|  _/| || .` | (_ | (_) |\n");
	printf("%-20s", info.broj); printf("\t\t\t|_| |___|_|\\_|\\___|\\___/ \n\n");


}

void upisInformacija() {
	INFO info;
	char opcija;
	FILE* informacije;
	printf("Unesi ime kompanije: "); scanf("%s", info.ime);
	printf("Unesi email kompanije: "); scanf("%s", info.email);
	printf("Unesi broj kompanije (xxx/xxx-xxx): "); scanf("%s", info.broj);

	if ((informacije = fopen("../../Datoteke/Informacije.txt", "w")) != NULL)
		fprintf(informacije, "%s %s %s", info.ime, info.email, info.broj);
	else
		printf("Nije moguce otvoriti Informacije.txt za upis!\n");
	fclose(informacije);

}

void restartInformacija() {
	FILE* informacije;
	if ((informacije = fopen("../../Datoteke/Informacije.txt", "w")) != NULL)
		fprintf(informacije, "ETF etf@unibl.net 051/221-820");
	else
		printf("Nije moguce otvoriti Informacije.txt za upis!\n");
	fclose(informacije);
}



