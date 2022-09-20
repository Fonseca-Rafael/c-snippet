/**
 * @ref: https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-sigsuspend-change-mask-suspend-thread
 */

#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

/**
 * @brief   signal processing
 */
void signal_catch(int signum)
{
    switch(signum){
        case SIGUSR1:
            printf("signal catch SIGUSR1\n");
            break;
        case SIGUSR2:
            printf("signal catch SIGUSR2\n");
            break;
        default:
            printf("signal catch unexpected signal %d\n", signum);
    }
}

/**
 *
 */
int main(int argc, char **argv)
{

    sigset_t            this_set;
    struct sigaction    this_action;
    time_t              t;

    if(fork() == 0){
        sleep(10);
        printf("child is sending SIGUSR2 signal - blocked\n");
        kill(getppid(), SIGUSR2);
        sleep(5);
        printf("child is sending SIGUSR1 signal - caught\n");
        kill(getppid(), SIGUSR1);
        exit(0);
    }

    sigemptyset(&this_action.sa_mask);
    this_action.sa_flags    = 0;
    this_action.sa_handler  = signal_catch;

    if(sigaction(SIGUSR1, &this_action, NULL) != 0){
        perror("1st signaction() error");
        exit(1);
    }

    if(sigaction(SIGUSR2, &this_action, NULL) != 0){
        perror("2dn signaction() error");
        exit(1);
    }

    sigfillset(&this_set);
    sigdelset(&this_set, SIGUSR1);
    time(&t);

    printf("Parent is waiting for child to send SIGUSR1 at %s",
            ctime(&t));

    if(sigsuspend(&this_set) == -1)
        perror("sigsuspend() returned -1 as expected");

    time(&t);

    printf("sigsuspend is over at %s\n", ctime(&t));

    return 0;
}
