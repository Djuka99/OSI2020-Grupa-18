#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX 15




typedef struct admin {
	char user_name[MAX], password[MAX];
	short attempts;
}ADMIN;

typedef struct hr_account {
	char user_name[MAX], password[MAX];
	int id;
}HR_ACC;

typedef struct flag {
	int activate, deactivate;
}FLAG;


int Admin_SignIn();
int Enter_Admin_Data();
//int Creating_HR_Accounts();
//int User_Accounts_ActivatonAndDeactivation();
//int HR_Accounts_ActivatonAndDeactivation();

int Enter_Admin_Data() {

	FILE* Datoteke;

	char user_name_temp[MAX], password_temp[MAX], temp;

	ADMIN admin;

	for (int i = 0; i < MAX; i++)
		admin.password[i] = 0;

	printf("Username: "); scanf("%s", admin.user_name);


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


	if ((Datoteke = fopen("C..\Datoteke\Administrator.txt", "r")) != NULL) {
		while (fscanf(Datoteke, "%s %s", user_name_temp, password_temp) != EOF)
			if (strcmp(user_name_temp, admin.user_name) == 0 && strcmp(password_temp, admin.password) == 0)
				return 1;
		fclose(Datoteke);

	}
	else
		printf("EROR: Failed to open Admin_log file!\n");
	

	return 0;
}

int Admin_SignIn() {

	char option;
	int attempts=3;										//Number of attempts

	while (attempts && !Enter_Admin_Data()) {
		--attempts;
		printf("Wrong username or password!\n");
		printf("Press T to try agin or E for exit!\n");
		scanf("%c", &option);

		while (option != 't' || option != 'T' && option != 'e' || option != 'E') {
			printf("Non - existent option!\nTry agin!\n");
			scanf("%c", &option);
		}

		if (option == 'e' || option == 'E')
			exit(1);
		else if (option == 't' || option == 'T') {
			printf("Remaining attempts: %d", attempts);
			continue;

		}

	}
	if (attempts == 0)
	{
		printf("Your account has been blocked for 1 hour!");
		do
		{
			printf("Press E for exit!");
			option = getchar();
		} while (option != 'e' && option != 'E');
	}
}











