#include "reversi.h"

/**
 * @brief New game
 *
 * @param[in] mode Game mode
 * @param[in] piece First player piece or bot piece
 * @param[in] lvl Bot level
 * @param[out] e State beeing reseted
 * @param[out] s History stack beeing reseted
 * 
 * @see inicialBoard
 * @see update
 */
void start(char mode, VALOR piece, char lvl, ESTADO *e, LState *s)
{
    LState new_s = NULL;                       // 
    
    newGame(s);                                // clears history from previous game
    
    new_s = malloc(sizeof(struct history));    // allocates new memory 
    
    new_s = *s;                                // 
    *s = new_s;                                // 
    
    e->modo = mode;                            // sets game mode to manual mode ('0' or '1')
    e->peca = mode - '0' ? VALOR_X : piece;    // sets piece to VALOR_X if in automatic mode or to piece if in manual mode
    e->bot = piece;                            // sets bot to piece
    e->botLVL = lvl;                           // sets botLVL to lvl
    
    inicialBoard(e->grelha);                   // sets board to inicial board
    
    update(e);                                 // updates state parameters
    
    (*s)->e = *e;                              // adds state to history
}

/**
 * @brief PLayes the level 3 bot in a championship
 *
 * If the file where the championship hasn't been created, it is first created.
 *
 * @param[in] file File where championship is beeing played
 *
 * @return Error codes
 *
 * @see readFile
 * @see start
 * @see bot3
 * @see gameOver
 * @see saveState
 */
int playChamp(char *file, ESTADO *e, LState *s)
{
    int num;
    static char saved[MAX_STR];
    
    if (file)
        strcpy(saved, file);
    
    if ((num = -readFile(saved, e, s)))
        start('1', VALOR_X, '3', e, s);
    else    
        num = bot3(e, s);
    
    if (gameOver(*e))
    {
        if (e->scoreX > e->scoreO)
            strcat(saved, ".gX");
        else if (e->scoreO < e->scoreX)
            strcat(saved, ".gO");
        else
            strcat(saved, ".g-");
    }
    
    writeFile(1, saved, *s);
    
    e->modo = '0';

    return num;
}
