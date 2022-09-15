#ifndef header_guard
#define header_guard

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Bunny
{
    char *name;
    char *place;
    char application_for_competition;
} Bunny;

void initBunny(Bunny *b){
    free(b->name);
    free(b->place);
    b->name = NULL;
    b->place = NULL;
    b->application_for_competition = 0;
}

char *readName(FILE *fp, size_t size)
{
    fgetc(fp);
    printf("Név: ");
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str) * size);
    if (!str)
    {
        return str;
    }
    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[len++] = ch;
        if (len == size)
        {
            str = realloc(str, sizeof(*str) * (size += 10));
            if (!str)
            {
                return str;
            }
        }
    }
    str[len++] = '\0';

    return realloc(str, sizeof(*str) * len);
}

void printPlaces()
{
    char place_list[7][17] = {"Baratfa", "Lovas", "Szula", "Kagyos-patak", "Malom telek", "Paskom", "Kaposztas kert"};
    printf("Add meg hol laksz az alábbi listából:\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d. %s\n", (i + 1), place_list[i]);
    }
    printf("Hely száma: ");
}

void readPlace(Bunny *b) {
    int place_number = 0;
    while (place_number <= 0 || place_number > 7) {
        printPlaces();
        if (scanf("%d", &place_number) != 1) {
            printf("Nem számot adtál meg!\n");
            readPlace(b);
        }
    }
    char place_list[7][17] = {"Barátfa", "Lovas", "Szula", "Kígyós-patak", "Malom telek", "Páskom", "Káposztás kert"};
    strcpy(b->place, place_list[place_number - 1]);
    
}

void printApplication() {
    printf("Hányadjára indulsz a versenyen?\nA versenyen ennyiszer indultál: ");
}

char readApplication() {
    int application_number = 0;
    while (application_number <= 0) {
        printApplication();
        if (scanf("%d", &application_number) != 1) {
            printf("Nem számot adtál meg!\n");
            readApplication();
        }
    }
    char charValue = application_number + '0';
    return charValue;
}

Bunny readBunny() {
    fflush(stdin);
    printf("Add meg az adataid nyúl uram!\n");
    Bunny b;

    b.name = readName(stdin, 10);
    readPlace(&b);
    b.application_for_competition = readApplication();

    printf("A neved: %s\n", b.name);
    printf("A lakhelyed: %s\n", b.place);
    printf("Hányadik versenyed: %c.\n", b.application_for_competition);

    return b;
}

void printBunny(Bunny b) {
    printf("--------------------------------------\n");
    printf("Nyúl neve: %s\n", b.name);
    printf("Nyúl lakhelye: %s\n", b.place);
    printf("Hányszor indult: %c\n", b.application_for_competition);
    printf("--------------------------------------\n");
}
#endif