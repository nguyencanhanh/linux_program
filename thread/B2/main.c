#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t id1, id2;
typedef struct {
    char name[20];
    int born;
    char phone[12];
    char home_town[20];
}human;

static void *handle(void *argv)
{
    pthread_t idx = pthread_self();
    human *h = (human *)argv;
    if (pthread_equal(idx,id1))
    {
        printf("This is tnread 1\n");

    }
    else{
        printf("This is thread 2\n");
        printf("Print from thread 2: %s %d %s %s \n",h->name, h->born, h->phone,h->home_town);
    }

}
int main()
{
    human person;

    printf("Enter name for person : ");
    gets(person.name);
    printf("Enter born year for person : ");
    scanf("%d",&person.born);
    getchar();
    printf("Enter phone number for person : ");
    gets(person.phone);
    printf("Enter home town for person : ");
    gets(person.home_town);

    if( pthread_create(&id1,NULL,&handle,NULL)){
        printf("Can not create thread 1\n");
    }
    if ( pthread_create(&id2,NULL,&handle,&person)){
        printf("Can not create thread 2\n");
    }

    sleep(1);
    
    return 0;
}