#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFSIZE 20

bool is_prime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFSIZE] = {0};
    char response[BUFSIZE] = {0};

    // Criação do socket do servidor
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro ao criar socket do servidor");
        exit(EXIT_FAILURE);
    }

    address.sin_family = PF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Vincula o socket do servidor a um endereço e porta
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Erro no vinculo do socket do servidor");
        exit(EXIT_FAILURE);
    }
    }

    // Inicia a escuta por conexões
    if (listen(server_fd, 5) < 0) {
        perror("Erro na escuta por conexões");
    // Inicia a escuta por conexões
    if (listen(server_fd, 5) < 0) {
        perror("Erro na escuta por conexões");
        exit(EXIT_FAILURE);
    }

    printf("Aguardando conexão do produtor...\n");

    // Aceita a conexão do produtor
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Erro na aceitação da conexão");
    printf("Aguardando conexão do produtor...\n");

    // Aceita a conexão do produtor
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Erro na aceitação da conexão");
        exit(EXIT_FAILURE);
    }

    printf("Conexão estabelecida com o produtor.\n");

    // Loop para receber os números do produtor
    while (true) {
        memset(buffer, 0, BUFSIZE);
        valread = recv(new_socket, buffer, BUFSIZE, 0);

        if (strcmp(buffer, "0") == 0) {
            // Sinal de término recebido, encerra o loop
            break;
        }

        int number = atoi(buffer);
        bool is_prime_number = is_prime(number);

        // Prepara a resposta com o resultado de ser primo ou não
        if (is_prime_number) {
            strcpy(response, "é primo");
        } else {
            strcpy(response, "não é primo");
        }

        // Envia a resposta ao produtor
        send(new_socket, response, BUFSIZE, 0);
    }

    printf("Término da conexão com o produtor.\n");

    printf("Fechando socket do servidor.\n");

    // Fecha o socket do servidor
    close(server_fd);

    return 0;
}
