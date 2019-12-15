/*
Defina una rutina que se conecte al puerto 9000 y acepte conexiones de forma secuencial. Al aceptar
una conexión, se escuchan los caracteres enviados por el cliente y se cierra la conexión. Si el cliente
envia ‘Q’, se dejan de recibir conexiones y finaliza el programa.
*/

/*
NOTA: Asumo que se pide escuchar los caracteres hasta que el cliente se desconecte porque no aclara
cuando se termina de escuchar y se pasa al siguiente cliente.
*/

#define _POSIX_C_SOURCE 201112L
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>

static const char* PORT = "9000";

int main(){
    //BIND AND LISTEN
    struct addrinfo hints, *res, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &res);
    int sockfd = -1;
    for(ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int binded = (bind(sockfd, ptr->ai_addr, ptr->ai_addrlen) == 0);
        int listening = (listen(sockfd, 1) == 0);
        if (binded && listening) break;
    }
    freeaddrinfo(res);

    bool exit = false;
    while(!exit){
        //ACCEPT
        int peerfd = accept(sockfd, NULL, NULL);

        //RECV
        bool client_disconnected = false;
        while (!client_disconnected){
            char buf = 0;
            int r = recv(peerfd, &buf, 1, 0);
            if (r <= 0){
                client_disconnected = true;
            } else {
                if (buf == 'Q'){
                    exit = true;
                    client_disconnected = true;
                } else {
                    //no pide printearlo pero es para probar
                    //este "else" se puede eliminar
                    printf("%s", &buf);
                }
            }
        }

        //SHUTDOWN AND CLOSE
        shutdown(peerfd, SHUT_RDWR);
        close(peerfd);
    }
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}
