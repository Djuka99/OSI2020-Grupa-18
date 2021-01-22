#pragma once
#include<stdio.h>
#include<stdlib.h>

#include<Windows.h>
#include "AdminAppFunctions.h"
#define _CRT_SECURE_NO_WARNINGS



void Admin_SignIn_Menu() {
	printf("...................................................................\n");
	printf("\t\tLOGIN!\n");
	printf("...................................................................\n");

	Admin_SignIn();
}

void AdminApp_MainMenu() {
	system("cls");
	printf("...................................................................\n");
	printf("                       WELCOME ADMIN!\n");
	printf("...................................................................\n\n\n");
	printf("                  \nWhat u want to do in app?\n");
	printf("       1. Create HR account.\n");
	printf("       2. Activate or Deactivate HR and User accounts.\n");

}

void CreateHrAccount_Menu() {
	printf("...................................................................\n");
	printf("                Creating Human Resources Account\n");
	printf("...................................................................\n\n\n");
	//Creating_HR_Accounts();
	printf("\n\nTo back on Main Menu press M or E for Exit!");

}

void ActivateOrDeactivate_Menu() {
	printf("...................................................................\n");
	printf("          User and HR account activation and deactivation\n");
	printf("...................................................................\n\n\n");
	printf("Which accounts you want to work with:\n");
	printf("\t1: With User accounts?\n");
	printf("\t2: With HR accounts?\n");
	
	printf("\n\nTo back on Main Menu press M or E for Exit!\n");

}

void User_Accounts_ActivatonAndDeactivation_Menu() {
	printf("...................................................................\n");
	printf("           User account activation and deactivation\n");
	printf("...................................................................\n\n\n");
	//User_Accounts_ActivatonAndDeactivation();
	printf("\n\nTo back on Main Menu press M or E for Exit!\n");

}

void HR_Accounts_ActivatonAndDeactivation_Menu() {
	printf("...................................................................\n");
	printf("           HR account activation and deactivation\n");
	printf("...................................................................\n\n\n");
	//HR_Accounts_ActivatonAndDeactivation();
	printf("\n\nTo back on Main Menu press M or E for Exit!");

}

void ActivationAndDeactivation_Selection() {
	int selection;

	while (1) {

		selection = getchar();

		while (selection != 1 && selection != 2) {
			printf("Incorect input! Try agin!\n");
			selection = getchar();
		}
		switch (selection) {
		case '1':
			system("cls");
			//User_Accounts_ActivatonAndDeactivation_Menu(); break;
		case '2':
			system("cls");
			//HR_Accounts_ActivatonAndDeactivation_Menu(); break;
		default: break;



		}
	}
}
