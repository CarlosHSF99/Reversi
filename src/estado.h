#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DIM     8       //
#define CLI     7       //
#define INPUT   1015    //
#define MAX_STR 1024    //
#define MAX_POS 64      //
#define READ    -133    //
#define UNDO    -266    //

//trocar isto por ncurses
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

/*
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/

// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O, VALIDA, HELP} VALOR;

// posicao
typedef struct posicao {
    int l, c;
} POSICAO;

//typedef struct vetor

typedef struct virar {
    POSICAO valida;
    POSICAO virar[MAX_POS];
    int nVirar;
} VALIDAS;

// Estrutura que armazena o estado do jogo
typedef struct estado {
    char modo;                  // modo em que se está a jogar! 0-> manual, 1-> contra computador
    VALOR peca;                 // peça do jogador que vai jogar!
    VALOR grelha[DIM][DIM];     // grelha
    VALIDAS validas[MAX_POS];   // posiçoes validas
    int nValidas;               // numero de posiçoes validas
    POSICAO help;               // help piece
    int NX;                     // numero de pecas X
    int NO;                     // numero de pecas O
    int showValid;              // mostra posicoes validas
    int showHelp;               // mostra posicao ajuda
} ESTADO;

typedef struct history {
    ESTADO e;
    struct history *next;       // proximo estado
} *LEST;

typedef struct{
    POSICAO grid;
    int score;
} MINMAX;

//interpreter.c
void interpreter(ESTADO e, LEST *s);
int interpret(ESTADO *e, LEST *s, char *input, char *error);
void updateCLI(char cli[DIM][MAX_STR]/*, int n_times*/);
void errorHandling(int num, char error, char cli[CLI][MAX_STR]);

//estado.c
void manual(ESTADO *e, VALOR n, LEST *s);
void automatic(ESTADO *e, VALOR n, LEST *s);

int readFile(ESTADO *e, char *file_name, int tipo);
void writeEstado(ESTADO *e);
void saveFile(ESTADO *e, char* filename, LEST s);

int play(int l, int c, ESTADO* e);

int stateUpdate(ESTADO *e);
void update(ESTADO *e);
int cerca(int i, int j, ESTADO* e, int n);
int cercaDir(int k, int l, int i, int j, ESTADO *e, int n);

void undo(ESTADO* e, LEST *s);

int isGameOver(ESTADO e);

void printg(ESTADO e, char lines[DIM][MAX_STR]);

int elem(int l, int c, ESTADO e);

int inBoard(int l, int c);
void switchPiece(VALOR *piece);

void printFirstLine(ESTADO e);
void showValid(ESTADO *e);
void showHelp(ESTADO *e);

void boardInicial(VALOR grelha[DIM][DIM]);

int miniMax(ESTADO *e, int depth, int max_depth, LEST *s);

//linked_lists.c
void freeStack(LEST *s);
void newGame(LEST *s);
void push(ESTADO e, LEST *s);
void pop(LEST *s);

#endif //PROJ_ESTADO_H
