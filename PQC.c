#include "PQC.h"

int main() {

    char *ip = "127.0.0.1";
    int port = 80;

    //initialize server and client address
    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;

    //initialize buffer
    char buffer[1024];
    int n;

    //using tcp
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("Scoket error");
        exit(1);
    }

    printf("[PQC]TCP server initialized successful!\n");


    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;//AF_INET means internet version 4
    addr.sin_port = port; //which we have already defined as 80
    addr.sin_addr.s_addr = inet_addr(ip); //which we have already defined "127.0.0.1"


    //start connection
    int verification_value;
    verification_value = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(verification_value < 0) {
        perror("Unable to establish connection to the PPS!\n");
        exit(1);
    }
    else{
        printf("[PQC]Connected to the PPQ.\n");
    }
    
    while(strcmp(buffer, "Exit") != 0) {
        //send message
        bzero(buffer, 1024); // clean the data
        strcpy(buffer, "Please select from one of following options: \"Type\" for Type search, \"Save\" for Save results, \"Exit\" for Exit the program: ");
        printf("[PQC]Client send: %s\n", buffer);

        bzero(buffer, 1024);
        scanf("%s", buffer);
        //need to add a method to verify input
        send(sock, buffer, strlen(buffer), 0);
        if(strcmp(buffer, "Type") == 0) {
            printf("Please enter the type you want to search: \n");
            bzero(buffer, 1024);
            scanf("%s", buffer);
            send(sock, buffer, strlen(buffer), 0);
        }
        else if(strcmp(buffer, "Save") == 0) {
            printf("Please enter the path you want to save: \n");
            bzero(buffer, 1024);
            scanf("%s", buffer);
            send(sock, buffer, strlen(buffer), 0);
        }

        //recieve message
        bzero(buffer, 1024); // clean the data
        recv(sock, buffer, sizeof(buffer), 0);
        printf("[PQC]Server send: %s\n", buffer);
    }
    
    close(sock);
    return 0;
}

