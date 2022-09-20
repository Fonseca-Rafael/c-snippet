#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
// key_t
#include <ctype.h>

/**
 *
 */
int main(int argc, char **argv)
{
    pid_t   pid;
    key_t   this_key;
    int     shm_id;
    pid_t*  shm_ptr;
    char    line[100];
    char    c;
    int     i;

    this_key    = ftok(".", 's');
    shm_id      = shmget(this_key, sizeof(pid_t), 0666);
    shm_ptr     = (pid_t*) shmat(shm_id, NULL, 0);
    pid         = *shm_ptr;
    shmdt(shm_ptr);

    while(1){

        printf("Want to interrupt the other process or kill it (i or k)?");
        fgets(line, 100, stdin);
        for(i=0; !(isalpha(line[i])); i++);
        c = line[i];
        if(c == 'i' || c == 'I'){
            kill(pid, SIGINT);
            printf("Sent a SIGINT signal\n");
        }else if(c == 'k' || c == 'K'){
            printf("About to send a SIGQUIT signal\n");
            kill(pid, SIGQUIT);
            printf("Done\n");
            exit(0);
        }else{
            printf("Wrong option (%c). Try again\n", c);
        }


    }

    return 0;
}
