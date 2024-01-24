#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Could not create socket.\n");
        return -1;
    }

    printf("Socket created successfully.\n");

    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);

    printf("server struct set up.\n");

    // Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        puts("connect error");
        close(socket_desc);
        return -1;
    }

    printf("Connected.\n");

    // sending data to server
    char *message = "Hello from long long time ago!!!";
    if (send(socket_desc, message, strlen(message), 0) < 0)
    {
        puts("send failed.");
        return -1;
    }

    puts("message sent.\n");

    close(socket_desc);

    return 0;
}