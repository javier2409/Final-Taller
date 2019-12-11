#define _POSIX_C_SOURCE 200112L
#include<stdbool.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<memory.h>
#include<stdio.h>
#include<netdb.h>

#define MAXLEN 20

typedef struct{
    int self_fd;
    int peer_fd;
} Socket;

void socket_init(Socket* socket){
    //nada
}

void socket_bind_listen(Socket* sock, char* ip, char* port){
    struct addrinfo hints;
    struct addrinfo* ptr;
    struct addrinfo* res;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(ip, port, &hints, &res);

    for (ptr = res; ptr != NULL; ptr = ptr->ai_next){
        sock->self_fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int b = bind(sock->self_fd, ptr->ai_addr, ptr->ai_addrlen);
        int l = listen(sock->self_fd, 1);
        if (b && l)
            break;
    }

    freeaddrinfo(res);
}

void socket_accept(Socket* socket){
    socket->peer_fd = accept(socket->self_fd, NULL, NULL);
}

int socket_receive(Socket* socket, char* buffer, int maxlen){
    int bytes = 0;
    while (bytes < maxlen){
        char buf;
        ssize_t bytes_now = recv(socket->peer_fd, &buf, 1, 0);
        printf("Buf: %d \n", buf);
        if (bytes_now > 0){
            buffer[bytes] = buf;
            bytes += bytes_now;
        }
        if (buf == ']')
            break;
    }
    printf("finished recv\n");
    return bytes;
}

void socket_clean(Socket* socket){
    shutdown(socket->self_fd, SHUT_RDWR);
    shutdown(socket->peer_fd, SHUT_RDWR);
    close(socket->self_fd);
    close(socket->peer_fd);
}

bool parse(char* buffer, int len){
    if (buffer[0] != '[' || len < 2)
        return true;
    int checksum = 0;
    for (int i = 1; i < len; i++){
        if (buffer[i] != ']')
            checksum += buffer[i];
    }
    if (checksum == 0)
        return true;
    printf("Checksum: %d \n", checksum);
    return false;
}

int main (int argc, char* argv[]){
    char* port = argv[1];
    char* ip = argv[2];

    Socket sock;
    socket_init(&sock);
    socket_bind_listen(&sock, ip, port);
    socket_accept(&sock);

    bool salir = false;
    while (!salir){
        char buffer[MAXLEN];
        int bytes = socket_receive(&sock, buffer, MAXLEN);
        salir = parse(buffer, bytes);
    }

    socket_clean(&sock);
}
