#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

void signalHandler1(int number) {
    printf("Első tag jelezte, hogy készen áll a munkára.\n");
}

void signalHandler2(int number) {
    printf("Második tag jelezte, hogy készen áll a munkára.\n");
}

void signalHandler3(int number){
    printf("Az ellenőrző tag jelzett a választási lapokat kezelő testvérnek.");
}

typedef struct Voter{
    int ID;
    bool canTheyVote;
} Voter;

int readVoters() {
    int voters = 0;
    while (voters <= 0) {
        if (scanf("%d", &voters) != 1) {
            printf("Nem számot adtál meg!\n");
        }
    }
    return voters;
}

bool isRandomUsed(struct Voter* voters, int votersSize, int randomID){
    bool returnValue = false;
    for(int j = 0; j < votersSize; j++){
        if(voters[j].ID == randomID){
            returnValue = true;
        }
    }
    return returnValue;
}

void initVoters(struct Voter* voters, int votersSize){
    for (int i = 0; i < votersSize; i++) {
        voters[i].ID = 0;
        voters[i].canTheyVote = true;
    }
}

bool decideIfCanVote(){
    int random = rand() % 101;
    if(random < 21){
        return false;
    } else {
        return true;
    }
}

int main(void) {

    signal(SIGUSR1, signalHandler1);
    signal(SIGUSR2, signalHandler2);

    pid_t child_one, child_two;
    pid_t pid_child_1, pid_child_2;

    int child_one_get_data[2],
        child_one_to_child_two[2];

    if (pipe(child_one_get_data) == -1) {
        perror("Hiba a child_one_get_data nyitaskor!");
        exit(EXIT_FAILURE);
    }
    if (pipe(child_one_to_child_two) == -1) {
        perror("Hiba a child_one_to_child_two nyitaskor!");
        exit(EXIT_FAILURE);
    }

    child_one = fork();
    if (child_one == -1) {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }
    if(child_one == 0) { //First child process
        sleep(2);
        kill(getppid(), SIGUSR1);

        pid_child_1 = getpid();

        Voter tmp;
        int index;
        index = 1;

        close(child_one_get_data[1]);
        close(child_one_to_child_two[0]);

        while(read(child_one_get_data[0], &tmp, sizeof(Voter)) > 0) {
            tmp.canTheyVote = decideIfCanVote();
            //printf("%d. szavazó egyéni azonosítója: %d, szavazhat: %d\n", index, tmp.ID, tmp.canTheyVote);
            index++;
            write(child_one_to_child_two[1], &tmp, sizeof(tmp));
        }

        close(child_one_get_data[0]);
        close(child_one_to_child_two[1]);
        
        printf("Kill előtt!");
        kill(pid_child_2, SIGINT);
        printf("Kill után!");
        exit(0);
    } else {
        child_two = fork();
        if (child_two == -1) { 
            perror("Fork hiba");
            exit(EXIT_FAILURE);
        }
        if(child_two == 0) { //Second child process
            close(child_one_to_child_two[1]);
            close(child_one_get_data[0]);
            close(child_one_get_data[1]);
            pid_child_2 = getpid();
            sleep(3);
            kill(getppid(), SIGUSR2);
            
            signal(SIGINT, signalHandler3);
            pause();

            Voter tmp;
            int num = 0;
            while(read(child_one_to_child_two[0], &tmp, sizeof(tmp)) > 0){
                if(tmp.canTheyVote) {
                    printf("A %d azonosítójú szavazó szavazhat.\n", tmp.ID);
                } else {
                    printf("A %d azonosítójú szavazó nem szavazhat.\n", tmp.ID);
                }
            }
            close(child_one_to_child_two[0]);
            exit(0);
        } else { //Parent process
            pause();
            pause();
            printf("Elnök várja a szavazókat: ");
            int howManyVoters = readVoters();
            struct Voter voters[howManyVoters];
            int randomID;
            int i = 0;
            srand(time(NULL));
            initVoters(&voters, howManyVoters);
            while(i < howManyVoters) {
                randomID = rand() % (howManyVoters + 1);
                if(isRandomUsed(&voters, howManyVoters, randomID)){
                    randomID = rand() % (howManyVoters + 1); 
                } else {
                    voters[i].ID = randomID;
                    i++;
                }
            }
            close(child_one_to_child_two[1]);
            close(child_one_to_child_two[0]);
            close(child_one_get_data[0]);
            for (int i = 0; i < howManyVoters; i++) {
                write(child_one_get_data[1], &voters[i], sizeof(Voter));
            }
            close(child_one_get_data[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}