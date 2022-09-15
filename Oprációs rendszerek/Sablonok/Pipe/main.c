#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX_MSG_LENGTH 256

typedef struct Pipe {
    int read_end[2];
    int write_end[2];
} Pipe;

typedef struct Message {
    char msg[MAX_MSG_LENGTH];
} Message;

void fork_error(pid_t fork_pid) {
    if (fork_pid == -1) {
        perror("Fork hiba");
        exit(EXIT_FAILURE);
    }
}

void open_pipe(Pipe* var_pipe) {
    if (pipe(var_pipe->read_end) == -1) {
        perror("Error on opening pipe.read_end!");
        exit(EXIT_FAILURE);
    }
    if (pipe(var_pipe->write_end) == -1) {
        perror("Error on opening pipe.write_end!");
        exit(EXIT_FAILURE);
    }
}

void close_pipe(Pipe* var_pipe) {
    close(var_pipe->read_end[0]);
    close(var_pipe->write_end[0]);
    close(var_pipe->read_end[1]);
    close(var_pipe->write_end[1]);
}

void write_in_parent_to_pipe(const Pipe var_pipe, Message m) {
    //close(var_pipe.read_end[0]);
    printf("Parent is writing this to pipe: \n %s", m.msg);
    write(var_pipe.read_end[1], &m, sizeof(Message));
    Message read_m;
    sleep(1);
    read(var_pipe.read_end[0], &read_m, sizeof(Message));
    printf("%s", read_m.msg);
    close(var_pipe.read_end[1]);
}

void read_in_parent_from_pipe(const Pipe var_pipe) {
    Message read_m;

    printf("Parent is reading message from pipe...\n");

    read(var_pipe.write_end[0], read_m.msg, sizeof(read_m.msg));

    printf("Parent read this:\n%s", read_m.msg);
}

void read_and_write_in_child_to_pipe(const Pipe var_pipe, Message m) {
    close(var_pipe.read_end[1]);
    close(var_pipe.write_end[0]);

    Message read_m;
    printf("Child is reading from pipe...\n");
    read(var_pipe.read_end[0],&read_m, sizeof(Message)+1);
    printf("Child read this:\n%s\n", read_m.msg);

    printf("Child is writing to pipe...\n");
    write(var_pipe.write_end[1], m.msg, sizeof(m.msg));

    close(var_pipe.read_end[0]);
    close(var_pipe.write_end[1]);
}

int main(int argv, char** args) {

    pid_t first_child_pid, second_child_pid;
    Pipe first_child_pipe, second_child_pipe;
    open_pipe(&first_child_pipe);
    first_child_pid = fork();

    fork_error(first_child_pid);

    if(first_child_pid == 0) { //First child process
        sleep(2);
        printf("First child process starts...\n");
        printf("First child reads and writes to pipe...\n");

        Message first_child_message;
        strcpy(first_child_message.msg ,"I know, I am the first and best.");

        read_and_write_in_child_to_pipe(first_child_pipe, first_child_message);

        printf("First child process ends...\n");
        exit(0);
    } else { //Second child process
        open_pipe(&second_child_pipe);
        second_child_pid = fork();
        fork_error(second_child_pid);

        if(second_child_pid == 0){
            sleep(3);
            printf("Second child process starts...\n");

            close_pipe(&first_child_pipe);

            Message second_child_message;
            strcpy(second_child_message.msg ,"I love you too, as a second child.");

            printf("Second child reads and writes to pipe...\n");
            read_and_write_in_child_to_pipe(second_child_pipe, second_child_message);

            printf("Second child process ends...\n");
            exit(0);
        } else { //Parent process
            printf("Parent process starts...\n");

            Message msg_to_first_child, msg_to_second_child;
            strcpy(msg_to_first_child.msg,"My first child I love you.");
            strcpy(msg_to_second_child.msg, "My second child I love you too.");

            printf("Parent writes in pipes...\n");
            write_in_parent_to_pipe(first_child_pipe, msg_to_first_child);
            write_in_parent_to_pipe(second_child_pipe, msg_to_second_child);
            wait(NULL);
            wait(NULL);
            printf("Parent reads from pipes...\n");
            read_in_parent_from_pipe(first_child_pipe);
            read_in_parent_from_pipe(second_child_pipe);

            close_pipe(&first_child_pipe);
            close_pipe(&second_child_pipe);

            printf("Parent process ends...\n");
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}
