#include "reversi.h"

/**
 * @brief Updates game state
 *
 * @param[in,out] e State beeing updated
 *
 * @see scoreUpdate
 * @see reversable
 * @see helpUpdate
 */
void update(ESTADO *e)
{
    int nVirarHelp = 0;
    
    e->nValids = e->scoreX = e->scoreO = 0;    // resets number of valid positions and score
    
    for (int l = 0; l < DIM; l++)              // iterates over board lines
        for (int c = 0; c < DIM; c++)          // iterates over board columns
        {
            scoreUpdate(l, c, e);
            
            if (reversable(l, c, e))             // checks if current position is a valid play
            {
                helpUpdate(&nVirarHelp, e);
                e->nValids++;
            }
        }
}

/**
 * @brief Checks if a postion will surround enemy pieces
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 * @param[in,out] e State being checked and updated
 *
 * @return 1 (true) if  or 0 (false) if not
 *
 * @see surround
 */
int reversable(int l, int c, ESTADO *e)
{
    if (!surround(l, c, e))                    // checks if current position is a valid play
        return 0;                              // returns no errors
    
    POSITION *valid = &VALID(e, nVALID(e));    // initializes valid to point to valid postion
    
    valid->l = l;                              // saves valid line to current position
    valid->c = c;                              // saves valid column to current position
    
    return 1;                                  // return error code
}

/**
 * @brief Checks if a postion surrounds enemy pieces in each direction
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 * @param[in] e State beeing checked
 *
 * @return 1 (true) if enemy pieces are surround in atleast on direction or 0 (false) if not
 *
 * @see surroundDir
 */
int surround(int l, int c, ESTADO *e)
{
    nREVERSE(e, e->nValids) = 0;          // resets number of reversable pieces to zero
    
    if (e->grelha[l][c])                  // checks if current posiiton is empty
        return 0;                         // returns false
    
    return                                // returns true if the position reverses any piece in one of the directions
        surroundDir(l, c, -1,  0, e) +    // up
        surroundDir(l, c,  1,  0, e) +    // down
        surroundDir(l, c,  0,  1, e) +    // right
        surroundDir(l, c,  0, -1, e) +    // left
        surroundDir(l, c, -1,  1, e) +    // up   right
        surroundDir(l, c, -1, -1, e) +    // up   left
        surroundDir(l, c,  1,  1, e) +    // down right
        surroundDir(l, c,  1, -1, e);     // down left
}

/**
 * @brief Checks if a position is a valid play in a certain direction
 *
 * At doing so it also saves reversable positions and how many there are.
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 * @param[in] i Line vector
 * @param[in] j Column vector
 * @param[in,out] e State beeing checked
 *
 * @return 1 (true) if the position (l,c) is valid or 0 (false) if not
 */
int surroundDir (int l, int c, int i, int j, ESTADO *e)
{
    VALOR opp = e->peca;                                                     // initializes onpt to current player piece
    
    switchPiece(&opp);                                                       // sets onpt to oponent player piece
    
    POSITION *reverse = REVERSE(e, e->nValids);                              // initializes reverse pointing reversable positions array
    int *nReverse = &nREVERSE(e, e->nValids);                                // initializes nReverse pointing number reversable positions
    int counter = 0;                                                         // initializes counter to 0
   
    for (l+=i, c+=j; inBoard(l, c) && e->grelha[l][c] == opp; l+=i, c+=j)    // iterates over board vector
    {
        reverse[*nReverse].l = l;                                            // adds coordenate l to reversable positions
        reverse[*nReverse].c = c;                                            // adds coordenate c to reversable positions
        (*nReverse)++;                                                       // increments number of reversable pieces by one
        counter++;                                                           // increments counter by one
    }
    
    if (inBoard(l, c) && e->grelha[l][c] == e->peca && counter)              // checks if position is valid in this direction
        return 1;                                                            // returns true
    
    *nReverse -= counter;                                                    // removes number of reversable pieces
    
    return 0;                                                                // returns false
}

/**
 * @brief Updates the score
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 * @param[in,out] e State where score is updated
 */
void scoreUpdate(int l, int c, ESTADO *e)
{
    VALOR piece = e->grelha[l][c];    // initializes piece to current position value
    
    e->scoreX += piece == VALOR_X;    // increments X score by one if piece is equal to X
    e->scoreO += piece == VALOR_O;    // increments O score by one if piece is equal to O
}

/**
 * @brief Updates help position
 *
 * @param[in,out] nVirarHelp Comparator of number of reversable positions for each valid play
 * @param[in,out] e State where help position is updated
 */
void helpUpdate(int *nVirarHelp, ESTADO *e)
{
    VALIDS *valid = &VALIDS(e, e->nValids);    // initializes valid to last valid position
    
    if (valid->nReverse > *nVirarHelp)         // checks if current positions will flip the most pieces
    {
        *nVirarHelp = valid->nReverse;         // updates comparator
        e->help = valid->valid;                // saves current position as help position
    }
}

/**
 * @brief Undoes the last play
 *
 * If the game is in automatic mode then the stack history is regressed twice to also undo the bot play
 *
 * @param[out] e State beeing updated
 * @param[in,out] s History stack regressed
 *
 * @see pop
 */
void popUndo(ESTADO *e, LState* s)
{
    pop(s);                // pops last state (first in stack)
    
    if (e->modo == '1')    // if the game is in automatic mode
        pop(s);            // pops last state (first in stack) again

    *e = (*s)->e;          // sets state e to now last state
}
