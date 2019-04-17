#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

// This is, in theory, the maximum size of a UDP packet before it splits into multiple packets
#define DATA_SIZE 1472

int sockfd;

void setupSocket(const char *addr, int port) {
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servaddr = {0};
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(addr);

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("Error : Connect Failed \n");
        exit(EXIT_FAILURE);
    }
}

void cleanup() {
    close(sockfd);
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Packet train sender tool\n");
        printf("\nDescription:\n");
        printf("  This is a tool that will send a train of UDP packets at a set interval to a target destination\n");
        printf("\nUsage:\n");
        printf("  %s <ip> <port> <usec_interval> <train_size> <amount>\n\n", argv[0]);
        printf("  ip: The ip adress of a UDP server\n");
        printf("  port: The port of the UDP server\n");
        printf("  usec_interval: Interval between packet trains in usecs\n");
        printf("  train_size: Amount of packets to send per train\n");
        printf("  amount: Amount of trains to send\n");
        printf("\nExample:\n");
        printf("  %s 127.0.0.1 5000 1100 2 1000\n", argv[0]);
        printf("  Send 1000 packet trains of a lenght of 2 to 127.0.0.1:5000 at an interval of 1100 usec\n\n");
        return EXIT_FAILURE;
    }

    int port = atoi(argv[2]);
    int usec = atoi(argv[3]);
    int trainSize = atoi(argv[4]);
    int amount = atoi(argv[5]);

    setupSocket(argv[1], port);

    uint8_t data[DATA_SIZE] = {trainSize, 0};
    for (int a = 0; a < amount; ++a) {
        printf("Sending train no %d of size %d\n", a, trainSize);
        for (int j = 0; j < trainSize; ++j) {
            data[1] = j;
            send(sockfd, data, DATA_SIZE, 0);
        }
        usleep(usec);
    }

    cleanup();

    printf("\nSent %d trains of size %d at an interval of %d usecs\n", amount, trainSize, usec);
    printf("%d_%d_%d\n", amount, trainSize, usec);

    return EXIT_SUCCESS;
}