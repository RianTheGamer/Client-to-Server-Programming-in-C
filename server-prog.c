#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Clear serv_addr and set fields
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 8080;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    // Accept a connection
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error on accept");
        exit(1);
    }

    // Generate a random number between 100 and 999
    int random_number = 100 + rand() % (999 - 100 + 1);

    // Send the random number to the client
    n = write(newsockfd, &random_number, sizeof(random_number));
    if (n < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    // Close the socket
    close(newsockfd);
    close(sockfd);
    return 0;
}
