#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int server_desc, client_fd;
    struct sockaddr_in server, client;
    int port = 12345;
    server_desc = socket(AF_INET, SOCK_STREAM, 0);
    char *message;

    if (server_desc < 0)
    {
        perror("Cannot create socket");
        return -1;
    }

    // Prepare the sockaddr_in structure
    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    // Bind
    if (bind(server_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
        return -1;
    }
    puts("bind done");

    if (listen(server_desc, 3) < 0)
    { // 10 is the backlog - max number of pending connections
        perror("Listen failed");
        close(server_desc);
        return -1;
    }

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    socklen_t client_len = sizeof(client);

    while (client_fd = accept(server_desc, (struct sockaddr *)&client, (socklen_t *)&client_len))
    {
        puts("Connection accepted");
        // reply to the client
        message = "I gotcha bro!!!";
        write(client_fd, message, strlen(message));
    }

    if (client_fd < 0)
    {
        perror("accept failed");
        close(server_desc);
        return -1;
    }

    return 0;
}
