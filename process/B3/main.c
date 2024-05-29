#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void func(int signum)//signal handler
{
    printf("Im in func()\n");
    wait(NULL);
}

int main()
{
    pid_t child_pid;

    child_pid = fork();//fork process

    if (child_pid >= 0)
    {
        if (child_pid == 0)
        {
        printf("I am the child process \n"); //child process
        printf("My PID is : %d , my parent PID is : %d \n", getpid(), getppid());
        sleep(3);
        printf("End child process\n");
        }
        else {
        printf("I am the parent process \n");
        printf("My PID id %d \n",getpid());

        signal(SIGCHLD, func);//signal register

        while(1) {
            printf("Process parrent running .....\n");
            sleep(1);
        }

        printf("End of parrent process \n");
        }
     }
    else {
        printf("Fork unsuccessfully\n");
    }

    return 0;
}