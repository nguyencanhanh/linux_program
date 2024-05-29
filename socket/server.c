#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>      
#include <netinet/in.h>     
#include <arpa/inet.h>
#include <unistd.h>

void chat_func(int fd)
{
    char buff_s[50];
    char buff_r[50];

    while(1)
    {
        printf("Message from client : ");
        read(fd, buff_r, 50);
        printf("%s",buff_r);

        
        printf("Message to client : ");
        fgets(buff_s, 50, stdin);
        write(fd, buff_s, 50);

    }
}

int main(int argc, char *argv[])
{
    int ser_id, cli_id;
    struct sockaddr_in ser_addr, cli_addr;

    ser_id = socket(AF_INET , SOCK_STREAM, 0);
    
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(atoi(argv[1]));
    ser_addr.sin_addr.s_addr = INADDR_ANY;
     
    bind(ser_id, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

    listen(ser_id, 5);

    while(1)
    {
        int len = sizeof(cli_addr);
        cli_id = accept(ser_id, (struct sockaddr *)&cli_addr,&len);
        chat_func(cli_id);
    }
    
    close(ser_id);
    close(cli_id);

    return 0;

}
