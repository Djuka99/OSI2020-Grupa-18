#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 30
#define MAXF 5000
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


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
	int id, stanje;
	DATUM datum;
}KORISNIK;



int unosPodataka();
int logovanje();
int kreiranjeHR();
int deaktiviranjeHR();
int deaktiviranjeKR();
int provjeraPostojanja();



int unosPodataka() {
	FILE* admini;
	char username_temp[MAX], password_temp[MAX], temp;
	ADMIN admin;

	for (int i = 0; i < MAX; i++)
		admin.password[i] = 0;

	printf("\nUsername: "); scanf("%s", admin.userName);
	printf("Password: ");
	temp = _getch();
	int i = 0;
	while (temp != 13) {
		if (temp != 8) {
			admin.password[i] = temp;
			printf("*");
		}
		temp = _getch();
		i++;
	}
	if ((admini = fopen("../Datoteke/Admini.txt", "r")) != NULL) {
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
	char c[5];
	int brPokusaja = 5;

	while (brPokusaja && !unosPodataka()) {
		--brPokusaja;
		printf("Pogresan unos podataka! Pokusaj ponovo (T) ili izadji iz aplikacije (E)!\n");
		scanf("%c", &c);

		while (c[1] != 0 || (c[0] != 'p' && c[0] != 'P' && c[0] != 'e' && c[0] != 'E'))
		{
			printf("Nepostojeca opcija!\nUnesite 'e' ili 'p': ");
			scanf("\n%s", &c);
		}
		if (c[0] == 'e' || c[0] == 'E')
			exit(1);
		else if (c[0] == 't' || c[0] == 'T') {
			printf("Ostalo je jos %d pokusaja!", brPokusaja);
			continue;
		}
	}
	if (brPokusaja == 0) {
		printf("Nalog je blokiran sat vremena!");
		do {
			printf("Pritisni E za izlazak iz aplikacije!");
			scanf("%s", c);
		} while (c != 'e' && c != 'E');
	}
}



int brojacNaloga() {																									     // Funkcija koja broji naloge                                                                                             
	FILE* hr;
	int brojac = 1;
	char c;
	if ((hr = fopen("../Datoteke/HR.txt", "r")) != NULL) {
		for (c = getc(hr); c != EOF; c = getc(hr))
			if (c == '\n')
				brojac++;

	}
	else printf("Greska pri otvaranju datoteke tokom brojanja!\n");
	fclose(hr);
	return brojac;
}




int kreiranjeHR() {
	FILE* hr;
	HR hrAccount, temp;
	int b = brojacNaloga();
	int stanjeRadnika = 1;															                                         // Promjenljiva koja reprezentuje stanje radnika:
																															 // 1 za aktivan nalog i 0 za neaktivan
	for (int i = 0; i < MAX; i++)
		hrAccount.password[i] = 0;

	do {

		printf("Unesi ime: "); scanf("%s", hrAccount.userName);
		printf("Unesi sifru: "); scanf("%s", hrAccount.password);

		if ((hr = fopen("../Datoteke/HR.txt", "r")) != NULL)
			while (fscanf(hr, "%d %s %s %d", &temp.id, temp.userName, temp.password, &temp.stanje) != EOF) {
				if (strcmp(hrAccount.userName, temp.userName) != 0) {
					continue;
				}
				else printf("Vec postoji nalog sa tim imenom!\n");
				break;
			}

	} while (fscanf(hr, "%d %s %s %d", &temp.id, temp.userName, temp.password, &temp.stanje) != EOF);
	if ((hr = fopen("../Datoteke/HR.txt", "a")) != NULL)
		fprintf(hr, "%d %s %s %d \n", b + 1, hrAccount.userName, hrAccount.password, stanjeRadnika);
	else
		printf("Nije moguce otvoriti HR datoteku!\n");
	fclose(hr);

}


int zamjena(char* fname, int brLinije, char* novaLinija)							                                         // Funkcija koja ce mijenjati stanje radnika
{
	FILE* fptr1, * fptr2;
	int  linectr = 0;
	char str[MAX];
	char temp[] = "temp.txt";
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
		fgets(str, MAX, fptr1);
		if (!feof(fptr1))
		{
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
	}
	fclose(fptr1);
	fclose(fptr2);
	remove(fname);
	rename(temp, fname);
	printf(" Nalog radnika je deaktiviran ! \n");
	return 0;
}

int deaktiviranjeHR() {
	FILE* hr, * hr_temp;
	HR hrAccount;
	char temp_u[MAX], idChar[MAX], stanjeChar[MAX], linija[MAXF] = "";
	char opcija;
	int brLinija = 0;
	printf("Unesi username HR korisnika kome zelis promjeniti stanje naloga!\n");
	scanf("%s", temp_u);
	if ((hr = fopen("../Datoteke/HR.txt", "r")) != NULL)
		while (fscanf(hr, "%d %s %s %d", &hrAccount.id, hrAccount.userName, hrAccount.password, &hrAccount.stanje) != EOF)
		{
			brLinija++;
			if (strcmp(hrAccount.userName, temp_u) == 0)
			{
				hrAccount.stanje = 0;																						 // Konverujem int u string i spajam sve u jedan string 
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

				break;
			}
		}
	fclose(hr);
	if (hrAccount.stanje == 0)
		zamjena("../Datoteke/HR.txt", brLinija, linija);
	else
		printf("Nalog radnika je vec neaktivan!");
	opcija = _getch();

}

int deaktiviranjeKR() {
	FILE* kr, * kr_temp;
	KORISNIK krAccount;
	char temp_u[MAX], idChar[MAX], stanjeChar[MAX], danChar[MAX], mjesecChar[MAX], godinaChar[MAX], linija[MAXF] = "";
	char opcija;
	int brLinija = 0;
	printf("Unesi ime radnika kome zelis promjeniti stanje naloga!\n");
	scanf("%s", temp_u);
	if ((kr = fopen("../Datoteke/Korisnici.txt", "r")) != NULL)
		while (fscanf(kr, "%d %s %s %s %s %s %s %d %d %d %d", &krAccount.id, krAccount.userName, krAccount.password, krAccount.ime, krAccount.prezime, krAccount.radnoMjesto, krAccount.sektor, &krAccount.datum.dan, &krAccount.datum.mjesec, &krAccount.datum.godina, &krAccount.stanje) != EOF)
		{
			brLinija++;
			if (strcmp(krAccount.ime, temp_u) == 0)
			{
				krAccount.stanje = 0;																						 // Konverujem int u string i spajam sve u jedan string 
				_itoa(krAccount.id, idChar, 10);
				_itoa(krAccount.stanje, stanjeChar, 10);
				_itoa(krAccount.datum.dan, danChar, 10);
				_itoa(krAccount.datum.mjesec, mjesecChar, 10);
				_itoa(krAccount.datum.godina, godinaChar, 10);
				strcat(linija, idChar);
				strcat(linija, " ");
				strcat(linija, krAccount.userName);
				strcat(linija, " ");
				strcat(linija, krAccount.password);
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
				break;
			}
		}
	fclose(kr);
	if (krAccount.stanje == 0)
		zamjena("../Datoteke/Korisnici.txt", brLinija, linija);
	else
		printf("Nalog radnika je vec neaktivan!");
	opcija = _getch();

}