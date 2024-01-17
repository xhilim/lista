#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<string.h>
#include "functions.h"

struct Person
{
    char* Lname;
    char* Name;
    int age;
    char* pesel;
    bool woman;
    struct Person* next;
    struct Person* prev;

};




int main() {
    struct Person* head = NULL;
    int choice = 0;
    int x = 0;
    char nLname[100];
    char nName[100];
    int nage;
   char npesel[12];
    int nwoman;

   

    do {
        // Wyświetlenie opcji menu
        printf("Menu:\n");
        printf("1. Dodaj osobe do listy\n");
        printf("2. Znajdz osobe z listy\n");
        printf("3. Usun osobe z listy 3\n");
        printf("4. Wyswietl liste\n");
        printf("5. Zapisz liste do pliku 1\n");
        printf("6. Wczytaj Liste z pliku i dodaj do aktualnej listy 2\n");
        printf("7. Posortuj liste\n");
        printf("8. Wyyczysc konsole\n");
        printf("9. Wyjście\n");
        printf("Wybierz opcję: ");

        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
    //        getchar();
            printf("Imie: ");
            scanf_s("%s", nName, 100);

            printf("Nazwisko: ");
            scanf_s("%s", nLname, 100);

            printf("Wiek: ");
            scanf_s("%d", &nage);

            printf("PESEL: ");
            scanf_s("%12s", npesel, 12);
            
            do
            {
                printf("Czy to kobieta? 1 -tak  2 - nie: ");
           
                scanf_s("%d", &nwoman);
            } while (nwoman != 1 && nwoman != 0);
            dodaj(&head,nLname,nName,nage,npesel,nwoman);
            break;
        case 2:
            printf("1 - po imieniu\n 2 - po nazwisku: ");

            scanf_s("%d", &x);
            znajdz(head,x);
            break;
        case 3:
            usun(&head);
            break;
        case 4:
            wyswietlListe(head);
            break;
        case 5:
            zapiszDoPliku(head);
            break;
        case 6:
            wczytajZPliku(&head);
            break;
        case 7:
            bubbleSort(head);
            break;
        case 8:
            system("cls");
        case 9:
            break;
        default:
            printf("Nieprawidłowy wybór. Wybierz ponownie.\n");
        }

    } while (choice != 9); // Pętla będzie działać dopóki użytkownik nie wybierze opcji "Wyjście (4)"
    zwolnij(&head);
    return 0;
}
