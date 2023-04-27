#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define BUFSIZE 20

int main(int argc, char const *argv[]) {

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFSIZE] = {0};
    int numbers_count;

    printf("Por favor, diga a quantidade de números que gostaria de enviar.\n");
    scanf("%d", &numbers_count);

    // Criação do socket do cliente
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar socket do cliente");
        return -1;
    }

    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(PORT);

    // Estabelecimento de conexão com o consumidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erro na conexão com o consumidor");
        return -1;
    }

    printf("Conexão estabelecida com o consumidor.\n");

    int n0 = 1;
    int delta = 0;
    int seq_num = n0 + delta;

    // Altera o seed para o random gerar números aleatórios a cada run
    time_t t = time(NULL);
    srandom((unsigned int) t);

    // Loop para gerar e enviar os números para o consumidor
    for (int i = 0; i < numbers_count; i++) {
        sprintf(buffer, "%d", seq_num);

        printf("%d - Enviando número: %d.\n", i+1, seq_num);
        send(sock, buffer, BUFSIZE, 0);

        // Aguarda a resposta do consumidor
        memset(buffer, 0, BUFSIZE);
        int valread = recv(sock, buffer, BUFSIZE, 0);

        // Verifica se a resposta foi recebida corretamente
        if (valread == -1) {
            perror("Erro na recepção da resposta do consumidor");
            exit(EXIT_FAILURE);
        } else if (valread == 0) {
            printf("O consumidor fechou a conexão.\n");
            exit(EXIT_SUCCESS);
        } else {
            printf("-- Resposta do consumidor: %s\n", buffer);
        }

        delta = (random() % 100 + 1);
        seq_num = seq_num + delta;

    }

    printf("Término da conexão com o consumidor.\n");

    // Envia sinal de término (número 0)
    sprintf(buffer, "0");
    send(sock, buffer, BUFSIZE, 0);

    // Fecha o socket do cliente
    close(sock);
    // Fecha o socket do cliente
    close(sock);

    return 0;
}


