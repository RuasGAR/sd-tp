#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int pid;
    int signal_num;

    printf("Para qual processo você deseja enviar o sinal?\n");
    scanf("%d",&pid);

    printf("Qual sinal você deseja enviar?\n");
    scanf("%d",&signal_num);
     
    // Checando se o processo existe...
    kill(pid,0);
    if(errno == ESRCH){
        printf("Processo inexistente!");
    }

    // Enviando o sinal...
    // precisamos tratar a possibilidade de ter algum erro de privilégio;
}


