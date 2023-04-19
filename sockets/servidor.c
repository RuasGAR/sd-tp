#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

// IMPORTANTE:
// Adoção do estilo de tratamento de erro visto nas documentações do GNU

int main(int argc, char const *argv[])
{

    
    // AF -> Address Format. São importantes por conta de namespaces (domínios)
    // A documentação do GNU orienta a escolha de protocolo na camada de transporte
    // conforme um "estilo de comunicação". No nosso caso, SOCK_STREAM é optar pelo TCP
    int server = socket(PF_INET,SOCK_STREAM,0); // o 0 indica uso do IP

    // Criando um nome e fazendo um binding com o socket criado
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons(PORT);
    name.sin_addr.s_addr = htonl(INADDR_ANY);

    int binding = bind(server, (struct sockaddr*) &name, sizof(name));
    if (binding < 0) {
        perror("Problems with binding.");
        exit(EXIT_FAILURE);
    }    

    if(listen(server, 1) < 0) {
        perror("Problemas no listening do socket.");
        exit(EXIT_FAILURE);
    }

    // Especificando o tamanho do formato que esperamos receber e aceitando uma conexão
    int addlen = sizeof(name);
    int accepted_socket;
    if (accepted_socket = accept(server, (struct sockaddr*) &name, addlen) < 0) {
        perror("Problemas no aceite.");
        exit(EXIT_FAILURE);
    }


    return 0;
}
