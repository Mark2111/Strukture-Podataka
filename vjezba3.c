#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define MINIMALNO_OSOBA (1)
#define NULA (0)

typedef struct Osoba* pokOsoba;

typedef struct Osoba
{
	char ime[20];
	char prezime[20];
	int godinaRodenja;
	pokOsoba next;
}OSOBA; 

pokOsoba alocirajOsobu();
void ispis();
void dodajNaPocetak(pokOsoba);
void unesiOsobu(pokOsoba);
void ispisiListu(pokOsoba);
void ispisiOsobu(pokOsoba);
void dodajNaKraj(pokOsoba);
void pretraziPoPrezimenu(pokOsoba);
void brisiElementNaPoziciji(pokOsoba);
int prebrojiListu(pokOsoba);
void brisiOsobu(pokOsoba);
void dodajIzaOdredenog(pokOsoba);
void dodajIspredOdredenog(pokOsoba);
void sortirajPoPrezimenu(pokOsoba);
void upisiUDatoteku(pokOsoba);

int main()
{
    pokOsoba head = alocirajOsobu();
    int check = 1;
    while (check){
        ispis();
        printf("Unesite odabir: ");
        scanf("%d", &check);

        switch (check)
        {
        case 1:
            dodajNaPocetak(head);
            break;
        case 2:
            ispisiListu(head);
            break;
        case 3:
            dodajNaKraj(head);
            break;
        case 4:
            pretraziPoPrezimenu(head);
            break;
        case 5:
            brisiElementNaPoziciji(head);
            break;
        case 6:
            dodajIzaOdredenog(head);
            break;
        case 7:
            dodajIspredOdredenog(head);
            break;
        case 8:
            sortirajPoPrezimenu(head);
            break;
        case 9:
            upisiUDatoteku(head);
            break;
        case 0:
            printf("\nBok !\n");
            break;
        default:
            printf("Unijeli ste krivi unos!\n");
            break;
        }
    }
}
pokOsoba alocirajOsobu()
{
    pokOsoba novaOsoba;
    novaOsoba = (pokOsoba)malloc(sizeof(OSOBA));
    strcpy(novaOsoba->ime, "");
    strcpy(novaOsoba->prezime, "");
    novaOsoba->godinaRodenja = 0;
    novaOsoba->next = NULL;
    return novaOsoba;
}
void unesiOsobu(pokOsoba novaOsoba)
{
    char buffer[20];
    printf("\nUnesite ime: ");
    scanf("%s", buffer);
    strcpy(novaOsoba->ime, buffer);

    printf("Unesite prezime: ");
    scanf("%s", buffer);
    strcpy(novaOsoba->prezime, buffer);

    printf("Unesite godinu rodenja: ");
    scanf("%d", &novaOsoba->godinaRodenja);
}
void dodajNaPocetak(pokOsoba head)
{
    pokOsoba novaOsoba = alocirajOsobu();
    unesiOsobu(novaOsoba);
    novaOsoba->next = head->next;
    head->next = novaOsoba;
    printf("\nUspjesno dodana osoba...\n");
}
void ispisiListu(pokOsoba head)
{
    if(head->next == NULL){
        printf("Lista je prazna!\n");
        return;
    }
    head = head->next;
    while (head->next != NULL){
        ispisiOsobu(head);
        head = head->next;
    }
    ispisiOsobu(head);
}
void ispisiOsobu(pokOsoba osoba)
{
    printf("\n\n------------------------------------------\n");
    printf("Ime: %s\n", osoba->ime);
    printf("Prezime: %s\n", osoba->prezime);
    printf("Godina rodenja: %d", osoba->godinaRodenja);
    printf("\n------------------------------------------\n\n");
}
void dodajNaKraj(pokOsoba head)
{
    while (head->next != NULL){
        head = head->next;
    }
    dodajNaPocetak(head);
}
void pretraziPoPrezimenu(pokOsoba head)
{
    bool check = false;
    char prez[20] = "";
    char buffer[20] = "";
    printf("Unesite prezime osobe: ");
    scanf("%s", prez);
    _strlwr(prez);
    if(head->next == NULL){
        printf("\nLista je prazna!\n");
        return;
    }

    while(head->next != NULL){
        head = head->next;
        strcpy(buffer, head->prezime);
        if(!strcmp(_strlwr(buffer), prez)){
            printf("\nPronadena je osoba:");
            ispisiOsobu(head);
            if(!check){
                check = !check;
            }
        }
    }

    if(!check){
        printf("\nNije pronadena osoba s unesenim prezimenom!\n");
    }
}
int prebrojiListu(pokOsoba head)
{
    int counter = 0;
    while(head->next != NULL){
        head = head->next;
        ++counter;
    }
    return counter;
}
void brisiOsobu(pokOsoba pozicija)
{
    pokOsoba buffer = alocirajOsobu();
    buffer = pozicija->next;
    pozicija->next = buffer->next;
    free(buffer);
    printf("\nOsoba je izbrisana!\n");
}
void brisiElementNaPoziciji(pokOsoba head)
{
    int brojClanova = prebrojiListu(head);
    int pozicija;
    printf("\nUnesite koji element zelite izbrisati: ");
    scanf("%d", &pozicija);

    if (pozicija > brojClanova){
        printf("\nIzabrali ste prevelik broj !\n");
        return;
    }
    else if (pozicija < MINIMALNO_OSOBA){
        printf("\nIzabrali ste premali broj !\n");
    }

    if (pozicija == MINIMALNO_OSOBA){
        brisiOsobu(head);
    }
    else if (pozicija == brojClanova){
        while (head->next->next != NULL){
            head = head->next;
        }
        brisiOsobu(head);
    }
    else{
        for(int i = NULA; i<pozicija;i++){
            head = head->next;
        }
        brisiOsobu(head);
    }
}
void ispis()
{
	printf("\n----------------------------------------\n");
	printf("1. Dodaj osobu na pocetak liste!\n");
	printf("2. Ispisi listu!\n");
	printf("3. Dodaj osobu na kraj liste!\n");
	printf("4. Pretrazi po prezimenu!\n");
	printf("5. Brisi element iz liste!\n");
    printf("6. Dodaj iza odredenog elementa!\n");
    printf("7. Dodaj ispred odredenog elementa!\n");
    printf("8. Sortiraj po prezimenu!\n");
    printf("9. Upisi listu u datoteku!\n");
	printf("0. Izlaz!\n");
	printf("\n----------------------------------------\n");
}
void dodajIzaOdredenog(pokOsoba head)
{
    int pozicija;
    int brojClanova = prebrojiListu(head);
    printf("\nNakon kojeg elementa zelite dodati osobu: ");
    scanf("%d", &pozicija);

    if (pozicija < 1 || pozicija > brojClanova){
        printf("\nOut of range !\n");
        return;
    }
    for(int i = NULA; i<pozicija; i++){
        head = head->next;
    }
    dodajNaPocetak(head);
}
void dodajIspredOdredenog(pokOsoba head)
{
    int pozicija;
    int brojClanova = prebrojiListu(head);
    printf("\nIspred kojeg elementa zelite dodati osobu: ");
    scanf("%d", &pozicija);

    if (pozicija < 1 || pozicija > brojClanova){
        printf("\nOut of range !\n");
        return;
    }
    for (int i=NULA; i<(pozicija-1); i++){
        head = head->next;
    }
    dodajNaPocetak(head);
}
void sortirajPoPrezimenu(pokOsoba head)
{
    if (head->next == NULL){
        printf("\nPrazna lista !\n");
        return;
    }
    pokOsoba j, prev_j, temp, end;

    end = NULL;
    while (head->next != end){
        prev_j = head;
        j = head->next;
        while(j->next != end){
            if(strcmp(j->prezime, j->next->prezime)>0){
                temp = j->next;
                prev_j->next = temp;
                j->next = temp->next;
                temp->next = j;

                j = temp;
            }
            prev_j = j;
            j = j->next;
        }
        end = j;
    }
}
void upisiUDatoteku(pokOsoba head)
{
    char buffer[20] = "";
    printf("Unesite naziv datoteke za zapis(max. 20 znakova): ");
    scanf("%s", buffer);

    if(head->next == NULL){
        printf("\nPrazna lista !\n");
        return;
    }

    FILE *f;
    f = fopen(buffer, "w");
    
    while(head->next != NULL){
        head = head->next;
	    fprintf(f, "\n\n------------------------------------------\n");
        fprintf(f, "\nIme: %s", head->ime);
    	fprintf(f, "\nPrezime: %s", head->prezime);
        fprintf(f, "\nGodina rodenja: %d", head->godinaRodenja);
        fprintf(f, "\n\n------------------------------------------\n");
    }
    fclose(f);
}
