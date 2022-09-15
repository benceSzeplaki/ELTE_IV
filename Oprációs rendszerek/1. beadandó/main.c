#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bunny.h"
#include "array_bunny.h"

#define MAX_APPLICANTS 256
#define LINE_SIZE 256

void printMainMenu() {
  printf("--------------------------------------\n");
  printf("Főmenü\n");
  printf("--------------------------------------\n");
  printf("1. - Új nyúl hozzáadása\n");
  printf("2. - Meglévő nyúl adatainak módosítása\n");
  printf("3. - Meglévő nyúl törlése\n");
  printf("4. - Listázás területi alapon\n");
  printf("5. - Összes jelentkező\n");
  printf("6. - Kilépés a programból\n");
  printf("--------------------------------------\n");
}

void readToArrayBunny(ArrayBunny *arr) {
    char line[LINE_SIZE][MAX_APPLICANTS];
	  char fname[20];
    FILE *fptr = NULL; 
    int i = 0;
    fptr = fopen("applicants.txt", "r");
    while(fgets(line[i], LINE_SIZE, fptr)) {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    Bunny b;
    initBunny(&b);
    int ctr = 0;
    for(int j = 0; j <= i; j++) {
        if(ctr == 0){
          b.name = realloc(b.name, sizeof(line[j]));
          strcpy(b.name, line[j]);
          ctr++;
        } else if(ctr == 1){
          b.place = realloc(b.place, sizeof(line[j]));
          strcpy(b.place, line[j]);
          ctr++;
        } else {
          b.application_for_competition = line[j][0];
          ctr = 0;
          insertArray(arr, b);
          initBunny(&b);
        }
    }
    fclose(fptr);
}

int main(void) {
  int main_menu_option = 0;
  bool run = true;
  ArrayBunny list;
  initArray(&list, 1);
  readToArrayBunny(&list);
  while (run) {
    printMainMenu();
    if (scanf("%d", &main_menu_option) != 1) {
      printf("Nem számot adtál meg!\n");
    }
    switch (main_menu_option) {
    case 1:
      // Adding new bunny
      insertArray(&list, readBunny());
      break;
    case 2:
      // Bunny modification
      break;
    case 3:
      // Bunny deletion
      break;
    case 4:
      // Listing Bunnies - by place
      break;
    case 5:
      // Listing Bunnies - all
      printArray(&list);
      break;
    case 6:
      run = false;
      break;
    default:
      perror("ERROR\n Nem jó menüpontot adtál meg!\n");
      break;
    }
  }
  freeArray(&list);
  return 0;
}