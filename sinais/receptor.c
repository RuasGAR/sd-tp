#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void term_handler(int signum){
    printf("Este programa recebeu uma ordem de interrupção. Vamos ser desligados em 3 segundos.\n");
    sleep(3);
    exit(0);
}

void trap_handler(int signum){
    printf("IT'S A TRAP!, disse Jar Jar Binks.\n");
}

void alarm_handler(int signum){
    printf("Recebi um alarme, mas continuo rodando. Sou como seu sono.\n");
}


int main(int argc, char const *argv[])
{
    int chosen_type;

    printf("Olá, sou o processo %d.\n", getpid());

    printf("Você deseja que este programa utilize qual estratégia de espera?\nDigite o número associado à modalidade escolhida:\n");
    printf("1 - Busy wait  #########  2 - Blocking wait\n");
    scanf("%d", &chosen_type);
    printf("Ok. Vou aguardar de acordo com a estatégia %d.\n", chosen_type);

    signal(SIGTERM, term_handler);
    signal(SIGTRAP, trap_handler);
    signal(SIGALRM, alarm_handler);

    switch (chosen_type)
    {
    case 1:
        while(1==1) {} 
    case 2:
        while(1) {
            pause();
        }       
    default:
        break;
    }

}
