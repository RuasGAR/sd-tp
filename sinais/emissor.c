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
        printf("Não existe um processo de número %d! Tente novamente com outro PID.\n",pid);
    } else {
        // Enviando o sinal...
        int sent = kill(pid,signal_num);
        if(sent>0){
            printf("O sinal de número %d foi enviado ao processo de PID %d\n", signal_num, pid);
        }else{
            printf("Erro desconhecido ao enviar o sinal. Tente novamente!\n");
        }
    }

    
}


