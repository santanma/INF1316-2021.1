#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define STRING_SIZE 30

int main(int argc, char* argv[])
{
    for(int i = 0;i < 3;i++)
    {
        if(fork() == 0)
        {
            switch (i)
            {
                case 0: ;
                    char *argsZero[]={"./bomdia",NULL};
                    execvp(argsZero[0],argsZero);
                    break;
                case 1: 
                    system("cat bomdia.c");
                    printf("\n");
                    break;
                case 2: ;
                    // Simular com Echo sempre Recebendo Exatamente 3 Argumentos
                    // Facilitar a Implementação
                    char *argsTwo[]={"./meuecho",argv[1],argv[2],argv[3],NULL};

                    execvp(argsTwo[0],argsTwo);
                    break;
            }

            printf("Terminando Processo Filho\n");
            exit(200);
        }
    }

    sleep(3);
    printf("Terminando Processo Pai\n");
}