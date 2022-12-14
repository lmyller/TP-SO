
#pragma once

// Tamanho máximo do nome de arquivo.
#define TAMANHO_NOME_ARQUIVO 80

// Tamanho máximo de uma instrução LPAS.
#define TAMANHO_INSTRUCAO 10

// Número máximo de instruções do programa LPAS.
#define NUMERO_MAXIMO_DE_INSTRUCOES 255

// Número máximo de variáveis do programa.
#define NUMERO_MAXIMO_DE_VARIAVEIS 50

// Número máximo de programas da máquina de execução.
#define NUMERO_MAXIMO_DE_PROGRAMAS 4

#define LOCALIZACAO "pt-BR"

#define EXTENSAO ".lpas"

#define SAIR "exit"

#define READ "READ"
#define WRITE "WRITE"
#define LOAD "LOAD"
#define STORE "STORE"
#define ADD "ADD"
#define SUB "SUB"
#define MUL "MUL"
#define DIV "DIV"
#define HALT "HALT"

// Códigos das instruções LPAS.
/*#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUB 31
#define MUL 32
#define DIV 33
#define HALT 40*/

// Representa uma instrução LPAS.
typedef char Instrucao[TAMANHO_INSTRUCAO];

// Representa o nome do programa.
typedef char NomePrograma[TAMANHO_NOME_ARQUIVO];

// Representa a estrutura de um programa LPAS.
typedef struct  {
   	// Número de instruções do programa.
	unsigned short numeroDeInstrucoes;

	// Nome do programa.
	NomePrograma nome;

	/* Memória de código para armazenar as instruções LPAS que compõem o programa.
	   Cada instrução é armazenada em uma posição do vetor. */
	Instrucao instrucoes[NUMERO_MAXIMO_DE_INSTRUCOES];
} Programa;


/* Códigos resultantes da excução do programa LPAS. Os códigos válidos são:
 
	 0 = execução bem sucedida; 
	 1 = instrução LPAS inválida;
	 2 = argumento de instrução LPAS inválido;
	 3 = argumento de instrução LPAS ausente;
	 4 = duas ou mais instruções LPAS na mesma linha de código;
	 5 = símbolo inválido.
*/
typedef enum { 
	EXECUCAO_BEM_SUCEDIDA, 
	INSTRUCAO_LPAS_INVALIDA, 
	ARGUMENTO_INSTRUCAO_LPAS_INVALIDO, 
	ARGUMENTO_INSTRUCAO_LPAS_AUSENTE, 
	MUITAS_INSTRUCOES, 
	SIMBOLO_INVALIDO 
} Erro;

// Representa os dados sobre um erro de execução do programa.
typedef struct {
	unsigned short numeroLinha;
	Instrucao instrucao;
	NomePrograma nome;
	Erro erro;
} ErroExecucao;			   

//  Indica o estado atual da tarefa. 
typedef enum { 
	NOVA, PRONTA, EXECUTANDO, SUSPENSA, TERMINADA 
} EstadoTarefa;

// Como a tarefa (processo) é um programa em execução, esta estrutura relaciona a identificação de cada tarefa com o programa a ser executado por ela.
typedef struct {
	// Identificador da tarefa.
	unsigned identificador;

	// Programa a ser executado pela tarefa.
	Programa programa;
} Tarefa;

// Representa o descritor da tarefa, conhecido como bloco de controle da tarefa (TCB - Task Control Block).
typedef struct {
	// Identificação da tarefa deste bloco de controle da tarefa.
	Tarefa tarefa;

	// Indica o estado atual da tarefa. O estado da tarefa deve ser atualizado segundo o seu ciclo de vida durante sua execução. 
	EstadoTarefa estado;

	// O contador de programa (PC - Program Counter) indica a próxima instrução do programa a ser executada.
	unsigned char pc;

	// Indica o tempo total de uso do processador que a tarefa precisa para executar suas instruções. 
	unsigned char tempoCPU;

	// Indica o tempo total das operações de E/S executadas pela tarefa, nesta implementação, o tempo total de E/S apenas das instruções READ. 
	unsigned char tempoES;
} DescritorTarefa;

// Representa a estrutura da máquina de execução LPAS.
typedef struct  {
	// Número de programas LPAS carregados na memória da Máquina de Execução.
	int numeroDeProgramas;

	/* Memória de código que armazena os programas LPAS a serem executados na máquina de execução.
	   Como para cada programa a ser executado na máquina de execução é necessário criar uma tarefa para representá-lo, essas tarefas possuem um 
	   descritor de tarefa para representar o seu contexto de execução e os dados do programa a ser executado, como nome e suas instruções LPAS.
	*/
	DescritorTarefa tarefas[NUMERO_MAXIMO_DE_PROGRAMAS];

	// Registrador da máquina de execução LPAS.
	int registrador;

	// Memória de dados que armazena as variáveis do programa LPAS que está em execução na ME.
	int variaveis[NUMERO_MAXIMO_DE_VARIAVEIS];

	// Identifica a instrução, o número da linha e o nome do programa onde o erro de execução ocorreu.
	ErroExecucao erroExecucao;
} MaquinaExecucao;

int iniciar();
void tes();
void prompt(char *entrada);
void exibirPrompt();
void verificarNomesArquivos(char *entrada, char *nomesArquivos[]);
char** alocarMemoria(const int linhas, const int colunas);
void retiraBarraN(char *palavra);
int lerArquivos(Programa *programas, char *nomesArquivos[], int quantidadeMaximaProgramas);
void lpas(Programa *programas, int quantidadeProgramas);
pid_t criarProcesso();
MaquinaExecucao criarMaquinaExecucao(Programa *programa, int quantidadeProgramas);
Tarefa criarTarefa(int identificador, Programa programa);
DescritorTarefa criarDescritorTarefa(Tarefa tarefa);