#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

struct Person
{
	char* Forname;
	char* Name;
	int wiek;
	long int pesel;
	bool woman;
	int* next;
	int* prev;

};


int main()
{
	int option = getchar();

	do
	switch (option)
	{
	case '1':
		dodaj();
		break;
	case '2':
		znajdz();
		break;
	case '3':
		usun();
		break;
	case '4':
		wyswietl();
		break;
	case '5':
		wczytaj();
		break;
	case '6':
		zapisz();
		break;
	case '7':
		sortuj();
		break;
	case '8':
		chujwieco();
		break;
	default:
		break;
	}
	while (true);
}

new int 12;





