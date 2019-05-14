#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define DIM     8       //
#define CLI     7       //
#define INPUT   1015    //
#define MAX_STR 1024    //
#define MAX_POS 64      //

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

typedef struct virar {
    POSICAO valida;
    POSICAO virar[MAX_POS];
    int nVirar;
} VALIDAS;

// Estrutura que armazena o estado do jogo
typedef struct estado {
    char modo;                  // modo em que se está a jogar! 0-> manual, 1-> contra computador
    VALOR peca;                 // peça do jogador que vai jogar!
    VALOR botPiece;             // peça do bot
    VALOR grelha[DIM][DIM];     // grelha
    VALIDAS validas[MAX_POS];   // posiçoes validas
    int nValidas;               // numero de posiçoes validas
    POSICAO help;               // help piece
    int scoreX;                 // numero de pecas X
    int scoreO;                 // numero de pecas O
    char botLVL;                // dificuldade do bot
    int showValid;              // mostra posicoes validas
    int showHelp;               // mostra posicao ajuda
} ESTADO;

typedef struct history {
    ESTADO e;
    struct history *next;       // proximo estado
} *LEST;

#define MODO(e)         e->modo         //
#define PIECE(e)        e->peca         //
#define BOARD(l,c)      e->grelha[l][c] //
#define VALIDS(e, i)    e->validas[i]      //
#define nVALID(e)       e->nValidas     //
#define HELPP(e)        e->help         //
#define SCOREX(e)       e->NX           //
#define SCOREO(e)       e->NO           //
#define SVALID(e)       e->showValid    //
#define SHELP(e)        e->showHelp     //

#define VALID(e, i)     e->validas[i].valida  //
#define nREVERSE(e)     e->validas->nVirar    //

#define SCORE(e, a)     a == VALOR_X ? e.scoreX : e.scoreO;

//
typedef struct minimax {
    int score;
    POSICAO play;
} MINIMAX;

//interpreter.c
void interpreter(ESTADO e, LEST s);
int interpret(ESTADO *e, LEST *s, char *input);
void updateCLI(char cli[DIM][MAX_STR]/*,int n_times*/);
void errorHandling(int num, char cli[CLI][MAX_STR]);
int botTurn(ESTADO *e, LEST *s);
int playerTurn(char cli[DIM][MAX_STR], ESTADO *e, LEST *s);


int new(int i, char *cmd, ESTADO *e, LEST *s);
int automatic(int i, char *cmd[MAX_STR],ESTADO *e, LEST *s);
int load(int i, char *cmd, ESTADO *e, LEST *s);
int save(int i, char *cmd, ESTADO *e, LEST *s);
int play(int i, char *cmd[MAX_STR], ESTADO *e, LEST *s);
int valid(int i, ESTADO *e);
int help(int i, ESTADO *e);
int undo(int i, ESTADO *e, LEST *s);
int championship(int i, char *cmd);
int quit(int i);

//estado.c
void manual(ESTADO *e, VALOR n, LEST *s);
void autoVSbot(VALOR piece, char lvl, ESTADO *e, LEST *s);

int readFile(ESTADO *e, char *file_name, LEST *s);
//void writeEstado(ESTADO *e);
void saveState(ESTADO *e, char *filename, LEST s);

int doPlay(int l, int c, ESTADO *e, LEST *s);
void reverse(int l, int c, ESTADO *e);

void scoreUpdate(ESTADO *e, int l, int c);
int surround(int l, int c, ESTADO *e);
void helpUpdate(ESTADO *e, int *nVirarHelp);

int nextState(ESTADO *e);
int stateUpdate(ESTADO *e);
void update(ESTADO *e);
int cerca(int i, int j, ESTADO* e);
int cercaDir(int k, int l, int i, int j, ESTADO *e);

void popundo(ESTADO* e, LEST *s);

int isGameOver(ESTADO e);

int playBot(char *file);

void printInterface(ESTADO e, char lines[DIM][MAX_STR]);

int isValid(int l, int c, ESTADO e);

int inBoard(int l, int c);
void switchPiece(VALOR *piece);

void printFirstLine(ESTADO e);
void showValid(ESTADO *e);
void showHelp(ESTADO *e);

void boardInicial(VALOR grelha[DIM][DIM]);

int bot1(ESTADO *e, LEST *s);
int bot2(ESTADO *e, LEST *s);
int bot3(ESTADO *e, LEST *s);
int miniMax(ESTADO father, int depth, int minmax, POSICAO *play);
int negaMax(ESTADO father, int depth, int player, POSICAO *play);
MINIMAX negaMax2(ESTADO father, int depth, int player);

//linked_lists.c
void freeStack(LEST *s);
void newGame(LEST *s);
void push(ESTADO e, LEST *s);
void altPush(ESTADO e, LEST *s);
void pop(LEST *s);

#endif //PROJ_ESTADO_H
