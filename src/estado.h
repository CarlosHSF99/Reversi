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

// 
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

/*
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/

/**
 * @brief definição de valores possiveis no tabuleiro
 */
typedef enum {VAZIA, VALOR_X, VALOR_O, VALIDA, HELP,ERROR} VALOR;

/**
 * @brief 
 */
typedef struct position {
    int l, c;
} POSITION;

/**
 * @brief 
 */
typedef struct valids {
    POSITION valid;
    POSITION reverse[MAX_POS];
    int nReverse;
} VALIDS;

/**
 * @brief Estrutura que armazena o estado do jogo
 */
typedef struct estado {
    char modo;                  // modo em que se está a jogar! 0-> manual, 1-> contra computador
    VALOR peca;                 // peça do jogador que vai jogar!
    VALOR bot;                  // peça do bot
    VALOR grelha[DIM][DIM];     // grelha
    VALIDS valids[MAX_POS];   // posiçoes valids
    int nValids;               // numero de posiçoes valids
    POSITION help;               // help piece
    int scoreX;                 // numero de pecas X
    int scoreO;                 // numero de pecas O
    char botLVL;                // dificuldade do bot
    int showValid;              // mostra posicoes valids
    int showHelp;               // mostra posicao ajuda
} ESTADO;

/**
 * @brief 
 */
typedef struct history {
    ESTADO e;
    struct history *next;       // proximo estado
} *LState;

#define MODO(e)         e->modo         //
#define PIECE(e)        e->peca         //
#define BOARD(l,c)      e->grelha[l][c] //
#define VALIDS(e, i)    e->valids[i]    //
#define nVALID(e)       e->nValids      //
#define HELPP(e)        e->help         //
#define SCOREX(e)       e->scoreX       //
#define SCOREO(e)       e->scoreO       //
#define SVALID(e)       e->showValid    //
#define SHELP(e)        e->showHelp     //

#define VALID(e, i)     e->valids[i].valid      //
#define nREVERSE(e, i)  e->valids[i].nReverse   //
#define REVERSE(e, i)   e->valids[i].reverse    //

#define SCORE(e, a)     a == VALOR_X ? e.scoreX : e.scoreO;

/**
 * @brief 
 */
typedef struct minimax {
    double score;
    POSITION play;
} MINIMAX;

// game_cycle.c
void gameCycle(ESTADO e, LState s);
int botTurn(ESTADO *e, LState *s);
int playerTurn(char cli[DIM][MAX_STR], ESTADO *e, LState *s);

// interpreter.c
int interpreter(ESTADO *e, LState *s, char *input);
void errorHandling(int num, char cli[CLI][MAX_STR]);
int newMode(int i, char *cmd, ESTADO *e, LState *s);
int autoMode(int i, char *cmd[MAX_STR],ESTADO *e, LState *s);
int load(int i, char *cmd, ESTADO *e, LState *s);
int save(int i, char *cmd, ESTADO e, LState *s);
int play(int i, char *cmd[MAX_STR], ESTADO *e, LState *s);
int valid(int i, ESTADO *e);
int help(int i, ESTADO *e);
int undo(int i, ESTADO *e, LState *s);
int championship(int i, char *cmd, ESTADO *e, LState *s);
int quit(int i, LState *s);

// game_start.c
void start(char mode, VALOR piece, char lvl, ESTADO *e, LState *s);
int playChamp(char *file, ESTADO *e, LState *s);

// state_play.c
int doPlay(POSITION play, ESTADO *e, LState *s);
void reverse(VALIDS *valided, ESTADO *e);
VALIDS *isValid(POSITION play, ESTADO e);
int nextState(ESTADO *e);

// state_update.c
void update(ESTADO *e);
void scoreUpdate(int l, int c, ESTADO *e);
void helpUpdate(int *nVirarHelp, ESTADO *e);
int reversable(int l, int c, ESTADO *e);
int surround(int i, int j, ESTADO* e);
int surroundDir(int k, int l, int i, int j, ESTADO *e);

// state_print.c
void printInterface(ESTADO e, char lines[DIM][MAX_STR]);
void printFirstLine(ESTADO e);
void showValid(ESTADO *e);
void showHelp(ESTADO *e);

// file.c
int readFile(char *file, ESTADO *e, LState *s);
void writeFile(int champ, char *filename, LState s);
void writeFirstLine(FILE **fp, LState s);

// helper_functions.c
void switchPiece(VALOR *piece);
int gameOver(ESTADO e);
int compPosition(POSITION a, POSITION b);
int inBoard(int l, int c);
void inicialBoard(VALOR grelha[DIM][DIM]);
void updateCLI(char cli[DIM][MAX_STR]);
void popUndo(ESTADO* e, LState *s);

// bot.c
int bot1(ESTADO *e, LState *s);
int bot2(ESTADO *e, LState *s);
int bot3(ESTADO *e, LState *s);
MINIMAX negaMax(ESTADO father, int depth, int player);
int evalFunc(ESTADO e);

//linked_lists.c
void freeStack(LState *s);
void newGame(LState *s);
void push(ESTADO e, LState *s);
void altPush(ESTADO e, LState *s);
void pop(LState *s);

//
int miniMax(ESTADO father, int depth, int minmax, POSITION *play);
int negaScout(ESTADO father, int depth, int A, int B, int player, POSITION *play);
int negaMax2(ESTADO father, int depth, int player, POSITION *play);
int miniMaxAB(ESTADO father, int depth, int A, int B, int minmax, POSITION *play);

#endif //PROJ_ESTADO_H
