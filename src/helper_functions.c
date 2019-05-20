#include "estado.h"

/**
 * @brief Switches piece
 *
 * @param[in,out] piece
 */
void switchPiece(VALOR *piece)
{
    *piece = 3 - *piece;
}

/**
 * @brief Checks if the game is over
 *
 * @param[in] e State beeing checked
 *
 * @return 1 (true) if the game is over or 0 (false) if not
 *
 * @see switchPiece
 * @see update
 */
int gameOver(ESTADO e)
{
    int nValids = e.nValids;    // initializes nValids to number of valid plays
    
    switchPiece(&e.peca);       // switches current playing piece
    update(&e);                 // updates state
    
    nValids += e.nValids;       // sums number of valid plays before and after update
    
    return !nValids;            //
}

/**
 * @brief Checks if position (l,c) is in the game board
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 *
 * @return 1 (true) if position (l,c) is in the game board or 0 (false) if not
 */
int inBoard(int l, int c)
{
    return l >= 0 && l < DIM && c >= 0 && c < DIM;
}

/**
 * @brief Compares two positions
 *
 * @param[in] a First position
 * @param[in] b Second position
 *
 * @return 1 (true) if the two positions are equal or 0 (false) if not
 */
int compPosition(POSITION a, POSITION b)
{
    return a.l == b.l && a.c == b.c;
}

/**
 * @brief Updates CLI
 *
 * Moves each CLI line one line up
 *
 * @param cli[DIM][MAX_STR]
 */
void updateCLI(char cli[DIM][MAX_STR])
{
        for (int i = 0; i < CLI; i++)    // iterates over CLI lines                                   
            strcpy(cli[i], cli[i+1]);    // climbs CLI                                                
}

/**
 * @brief Sets board to inicial board
 *
 * @param[out] grelha[DIM][DIM] Board beeing setted to its inicial layout
 */
void inicialBoard(VALOR grelha[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)        // iterates over board lines
        for (int j = 0; j < DIM; j++)    // iterates over board columns
            grelha[i][j] = VAZIA;        // sets position (i,j) to empty (VAZIA)
    
    grelha[3][4] = VALOR_X;              // sets position (3,4) to X
    grelha[4][3] = VALOR_X;              // sets position (4,3) to X
    grelha[3][3] = VALOR_O;              // sets position (3,3) to O
    grelha[4][4] = VALOR_O;              // sets position (4,4) to O
}
