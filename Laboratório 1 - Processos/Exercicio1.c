#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 

#define ERRO_FILHO -100 // Indica Erro Na Geração do Processo
#define ERRO_NETO -200 // Indica Erro Na Geração do Processo
#define SUCCESS 200

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

   iPidFilho = fork();
   if (iPidFilho < 0)
      exit(ERRO_FILHO);
 
   if(iPidFilho != 0) // PAI
   {
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
      fprintf(log,"%s%d\n","Processo PAI vai Finalizar - PID:",getpid());

      wait(&status);

      fclose(log);
   }
   else if(iPidFilho == 0)
   {
      pid_t iPidNeto;
      iPidNeto = fork();
         if (iPidNeto < 0)
            exit(ERRO_NETO);
      
      if(iPidNeto != 0) // FILHO
      {
         fprintf(log,"%s\n","FILHO foi Criado");
         fprintf(log,"%s%d\n","FILHO - PID: ", getpid());
         fprintf(log,"%s%d\n","FILHO - PPID: ", getppid());

         for(index = 1000; index <= 1999; index++)
         {
            fprintf(log,"%s%d\n","Valor a ser somado FILHO = ",index);
            soma += index;
            fprintf(log,"%s%d\n","Soma Parcial FILHO = ",soma);
         }

         fprintf(log,"%s%d\n","Processo FILHO vai Finalizar - PID:",getpid());
         wait(&status);
         exit(SUCCESS);
      }
      else if (iPidNeto == 0) //NETO
      {
         fprintf(log,"%s\n","NETO foi Criado");

         for(index = 2000; index <= 2999; index++)
         {
            fprintf(log,"%s%d\n","Valor a ser somado NETO = ",index);
            soma += index;
            fprintf(log,"%s%d\n","Soma Parcial NETO = ",soma);
         }
         
         fprintf(log,"%s%d\n","Processo NETO vai Finalizar - PID:",getpid());
         exit(SUCCESS);
      }
   }
 }