#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER (1024)

typedef struct Artikli* art;
typedef struct Artikli
{
    char artikl[30];
    int kolicina;
    float cijena;
    art next;
}ARTIKLI;

typedef struct Racuni* rac;
typedef struct Racuni
{
    char naziv[30];
    int godina;
    int misec;
    int dan;
    art head;
    rac next;
}RACUNI;

void procitaj_racune(char [30], rac);
int usporedi_datum(rac, rac);
rac alociraj_racun();
art alociraj_artikal();
void procitaj_artikle(char [30], rac);
void unesi_artikal_sortirano(rac, art);
void unesi_racun_sortirano(rac, rac);

int main()
{
    char naziv_datoteke[30];
    rac head_racuna = alociraj_racun();
    printf("Unesite naziv datoteke s imenima racuna: ");
    scanf(" %30s", &naziv_datoteke);

    procitaj_racune(naziv_datoteke, head_racuna);
    
    printf("\n\n\n\n\n");
    while(head_racuna->next != NULL){
        while(head_racuna->head->next != NULL){
            printf("Artikal: %s\tKolicina: %d\tCijena: %.2f\n", head_racuna->head->artikl, head_racuna->head->kolicina, head_racuna->head->cijena);
            head_racuna->head = head_racuna->head->next;
        }

        head_racuna = head_racuna->next;
    }

    return 0;
}

void procitaj_racune(char naziv_dat[30], rac head_racuna)
{
    char buffer[BUFFER];
    FILE *f = fopen(naziv_dat, "r");
    if (f == NULL){
        printf("Error opening racuni file !\n");
    }

    while(fgets(buffer, BUFFER, f)){   // Citaj racun po racun
        char temp_buff[BUFFER];
        sscanf(buffer, "%s ", temp_buff);
        printf("\nCitam racun: -%s-\n\n", temp_buff);
        procitaj_artikle(temp_buff, head_racuna);
    }
    fclose(f);

}
int usporedi_datum(rac prvi, rac drugi)
{
    if(prvi->godina < drugi->godina){
        return -1;
    }
    else if(prvi->godina > drugi->godina){
        return 1;
    }

    if(prvi->godina == drugi->godina){
        if(prvi->misec < drugi->misec){
            return -1;
        }
        else if(prvi->misec > drugi->misec){
            return 1;
        }
        else if(prvi->dan < drugi->dan){
            return -1;
        }
        else if(prvi->dan > drugi->dan){
            return 1;
        }
        else{
            return 0;
        }
    }
}
rac alociraj_racun()
{
    rac novi_racun = (rac)malloc(sizeof(RACUNI));
    novi_racun->dan = 0;
    novi_racun->misec = 0;
    novi_racun->godina = 0;
    strcpy(novi_racun->naziv, "");
    novi_racun->next = NULL;
    novi_racun->head = alociraj_artikal();
    return novi_racun;
}
art alociraj_artikal()
{
    art novi_artikal = (art)malloc(sizeof(ARTIKLI));
    strcpy(novi_artikal->artikl, "");
    novi_artikal->kolicina = 0;
    novi_artikal->cijena = 0.0;
    novi_artikal->next = NULL;
    return novi_artikal;
}

void procitaj_artikle(char ime[30], rac head_svih_racuna)
{
    rac novi_racun = alociraj_racun();
    strcpy(novi_racun->naziv, ime);
    int counter = 0;
    char buffer[BUFFER];
    FILE *fp = fopen(novi_racun->naziv, "r");
    if (fp == NULL){
        printf("Error opening file !\n");
    }

    while(fgets(buffer, BUFFER, fp)){
        if(counter == 0){
            sscanf(buffer, "%d-%d-%d ", &novi_racun->godina, &novi_racun->misec, &novi_racun->dan);
            counter++;
            printf("%d godina %d misec %d dan\n", novi_racun->godina, novi_racun->misec, novi_racun->dan);
        }
        else{
            art novi_artikal = alociraj_artikal();
            sscanf(buffer, "%s %d %f ", novi_artikal->artikl, &novi_artikal->kolicina, &novi_artikal->cijena);
            printf("artikal: %s kolicina: %d cijena: %.2f\n", novi_artikal->artikl, novi_artikal->kolicina, novi_artikal->cijena);
            unesi_artikal_sortirano(novi_racun, novi_artikal);
        }
    }
    unesi_racun_sortirano(head_svih_racuna, novi_racun);
    fclose(fp);
}
void unesi_artikal_sortirano(rac racun, art artikal)
{
    if (racun->head->next == NULL){
        racun->head->next = artikal;
    }
    else{
        while(racun->head->next != NULL){
            racun->head = racun->head->next;
        }
        artikal->next = racun->head->next;
        racun->head->next = artikal;
    }
    printf("\nDodan artikal !\n");
}
void unesi_racun_sortirano(rac head_svih_racuna, rac novi_racun)
{
    if(head_svih_racuna == NULL){
        head_svih_racuna->next = novi_racun;
    }
    else{
        while(head_svih_racuna->next != NULL){
            head_svih_racuna = head_svih_racuna->next;
        }
        novi_racun->next = head_svih_racuna->next;
        head_svih_racuna->next = novi_racun;
    }
    printf("\nDodan racun !\n");
}
