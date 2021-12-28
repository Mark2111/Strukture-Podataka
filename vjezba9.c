#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define BUFFER (50)

typedef struct cvor* node;
typedef struct cvor
{
	int value;
	node left;
	node right;
}CVOR;

typedef struct lista* lis;
typedef struct lista
{
	int value;
	lis next;
}LISTA;

lis alociraj_list(int);
void push(lis, int);
int pop(lis);

node alociraj_cvor(int);
void ispis();
node insert(node, node);
int replace(node);
void inorder_ispis(node);

void writetolist(node, lis);
void printtofile(lis, char [BUFFER]);

int main()
{
	int c = 0, temp = 0;
	node root = NULL;
	lis head = alociraj_list(0);
	
	while (c != 6) {
		ispis();
		scanf("%d", &c);
		switch (c)
		{
		case 1:
			printf("Unesite element:  ");
			scanf("%d", &temp);
			node q = alociraj_cvor(temp);
			root = insert(root, q);
			printf("\n");
			break;
		case 2:
			printf("\nReplacing tree with sum of elements...\n\n");
			root->value = replace(root);
			printf("\nReplaced !\n");
			break;
		case 3:
			printf("\nInput num of numbers in tree:  ");
			int size;
			scanf("%d", &size);
			printf("\n");
			printf("\nRandom numbers insert into tree...\n\n");
			srand(time(0));
			for (int i = 0; i < size; i++) {
				node qu = alociraj_cvor(rand() % 80 + 10);
				root = insert(root, qu);
			}
			break;
		case 4:
			printf("\nInorder ispis !\n\n");
			inorder_ispis(root);
			printf("\n");
			break;
		case 5:
			printf("\nPrinting tree to file (inorder)...\n\n");
			char name[BUFFER];
			printf("Enter file name:  ");
			scanf(" %50s", name);
			writetolist(root, head);
			printtofile(head, name);
			break;
		case 6:
			c = 6;
			break;
		default:
			printf("\nPogresan unos !\n\n");
			c = 0;
			continue;
		}
	}
	printf("\nBye Bye !\n\n");

	return 0;
}
node alociraj_cvor(int val)
{
	node noviCvor = (node)malloc(sizeof(CVOR));
	noviCvor->value = val;
	noviCvor->left = NULL;
	noviCvor->right = NULL;
	return noviCvor;
}
void ispis()
{
	printf("----------------Izbornik----------------\n");
	printf("--1--  Insert number\n");
	printf("--2--  Replace tree\n");
	printf("--3--  Random tree\n");
	printf("--4--  Print tree inorder\n");
	printf("--5--  Print replaced tree into folder\n");
	printf("--6--  Exit\n");
	printf("-----------------------------------------\n");
	printf("Unesite opciju:   ");
}
node insert(node current, node q)
{
	if (current == NULL) {
		return q;
	}
	if (current->value > q->value) {
		current->right = insert(current->right, q);
	}
	else {
		current->left = insert(current->left, q);
	}
	return current;
}
int replace(node root)
{
	if (root == NULL) {
		return 0;
	}
	int temp = root->value;
	root->value = replace(root->left) + replace(root->right);

	return root->value + temp;

}
void inorder_ispis(node head)
{
	if (head == NULL) {
		return;
	}
	inorder_ispis(head->left);
	printf("%d ", head->value);
	inorder_ispis(head->right);
}
lis alociraj_list(int value)
{
	lis novi = (lis)malloc(sizeof(LISTA));
	if (novi == NULL) {
		printf("\nMemory allocation falied !\n\n");
		return NULL;
	}
	novi->value = value;
	novi->next = NULL;
	return novi;
}
void push(lis head, int val)
{
	lis q = alociraj_list(val);
	q->next = head->next;
	head->next = q;
}
int pop(lis head)
{
	lis temp = head->next;
	head->next = temp->next;
	int val = temp->value;
	free(temp);
	return val;
}
void writetolist(node root, lis head)
{
	if (root == NULL) {
		return;
	}
	writetolist(root->right, head);
	push(head, root->value);
	writetolist(root->left, head);
}
void printtofile(lis head, char name[BUFFER])
{
	if (head->next == NULL) {
		return;
	}
	FILE* f = fopen(name, "a");
	while (head->next != NULL) {
		fprintf(f, "%d ", pop(head));
	}
	fprintf(f, "\n\n");
	fclose(f);
}