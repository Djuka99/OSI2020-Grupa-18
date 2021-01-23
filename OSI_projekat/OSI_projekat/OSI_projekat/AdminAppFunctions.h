#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX 20
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>


typedef struct admin {
	char userName[MAX], password[MAX];
}ADMIN;

typedef struct HR {
	char userName[MAX], password[MAX];
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
			scanf("%s", c);
		} while (c != 'e' && c != 'E');
	}
}

int provjeraPostojanja(char name, char password) {
	FILE* hracc;
	char temp_username[MAX], temp_password[MAX];

	if ((hracc = fopen("../Datoteke/HR.txt", "r")) != NULL) {
		while (fscanf(hracc, "%s %s", temp_username, temp_password) != EOF)
			if (strstr(hracc, name) == 0 && strstr(hracc, password) == 0)
				return 1;
			else
				return 0;
		fclose(hracc);
	}
}

int brojacNaloga() {
	FILE* hraccc;
	int brojac = 1;
	char c;
	for (c = getc(hraccc); c != EOF; c = getc(hraccc))
		if (c == '\n')
			brojac++;
	return brojac;
}


int kreiranjeHR() {
	FILE* hr;
	HR hrAccount;

	for (int i = 0; i < MAX; i++)
		hrAccount.password[i] = 0;

	printf("Unesi ime novog clana: "); scanf("%s", hrAccount.userName);
	printf("Unesi lozinku novog clana: "); scanf("%s", hrAccount.password);

	if ((hr = fopen("../Datoteke/HR.txt", "w+")) != NULL)
		fprintf(hr, "%s %s", hrAccount.userName, hrAccount.password);
	else
		printf("Nije moguce otvoriti HR datoteku!\n");
	fclose(hr);





}