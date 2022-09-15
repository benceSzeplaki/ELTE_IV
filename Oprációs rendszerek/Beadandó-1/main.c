#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX 256
#define MAX_LINE 900
#define MAX_COMPETITORS 100

typedef struct Bunny {
  char name[MAX];
  char place[17];
  int eggs;
} Bunny;

char place_list[7][17] = {"Barátfa", "Káposztás kert", "Kígyós-patak", "Lovas", "Malom telek", "Páskom", "Szula"};

//1 Beadandó függvényei:
void printMainMenu() {
    printf("--------------------------------------------------- \n");
    printf("Főmenü\n");
    printf("--------------------------------------------------- \n");
    printf("1. - Új nyúl hozzáadása\n");
    printf("2. - Meglévő nyúl adatainak módosítása\n");
    printf("3. - Meglévő nyúl törlése\n");
    printf("4. - Listázás területi alapon\n");
    printf("5. - Összes jelentkező\n");
    printf("6. - Verseny indítása\n");
    printf("7. - Kilépés a programból\n");
    printf("--------------------------------------------------- \n");
    printf("Adj meg egy menüpontot: ");
}

void printPlaces(int x) {
    if (x == 0) {
        printf("Add meg hol lakik az alábbi listából:\n");
    } else {
        printf("Melyik település alapján szeretnél listázni?\n");
    }
    for (int i = 0; i < 7; i++) {
        printf("%d. %s\n", (i + 1), place_list[i]);
    }
    printf("Hely száma: ");
}

void printApplication() {
    printf("Hányadjára indul a versenyen?\nA versenyen ennyiszer indult: ");
}

char *readName(FILE *f, size_t size) {
    fgetc(f);
    printf("Név: ");
    char *name;
    char ch;
    size_t len = 0;
    name = realloc(NULL, sizeof(*name) * size);
    if (!name) {
        return name;
    }
    while (EOF != (ch = fgetc(f)) && ch != '\n') {
        name[len++] = ch;
        if (len == size) {
            name = realloc(name, sizeof(*name) * (size += 10));
            if (!name) {
                return name;
            }
        }
    }
    name[len++] = '\0';
    return realloc(name, sizeof(*name) * len);
}

void readPlace(FILE *fp) {
    int place_number = 0;
    while (place_number <= 0 || place_number > 7) {
        printPlaces(0);
        if (scanf("%d", &place_number) != 1) {
            printf("Nem számot adtál meg!\n");
            readPlace(fp);
        }
    }
    fprintf(fp, "%s\n", place_list[place_number - 1]);
}

int readApplication() {
    int application_number = 0;
    while (application_number <= 0) {
        printApplication();
        if (scanf("%d", &application_number) != 1) {
            printf("Nem számot adtál meg!\n");
            readApplication();
        }
    }
    return application_number;
}

void modifyBunny() {
    printf("--------------------------------------------------- \n");
    printf("Kit szeretnél módosítani?\n");
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int j = 0;
    fp = fopen("applicants.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int line_ctr = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (j % 3 == 0) {
            line_ctr++;
            printf("%d. Név: %s", line_ctr, line);
            j++;
        } else if (j % 3 == 1) {
            printf("Lakhely: %s", line);
            j++;
        } else {
            printf("Hányadjára indult: %s\n", line);
            j = 0;
            printf("--------------------------------------------------- \n");
        }
    }
    fclose(fp);
    printf("\n");
    int lno, ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
    char fname[] = "applicants.txt", temp[] = "temp.txt";
    char str[MAX];
    fptr1 = fopen(fname, "r");
    if (!fptr1) {
        printf("Nem létezik a file: %s!!\n", fname);
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2) {
        printf("Nem lehett létrehozni a tmp.txt file-t!!\n");
        fclose(fptr1);
    }
    printf("Add meg a módosítani kívánt nyuszi sorszámát: ");
    scanf("%d", &lno);
    lno = ((lno - 1) * 3) + 1;
    printf("--------------------------------------------------- \n");
    printf("1. - A nevét.\n");
    printf("2. - A lakhelyét\n");
    printf("3. - Azt, hogy hányadjára indult\n");
    printf("--------------------------------------------------- \n");
    printf("Válaszd ki hogy melyik adatát szeretnéd módosítani: \n");
    int modify;
    scanf("%d", &modify);
    printf("--------------------------------------------------- \n");
    lno = lno + (modify - 1);
    printf("Add meg mire módosuljon: ");
    char *name;
    int place_number = 0;
    int application = 0;
    switch (modify) {
        case 1:
            name = readName(stdin, 10);
            break;
        case 2:
            printPlaces(0);
            scanf("%d", &place_number);
            break;
        case 3:
            application = readApplication();
            break;
        default:
            break;
    }
    while (!feof(fptr1)) {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1)) {
            ctr++;
            if (ctr != lno) {
                fprintf(fptr2, "%s", str);
            } else {
                switch (modify) {
                case 1:
                    fprintf(fptr2, "%s\n", name);
                    break;
                case 2:
                    fprintf(fptr2, "%s\n", place_list[place_number - 1]);
                    break;
                case 3:
                    fprintf(fptr2, "%d\n", application);
                    break;
                default:
                    break;
                }
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fname);
    rename(temp, fname);
}

void deleteBunny() {
    printf("--------------------------------------------------- \n");
    printf("Kit szeretnél törölni?\n");
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int j = 0;
    fp = fopen("applicants.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int line_ctr = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (j % 3 == 0) {
            line_ctr++;
            printf("%d. Név: %s", line_ctr, line);
            j++;
        } else if (j % 3 == 1) {
            printf("Lakhely: %s", line);
            j++;
        } else {
            printf("Hányadjára indult: %s\n", line);
            j = 0;
            printf("--------------------------------------------------- \n");
        }
    }
    fclose(fp);
    printf("\n");
    int lno, ctr = 0;
    char ch;
    FILE *fptr1, *fptr2;
    char fname[] = "applicants.txt", temp[] = "temp.txt";
    char str[MAX];
    fptr1 = fopen(fname, "r");
    if (!fptr1) {
        printf("Nem létezik a file: %s!!\n", fname);
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2) {
        printf("Nem lehett létrehozni a tmp.txt file-t!!\n");
        fclose(fptr1);
    }
    printf("Add meg a törölni kívánt nyuszi sorszámát: ");
    scanf("%d", &lno);
    lno = ((lno - 1) * 3) + 1;
    while (!feof(fptr1)) {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1)) {
            ctr++;
            if (ctr != lno && ctr != lno + 1 && ctr != lno + 2) {
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    remove(fname);
    rename(temp, fname);
}

void addBunny() {
    FILE *fp;
    printf("--------------------------------------------------- \n");
    printf("Új nyúl versenyző hozzáadása:\n");
    fp = fopen("applicants.txt", "a");
    fseek(fp, 0, SEEK_END - 1);
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    char *name = readName(stdin, 10);
    fprintf(fp, "%s\n", name);
    readPlace(fp);
    int application = readApplication();
    fprintf(fp, "%d\n", application);
    fclose(fp);
    printf("--------------------------------------------------- \n");
    printf("Új nyúl versenyző sikeresen hozzáadva!\n");
}

// 2 Beadandó függvényei: 
bool isItInCities(char* city, int* territories, int territories_size){
    for (size_t i = 0; i < territories_size; i++) {
        if(city[strlen(city)-1] == '\n'){
            city[strlen(city)-1] = '\0';
        }
        if(strcmp(city, place_list[territories[i]]) == 0) {
            return true;
        }
    }
    return false;
}

void giveName(const int* pipefd_oda, int* territories, int territories_size, Bunny* bunnies, int sizeOfBunnies){
    close(pipefd_oda[0]);
    for(int i = 0; i < sizeOfBunnies; i++) {   
        if(isItInCities(bunnies[i].place, territories, territories_size)) {
            write(pipefd_oda[1], bunnies[i].name, sizeof(bunnies[i].name));
        }
    }
    close(pipefd_oda[1]);
}

Bunny maxEggs(const int* pipe){
    close(pipe[1]);
    Bunny maxBunny, tmp;
    maxBunny.eggs = 0;
    while (read(pipe[0], &tmp, sizeof(Bunny))) {
        if(tmp.eggs > maxBunny.eggs){
            strcpy(maxBunny.name, tmp.name);
            maxBunny.eggs = tmp.eggs;
        }
    }
    return maxBunny;
}

void startCompetition() {
    struct Bunny bunnies[MAX_COMPETITORS];
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read_d;
    int j = 0;
    fp = fopen("applicants.txt", "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int competitors = 0;
    struct Bunny b;
    while ((read_d = getline(&line, &len, fp)) != -1) {
        if (j % 3 == 0) {
            competitors++;
            j++;
            strcpy(b.name, line);
        } else if (j % 3 == 1) {
            j++;
            strcpy(b.place, line);
        } else {
            j = 0;
            bunnies[competitors - 1] = b;
        }
    }
    fclose(fp);
    printf("--------------------------------------------------- \n");
    printf("Verseny elindul!\n");
    printf("--------------------------------------------------- \n");
    int pipefd_oda[2];
    if (pipe(pipefd_oda) == -1) {
        perror("Hiba a pipefd_oda nyitaskor!");
        exit(EXIT_FAILURE);
    }
    int pipefd_vissza[2];
    if (pipe(pipefd_vissza) == -1) {
        perror("Hiba a pipefd_vissza nyitaskor!");
        exit(EXIT_FAILURE);
    }
    pid_t pid_eslo = fork(); // creating parent-child processes
    if (pid_eslo == -1) {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }
    if (pid_eslo == 0) { //elso gyerek process
            sleep(1);
            srand(time(NULL));
            close(pipefd_oda[1]);
            close(pipefd_vissza[0]);
            Bunny res;
            int random;
            printf("Az első versenyfelügyelő megnézi, hogy ki hány tojást gyüjtött...\n");
            while(read(pipefd_oda[0], res.name, sizeof(res.name))){
                if(res.name[strlen(res.name)-1] == '\n'){
                    res.name[strlen(res.name)-1] = '\0';
                }
                random = (rand() % 100) + 1;
                res.eggs = random;
                write(pipefd_vissza[1], &res, sizeof(Bunny));
            }
            printf("Az első versenyfelügyelő visszaküldte a Főnyuszinak, hogy ki hány tojást gyüjtött\n");
            close(pipefd_oda[0]);
            close(pipefd_vissza[1]);
            exit(0);
    } else {
        int pipefd_oda_2[2];
        if (pipe(pipefd_oda_2) == -1) {
            perror("Hiba a pipefd_oda nyitaskor!");
            exit(EXIT_FAILURE);
        }
        int pipefd_vissza_2[2];
        if (pipe(pipefd_vissza_2) == -1) {
            perror("Hiba a pipefd_oda nyitaskor!");
            exit(EXIT_FAILURE);
        }
        pid_t pid_masodik;
        pid_masodik = fork();
        if (pid_masodik == -1) {
            perror("Fork hiba");
            exit(EXIT_FAILURE);
        }
        if(pid_masodik == 0) { // masodik gyerek process
            srand(time(NULL));
            close(pipefd_oda[0]);
            close(pipefd_vissza[0]);
            close(pipefd_oda[1]);
            close(pipefd_vissza[1]);
            sleep(2);
            close(pipefd_oda_2[1]);
            close(pipefd_vissza_2[0]);
            Bunny res;
            int random;
            printf("Az masodik versenyfelügyelő megnézi, hogy ki hány tojást gyüjtött...\n");
            while(read(pipefd_oda_2[0], res.name, sizeof(res.name))){
                if(res.name[strlen(res.name)-1] == '\n'){
                    res.name[strlen(res.name)-1] = '\0';
                }
                random = (rand() % 100) + 1;
                res.eggs = random;
                write(pipefd_vissza_2[1], &res, sizeof(Bunny));
            }
            printf("Az masodik versenyfelügyelő visszaküldte a Főnyuszinak, hogy ki hány tojást gyüjtött\n");
            close(pipefd_oda_2[0]);
            close(pipefd_vissza_2[1]);
            exit(0);
        } else { // szulo process
            printf("A Főnyuszi elküldi a jelentkezők adatait\n");
            int elsoGyereknek [4] = {0, 3, 2, 1};
            int masodikGyereknek[3] = {4, 5, 6};
            giveName(pipefd_oda, elsoGyereknek, 4, bunnies, competitors);
            giveName(pipefd_oda_2, masodikGyereknek, 3, bunnies, competitors);
            wait(NULL);
            wait(NULL);
            Bunny max_1, max_2;
            printf("A Főnyuszi, régiónként ellenőrzi, hogy ki gyüjtötte a legtöbb tojást...\n");
            max_1 = maxEggs(pipefd_vissza);
            max_2 = maxEggs(pipefd_vissza_2);
            printf("A Főnyuszi már csak két régiót hasonlítja össze...\n");
            if(max_1.eggs < max_2.eggs) {
                printf("A Főnyuszi kihírdeti, hogy ki nyerte a tojásgyüjtést:\n");
                printf("A nyertes: %s, aki %d tojást gyűjtött.\n", max_2.name, max_2.eggs);
            } else if(max_1.eggs > max_2.eggs) {
                printf("A Főnyuszi kihírdeti, hogy ki nyerte a tojásgyüjtést:\n");
                printf("A nyertes: %s, aki %d tojást gyűjtött.\n", max_1.name, max_1.eggs);
            } else {
                printf("A Főnyuszi kihírdeti, hogy ki nyerte a tojásgyüjtést:\n");
                printf("Döntetlen\n");
                printf("%s és %s ugyanannyi ( %d ) tojást gyűjtöttek, így Ők nyerték a versenyt.\n", max_1.name, max_2.name, max_1.eggs);
            }
            close(pipefd_oda[0]);
            close(pipefd_oda[1]);
            close(pipefd_oda_2[0]);
            close(pipefd_oda_2[1]);
            close(pipefd_vissza[0]);
            close(pipefd_vissza[1]);
            close(pipefd_vissza_2[0]);
            close(pipefd_vissza_2[1]);
        }
    }
    printf("--------------------------------------------------- \n");
    printf("Verseny vége!\n");
    printf("--------------------------------------------------- \n");	
	exit(EXIT_SUCCESS);
}

int main(void) {
    int main_menu_option = 0;
    bool run = true;
    FILE *fp;
    char *line = NULL;
    char l[MAX_LINE][MAX_LINE];
    int size_of_l = 0;
    size_t len = 0;
    ssize_t read;
    int j = 0;
    int place_number = 0;
    while (run) {
        printMainMenu();
        if (scanf("%d", &main_menu_option) != 1) {
            printf("Nem létező menüpont!\n");
        }
        switch (main_menu_option) {
            case 1: //Adding new bunny
                addBunny();
                break;
            case 2: //Bunny modification
                modifyBunny();
                break;
            case 3: //Bunny deletion
                deleteBunny();
                break;
            case 4: //Listing Bunnies - by place
                printf("--------------------------------------------------- \n");
                printf("Nyúl listázása területenként:\n");
                printf("--------------------------------------------------- \n");
                printPlaces(1);
                scanf("%d", &place_number);
                printf("--------------------------------------------------- \n");
                printf("Település: %s\n", place_list[place_number - 1]);
                fp = fopen("applicants.txt", "r");
                int i = 0;
                while (fgets(l[i], MAX_LINE, fp)) {
                    l[i][strlen(l[i]) - 1] = '\0';
                    i++;
                }
                size_of_l = i;
                for (i = 0; i < size_of_l; ++i) {
                    if (strcmp(l[i], place_list[place_number - 1]) == 0) {
                        printf("--------------------------------------------------- \n");
                        printf("Név: %s\nHányadjára indul: %s\n", l[i - 1], l[i + 1]);
                        printf("--------------------------------------------------- \n");
                        i++;
                    }
                }
                break;
            case 5: //Listing Bunnies - all
                printf("--------------------------------------------------- \n");
                printf("Összes nyúl listázása:\n");
                printf("--------------------------------------------------- \n");
                fp = fopen("applicants.txt", "r");
                if (fp == NULL) {
                    exit(EXIT_FAILURE);
                }
                int line_ctr = 0;
                while ((read = getline(&line, &len, fp)) != -1) {
                    if (j % 3 == 0) {
                        line_ctr++;
                        printf("%d. Név: %s", line_ctr, line);
                        j++;
                    } else if (j % 3 == 1) {
                        printf("Lakhely: %s", line);
                        j++;
                    } else {
                        printf("Hányadjára indult: %s", line);
                        j = 0;
                        printf("--------------------------------------------------- \n");
                    }
                }
                fclose(fp);
                break;
            case 6:
                startCompetition();
                break;
            case 7:
                run = false;
                printf("--------------------------------------------------- \n");
                printf("Viszlát!\n");
                printf("--------------------------------------------------- \n");
                break;
            default:
                perror("ERROR\n Nem jó menüpontot adtál meg!\n");
                break;
        }
    }
    if (line) {
        free(line);
    }
    return 0;
}