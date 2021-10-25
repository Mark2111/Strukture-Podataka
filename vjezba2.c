#define _CRT_SECURE_NO_WARNINGS
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

void dodajNaPocetakListe(pokOsoba);

void dodajNaKrajListe(pokOsoba);

void dodaj(pokOsoba);

void unesiOsobu(pokOsoba);

void ispisiListu(pokOsoba);

void ispisiOsobu(pokOsoba);

void brisanjeOsobeSaPozicije(pokOsoba, int);

void brisiOsobu(pokOsoba);

int prebrojiOsobe(pokOsoba);

void pretraziPoPrezimenu(pokOsoba, char*);

void ispis();

int main()
{
	pokOsoba head = alocirajOsobu();
	int check = 1, pozicija = 0;
	char prezime[20] = "";

	while (check)
	{
		ispis();
		printf("Unesite broj: ");
		scanf("%d", &check);

		switch (check)
		{
		case 1:
			dodajNaPocetakListe(head);
			break;
		case 2:
			dodajNaKrajListe(head);
			break;
		case 3:
			printf("Unesite poziciju: ");
			scanf("%d", &pozicija);
			brisanjeOsobeSaPozicije(head, pozicija);
			break;
		case 4:
			ispisiListu(head);
			break;
		case 5:
			printf("Unesite prezime osobe: ");
			scanf("%s", prezime);
			pretraziPoPrezimenu(head, prezime);
			break;
		case 0:
			printf("\nDovidenja!\n");
			break;
		default:
			printf("Unijeli ste krivi unos!\n");
			break;
		}
	}
	return 0;
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

void dodajNaPocetakListe(pokOsoba head)
{
	dodaj(head);
}

void dodaj(pokOsoba head)
{
	pokOsoba novaOsoba = alocirajOsobu();
	unesiOsobu(novaOsoba);
	novaOsoba->next = head->next;
	head->next = novaOsoba;
	printf("\nUspjesno dodana osoba...\n");
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

void ispisiListu(pokOsoba head)
{
	if (head->next == NULL)
	{
		printf("Lista je prazna!\n");
		return;
	}

	head = head->next;
	while (head->next != NULL)
	{
		ispisiOsobu(head);
		head = head->next;
	}
	ispisiOsobu(head);
}

void ispisiOsobu(pokOsoba osoba)
{
	printf("\n\n------------------------------------------\n");
	printf("\nIme: %s", osoba->ime);
	printf("\nPrezime: %s", osoba->prezime);
	printf("\nGodina rodenja: %d", osoba->godinaRodenja);
	printf("\n------------------------------------------\n\n");
}

void dodajNaKrajListe(pokOsoba head)
{
	while (head->next != NULL)
	{
		head = head->next;
	}
	dodaj(head);
}

void brisanjeOsobeSaPozicije(pokOsoba head, int pozicija)
{
	int brojOsoba = prebrojiOsobe(head);
	
	if (pozicija > brojOsoba)
	{
		printf("\nIzabrali ste prevelik broj!\n");
		return;
	}
	else if (pozicija < MINIMALNO_OSOBA)
	{
		printf("\nIzabrali ste premali broj!\n");
		return;
	}
	
	if (pozicija == MINIMALNO_OSOBA)
	{
		brisiOsobu(head);
	}
	else if (pozicija == brojOsoba)
	{
		while (head->next->next != NULL)
		{
			head = head->next;
		}
		brisiOsobu(head);
	}
	else
	{
		for (int i = NULA; i < pozicija; i++)
		{
			head = head->next;
		}
		brisiOsobu(head);
	}

}

void brisiOsobu(pokOsoba pozicija)
{
	pokOsoba buffer = alocirajOsobu();
	buffer = pozicija->next;
	pozicija->next = buffer->next;
	free(buffer);
	printf("\nOsoba je izbrisana!\n");
}

int prebrojiOsobe(pokOsoba head)
{
	int brojac = 0;
	
	while (head->next != NULL)
	{
		head = head->next;
		++brojac;
	}

	return brojac;
}

void pretraziPoPrezimenu(pokOsoba head, char* prezime)
{
	bool check = false;
	char buffer1[20] = "";
	char buffer2[20] = "";
	strcpy(buffer1, prezime);
	_strlwr(buffer1);

	if (head->next == NULL)
	{
		printf("\nLista je prazna!\n");
		return;
	}

	while (head->next != NULL)
	{
		head = head->next;
		strcpy(buffer2, head->prezime);
		if (!strcmp(_strlwr(buffer2), buffer1))
		{
			printf("\nPronadena je osoba:");
			ispisiOsobu(head);
			if (!check)
			{
				check = !check;
			}
		}
	}

	if (!check)
	{
		printf("\nNije pronadena osoba s tim prezimenom!\n");
	}
}

void ispis()
{
	printf("\n----------------------------------------\n");
	printf("1. Dodaj osobu na pocetak liste!\n");
	printf("2. Dodaj osobu na kraj liste!\n");
	printf("3. Izbrisi osobu na tocnoj poziciji!\n");
	printf("4. Ispisi listu!\n");
	printf("5. Pretrazi osobe po prezimenu!\n");
	printf("0. Izlaz!\n");
	printf("\n----------------------------------------\n");
}