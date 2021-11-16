#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (50)

typedef struct _StackElement* pok;
typedef struct _StackElement {
    double number;
    pok next;
}StackElement;

pok alocirajElement(double);

void unesiNakon(pok, pok);

void izbrisiNakon(pok);

void push(pok, double);

void pop(double*, pok);

int operacija(pok, char);

void racunajIzDatoteke(double*, char*);

int main(int argc, char** argv)
{
    char imeDatoteke[MAX] = { 0 };
    double rez = 0;

    printf("Unesite naziv datoteke: ");
    scanf(" %s", imeDatoteke);

    racunajIzDatoteke(&rez, imeDatoteke);

    printf("Rezultat je: %.2lf\n", rez);

    return 0;
}

pok alocirajElement(double broj)
{
    pok noviEl;
    noviEl = (pok)malloc(sizeof(StackElement));
    noviEl->number = broj;
    noviEl->next = NULL;
    return noviEl;
}

void unesiNakon(pok poz1, pok poz2)
{
    poz2->next = poz1->next;
    poz1->next = poz2;
}

void izbrisiNakon(pok head)
{
    pok temp = head->next;
    if (temp != NULL){
        head->next = temp->next;
        free(temp);
    }
}

void push(pok head, double broj)
{
    pok noviEl = alocirajElement(broj);
    if (noviEl != NULL){
        unesiNakon(head, noviEl);
    }
}

void pop(double* broj, pok head)
{
    pok prvi = head->next;
    if(!prvi){
        printf("Not valid form !\n");
        printf("Error !\n");
    }
    *broj = prvi->number;
}

int operacija(pok head, char operation)
{
    double br1 = 0, br2 = 0, rez = 0;
    

    pop(&br2, head);
    pop(&br1, head);

    switch (operation)
    {
    case '+':
        rez = br2 + br1;
        break;
    case '-':
        rez = br2 - br1;
        break;
    case '*':
        rez = br2 * br1;
        break;
    case '/':
        if(br2 == 0){
            printf("Zero division !\n");
            break;
        }
        else {
            rez = br2 / br1;
        }
        break;
    default:
        printf("Invalid operation !\n");
        return -1;
    }
    push(head, rez);
    return 0;
}

void racunajIzDatoteke(double* brojzaupis, char* imeDatoteke)
{
    FILE *f = fopen(imeDatoteke, "rb");
    if(!f){
        printf("Cannot read file !!\n");
    }
    int n = 0, flength = 0, st = 0;
    double broj = 0;
    char* buffer = NULL;
    char* currentBuffer = NULL;
    char operation = 0;

    pok head = alocirajElement(0);

    fseek(f, 0, SEEK_END);
    flength = ftell(f);

    buffer = (char*)calloc(flength + 1, sizeof(char));
    if(!buffer){
        printf("Allocation error !\n");
    }

    rewind(f);
    fread(buffer, sizeof(char), flength, f);
    printf("%s \n", buffer);
    fclose(f);

    currentBuffer = buffer;
    while(strlen(currentBuffer) > 0){
        st = sscanf(currentBuffer, " %lf %n", &broj, &n);
        if(st == 1){
            push(head, broj);
            currentBuffer += n;
        }
        else {
            sscanf(currentBuffer, " %c %n", &operation, &n);
            st = operacija(head, operation);
            if (st != 0) {
                free(buffer);
                while (head->next != NULL){
                    izbrisiNakon(head);
                }
            }
            currentBuffer += n;
        }
    }
    free(buffer);
    if(head->next->next) {
        printf("Invalid postfix form !\n");
    }

    pop(brojzaupis, head);
}
