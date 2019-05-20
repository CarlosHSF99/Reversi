#include "reversi.h"

/**
 * @brief Makes a play
 *
 * In this order, the function calls the functions that: 
 *   -# verify if a play is valid;
 *   -# reverse the pieces;
 *   -# update the game to its next state;
 *   -# push this state to stack history.
 *
 * @param[in] play Position played
 * @param[in,out] e State where the position is beeing played
 * @param[in,out] s History stack
 *
 * @return The error code
 *
 * @see isValid
 * @see reverse
 * @see nextState
 * @see push
 */
int doPlay(POSITION play, ESTADO *e, LState *s)
{
    int num;                               //
    VALIDS *valided;                       //
    
    if (!(valided = isValid(play, *e)))    // cheks if play is valid and receives pointer to valid position
        return 8;                          // returns error
    
    reverse(valided, e);                   // reverses reversable positions
    
    num = nextState(e);                    // updates state
    
    push(*e, s);                           // pushes new state to history stack
    
    return num;
}

/**
 * @brief Checks if "play" is a valid play
 *
 * @param[in] play Position played beeing validated
 * @param[in] e State where the position is being validated
 *
 * @return If "play" is valid returns corresponding valid position pointer else returns NULL
 *
 * @see compPosition
 */
VALIDS *isValid(POSITION play, ESTADO e)
{
    VALIDS *valids = e.valids;                          // initializes valids to point to valid positions array
    POSITION *valid = &valids->valid;                   // initializes valid to point to first valid position
    int nValids = e.nValids;                            // initializes nValids to number of valid plays
    
    while (--nValids && !compPosition(play, *valid))    // iterates over valid positions
        valid = &(++valids)->valid;                     // increments valids pointer by one
    
    return compPosition(play, *valid) ? valids : NULL;
}

/**
 * @brief Reverses reversable postions
 *
 * @param[in] valids Valid position played
 * @param[in,out] e State where pieces are being reversed
 */
void reverse(VALIDS *valids, ESTADO *e)
{
    POSITION *valid = &valids->valid;                   // initializes valid to point to first valid position
    
    e->grelha[valid->l][valid->c] = e->peca;            // puts playing piece in the chosen position
    
    POSITION *reverse = valids->reverse;                // initializes reverse to point to reversable positions array
    int nReverse = valids->nReverse;                    // initializes nReverse to number of reversable positions
    
    for (; nReverse--; ++reverse)                       // iterates over reversable positions
        e->grelha[reverse->l][reverse->c] = e->peca;    // reverses reversable positions
}

/**
 * @brief Updates game to its next state
 *
 * If next state has no valid plays, updates the state again. If it still has no valid plays then the game is over.
 *
 * @param[in,out] e State beeing update
 *
 * @return Error code
 *
 * @see switchPiece
 * @see update
 */
int nextState(ESTADO *e)
{
    switchPiece(&e->peca);                     // Switches playing piece
    update(e);                                 // Updates state
    
    if (!e->nValids)                           // Checks if current state doesn't have valid plays
    {
        switchPiece(&e->peca);                 // Switches playing piece
        update(e);                             // Updates state
        
        if (!e->nValids)                       // Checks if current state doesn't have vaid plays
        {
            if (e->scoreX == e->scoreO)        // checks if score is tied
                return 10;                     // 
            else if (e->scoreX > e->scoreO)    // checks if X has won
                return 11;                     // 
            else                               // else O has won
                return 12;                     // 
        }
        
        return 9;
    }
    
    return 0;
}
