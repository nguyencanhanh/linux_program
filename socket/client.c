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
    char buff_r[50];
    char buff_s[50];

    while(1)
    {
        printf("Message to server: ");
        fgets(buff_s, 50, stdin);
        write(fd, buff_s, 50);

        printf("Message from server: ");
        read(fd, buff_r, 50);
        printf("%s",buff_r);
    }

}
int main(int argc, char *argv[])
{
    int ser_fd;
    struct sockaddr_in ser_addr;

    ser_fd = socket(AF_INET, SOCK_STREAM, 0);

    ser_addr.sin_port = htons(atoi(argv[2]));
    ser_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &ser_addr.sin_addr.s_addr);

    connect(ser_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

    chat_func(ser_fd);

    close(ser_fd);

    return 0;
}
