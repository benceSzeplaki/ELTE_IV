#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <wait.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <string.h>

void forkError(pid_t fork_pid){
    if (fork_pid == -1) {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }
}

void jelezTapsi() {
    printf("Tapsi jelezte, hogy készen áll a számlálásra.\n");
}

void jelezFules() {
    printf("Füles jelezte, hogy készen áll a számlálásra.\n");
}

#define MAX_CHAR 1024

typedef struct Uzenet {
    long msg_type;
    char mtext [MAX_CHAR]; 
} Uzenet;

int uzenetFogadas(int uzenetsor) 
{ 
     Uzenet uzenet;
     int status;
     status = msgrcv(uzenetsor, &uzenet, sizeof(uzenet.mtext), 5, 0 ); 
     
     if ( status < 0 ) 
          perror("msgsnd"); 
     else
          printf( "%s\n",  uzenet.mtext); 
     return 0; 
}

int uzenetKuldes(int uzenetsor, Uzenet uzenet) 
{ 
    int status; 
    status = msgsnd(uzenetsor, &uzenet,  sizeof(uzenet.mtext), 0 );
    if ( status < 0 ) 
        perror("msgsnd"); 
    return 0; 
}

int main(void) {
    //1. feladat:
    
    
    pid_t tapsi, fules;
    int uzenetsorTapsihoz, uzenetsorFuleshez, statusTapsi, statusFules; 
    key_t kulcsTapsihoz, kulcsFuleshez;

    kulcsTapsihoz = ftok("tapsi", 1);
    uzenetsorTapsihoz = msgget(kulcsTapsihoz, 0600 | IPC_CREAT);

    kulcsTapsihoz += 1; 
    uzenetsorFuleshez = msgget(kulcsTapsihoz, 0600 | IPC_CREAT);
    
    signal(SIGUSR1, jelezTapsi);
    signal(SIGUSR2, jelezFules);

    tapsi = fork();
    fules = fork();
    forkError(tapsi);
    forkError(fules);
    if (tapsi == 0) { //First child process - Tapsi
        sleep(1);
        kill(getppid(), SIGUSR1);

        char* asd;

        printf("Tapsi területe: ");
        uzenetFogadas(uzenetsorTapsihoz);
        exit(EXIT_SUCCESS);

    } else if(fules == 0) { //Second child process - Füles
        sleep(1);
        kill(getppid(), SIGUSR2);

        char* asd;
        
        printf("Füles területe: ");
        uzenetFogadas(uzenetsorFuleshez);
        exit(EXIT_SUCCESS);

    } else { //Parent process - Főnyuszi
           
        printf("Főnyuszi felkérte Tapsit és Fülest.\n");
        printf("Főnyuszi várja, amíg Tapsi és Füles jelez, hogy készen állnak...\n");
        
        pause();
        pause();

        const Uzenet tapsiUzenet = { 5, "Barátfa" }; 
        uzenetKuldes(uzenetsorTapsihoz,tapsiUzenet);

        const Uzenet fulesUzenet = { 5, "Szula" }; 
        uzenetKuldes(uzenetsorFuleshez,fulesUzenet);
        
        int status;
        wait(&status);

        return 0;
    }
}
