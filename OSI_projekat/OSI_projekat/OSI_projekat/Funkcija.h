#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#define MAXF 1000
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
			scanf("%s", c[0]);
		} while (c[0] != 'e' && c[0] != 'E');
	}
}



int brojacNaloga() {
	FILE* hr;
	int brojac = 0;
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
	HR hrAccount;
	char temp;
	int b = brojacNaloga();
	int stanjeRadnika = 1;                           //Za aktivne radnike 1, neaktivne 0

	for (int i = 0; i < MAX; i++)
		hrAccount.password[i] = 0;

	printf("Unesi ime novog clana: "); scanf("%s", hrAccount.userName);
	printf("Unesi lozinku novog clana: "); scanf("%s", hrAccount.password);

	if ((hr = fopen("../Datoteke/HR.txt", "a")) != NULL)
		fprintf(hr, "%d %s %s %d \n", b + 1, hrAccount.userName, hrAccount.password, stanjeRadnika);
	else
		printf("Nije moguce otvoriti HR datoteku!\n");
	fclose(hr);

}
int zamjena(char* fname, int brLinije, char* novaLinija)
{
	FILE* fptr1, * fptr2;
	int  linectr = 0;
	char str[MAX];
	char temp[] = "temp.txt";

	fptr1 = fopen(fname, "r");
	if (!fptr1)
	{
		printf("Unable to open the input file!!\n");
		return 0;
	}
	fptr2 = fopen(temp, "w");
	if (!fptr2)
	{
		printf("Unable to open a temporary file to write!!\n");
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
	printf("\n\n\n\n\nNalog je deaktiviran! \n");
	return 0;
}

int deaktiviranjeHR() {
	FILE* hr, * hr_temp;
	HR hrAccount;
	char temp_u[MAX], idChar[MAX], stanjeChar[MAX], linija[MAXF] = "";
	char opcija;
	int brLinija = 0;
	printf("Unesi ime radnika kome zelis promjeniti stanje naloga!\n");
	printf("Ime radnika: ");
	scanf("%s", temp_u);
	if ((hr = fopen("../Datoteke/HR.txt", "r")) != NULL)
		while (fscanf(hr, "%d %s %s %d", &hrAccount.id, hrAccount.userName, hrAccount.password, &hrAccount.stanje) != EOF)
		{
			brLinija++;
			if (strcmp(hrAccount.userName, temp_u) == 0)
			{
				hrAccount.stanje = 0;
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
				printf("Nalog ovog radnika je ");
				if (hrAccount.stanje == 0)
					printf("aktivan!\n");
				else
					printf("neaktivan!\n");
				break;
			}
		}
	fclose(hr);
	zamjena("../Datoteke/HR.txt", brLinija, linija);
	printf("Ukoliko zelite da deaktivirate nalog pritisnite Y!\n");
	opcija = _getch();




}