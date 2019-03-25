#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 8
#define MAX_LENGTH 1024
#define MAX_POS 64
#define CLEAR system("clear")

/*
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/

// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O, VALOR_DOT, VALOR_HELP} VALOR;

// posicao
typedef struct posicao {
    int l, c;
} POSICAO;

// Estrutura que armazena o estado do jogo
typedef struct estado {
    char modo;                  // modo em que se está a jogar! 0-> manual, 1-> contra computador
    VALOR peca;                 // peça do jogador que vai jogar!
    VALOR grelha[DIM][DIM];     // grelha
    POSICAO validas[MAX_POS];   // posiçoes validas
    int nValidas;               // numero de posiçoes validas
    POSICAO alterar[MAX_POS];   // posiçoes a alterar
    POSICAO ajuda;              // posiçao ajuda
} ESTADO;

void printg(ESTADO e, int validas, int ajuda);

void menu();

void newVsHuman();

void newVsBot();

void readFile (ESTADO *e, char *file_name);

void writeFile(ESTADO *e, char *file_name);

void play(int l, int c, ESTADO *e, char *file_name); 

void something(ESTADO *e);

int cerca(int i, int j, ESTADO e);

int cercaDir(int k, int l, int i, int j, ESTADO e);

void help();

void undo();

#endif //PROJ_ESTADO_H
