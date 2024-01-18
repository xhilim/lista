#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include <string.h>
#include <ctype.h>

struct Person
{
	 char* Lname;
	 char* Name;
	int age;
	char  *pesel;
	bool woman;
	struct Person* next;
	struct Person* prev;

};

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include <string.h>
#include <ctype.h>

struct Person
{
	 char* Lname;
	 char* Name;
	int age;
	char  *pesel;
	bool woman;
	struct Person* next;
	struct Person* prev;

};



void dodaj(struct Person** head, const char nLname[], const char nName[], int nage, char npesel[], bool woman)
{
	struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));

	if (newPerson == NULL) {
		printf("blad pamiec.\n");
		exit(EXIT_FAILURE);
	}

	// Alokacja pamięci i kopiowanie ciągów znaków
	newPerson->Lname = _strdup(nLname);
	newPerson->Name = _strdup(nName);
	newPerson->pesel = _strdup(npesel);

	if (newPerson->Lname == NULL || newPerson->Name == NULL) {
		printf("blad pamieci.\n");
		exit(EXIT_FAILURE);
	}

	// Ustawianie reszty pól struktury
	newPerson->age = nage;
	newPerson->woman = woman;
	newPerson->next = NULL;
	newPerson->prev = NULL;

	// Dodawanie do listy
	if (*head == NULL) {
		// Lista jest pusta, nowy element staje się głową listy
		*head = newPerson;
	}
	else {
		// Lista nie jest pusta, szukamy ostatniego elementu i dodajemy nowy element na koniec
		struct Person* current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newPerson;
		newPerson->prev = current;
	}
}


void zwolnij(struct Person** head) {
	struct Person* current = *head;
	struct Person* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}


void wyswietlListe(struct Person* head) {
	struct Person* current = head;
	
	int x=0;
	printf("od przodu -1\n od tylu -2: ");
	scanf_s("%d", &x);
	if (x == 1)
	{
		while (current != NULL) {
			wyswietlElement(current);
			current = current->next;
		}
		return;
	}
	while (current->next != NULL) {
		current = current->next;
	}

	do
	{
		wyswietlElement(current);
		current = current->prev;
	} while (current != NULL);
}


void znajdz(struct Person* head,int x) {
	struct Person* current = head;

	char data[100];

	if (head == NULL) {
		printf("List is empty. Cannot search in an empty list.\n");
		return;
	}
	if (x == 1)
	{
		printf("imie: ");
	}
	else
	{
		printf("Nazwisko: ");
	}
	scanf_s("%s", data, 100);
	while (current != NULL) {
		const char* targetValue = (x == 1) ? current->Name : current->Lname;

		if (targetValue != NULL && strcmp(targetValue, data) == 0) {

			wyswietlElement(current);
		}

		current = current->next;
	}
}

void wyswietlElement(struct Person* person)
{
	printf("Name: %s, Last Name: %s, Age: %d, Pesel: %s, Gender: %s\n",
		person->Name, person->Lname, person->age, person->pesel,
		person->woman ? "Kobieta" : "Mezczyzna");
}


void usun(struct Person** head) {
	if (*head == NULL) {
		printf("pusto\n");
		return;
	}

	char lname[100];
	printf("Podaj nazwisko: ");
	scanf_s("%s", lname, 100);

	struct Person* current = *head;

	while (current != NULL && strcmp(current->Lname, lname) != 0) {
		current = current->next;
	}

	if (current == NULL) {
		printf("Nie ma podanej osoby na liste.\n", lname);
		return;
	}

	if (current->prev != NULL) {
		current->prev->next = current->next;
	}
	else {
		*head = current->next; // Zaktualizuj wskaźnik na głowę listy
	}

	if (current->next != NULL) {
		current->next->prev = current->prev;
	}

	// Zwolnienie pamięci zaalokowanej na strukturę
	free(current);
}


void zapiszDoPliku(struct Person* head) {
	char nazwaPliku[100];
	FILE* plik;
	int wynik;

	printf("Podaj nazwe pliku do zapisu: ");
	wynik = scanf_s("%s", nazwaPliku, sizeof(nazwaPliku));

	if (wynik != 1) {
		printf("Blad wczytywania nazwy pliku.\n");
		return;
	}

	wynik = fopen_s(&plik, nazwaPliku, "w");


	struct Person* current = head;

	while (current != NULL) {
		fprintf(plik, "%s %s %d %s %s\n", current->Name, current->Lname, current->age, current->pesel, current->woman ? "Kovieta" : "Mezczyzna");
		current = current->next;
	}

	fclose(plik);
	printf("Dane zostaly zapisane do pliku %s.\n", nazwaPliku);
}

void wczytajZPliku(struct Person** head) {
	int choice = 0;
	int x = 0;
	char nLname[100];
	char nName[100];
	int nage = 0;
	char npesel[12];
	bool nwoman;
	FILE* plik;
	char kob[100], file[100];

	printf("Podaj nazwe pliku: ");
	scanf_s("%s", file, 100);

	errno_t lol = fopen_s(&plik, file, "r");

	if (lol != 0 || plik == NULL) {
		printf("Nie udalo sie otworzyc pliku.\n");
		return;
	}

	while (fscanf_s(plik, "%99s %99s %d %12s %99s", nLname, 100, nName, 100, &nage, npesel,12, kob, 100) != EOF)
	{
		if (strcmp(kob, "Kobieta") == 0)
			nwoman = true;
		else
			nwoman = false;

		dodaj(head, _strdup(nLname), _strdup(nName), nage, _strdup(npesel), nwoman);
	}

	fclose(plik);
}

void swap(struct Person* a, struct Person* b)
{
	char* tempLname = a->Lname;
	char* tempName = a->Name;
	int tempAge = a->age;
	char* tempPesel = a->pesel;
	bool tempWoman = a->woman;

	a->Lname = b->Lname;
	a->Name = b->Name;
	a->age = b->age;
	a->pesel = b->pesel;
	a->woman = b->woman;

	b->Lname = tempLname;
	b->Name = tempName;
	b->age = tempAge;
	b->pesel = tempPesel;
	b->woman = tempWoman;
}


void bubbleSort(struct Person* start)
{
	int swapped;
	struct Person* ptr1;
	struct Person* lptr = NULL;

	if (start == NULL)
	{
		return;
		printf("pusto\n");
	}
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			// Porównanie elementów na podstawie nazwiska (Lname)
			if (strcasecmp(ptr1->Lname, ptr1->next->Lname) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	printf("posortowano\n");
}
int strcasecmp(const char* s1, const char* s2)
{
	while (*s1 && *s2)
	{
		int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
		if (diff != 0)
			return diff;
		s1++;
		s2++;
	}
	return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}


void dodaj(struct Person** head, const char nLname[], const char nName[], int nage, char npesel[], bool woman)
{
	struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));

	if (newPerson == NULL) {
		printf("blad pamiec.\n");
		exit(EXIT_FAILURE);
	}

	// Alokacja pamięci i kopiowanie ciągów znaków
	newPerson->Lname = _strdup(nLname);
	newPerson->Name = _strdup(nName);
	newPerson->pesel = _strdup(npesel);

	if (newPerson->Lname == NULL || newPerson->Name == NULL) {
		printf("blad pamieci.\n");
		exit(EXIT_FAILURE);
	}

	// Ustawianie reszty pól struktury
	newPerson->age = nage;
	newPerson->woman = woman;
	newPerson->next = NULL;
	newPerson->prev = NULL;

	// Dodawanie do listy
	if (*head == NULL) {
		// Lista jest pusta, nowy element staje się głową listy
		*head = newPerson;
	}
	else {
		// Lista nie jest pusta, szukamy ostatniego elementu i dodajemy nowy element na koniec
		struct Person* current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newPerson;
		newPerson->prev = current;
	}
}


void zwolnij(struct Person** head) {
	struct Person* current = *head;
	struct Person* next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
}


void wyswietlListe(struct Person* head) {
	struct Person* current = head;
	
	int x=0;
	printf("od przodu -1\n od tylu -2: ");
	scanf_s("%d", &x);
	if (x == 1)
	{
		while (current != NULL) {
			wyswietlElement(current);
			current = current->next;
		}
		return;
	}
	while (current->next != NULL) {
		current = current->next;
	}

	do
	{
		wyswietlElement(current);
		current = current->prev;
	} while (current != NULL);
}


void znajdz(struct Person* head,int x) {
	struct Person* current = head;

	char data[100];

	if (head == NULL) {
		printf("List is empty. Cannot search in an empty list.\n");
		return;
	}
	if (x == 1)
	{
		printf("imie: ");
	}
	else
	{
		printf("Nazwisko: ");
	}
	scanf_s("%s", data, 100);
	while (current != NULL) {
		const char* targetValue = (x == 1) ? current->Name : current->Lname;

		if (targetValue != NULL && strcmp(targetValue, data) == 0) {

			wyswietlElement(current);
		}

		current = current->next;
	}
}

void wyswietlElement(struct Person* person)
{
	printf("Name: %s, Last Name: %s, Age: %d, Pesel: %s, Gender: %s\n",
		person->Name, person->Lname, person->age, person->pesel,
		person->woman ? "Kobieta" : "Mezczyzna");
}


void usun(struct Person** head) {
	if (*head == NULL) {
		printf("pusto\n");
		return;
	}

	char lname[100];
	printf("Podaj nazwisko: ");
	scanf_s("%s", lname, 100);

	struct Person* current = *head;

	while (current != NULL && strcmp(current->Lname, lname) != 0) {
		current = current->next;
	}

	if (current == NULL) {
		printf("Nie ma podanej osoby na liste.\n", lname);
		return;
	}

	if (current->prev != NULL) {
		current->prev->next = current->next;
	}
	else {
		*head = current->next; // Zaktualizuj wskaźnik na głowę listy
	}

	if (current->next != NULL) {
		current->next->prev = current->prev;
	}

	// Zwolnienie pamięci zaalokowanej na strukturę
	free(current);
}


void zapiszDoPliku(struct Person* head) {
	char nazwaPliku[100];
	FILE* plik;
	int wynik;

	printf("Podaj nazwe pliku do zapisu: ");
	wynik = scanf_s("%s", nazwaPliku, sizeof(nazwaPliku));

	if (wynik != 1) {
		printf("Blad wczytywania nazwy pliku.\n");
		return;
	}

	wynik = fopen_s(&plik, nazwaPliku, "w");

	if (wynik != 0 || plik == NULL) {
		printf("Nie udalo sie otworzyc pliku do zapisu.\n");
		return;
	}

	struct Person* current = head;

	while (current != NULL) {
		current = current->next;
	}

	fclose(plik);
	printf("Dane zostaly zapisane do pliku %s.\n", nazwaPliku);
}

void wczytajZPliku(struct Person** head) {
	int choice = 0;
	int x = 0;
	char nLname[100];
	char nName[100];
	int nage = 0;
	char npesel[12];
	bool nwoman;
	FILE* plik;
	char kob[100], file[100];

	printf("Podaj nazwe pliku: ");
	scanf_s("%s", file, 100);

	errno_t lol = fopen_s(&plik, file, "r");

	if (lol != 0 || plik == NULL) {
		printf("Nie udalo sie otworzyc pliku.\n");
		return;
	}

	while (fscanf_s(plik, "%99s %99s %d %12s %99s", nLname, 100, nName, 100, &nage, npesel,12, kob, 100) != EOF)
	{
		if (strcmp(kob, "Kobieta") == 0)
			nwoman = true;
		else
			nwoman = false;

		dodaj(head, _strdup(nLname), _strdup(nName), nage, _strdup(npesel), nwoman);
	}

	fclose(plik);
}

void swap(struct Person* a, struct Person* b)
{
	char* tempLname = a->Lname;
	char* tempName = a->Name;
	int tempAge = a->age;
	char* tempPesel = a->pesel;
	bool tempWoman = a->woman;

	a->Lname = b->Lname;
	a->Name = b->Name;
	a->age = b->age;
	a->pesel = b->pesel;
	a->woman = b->woman;

	b->Lname = tempLname;
	b->Name = tempName;
	b->age = tempAge;
	b->pesel = tempPesel;
	b->woman = tempWoman;
}


void bubbleSort(struct Person* start)
{
	int swapped;
	struct Person* ptr1;
	struct Person* lptr = NULL;

	if (start == NULL)
	{
		return;
		printf("pusto\n");
	}
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			// Porównanie elementów na podstawie nazwiska (Lname)
			if (strcasecmp(ptr1->Lname, ptr1->next->Lname) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);

	printf("posortowano\n");
}
int strcasecmp(const char* s1, const char* s2)
{
	while (*s1 && *s2)
	{
		int diff = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
		if (diff != 0)
			return diff;
		s1++;
		s2++;
	}
	return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
