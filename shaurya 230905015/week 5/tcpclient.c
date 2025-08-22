#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int len, result, sockfd;
    struct sockaddr_in address;
    char ch[256], buf[256];

    // Create a socket for the client
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("172.16.48.97");
    address.sin_port = htons(10200);
    len = sizeof(address);

    // Connect to the server
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("CLIENT ERROR");
        exit(1);
    }

    // Input from user
    printf("ENTER STRING: ");
    fgets(ch, sizeof(ch), stdin);
    ch[strcspn(ch, "\n")] = '\0'; // Remove newline

    // Send to server
    write(sockfd, ch, strlen(ch));

    // Read response
    int n = read(sockfd, buf, sizeof(buf) - 1);
    if (n > 0) {
        buf[n] = '\0';
        printf("STRING SENT BACK FROM SERVER IS: %s\n", buf);
    } else {
        perror("Read failed or connection closed");
    }

    close(sockfd);
    return 0;
}

