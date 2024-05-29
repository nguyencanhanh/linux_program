#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER ;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t condt = PTHREAD_COND_INITIALIZER;
pthread_cond_t condk = PTHREAD_COND_INITIALIZER;
pthread_t id1,id2,id3;
int fd;
int i=0;
int j=0;
int k=1;
int count = 1;
typedef struct{
    char name[20];
    char born[5];
    char hown_town[20];
}person;

static void *func1(void *para)
{
    while(1){
    pthread_mutex_lock(&m);

    //wait for signal in thread3
    while(!k)
    {
        pthread_cond_wait(&condk,&m);
    }

    //enter information 
    printf("Enter person's infor number: %d\n",count);
    count++;
    person *p= (person *)para;
    printf("Enter name : ");
    gets(p->name);
    printf("Enter born year: ");
    gets(p->born);
    printf("Enter Howmtown: ");
    gets(p->hown_town);

    //number to check conditional of signal
    i=1;
    k=0;

    //send signal to thread2
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&m);
    }
}

static void *func2(void *para)
{
    while(1)
    {
    pthread_mutex_lock(&m);
    
    //wait for signal in thread1
    while(!i)
    {
        pthread_cond_wait(&cond,&m);
    }

    person *p= (person *)para;
    char str[47];

    //write person's infor just entered in thread1 to file
    sprintf(str,"%s %s %s\n",p->name,p->born,p->hown_town);
    write(fd,str,strlen(str));

    //number to check conditional of signal
    i=0;
    j=1;

    //send signal to thread3
    pthread_cond_signal(&condt);
    pthread_mutex_unlock(&m);
    }

}

static void *func3(void *para)
{
    while(1)
    {
    pthread_mutex_lock(&m);

    //wait for signal in thread1
    while(!j){
        pthread_cond_wait(&condt,&m);
    }
    person *p= (person *)para;

    //print person's infor just entered in thread1 in terminal
    char str[47];
    sprintf(str,"%s %s %s\n",p->name,p->born,p->hown_town);
    printf("%s",str);

    //number to check conditional of signal
    j=0;
    k=1;

    //send signal to thread1
    pthread_cond_signal(&condk);
    pthread_mutex_unlock(&m);
    }
}

int main()
{
    person pe;

    //create file txt
    fd = open("text.txt",O_RDWR | O_CREAT | O_APPEND, 0667);

    if (pthread_create(&id1,NULL,&func1,&pe)){
        printf("Create Thread 1 Error\n");
    }
    
    if (pthread_create(&id2,NULL,&func2,&pe)){
        printf("Create Thread 2 Error\n");
    }
    
    if (pthread_create(&id3,NULL,&func3,&pe)){
        printf("Create Thread 3 Error\n");
    }
    
    while(1);
    close(fd);

    return 0;

}