#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

pthread_t id1 , id2;
char str[5];
int fd ;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *task1(void *argv)
{
    pthread_mutex_lock(&mutex);

    //write number 0 to 999999 to file
    for (int i=0; i<1000000 ;i++)
    {
        sprintf(str,"%d \n",i);
        write(fd,str,sizeof(str));
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main()
{
    clock_t start_time = clock();//timer counter start
    
    //create file txt2
    fd =  open ("text.txt", O_RDWR | O_APPEND | O_CREAT,0667);
    if (fd == -1){
        printf("Can not open file txt1 \n");
    }

    //create task
    pthread_create(&id1, NULL, &task1,NULL);
    pthread_join(id1,NULL);
    
    clock_t  end_time = clock();//timer counter end
    double time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time_used in case multi thread : %f",time_used);

    close(fd);
    
    return 0;

}