

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

int t = 0;

void sig_handler1(int num)
{
    printf("I am signal 1 : %d\n",num);
   // exit(EXIT_SUCCESS);
}


int main()
{
    sigset_t new_set,old_set;
    if (signal(SIGINT,sig_handler1) == SIG_ERR)
    {
        printf("Can not handler SIGINT\n");
     
    }
    
    sigemptyset(&new_set);
    sigemptyset(&old_set);
    sigprocmask(SIG_BLOCK, NULL,&old_set);

    if (sigismember(&old_set,SIGINT) == 1)
    {
        printf("SIGINT exist in signal mask\n");
 
    }
    else
    {
        printf("SIGINT does not exist in signal mask\n");

        sigaddset(&new_set,SIGINT);
        //block SIGINT
        if ( sigprocmask(SIG_BLOCK, &new_set, &old_set) == 0)
        {
            printf("set block for SIGINT OK\n");
        }
        printf("Sending SIGINT !\n");
        kill(getpid(),SIGINT);

        while(t < 4)
        {
            printf("SIGINT is blocking and waiting for unblocking.....\n");
            t++;
            sleep(2);
        }
        //unblock SIGINT
        if (sigprocmask(SIG_UNBLOCK, &new_set, &old_set) == 0) {
            printf ("Set unblock for SIGINT OK\n");
        }
        
        while(1);
        
    }
    
    return 0;
}
