/*
Defina una rutina en C que se conecte a la IP 10.9.8.7, puerto 7777 y procese la información recibida.
El proceso consiste en recibir textos numéricos utilizando el \n como caracter delimitador. Para
cada entero recibido se debe enviar su valor convertido en 32 bits big-endian en modo binario sin
delimitadores. El proceso finaliza al recibir el valor 0.
*/

//NOTA: Cuando es conectarse es mas facil porque es solo Connect + Recv + Send + Shutdown/Close

#define _POSIX_C_SOURCE 201112L
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#define BUFSIZE 100

int main(){

    //CONNECT
    struct addrinfo hints, *res, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("localhost", "7777", &hints, &res); //me conecto a localhost para probarlo con netcat
    int sockfd = -1;
    for (ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (connect(sockfd, ptr->ai_addr, ptr->ai_addrlen) == 0) break;
    }
    freeaddrinfo(res);

    //LOOP
    while (1){
        char buffer[BUFSIZE];
        memset(buffer, 0, BUFSIZE);

        //RECV
        for (int i = 0; i < BUFSIZE; i++){
            recv(sockfd, &buffer[i], 1, 0);
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                buffer[BUFSIZE - 1] = '\0'; //asegurar que sea zero-terminated string para el atoi
                break;
            }
        }

        if (buffer[0] == '\0') break;

        //PROCESAR
        int nbr = htonl(atoi(buffer));

        //SEND
        int sent = 0;
        while (sent < 4){
            int sent_now = send(sockfd, (char*)&nbr, 4 - sent, 0);
            sent += sent_now;
        }
    }

    //SHUTDOWN + CLOSE
    shutdown(sockfd, SHUT_RDWR); //el shutdown dijeron en clase que es "opcional"
    close(sockfd);
}
