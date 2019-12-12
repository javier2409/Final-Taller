/*
Escriba un programa que reciba paquetes de 10 bytes por el puerto TCP 815 y los imprima por pantalla.
Al recibir el byte 0xff debe cerrarse ordenadamente. No considere errores.
*/

#define _POSIX_C_SOURCE 201112L
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
const char* port = "7777"; //uso puerto 7777 porque con 815 no me anda

int main(){

    //BIND AND LISTEN
    struct addrinfo hints, *res, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, port, &hints, &res);
    int sockfd = -1;
    for (ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        bool binded = (bind(sockfd, ptr->ai_addr, ptr->ai_addrlen) == 0);
        bool listening = (listen(sockfd, 1) == 0);
        if (binded && listening) break;
    }
    freeaddrinfo(res);

    //ACCEPT
    int peerfd = accept(sockfd, NULL, NULL);

    bool exit = false;
    while(!exit){
        //RECV
        char buffer[11]; //uno mas para que sea zero-terminated
        memset(buffer, 0, 11);
        for (int i = 0; i < 10; i++){
            int r = recv(peerfd, &buffer[i], 1, 0);
            if (buffer[i] == 0xff || r <= 0){
                exit = true;
                break;
            }
        }

        //PROCESS
        if (!exit)
            printf("%s \n", buffer); 
    }
}
