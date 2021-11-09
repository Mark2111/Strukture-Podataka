#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX (1024)

typedef struct Polinom* pol;
typedef struct Polinom
{
    int koef;
    int exp;
    pol next;
}POLINOM;

pol alocirajPolinom();
void dodajNakon(pol, int, int);
void izbrisiNakon(pol);
void procitajDatoteku(pol, pol, char*);
void unesiUListu(pol, char*);
void unesiSortirano(pol, int, int);
void ispisiPolinom(pol);
void zbrojiPolinome(pol, pol, pol);
void pomnoziPolinome(pol, pol, pol);

int main(int argc, char** argv)
{
    pol head1 = alocirajPolinom();
    pol head2 = alocirajPolinom();
    pol headZbroj = alocirajPolinom();
    pol headUmnozak = alocirajPolinom();

    if(argc < 2){
        printf("Usage: ./file <.txt file>\n");
        return 1;
    }
  
    procitajDatoteku(head1, head2, argv[1]);   //Procitaj datoteku za prve 2 liste

    printf("Prva lista:");
    ispisiPolinom(head1);
    printf("\n\nDruga lista:");
    ispisiPolinom(head2);

    zbrojiPolinome(head1, head2, headZbroj);
    pomnoziPolinome(head1, head2, headUmnozak);

    printf("\n\n----Zbrojeno----");
    ispisiPolinom(headZbroj);
    printf("\n\n----Pomnozeno----");
    ispisiPolinom(headUmnozak);

    free(head1);
    free(head2);
    free(headZbroj);
    free(headUmnozak);
    
    return 0;
}

pol alocirajPolinom()
{
    pol novipol;
    novipol = (pol)malloc(sizeof(POLINOM));
    novipol->koef = 0;
    novipol->exp = 0;
    novipol->next = NULL;
    return novipol;
}
void dodajNakon(pol head, int k, int e)
{
    pol novi = alocirajPolinom();
    novi->koef = k;
    novi->exp = e;
    novi->next = head->next;
    head->next = novi;
}
void izbrisiNakon(pol head)
{
    pol tmp = head->next;
    head->next = tmp->next;
    free(tmp);
}
void procitajDatoteku(pol head1, pol head2, char* filename)
{
    FILE *f = fopen(filename, "r");
    char buffer[MAX] = { 0 };

    if(!f){
        printf("Can't open file !\n");
        printf("Error !\n");
    }
    fgets(buffer, MAX, f);
    unesiUListu(head1, buffer);
    fgets(buffer, MAX, f);
    unesiUListu(head2, buffer);

    fclose(f);
}
void unesiUListu(pol head, char* buffer)
{
    char* pos = buffer;
    int koef = 0;
    int exp = 0;
    int num = 0;
    int st = 0;
    while(strlen(pos) > 0){
        st = sscanf(pos, " %d %d %n", &koef, &exp, &num);
        if (st != 2){
            printf("Nije ucitan koeficijent/eksponent !\n");
            break;
        }
        unesiSortirano(head, koef, exp);
        pos += num;
    }
}
void unesiSortirano(pol head, int koef, int exp)
{
    pol iterator = head;
    while(iterator->next != NULL && iterator->next->exp < exp){
        iterator = iterator->next;
    }

    if(iterator->next == NULL || iterator->next->exp != exp){
        dodajNakon(iterator, koef, exp);
    }
    else{
        int zbr = iterator->next->koef + koef;
        if(zbr = 0){
            izbrisiNakon(iterator);
        }
        else{
            iterator->next->koef = zbr;
        }
    }
}
void ispisiPolinom(pol head)
{
    pol iterator = head->next;
    while(iterator != NULL){
        if(iterator->koef == 0){
            iterator = iterator->next;
        }
        else if(iterator->koef == 1){
            printf("\nx^(%d)\n", iterator->exp);
            iterator = iterator->next;
        }
        else{
            printf("\n%dx^(%d)\n", iterator->koef, iterator->exp);
            iterator = iterator->next;
        }
    }
}
void zbrojiPolinome(pol head1, pol head2, pol headZbroj)
{
    pol i = NULL;
    pol j = NULL;

    for (i=head1->next; i != NULL; i = i->next){
        unesiSortirano(headZbroj, i->koef, i->exp);
    }
    for(j= head2->next; j != NULL; j = j->next){
        unesiSortirano(headZbroj, j->koef, j->exp);
    }
    free(i);
    free(j);
}
void pomnoziPolinome(pol head1, pol head2, pol headUmnozak)
{
    pol i = NULL;
    pol j = NULL;

    for(i = head1->next; i!=NULL; i=i->next){
        for(j=head2->next; j!=NULL;j=j->next){
            unesiSortirano(headUmnozak, (i->koef*j->koef), (i->exp + j->exp));
        }
    }
    free(i);
    free(j);
}