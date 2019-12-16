/*
Escriba una función que dado un arreglo de file descriptors de sockets ‘list’, la cantidad de sockets ‘qty’
y una cadena de caracteres ‘text’ finalizada en NULL, envíe todo el contenido de ‘text’ a cada uno de
los sockets. A su vez, se debe esperar una respuesta de 2 bytes de cada socket para retornar true si
todas las respuestas fueron ‘OK’ y false en caso contrario.
*/

//Para probar este programa habria que hacer un servidor que reciba muchos clientes

#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdbool.h>

bool funcion(int* list, int qty, char* text){
    bool all_ok = true;
    for (int socket = 0; socket < qty; socket++){
        for (int i = 0; text[i] != 0; i++){
            send(list[socket], &text[i], 1, 0);
        }
        char buf[2];
        recv(list[socket], buf, 2, 0);
        if (strncmp(buf, "OK", 2) != 0)
            all_ok = false;
    }
    return all_ok;
}