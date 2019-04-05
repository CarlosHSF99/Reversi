#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DIM 8
#define MAX_LENGTH 1024
#define MAX_POS 64
#define CLEAR system("clear")
#define READ -133
#define UNDO -266

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
    int NX;                     // numero de pecas X
    int NO;                     // numero de pecas O
    //struct estado *next;        // proximo estado
} ESTADO;

typedef struct{
    POSICAO grid;
    int score;
} MINIMAX;

void printg(ESTADO e, int validas, int ajuda);

void menu();

void newVsHuman(ESTADO *e, VALOR n);

void newVsBot();

int readFile(ESTADO *e, char *file_name, int tipo);

void writeEstado(ESTADO *e);

void saveFile(ESTADO *e, char *filename);

void play(int l, int c, ESTADO *e); 

void something(ESTADO *e);

int cerca(int i, int j, ESTADO *e, int n);

int cercaDir(int k, int l, int i, int j, ESTADO *e, int n);

void help();

void undo(ESTADO *e);

void isGameOver(ESTADO e);

int elem(int l, int c, ESTADO e);

int miniMax(ESTADO *e, int depth, int max_depth);
#endif //PROJ_ESTADO_H
