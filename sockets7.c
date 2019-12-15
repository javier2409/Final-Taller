/*
Defina una rutina en C que se conecte a la IP 10.10.10.10, bajo el puerto 9000 y reciba un archivo
binario. El archivo debe ser descargado a un archivo llamado ‘datos.bin’, cuidando el uso de recursos
de memoria. El archivo finaliza al detectar conexión cerrada.
*/

//NOTA: Me voy a conectar a localhost para poder probar el programa

#define _POSIX_C_SOURCE 201112L
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <unistd.h>

static const char* IP = "localhost";
static const char* PORT = "9000";
static const char* FILENAME = "datos.bin";

int main(int argc, char** argv){
    struct addrinfo hints, *res, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(IP, PORT, &hints, &res);

    int sockfd = -1;
    for (ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        bool connected = connect(sockfd, ptr->ai_addr, ptr->ai_addrlen) == 0;
        if (connected) break;
    }
    freeaddrinfo(res);

    FILE* file = fopen(FILENAME, "wb");

    bool exit = false;
    while (!exit){
        char buf;
        int r = recv(sockfd, &buf, 1, 0);
        if (r <= 0) break;

        fwrite(&buf, 1, 1, file);
    }

    fflush(file);
    fclose(file);

    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}