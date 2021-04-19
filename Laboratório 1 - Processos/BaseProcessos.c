#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERRO -100 // Indica Erro Na Geração do Processo
 
int main(void)
{
   pid_t iPid;
   FILE *log;

   log = fopen("Log.txt", "a");

   iPid = fork();
   if (iPid < 0)
      exit(ERRO);

   if(iPid != 0)
   {
      fprintf(log,"%s","Codigo Executado no Processo Pai\n");
      fprintf(log,"%s%d\n","PAI - Processo pai.   PID: ", getpid());
      fprintf(log,"%s%d\n","PAI - Processo filho. PID: ", iPid);
   }
   else if(iPid == 0)
   {
      fprintf(log,"%s","Codigo executado no processo filho\n");
      fprintf(log,"%s%d\n","FILHO - Processo pai.   PID: ",getppid());
      fprintf(log,"%s%d\n","FILHO - Processo filho. PID: ",getpid());
   }
 
   fprintf(log,"%s%d\n","Finalizando Processo PID: ",getpid());

   fclose(log);
   return 0;
}