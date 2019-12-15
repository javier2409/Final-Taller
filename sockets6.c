/*
Implemente un servidor que escuche en el puerto 5000. El servidor debe aceptar conexiones (de 1 a
la vez) escribiendo el contenido recibido en un archivo (001.txt, 002.txt, etc) y sin responder nada.
Cada conexión debe ser cerrada por el servidor al recibir la palabra “FIN”. Luego de una conexión sin
contenido (se recibe sólo la palabra “FIN”), el servidor debe cerrarse ordenadamente.
*/

#define _POSIX_C_SOURCE 201112L
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>

static const char* PORT = "5000";

int main(){
    //BIND AND LISTEN
    struct addrinfo hints, *res, *ptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, PORT, &hints, &res);

    int sockfd = -1;
    for (ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        bool bound = bind(sockfd, ptr->ai_addr, ptr->ai_addrlen) == 0;
        bool listening = listen(sockfd, 1) == 0;
        if (bound && listening) break;
    }
    freeaddrinfo(res);

    bool exit = false;
    int file_n = 0;
    while(!exit){
        //ACCEPT
        file_n++;
        char filename[9];
        snprintf(filename, 9, "00%d.txt", file_n);
        
        int peerfd = accept(sockfd, NULL, NULL);
        
        FILE* file = fopen(filename, "w");

        bool disconnect = false;
        int bytes_wrote = 0;
        while (!disconnect){
            char end_buffer[3];
            char buf;
            int r = recv(peerfd, &buf, 1, 0);
            for (int i = 0; i < 2; i++){
                end_buffer[i] = end_buffer[i+1];
            }
            end_buffer[2] = buf;
            if (strncmp(end_buffer, "FIN", 3) == 0){
                disconnect = true;
            }
            fwrite(&buf, 1, 1, file);
            bytes_wrote++;
            if (disconnect && bytes_wrote == 3)
                exit = true;
        }  

        fflush(file);
        fclose(file);
        shutdown(peerfd, SHUT_RDWR);
        close(peerfd);     
    }

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}