/**
 * @ref https://www.csl.mtu.edu/cs4411.ck/www/NOTES/signal/kill.html
 */

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
// key_t

int     shm_id;
pid_t*  shm_ptr;

/**
 *
 */
void SIGINT_handler(int sig)
{
    signal(sig, SIG_IGN);
    printf("From SIGINT: just got a %d (SIGINT ^C) signal\n", sig);
    signal(sig, SIGINT_handler);
}

/**
 *
 */
void SIGQUIT_handler(int sig)
{
    signal(sig, SIG_IGN);
    printf("From SIGQUIT: just got a %d (SIGQUIT ^\\) signal"
           "and is about to quit\n", sig);
    shmdt(shm_ptr);
    shmctl(shm_id, IPC_RMID, NULL);
    exit(3);
}

/**
 * Process 0
 */
int main(int argc, char **argv)
{
    pid_t   this_pid;
    key_t   this_key;
    int     ct;

    if(signal(SIGINT, SIGINT_handler) == SIG_ERR){
        printf("SIGINT error\n");
        exit(1);
    }
    if(signal(SIGQUIT, SIGQUIT_handler) == SIG_ERR){
        printf("SIGQUIT error\n");
        exit(1);
    }

    this_pid    = getpid();
    this_key    = ftok(".", 's');
    shm_id      = shmget(this_key, sizeof(pid_t), IPC_CREAT | 0666);
    shm_ptr     = (pid_t*) shmat(shm_id, NULL, 0);
    *shm_ptr    = this_pid;

    ct = 0;
    while(1){
        printf("process [%d]: %d\n", this_pid, ct++);
        sleep(2);
    }

    return 0;
}
