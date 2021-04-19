#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 

#define ERRO -200 // Indica Erro Na Geração do Processo
#define N_FILHOS 3

int main(void)
{
   pid_t iPidFilho;
   FILE *log;
   char fileName[30];
   int soma = 0;
   int index;
   int status;

   strcpy(fileName,"Log_");
   strcat(fileName,__FILE__);
   strcat(fileName,"_.txt");

   log = fopen(fileName, "a");

   // FILHO
   for (int i = 1; i <= N_FILHOS; i++)
   {
      iPidFilho = fork();
      if (iPidFilho < 0)
        exit(ERRO); 
      else if(iPidFilho == 0)
      {
        fprintf(log,"%s\n","FILHO foi Criado");
        fprintf(log,"%s%d\n","FILHO - PID: ",  getpid());
        fprintf(log,"%s%d\n","FILHO - PPID: ", getppid()); 

        for(index = 1000 * i; index <= 2000 * i; index++)
        {
            fprintf(log,"%s%d\n","Valor a ser somado FILHO = ",index);
            soma += index;
            fprintf(log,"%s%d\n","Soma Parcial FILHO = ",soma);
        }

        fprintf(log,"%s%d\n","Processo FILHO vai Finalizar - PID: ",getpid());
        exit(i);
      }
   }

   // PAI
   fprintf(log,"%s\n","PAI foi Criado");
   fprintf(log,"%s%d\n","PAI - PID: ",  getpid());
   fprintf(log,"%s%d\n","PAI - PPID: ", getppid()); 

   for(index = 0; index <= 999; index++)
   {
      fprintf(log,"%s%d\n","Valor a ser somado PAI = ",index);
      soma += index;
      fprintf(log,"%s%d\n","Soma Parcial PAI = ",soma);
   }

   fprintf(log,"%s%d\n","Resultado da Soma PAI = ",soma);
   fprintf(log,"%s%d\n","Processo PAI vai Finalizar - PID: ",getpid());

   for(int i = 1;i <= N_FILHOS; i++)
   {
       pid_t pid = wait(&status);
       if(WIFEXITED(status))
            fprintf(log,"%s %d %d\n","FILHO terminou com Sucesso ",pid,WEXITSTATUS(status));
   }
   
   fclose(log);
 }