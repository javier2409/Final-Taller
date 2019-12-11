/*
Escriba un programa que reciba por línea de comandos un Puerto y una IP. El programa debe recibir
una única conexión e imprimir en stdout la sumatoria de los enteros recibidos en cada paquete. Un
paquete está definido como una sucesión de números recibidos como texto, en decimal, separados por
comas y terminado con signo igual (ej: 27,12,32=). Al recibir el texto ‘FIN’ debe finalizar el programa
ordenadamente liberando los recursos.
*/

#define _POSIX_C_SOURCE 200112L
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

int main(int argc, char* argv[]){
    char* ip = argv[1];
    char* port = argv[2];

    // BIND AND LISTEN
    struct addrinfo hints;
    struct addrinfo* res;
    struct addrinfo* ptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, port, &hints, &res);

    int sockfd = -1;
    for (ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int b = bind(sockfd, ptr->ai_addr, ptr->ai_addrlen);
        int l = listen(sockfd, 1);
        if (b && l) break;
    }

    if (sockfd <= 0) return 1;
    freeaddrinfo(res);

    //ACCEPT
    int peerfd = accept(sockfd, NULL, NULL);

    //LOOP
    char buffer[BUFSIZE];
    bool exit = false;
    while(!exit){

        //RECIBIR
        memset(buffer, 0, BUFSIZE);
        for (int i = 0; i < BUFSIZE; i++){
            recv(peerfd, &buffer[i], 1, 0);
            if (i == 2 && strncmp(buffer, "FIN", BUFSIZE) == 0){
                exit = true;
                break;
            }
            if (buffer[i] == '=')
                break;
        }
        if (exit) break;
        
        printf("Recibido: %s \n", buffer);

        //IMPRIMIR SUMATORIA
        char num[BUFSIZE];
        memset(num, 0, BUFSIZE);

        int count = 0;
        for (int i = 0; i < BUFSIZE; i++){
            if (buffer[i] == '=') {
                count += atoi(num);
                break;
            } else if (buffer[i] == ','){
                count += atoi(num);
            } else {
                num[i] = buffer[i];
            }
        }
        printf("Sumatoria: %d \n", count);
    }

    close(sockfd);
    close(peerfd);
}
