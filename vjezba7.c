#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct direktorij* dir;
typedef struct direktorij
{
	char name[30];
	dir sibling;
	dir child;
}DIREKTORIJ;

typedef struct stack* st;
typedef struct stack
{
	dir element;
	st next;
}STACK;

st alociraj_stack();
void push(st, dir);
dir pop(st head);
dir cdParentDir(dir, st);

dir alociraj_direktorij();
dir insert(dir, dir);
void ispis_izbora();
void makedirectory(dir);
int listdirs(dir);
dir changedir(dir, st);

int delStack(st);
int delDir(dir);

int main()
{
	dir headC = alociraj_direktorij();
	strcpy(headC->name, "C:");

	st headStack = alociraj_stack();

	int c = 0;
	dir pok = headC;
	printf("Path:  C:\n/");
	while (c != 5) {
		ispis_izbora();
		scanf("%d", &c);
		printf("\n");
		switch (c)
		{
		case 1: //md
			makedirectory(pok);
			break;
		case 2: //cd dir
			pok = changedir(pok, headStack);
			break;
		case 3:  //cd ..
			pok = cdParentDir(pok, headStack);
			break;
		case 4: // dir
			if (listdirs(pok->child) == 0) {
				printf("\nSuccessfully printed dir content !\n\n");
			}
			break;
		case 5: // izlaz //prekid while petlje
			break;
		default:
			printf("Pogresan unos !\n\n");
			c = 0;
			continue;
		}
	}
	// Izlaz iz programa 



	return 0;
}

dir alociraj_direktorij()
{
	dir novi_direktorij = (dir)malloc(sizeof(DIREKTORIJ));
	if (novi_direktorij == NULL) {
		printf("\nMemory allocation failed !\n\n");
		return NULL;
	}
	strcpy(novi_direktorij->name, "");
	novi_direktorij->sibling = NULL;
	novi_direktorij->child = NULL;
	return novi_direktorij;
}
dir insert(dir current, dir q)
{
	if (current == NULL) {
		return q;
	}
	if (strcmp(current->name, q->name) > 0) {
		q->sibling = current;
		return q;
	}
	else if (strcmp(current->name, q->name) < 0) {
		current->sibling = insert(current->sibling, q);
	}
	else {
		printf("Directory already exists !");
		free(q);
	}
	return current;
}
void ispis_izbora()
{
	printf("-----Unesite redni broj naredbe-----\n");
	printf("1. md (napravi direktorij)\n");
	printf("2. cd dir (Ulazak u odredeni direktorij)\n");
	printf("3. cd.. (Enter parent directory)\n");
	printf("4. dir (ispis svih direktorija)\n");
	printf("5. Izlaz (Napustite program)\n");
	printf("-------------------------------------\n");
	printf("Naredba:     ");
}
void makedirectory(dir pozicija)
{
	dir novi = alociraj_direktorij();
	char ime[30] = { 0 };
	printf("Unesite ime novog direktorija(max 30 znakova):  ");
	scanf("%30s", ime);

	strcpy(novi->name, ime);
	pozicija->child = insert(pozicija->child, novi);

	printf("\nSuccessfully added folder !\n\n");
}
int listdirs(dir pozicija)
{
	if (pozicija == NULL) {
		printf("\nDirectory empty !\n\n");
		return 0;
	}
	printf("\n-----Dirs-----\n\n");
	printf("--Name--\n");
	while (pozicija->sibling != NULL) {
		printf("%s\n", pozicija->name);
		pozicija = pozicija->sibling;
	}
	printf("%s\n\n", pozicija->name);
	return 0;
}
st alociraj_stack()
{
	st novi = (st)malloc(sizeof(STACK));
	if (novi == NULL) {
		printf("\nMemory allocation failed !\n\n");
		return NULL;
	}
	novi->element = alociraj_direktorij();
	novi->next = NULL;
	return novi;
}
void push(st head, dir element)
{
	st novi_stack = alociraj_stack();
	novi_stack->element = element;
	
	novi_stack->next = head->next;
	head->next = novi_stack;
}
dir pop(st head)
{
	if (head->next == NULL) {
		printf("\nStack empty !\n\n");
		return NULL;
	}
	st temp = head->next;
	head->next = temp->next;
	dir tempdir = temp->element;
	free(temp);
	return tempdir;
}
dir changedir(dir pok, st headStack)
{

	dir temp = pok->child;
	char ime[30] = { 0 };
	printf("Unesite ime direktorija u koji zelite uci:  ");
	scanf("%30s", ime);

	if (temp == NULL) {
		printf("\nEmpty directory !\n\n");
		return pok;
	}
	while (temp != NULL) {
		if (strcmp(ime, temp->name) == 0) {
			push(headStack, pok);
			printf("\nChanged directory !\n\n");
			return temp;
		}
		temp = temp->sibling;
	}
	printf("\nDirectory not found !\n\n");
	return pok;
}
dir cdParentDir(dir pok, st headStack)
{
	if (headStack->next == NULL) {
		printf("\nStack empty !\nThis is root directory !\n\n");
		return pok;
	}
	printf("\nOpened parent dir !\n\n");
	pok = pop(headStack);
	return pok;
}