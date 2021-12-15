#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct cvor* node;
typedef struct cvor
{
	node left;
	node right;
	int data;
}CVOR;

typedef struct queue* qu;
typedef struct queue
{
	node data;
	qu next;
}QUEUE;

qu alociraj_queue();
void pushtoqueue(qu, node);
node popfromqueue(qu);

int levelorder_ispis(node, qu);

node alociraj_nod(int);
void ispisOpcija();
node unesiustablo(node, node);
void inorder_ispis(node);
void preorder_ispis(node);
void postorder_ispis(node);
node brisiizstabla(node, int);
bool findelement(node, int);

int main()
{
	struct cvor* root = NULL;
	qu head_queue = alociraj_queue();

	int c = 0, temp = 0;
	while (c != 8) {
		ispisOpcija();
		scanf("%d", &c);
		switch (c)
		{
		case 1:  //unos
			printf("Unesite element:  ");
			scanf("%d", &temp);
			node q = alociraj_nod(temp);
			root = unesiustablo(root, q);
			printf("\n");
			break;
		case 2:  //ispis inorder
			inorder_ispis(root);
			printf("\n\n");
			break;
		case 3:  //ispis preorder
			preorder_ispis(root);
			printf("\n\n");
			break;
		case 4:  //ispis postorder
			postorder_ispis(root);
			printf("\n\n");
			break;
		case 5:  //ispis levelorder !!
			if (levelorder_ispis(root, head_queue) != 0) {
				printf("\nIspis neuspjesan !\n\n");
			}
			printf("\n\n");
			break;
		case 6:  //brisanje
			printf("\nUnder development !\n\n");
			break;
		case 7:  //pretraga
			printf("Unesite element koji zelite pronaci:  ");
			scanf("%d", &temp);
			if (findelement(root, temp)) {
				printf("\nElement [%d] pronaden !\n\n", temp);
			}
			else {
				printf("\nElement [%d] nije pronaden !\n\n", temp);
			}
			break;
		case 8:  //izlaz
			break;
		default:  //default
			printf("\nNeispravan unos !\n\n");
			c = 0;
			continue;
		}
		
	}

	printf("\n\n----------------Bye Bye----------------\n\n");
	return 0;
}

node alociraj_nod(int data)
{
	node novi_cvor = (node)malloc(sizeof(CVOR));
	if (novi_cvor == NULL) {
		printf("\nMemory allocation failed !\n\n");
	}
	novi_cvor->data = data;
	novi_cvor->left = NULL;
	novi_cvor->right = NULL;
	return novi_cvor;
}
void ispisOpcija()
{
	printf("-------Izbornik-------\n");
	printf("1. --- Unos u stablo !\n");
	printf("2. --- Ispis (inorder) !\n");
	printf("3. --- Ispis (preorder) !\n");
	printf("4. --- Ispis (postorder) !\n");
	printf("5. --- Ispis (levelorder) !\n");
	printf("6. --- Brisanje elementa !\n");
	printf("7. --- Trazenje elementa !\n");
	printf("8. --- Izlaz iz programa !\n");
	printf("----------------------\n");
	printf("\nUnesite broj za odabir:  ");
}
node unesiustablo(node root, node q)
{
	if (root == NULL) {
		return q;
	}
	if (root->data > q->data) {
		root->left = unesiustablo(root->left, q);
	}
	else if (root->data < q->data) {
		root->right = unesiustablo(root->right, q);
	}
	else {
		printf("\nElement se vec nalazi u stablu !\n\n");
		free(q);
	}
	return root;
}
void inorder_ispis(node head)
{
	if (head == NULL) {
		return;
	}
	inorder_ispis(head->left);
	printf("%d ", head->data);
	inorder_ispis(head->right);
}
void preorder_ispis(node head)
{
	if (head == NULL) {
		return;
	}
	printf("%d ", head->data);
	preorder_ispis(head->left);
	preorder_ispis(head->right);
}
void postorder_ispis(node head)
{
	if (head == NULL) {
		return;
	}
	postorder_ispis(head->left);
	postorder_ispis(head->right);
	printf("%d ", head->data);
}
node brisiizstabla(node root, int value)
{
	if (root == NULL) {
		return NULL;
	}
}
bool findelement(node root, int value)
{
	while (root->data != value) {
		if (root->data > value) {
			root = root->left;
		}
		else {
			root = root->right;
		}
		if (root == NULL) {
			return false;
		}
	}
	return true;
}
qu alociraj_queue()
{
	qu novi = (qu)malloc(sizeof(QUEUE));
	if (novi == NULL) {
		printf("\nMemory allocation failed !\n\n");
	}
	novi->data = NULL;
	novi->next = NULL;
	return novi;
}
void pushtoqueue(qu head, node q)
{
	qu novi = alociraj_queue();
	novi->data = q;
	if (head->next == NULL) {
		head->next = novi;
		return;
	}
	while (head->next != NULL) {
		head = head->next;
	}
	head->next = novi;
}
node popfromqueue(qu head)
{
	if (head->next == NULL) {
		return NULL;
	}
	qu temp = head->next;
	head->next = temp->next;
	node priv = temp->data;
	free(temp);
	return priv;
}
int levelorder_ispis(node root, qu head_queue)
{
	if (root == NULL) {
		printf("\nPrazno stablo !\n\n");
		return 1;
	}
	
	pushtoqueue(head_queue, root);
	while (head_queue->next != NULL) {
		node temp = popfromqueue(head_queue);
		printf("%d ", temp->data);
		if (temp->left != NULL) {
			pushtoqueue(head_queue, temp->left);
		}
		if (temp->right != NULL) {
			pushtoqueue(head_queue, temp->right);
		}
	}
}