#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_BODOVI 24

typedef struct _student {
    char ime[MAX_SIZE];
    char prezime[MAX_LINE];
    double bodovi;
}student;

int ProcitajBrojRedakaizDatoteke(char* nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke);
student NajboljiRezultat(student* studenti, int brojStudenata);
int IspisPod(student* studenti, int brojStudenata);

int main()
{
    
    int brojStud = 0;
    student* Stud = NULL;
    char* datoteka = "popis.txt";

    brojStud = ProcitajBrojRedakaizDatoteke(datoteka);
    if (brojStud == -1)
        return 0;

    Stud = AlocirajMemorijuIProcitajStudente(brojStud, datoteka);
    if (!Stud)
        return 0;

    IspisPod(Stud, brojStud);

    return 0;
}

int ProcitajBrojRedakaizDatoteke(char* nazivDatoteke)
{
    int brojac = 0;
    FILE* datoteka = NULL;
    char buffer[MAX_LINE] = { 0 };

    datoteka = fopen(nazivDatoteke, "r");
    if (!datoteka) {
        printf("Greska!");
        return -1;
    }
    while (!feof(datoteka))
    {
        fgets(buffer, MAX_LINE, datoteka);
        brojac++;
    }

    fclose(datoteka);

    return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteka)
{
    int brojac = 0;
    FILE* datoteka = NULL;
    student* studenti = NULL;

    studenti = (student*)malloc(brojStudenata * sizeof(student));
    if (!studenti)
    {
        printf("Pogreska u alociranju memorije!");
        free(studenti);
        return NULL;
    }
    
    datoteka = fopen(nazivDatoteka, "r");
    if (!datoteka)
    {
        printf("Greska u otvaranju datoteke!");
        return NULL;
    }
    while (!feof(datoteka))
    {
        fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
        brojac++;
    }

    fclose(datoteka);

    return studenti;
}

student NajboljiRezultat(student* studenti, int brojStudenata)
{
    int i;
    student najbolji = { 0 };

    for (i = 1; i < brojStudenata; i++)
        if (najbolji.bodovi < studenti[i].bodovi)
            najbolji = studenti[i];

    return najbolji;
}

int IspisPod(student* studenti, int brojStudenata)
{
    int i;
    student stud = { 0 };

    stud = NajboljiRezultat(studenti, brojStudenata);

    printf("Ispisuju se rezultati redom:\nIme i prezime / Aps. br. bod. / Rel. br. bod\n\n");

    for (i = 0; i < brojStudenata; i++) {
        printf("%s %s / %.3lf / %.3lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi / MAX_BODOVI * 100, (studenti[i].bodovi) / stud.bodovi * 100);
    }

    return 1;
}