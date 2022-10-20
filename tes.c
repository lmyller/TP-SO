#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "tes.h"

int main(){
   return iniciar();
}

// Inicia o programa.
int iniciar(){
   setlocale(LC_ALL, LOCALIZACAO);

   tes();

   return EXIT_SUCCESS;
}

// tes
void tes(){
   char entrada[TAMANHO_NOME_ARQUIVO * 4];
   char **nomesArquivos = alocarMemoria(NUMERO_MAXIMO_DE_PROGRAMAS, TAMANHO_NOME_ARQUIVO);
   Programa programas[NUMERO_MAXIMO_DE_PROGRAMAS];
   int numeroDeProgramas, numeroDeProcessos, quantidadeProgramas = NUMERO_MAXIMO_DE_PROGRAMAS;
   pid_t tes1, tes2;

   while(1){
      prompt(entrada);

      retiraBarraN(entrada);

      if(strcmp(entrada, SAIR) == 0){
         break;
      }

      verificarNomesArquivos(entrada, nomesArquivos);

      numeroDeProgramas = lerArquivos(programas, nomesArquivos, quantidadeProgramas);

      if(numeroDeProgramas > 2)
         numeroDeProcessos = 2;

      else
         numeroDeProcessos = 1;

      

      for(int indice = 0; indice < numeroDeProcessos; indice++){
         if(criarProcesso() != 0)
            wait(NULL);

         else
            lpas
      }

      lpas(programas, quantidadeProgramas);
   }
   /*Tarefa tarefaTerminada[argc - 1];
   limparVetor(tarefaTerminada, argc);
   fila filaProcessador = criaFila();
   verificarArquivos(argc, argv, filaProcessador);
   lerArquivo(filaProcessador, tarefaTerminada, argv, argc);
   relatorio(tarefaTerminada, argc);*/
}

void prompt(char *entrada){
   exibirPrompt();

   setbuf(stdin, NULL);
   fgets(entrada, TAMANHO_NOME_ARQUIVO, stdin);
}

void exibirPrompt(){
   printf("tes > ");
}

void verificarNomesArquivos(char *entrada, char *nomesArquivos[]){
   const char delimitador[4] = " ";
   char *token;
   int indice = 0;

   token = strtok(entrada, delimitador);

   while (token != NULL)
   {
      strcpy(nomesArquivos[indice], token);

      token = strtok(NULL, delimitador);

      indice++;
   }
}

char** alocarMemoria(const int linhas, const int colunas){
   char **string = (char**)malloc(sizeof(char*) * NUMERO_MAXIMO_DE_PROGRAMAS);

   for(int indice = 0; indice < NUMERO_MAXIMO_DE_PROGRAMAS; indice++){
      string[indice] = (char*)malloc(sizeof(char) * TAMANHO_NOME_ARQUIVO);
      memset(string[indice], '\0', TAMANHO_NOME_ARQUIVO);
   }

   return string;
}

FILE* abrirArquivo(char* nomeArquivo){
   return fopen(nomeArquivo, "r");
}

int lerArquivos(Programa *programas, char *nomesArquivos[], int quantidadeMaximaProgramas){
   char comando[100];
   Instrucao instrucao;
   int numeroDeInstrucoes, numeroDeProgramas = 0;

   for(int indice = 0; indice < quantidadeMaximaProgramas; indice++){
      if (nomesArquivos[indice][0] == '\0')
      {
         programas[indice].numeroDeInstrucoes = 0;
         continue;
      }
      
      numeroDeProgramas++;

      strcat(nomesArquivos[indice], EXTENSAO);
      FILE* file = abrirArquivo(nomesArquivos[indice]);

      if(file == NULL){
         continue;
      }

      strcpy(programas[indice].nome, nomesArquivos[indice]);

      numeroDeInstrucoes = 0;

      while (fgets(comando, 100, file) != NULL)
      {
         if(comando[0] == ';')
            continue;

         retiraBarraN(comando);

         strcpy(instrucao, comando);

         strcpy(programas[indice].instrucoes[numeroDeInstrucoes], instrucao);

         numeroDeInstrucoes++;
      }

      programas[indice].numeroDeInstrucoes = numeroDeInstrucoes;
   }

   return numeroDeProgramas;
}

void lpas(Programa *programas, int quantidadeProgramas){
   Programa programa;

   for(int indice = 0; indice < quantidadeProgramas; indice++){
      programa = programas[indice];
      
      for(int indiceInstrucao = 0; indiceInstrucao < programa.numeroDeInstrucoes; indiceInstrucao++){
         if(strncmp(programa.instrucoes[indiceInstrucao], READ, strlen(READ)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], WRITE, strlen(WRITE)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], LOAD, strlen(LOAD)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], STORE, strlen(STORE)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], ADD, strlen(ADD)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], SUB, strlen(SUB)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], MUL, strlen(MUL)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], DIV, strlen(DIV)) == 0){
            instrucaoRead();
         }

         if(strncmp(programa.instrucoes[indiceInstrucao], HALT, strlen(HALT)) == 0){
            instrucaoRead();
         }
      }
   }
}

pid_t criarProcesso(){
   return fork();
}

/**
*   Função que retira o \n no final da string
*/
void retiraBarraN(char *palavra){
    if(palavra[strlen(palavra)-1]!='\0')
        palavra[strlen(palavra)-1]='\0';
}

//void removerEspacos

/*
// Lê o arquivo
void lerArquivo(fila filaProcessador, Tarefa *tarefaTerminada, char *argv[], int argc){
   fila filaSuspenso = criaFila();
   int tipoInstrucao, linha, tempoExecucao = 0, tempoSuspenso = 0, ultimaLinha;
   char instrucao[20];
   Tarefa tarefa;
   FILE *file;

   // Vai repetir até a fila do processador e a fila de suspensos ficarem vazia
   while (filaProcessador->tamanho > 0 || filaSuspenso->tamanho > 0){
      if(filaProcessador->tamanho == 0){
         tempoExecucao++;
         if(retirarFilaSuspenso(filaSuspenso, filaProcessador, &tempoSuspenso) == 0)
            continue;
      }

      desenfileira(filaProcessador, &tarefa);
      if((file = abrirArquivo(tarefa.nomeArquivo, TSK)) == NULL)
         continue;

      linha = 0;
      ultimaLinha = tarefa.linha;

      // Lê as instruções no arquivo
      while (fgets(instrucao, 20, file) != NULL){

         //Verifica se a linha atual já foi lida anteriormente
         if(tarefa.linha > 0 && linha < tarefa.linha){
            if(instrucao[0] == '#')
               continue;
               
            linha++;
            continue;
         }

         //Verifica se é a última linha
         if(instrucao[0] == ' ' || instrucao[0] == '\n'){
            tarefa.saida = tempoExecucao;
            terminarTarefa(tarefa, tarefaTerminada);
            break;
         }

         retiraBarraN(instrucao);
         
         if(instrucao[0] == '#')
            continue;

         retirarFilaSuspenso(filaSuspenso, filaProcessador, &tempoSuspenso);

         tempoExecucao++;
         linha++;

         // Adiciona uma tarefa na lista de prontos
         if(tempoExecucao < argc - 1)
            adicionarPronto(filaProcessador, tempoExecucao, argv);

         // Verifica se a instrução é válida
         if((tipoInstrucao = validarInstrucao(instrucao, &tarefa)) == 2){
            if(acessarAlocarMemoria(filaProcessador, &tarefa, linha, ultimaLinha, file, tempoExecucao) == 1)
               break;
         }

         else if(tipoInstrucao == 1){
            acessarDisco(filaSuspenso, tarefa, file, tempoExecucao);
            break;
         }

         else if(tipoInstrucao == -1){
            instrucaoInvalida(tarefaTerminada, tarefa, file, tempoExecucao);
            break;
         } 

         else{
            acessoMemoriaInvalido(tarefa, tarefaTerminada, file, tempoExecucao, instrucao);
            break;
         }
      }
   }  
   encerrarFila(filaProcessador);
   encerrarFila(filaSuspenso); 
}

//Incrementa o tempo suspenso, recebe o tempo suspenso, retorna 1 se tiver chegado a 5 ut, senão retorna 0
int incrementarTempoSuspenso(int *tempoSuspenso){
   (*tempoSuspenso)++;
   if(*tempoSuspenso == 5){
      *tempoSuspenso = 0;
      return 1;
   }
   return 0;
}

// Retira uma tarefa da fila de suspenso e insere na fila do processador se tiver 5 ut de operação no disco, recebe a fila de suspensos,
// a fila do processador e o tempo suspenso, retorna 1 se tiver esgotado o tempo de suspensão, senão retorna 0.
int retirarFilaSuspenso(fila filaSuspenso, fila filaProcessador, int *tempoSuspenso){
   Tarefa tarefa;

   if(filaSuspenso->tamanho > 0 && (incrementarTempoSuspenso(tempoSuspenso) == 1)){
      desenfileira(filaSuspenso, &tarefa);
      alterarEstado(&tarefa, PRONTO);
      enfileira(filaProcessador, tarefa);
      return 1;
   }
   return 0;
}

// Faz as alterações que simulam o acesso a memória e a alocação da memória, recebe a fila do processador, a tarefa, o file, a linha atual, 
// a última linha lida do arquivo e o tempo de execução
int acessarAlocarMemoria(fila filaProcessador, Tarefa *tarefa, int linha, int ultimaLinha, FILE *file, int tempoExecucao){
   tarefa->linha++;
   tarefa->tempoCpu++;

   // Verifica se foi feito as duas intruções
   if (linha == ultimaLinha + 2){                 
      enfileira(filaProcessador, *tarefa);
      fecharArquivo(file);
      return 1;
   }
   return 0;
}

// Faz as alterações que simulam o acesso a disco, recebe a fila suspensa, a tarefa, o file e o tempo de execução 
void acessarDisco(fila filaSuspenso, Tarefa tarefa, FILE *file, int tempoExecucao){
   tarefa.tempoCpu++;
   tarefa.saida = tempoExecucao;
   tarefa.linha++;
   tarefa.tempoES += 5;
   alterarEstado(&tarefa, SUSPENSO);
   enfileira(filaSuspenso, tarefa);
   fecharArquivo(file);
}

// Faz as alterações que simulam una instrução inválida, recebe oo vetor de tarefas terminadas, a tarefa, o file e o tempo de execução 
void instrucaoInvalida(Tarefa *tarefaTerminada, Tarefa tarefa, FILE *file, int tempoExecucao){
   printf("\nA tarefa %s não será executada, pois tem instruções diferentes do tipo 1, 2 e 3.\n", tarefa.nomeArquivo);
   tarefa.tempoCpu++;
   tarefa.saida = tempoExecucao;
   terminarTarefa(tarefa, tarefaTerminada);
   fecharArquivo(file);
}

// Faz as alterações que simulam um acesso inválido à memória, recebe o vetor de tarefas terminadas, a tarefa, o file e o tempo de execução
void acessoMemoriaInvalido(Tarefa tarefa, Tarefa *tarefaTerminada, FILE *file, int tempoExecucao, char *instrucao){
   printf("\nA tarefa %s tentou realizar um acesso inválido à memória: %s\n", tarefa.nomeArquivo, instrucao);
   tarefa.tempoCpu++;
   tarefa.saida = tempoExecucao;
   terminarTarefa(tarefa, tarefaTerminada);
   fecharArquivo(file);
}

// Exibe o relatório, recebe o vetor de tarefas terminadas e a quantidade de argumentos de entrada fornecidos.
void relatorio(Tarefa *tarefas, int argc){
   float tempoProcessador = tempoTotalCpu(tarefas, argc);
   float tempoES = tempoTotalES(tarefas, argc);

   for(int indice = 0;indice < argc - 1;indice++){
      
      // Verifica se o vetor foi preenchido
      if(strlen(tarefas[indice].nomeArquivo) == 0)
         continue;
      
      printf("\nTarefa: %s\n", tarefas[indice].nomeArquivo);
      printf("%s%d s\n", TEMPO_EXECUCAO, tarefas[indice].saida - tarefas[indice].entrada);
      printf("%s%d s\n", TEMPO_ESPERA, (tarefas[indice].saida - tarefas[indice].entrada) - tarefas[indice].tempoCpu);
      printf("%s%d ut\n", TEMPO_CPU, tarefas[indice].tempoCpu);
      printf("%s%d ut\n", TEMPO_ES, tarefas[indice].tempoES);
      printf("%s%.2f%%\n", OCUPACAO_CPU, (tarefas[indice].tempoCpu / tempoProcessador) * 100);
      printf("%s%.2f%%\n", OCUPACAO_DISCO, (tarefas[indice].tempoES / tempoES) * 100);
   }
} 

// Calcula o tempo total de uso da cpu, recebe o vetor de tarefas terminadas e a quantidade de argumentos de linha de comando, retorna o 
// tempo total de uso da cpu
float tempoTotalCpu(Tarefa *tarefas, int argc){
   float tempoCpu = 0;

   for(int indice = 0;indice < argc - 1;indice++){
      
      // Verifica se o vetor foi preenchido
      if(strlen(tarefas[indice].nomeArquivo) == 0)
         continue;
      
      tempoCpu += tarefas[indice].tempoCpu;
   }
   return tempoCpu;
}

// Calcula o tempo total de uso do disco, recebe o vetor de tarefas terminadas e a quantidade de argumentos de linha de comando, retorna o 
// tempo total de uso do disco
float tempoTotalES(Tarefa *tarefas, int argc){
   float tempoES = 0;

   for(int indice = 0;indice < argc - 1;indice++){
      
      // Verifica se o vetor foi preenchido
      if(strlen(tarefas[indice].nomeArquivo) == 0)
         continue;
      
      tempoES += tarefas[indice].tempoES;
   }
   return tempoES;
}


// Verifica se os arquivos existem, recebe a quantidade de argumentos de entrada, os argumentos de entrada e a fila do processador
void verificarArquivos(int argc, char *argv[], fila filaProcessador){
   FILE *file;

   for (int indice = 1; indice < argc; indice++){

      // Se o arquivo existir ele é o primeiro adicionado na fila do processador
      if((file = abrirArquivo(argv[indice], TSK)) != NULL){
         adicionarTarefa(filaProcessador, argv[indice], 0);
         fclose(file);
         break;
      }
      limparString(argv[indice]);
   }
}

// Abre um arquivo, recebe o nome do arquivo e a entensão e retorna o arquivo.
FILE* abrirArquivo(char *nomeArquivo, const char *extensao){
   char arquivo[TAMANHO_NOME_ARQUIVO];

   strcpy(arquivo, nomeArquivo);

   FILE *file = fopen(strcat(arquivo, extensao), LEITURA);
   if (file == NULL) 
      printf("Erro ao abrir o arquivo %s!\n", nomeArquivo);
   
   return file;
}

//Fecha o arquivo, recebe o file
void fecharArquivo(FILE *file){
   fclose(file);
}

// Função que tira o \n das strings.
void retiraBarraN(char *palavra){
    if(palavra[strlen(palavra)-1] != '\0')
        palavra[strlen(palavra)-1] = '\0';
}

// Limpa uma string, recebe a string
void limparString(char *string){
   memset(string, '\0', strlen(string));
}

// Limpa o campo nome arquivo dos vetores, recebe o vetor de tarefas e a quantidade de argumentos de entrada
void limparVetor(Tarefa *tarefas, int argc){
   for(int indice = 0;indice < argc - 1;indice++)
      limparString(tarefas[indice].nomeArquivo);
}

// Altera o estado da tarefa, recebe a tarefa e para qual estado vai.
void alterarEstado(Tarefa *tarefa, const char *estado){
   strcpy(tarefa->estado, estado);
}

// Adiciona uma tarefa na fila de prontos, recebe a fila, o nome do arquivo e o tempo de execucao da entrada na fila.
void adicionarTarefa(fila f, char *argv, int entrada){
   Tarefa tarefa;
   
   if (strlen(argv) > 0){
      strcpy(tarefa.nomeArquivo, argv);
      alterarEstado(&tarefa, PRONTO);
      tarefa.tempoCpu = 0;
      tarefa.tempoES = 0;
      tarefa.linha = 0;
      tarefa.tamanhoMemoriaAlocada = 0;
      tarefa.entrada = entrada;
      tarefa.saida = 0;
      enfileira(f, tarefa);
   }
}

// Verifica se tem algum digito na instrucao na posicao correta, recebe a instrucao e o tamanho da string, retorna 1 se for um número.
int validarDigito(char *instrucao, size_t tamanho){
   for (size_t indice = strlen(instrucao) - 2; indice > tamanho - 1; indice--){
      if(!isdigit(instrucao[indice]))
         return -1;
   }
   return 1;
}

// Converte para inteiro o número na instrução, recebe a string onde vai converter e onde o número começa, retorna o número.
int converterParaInt(char *string, int inicioNumero){
   int indiceNumero = 0;
   char numero[strlen(string) - inicioNumero];

   for (size_t indice = inicioNumero; indice < strlen(string); indice++){
      numero[indiceNumero] = string[indice];
      indiceNumero++;
   }
   return atoi(numero);
}

// Verifica se a instrução é para alocação e se é válida, recebe a instrução e a tarefa, retorna 2 se for válida a instrução. 
int validarAlocacao(char *instrucao, Tarefa *tarefa){
   if(validarDigito(instrucao, strlen(ALOCAR_MEMORIA)) == 1){
      tarefa->tamanhoMemoriaAlocada = converterParaInt(instrucao, strlen(ALOCAR_MEMORIA));
      return 2;
   }
   return -1;
}

// Verifica se a instrução é de acesso à memória, recebe a instrução e a tarefa, retorna 2 se for válida a instrução.
int validarAcessoMemoria(char *instrucao, Tarefa *tarefa){
   int numero;
   
   // Verifica se na última posição tem o caractere "]".
   if(instrucao[strlen(instrucao) - 1] != ']')
      return -1;
   
   if(validarDigito(instrucao, strlen(ACESSAR_MEMORIA)) == 1){
      numero = converterParaInt(instrucao, strlen(ACESSAR_MEMORIA));

      // Verifica se o número é menor que a memória alocada.
      if(numero >= 0 && numero < tarefa->tamanhoMemoriaAlocada)
         return 2;
      
      else
         return 0;
   }
   return -1;
}

// Verifica se as instruções são válidas, ecebe a instrução e a tarefa, retorna 2 se for uso de processador, 1 se for acesso a disco 
// e -1 se for inválido
int validarInstrucao(char *instrucao, Tarefa *tarefa){
   if(strncmp(instrucao, ALOCAR_MEMORIA, strlen(ALOCAR_MEMORIA)) == 0)
      return validarAlocacao(instrucao, tarefa);

   if(strncmp(instrucao, ACESSAR_MEMORIA, strlen(ACESSAR_MEMORIA)) == 0)
      return validarAcessoMemoria(instrucao, tarefa);
   
   if(strcmp(instrucao, ACESSAR_DISCO) == 0)
      return 1;

   else 
      return -1;
}

// Adiciona uma tarefa na fila de pronto, recebe a fila, o tempo de execução e o nome do arquivo.
void adicionarPronto(fila f, int tempoExecucao, char *argv[]){
   switch (tempoExecucao){
   case 1: adicionarTarefa(f, argv[tempoExecucao + 1], tempoExecucao); break;
   case 2: adicionarTarefa(f, argv[tempoExecucao + 1], tempoExecucao); break;
   case 3: adicionarTarefa(f, argv[tempoExecucao + 1], tempoExecucao); break;
   }
}

// Termina uma tarefa colocando no vetor de terminados, recebe a tarefa, o vetor de tarefas terminadas, e o índice de última posição
// preenchida.
void terminarTarefa(Tarefa tarefa, Tarefa *tarefaTerminada){
   alterarEstado(&tarefa, TERMINADO);
   tarefaTerminada[tarefa.entrada] = tarefa;
}

int main(int argc, char *argv[]){
   return iniciar(argc, argv);
}*/