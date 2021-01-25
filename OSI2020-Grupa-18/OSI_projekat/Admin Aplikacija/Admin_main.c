#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"Admin_funkcije.h"
#include"Admin_meni.h"

int main() {
	printf("%d", citanjeFlaga());
	provjeraMenia();
	glavniMeni();
	odabirOpcije();


	return 0;
}
