#include "estado.h"

// New game against human adversary
void start(char mode, VALOR piece, char lvl, ESTADO *e, LEST *s)
{
    LEST new_s = NULL;                         // 
    
    newGame(s);                                // clears history from previous game
    
    new_s = malloc(sizeof(struct history));    // allocates new memory 
    
    new_s->next = (*s);                        // 
    *s = new_s;                                // 
    
    e->modo = mode;                            // sets game mode to manual mode ('0' or '1')
    e->peca = mode - '0' ? VALOR_X : piece;    // sets piece to VALOR_X if in automatic mode or to piece if in manual mode
    e->bot = piece;                            // sets bot to piece
    e->botLVL = lvl;                           // sets botLVL to lvl
    
    boardInicial(e->grelha);                   // sets board to inicial board
    
    update(e);                                 // updates state parameters
    
    (*s)->e = *e;                              // adds state to history
}
/*
// New game against human adversary
void manual(VALOR piece, ESTADO *e, LEST *s)
{
    LEST new_s = NULL;                         // 
    
    newGame(s);                                // clears history from previous game
    
    new_s = malloc(sizeof(struct history));    // allocates new memory 
    
    new_s->next = (*s);                        // 
    *s = new_s;                                // 
    
    e->modo = '0';                             // sets game mode to manual (0)
    e->peca = piece;                           // sets inicial player to the paramater n
    e->botLVL = ' ';                           // 
    
    boardInicial(e->grelha);                   // sets board to inicial board
    
    update(e);                                 // updates state parameters
    
    (*s)->e = *e;                              // adds state to history
}

// New game against computer adversary
void autoVSbot(VALOR piece, char lvl, ESTADO *e, LEST *s)
{
    LEST new_s = NULL;                         // 
    
    newGame(s);                                // clear history from previous game
    
    new_s = malloc(sizeof(struct history));    // allocates new memory
    
    new_s->next = (*s);                        // 
    *s = new_s;                                // 
    
    e->modo = '1';                             // stes game mode to manual (1)
    e->peca = VALOR_X;                         // sets inicial player X
    e->bot = piece;                            // 
    e->botLVL = lvl;                           // 
    
    boardInicial(e->grelha);                   // sets board to inicial board
    
    update(e);                                 // updates state parameters
    
    (*s)->e = *e;                              // adds state to history
}
*/
// Sets board to inicial board
void boardInicial(VALOR grelha[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)        // iterates over board lines
        for (int j = 0; j < DIM; j++)    // iterates over board columns
            grelha[i][j] = VAZIA;        // sets position (i,j) to empty (VAZIA)
    
    grelha[3][4] = VALOR_X;              // sets position (3,4) to X
    grelha[4][3] = VALOR_X;              // sets position (4,3) to X
    grelha[3][3] = VALOR_O;              // sets position (3,3) to O
    grelha[4][4] = VALOR_O;              // sets position (4,4) to O
}
