#ifndef FUNCTIONS
#define FUNCTIONS
void dodaj(struct Person** head, const char nLname[], const char nName[], int nage, char npesel[], bool woman);
void zwolnij(struct Person** head);

void wyswietlListe(struct Person* head);

void wyswietlElement(struct Person* person);

void znajdz(struct Person* head,int x);
void usun(struct Person** head);

void zapiszDoPliku(struct Person* head);
void wczytajZPliku(struct Person** head);
void swap(struct Person* a, struct Person* b);
void bubbleSort(struct Person* start);
int strcasecmp(const char* s1, const char* s2);

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

#endif // FUNCTIONS
