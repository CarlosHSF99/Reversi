#ifndef PROJ_ESTADO_H

#define PROJ_ESTADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 8

#define MAX_LENGTH 1024

/*
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/

// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O, VALOR_DOT, VALOR_HELP} VALOR;

// Estrutura que armazena o estado do jogo
typedef struct estado
{
    VALOR peca;         // peça do jogador que vai jogar!
    VALOR grelha[8][8]; // grelha
    char modo;          // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;

void printg(ESTADO e);

void menu();

void something(ESTADO e);

int cerca(int i, int j, ESTADO e);

int cercaDir(int k, int l, int i, int j, ESTADO e);

void readFile (ESTADO *e,char *file_name);

void writeFile();

void play(int l,int c,ESTADO *e);

#endif //PROJ_ESTADO_H
