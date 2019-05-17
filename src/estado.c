#include "estado.h"

/**
 * @brief 
 *
 * @param[in] play
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see isValid
 * @see reverse
 * @see nextState
 * @see push
 */
int doPlay(POSICAO play, ESTADO *e, LEST *s)
{
    int num;                               //
    VALIDAS *valided;                      //
    
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
 * @param[in] play Play beeing validated
 * @param[in] e State in which "play" is being validated
 *
 * @return If "play" is valid returns corresponding play pointer else return NULL
 *
 * @see compPosition
 */
VALIDAS *isValid(POSICAO play, ESTADO e)
{
    VALIDAS *valids = e.validas;                          // initializes valids to point to valid positions array
    POSICAO *valid = &valids->valida;                     // initializes valid to point to first valid position
    int nValids = e.nValidas;                             // initializes nValids to number of valid plays
    
    while (--nValids && !compPosition(play, *valid))      // iterates over valid positions
        valid = &(++valids)->valida;                      // increments valids pointer by one
    
    return compPosition(play, *valid) ? valids : NULL;
}

/**
 * @brief Reverses reversable postions
 *
 * @param[in] valids Pointer to 
 * @param[in,out] e Pointer two state where pieces are being reversed
 */
void reverse(VALIDAS *valids, ESTADO *e)
{
    POSICAO *valid = &valids->valida;                   // initializes valid to point to first valid position
    
    e->grelha[valid->l][valid->c] = e->peca;            // puts playing piece in the chosen position
    
    POSICAO *reverse = valids->virar;                   // initializes reverse to point to reversable positions array
    int nReverse = valids->nVirar;                      // initializes nReverse to number of reversable positions
    
    for (; nReverse--; ++reverse)                       // iterates over reversable positions
        e->grelha[reverse->l][reverse->c] = e->peca;    // reverses reversable positions
}

/**
 * @brief Compares two positions
 *
 * @param[in] a First position
 * @param[in] b Second position
 *
 * @return 1 (true) if the two positions are equal or 0 (false) if not
 */
int compPosition(POSICAO a, POSICAO b)
{
    return a.l == b.l && a.c == b.c;
}

/**
 * @brief Updates game to the next state
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
    
    if (!e->nValidas)                          // Checks if current state doesn't have valid plays
    {
        switchPiece(&e->peca);                 // Switches playing piece
        update(e);                             // Updates state
        
        if (!e->nValidas)                      // Checks if current state doesn't have vaid plays
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
int isGameOver(ESTADO e)
{
    int nValids = e.nValidas;    // initializes nValids to number of valid plays
    
    switchPiece(&e.peca);        // switches current playing piece
    update(&e);                  // updates state
    
    nValids += e.nValidas;       // sums number of valid plays before and after update
    
    return !nValids;             //
}

/**
 * @brief Updates game state
 *
 * @param[in,out] e
 *
 * @see scoreUpdate
 * @see surround
 * @see helpUpdate
 */
void update(ESTADO *e)
{
    int nVirarHelp = 0;                         // initializes nVirarHelp to 0
    
    e->nValidas = e->scoreX = e->scoreO = 0;    // resets number of valid positions and score
    
    for (int l = 0; l < DIM; l++)               // iterates over board lines
        for (int c = 0; c < DIM; c++)           // iterates over board columns
        {
            scoreUpdate(l, c, e);               // updates the score
            
            if (surround(l, c, e))              // checks if current position is a valid play
            {
                helpUpdate(&nVirarHelp, e);     // updates suggested position
                e->nValidas++;                  // increments number of valid positions by one
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
 * @see cerca
 */
int surround(int l, int c, ESTADO *e)
{
    if (!cerca(l, c, e))                      // checks if current position is a valid play
        return 0;                             // returns no errors
    
    POSICAO *valid = &VALID(e, nVALID(e));    // initializes valid to point to valid postion
    
    valid->l = l;                             // saves valid line to current position
    valid->c = c;                             // saves valid column to current positio
    
    return 1;                                 // return error code
}

/**
 * @brief Checks if a postion is a valid play
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 * @param[in] e
 *
 * @return 1 (true) if  or 0 (false) if not
 *
 * @see cercaDir
 */
int cerca(int l, int c, ESTADO *e)
{
    e->validas[e->nValidas].nVirar = 0;    // resets number of reversable pieces to zero
    
    if (e->grelha[l][c])                   // checks if current posiiton is empty
        return 0;                          // returns false
    
    return                                 // returns true if the current position reverses any piece in the direction
        cercaDir(l, c, -1,  0, e) +        // up
        cercaDir(l, c,  1,  0, e) +        // down
        cercaDir(l, c,  0,  1, e) +        // right
        cercaDir(l, c,  0, -1, e) +        // left
        cercaDir(l, c, -1,  1, e) +        // up   right
        cercaDir(l, c, -1, -1, e) +        // up   left
        cercaDir(l, c,  1,  1, e) +        // down right
        cercaDir(l, c,  1, -1, e);         // down left
}

/**
 * @brief Checks if a position is a valid play in a certain direction, saves reversable positions and how many there are
 *
 * @param[in] l Line coordinate
 * @param[in] c Column coordinate
 * @param[in] i Line vector
 * @param[in] j Column vector
 * @param[in,out] e State where...
 *
 * @return 1 (true) if the position (l,c) is valid or 0 (false) if not
 */
int cercaDir (int l, int c, int i, int j, ESTADO *e)
{
    VALOR opnt = e->peca;                                                     // initializes onpt to current player piece
    
    switchPiece(&opnt);                                                       // sets onpt to oponent player piece
    
    POSICAO *reverse = e->validas[e->nValidas].virar;                         // initializes reverse pointing reversable positions array
    int *nReverse = &e->validas[e->nValidas].nVirar;                          // initializes nReverse pointing number reversable positions
    int counter = 0;                                                          // initializes counter to 0
   
    for (l+=i, c+=j; inBoard(l, c) && e->grelha[l][c] == opnt; l+=i, c+=j)    // iterates over board vector
    {
        reverse[*nReverse].l = l;                                             // adds coordenate l to reversable positions
        reverse[*nReverse].c = c;                                             // adds coordenate c to reversable positions
        (*nReverse)++;                                                        // increments number of reversable pieces by one
        counter++;                                                            // increments counter by one
    }
    
    if (inBoard(l, c) && e->grelha[l][c] == e->peca && counter)               // checks if position is valid in this direction
        return 1;                                                             // returns true
    
    *nReverse -= counter;                                                     // removes number of reversable pieces
    
    return 0;                                                                 // returns false
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

    e->scoreX += piece == VALOR_X;    // increments X by one score if pos is equal to X
    e->scoreO += piece == VALOR_O;    // increments O by one score if pos is equal to O
}

/**
 * @brief Updates help position
 *
 * @param[in,out] nVirarHelp Counter which controls...comparing purposes
 * @param[in,out] e State where help position is updated
 */
void helpUpdate(int *nVirarHelp, ESTADO *e)
{
    VALIDAS *nReverse = &VALIDS(e, nVALID(e));    // initializes nReverse to number of reversable poriitons
    
    if (nReverse->nVirar > *nVirarHelp)           // checks if current positions will flip the most pieces
    {
        *nVirarHelp = nReverse->nVirar;           // updates counter
        e->help = nReverse->valida;               // saves current position as suggestion play
    }
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
 * @brief Switches piece
 *
 * @param[in,out] piece
 */
void switchPiece(VALOR *piece)
{
    *piece = 3 - *piece;
}

/**
 * @brief Undoes the last play
 *
 * @param[in,out] e
 * @param[in,out] s
 *
 * @see pop
 */
void popundo(ESTADO *e, LEST* s) // DEFINIR MELHOR QUANTAS VEZES SE FAZ UNDO
{
    pop(s);                // pops last state (first in stack)
    
    if (e->modo == '1')    // if the game is in automatic mode
        pop(s);            // pops last state (first in stack) again

    *e = (*s)->e;          // sets state e to now last state
}

// Championship function
/**
 * @brief 
 *
 * @param file
 *
 * @return 
 */
int playBot(char *file)
{
    FILE *fp;
    char file_txt[MAX_STR];
    
    sprintf(file_txt, "../../../../../../mnt/dav/%s.txt", file);    // 
    
    if (!(fp = fopen(file_txt, "r")))                               //
        return 1;                                                   //
    
    return 0;                                                       //
}
