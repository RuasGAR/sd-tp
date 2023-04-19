#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// constantes
#define BUFSIZE 20
#define ENDING_COND 0
#define POWER 2
#define NULL ((void *)0)



// função principal
int main(int argc, char const *argv[])
{

    // config da randomização
    srand(time(NULL));
    
    int dest_pid;
    int n_total;
    int pipe_channel[2];

    printf("Por favor, diga a quantidade de números que gostaria de enviar.\n");
    scanf("%d", &n_total);

    pipe(pipe_channel);

    dest_pid = fork();

    if (dest_pid > 0) {
        // processo pai

        int n0 = 1;
        int delta = random_part();
        int seq_num = n0 + delta;
        unsigned char sent_buffered_num[BUFSIZE];
    
        for (int i = 0; i < n_total; i++)
        {
            sprintf(sent_buffered_num, "%d", seq_num);
            printf("%d - Enviando número %s.\n", i+1,sent_buffered_num);
            write(pipe_channel[1], sent_buffered_num, BUFSIZE);
            delta = random_part();
            seq_num = seq_num + delta;
        } 
    
        sprintf(sent_buffered_num, "%d", ENDING_COND);
        printf("Enviando o número de PARADA: %s\n", sent_buffered_num);
        write(pipe_channel[1],sent_buffered_num, BUFSIZE);
        

    } else if(dest_pid == 0) {
        // processo filho -> consumidor
        unsigned char received_buffered_num[BUFSIZE];
        
        read(pipe_channel[0], received_buffered_num, BUFSIZE);

        while(atoi(received_buffered_num)!=0) {
            int bool_prime = is_prime(atoi(received_buffered_num),2);
            printf("Chegou o número %s.\n", received_buffered_num);
            if(bool_prime == 1) {
                printf("O número %s é primo.\n", received_buffered_num);
            }
            read(pipe_channel[0], received_buffered_num, BUFSIZE);
        }

    } else {
        printf("Ocorreu algum erro no fork.");
    }

}

int random_part(){
    int num = (random() % 100) + 1;
    return num;
}

int is_prime(int number, int iter) { //iter = 2, cond inicial

    if(number < 2) {
        return 0;
    }
    else if (number == 2) {
        return 1;
    } else if (number % iter == 0){
        return 0;
    } else if (pow((double)iter,(double)POWER) > number){
        return 1;
    } 

    return is_prime(number, iter+1);

}
