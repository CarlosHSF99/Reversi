#include "estado.h"

// New game against human adversary
void manual(ESTADO *e, VALOR n, LEST* s)
{
    LEST new_s = NULL;                      //
    
    newGame(s);                             // clears history from previous game
    
    new_s = malloc(sizeof(struct history)); // allocates new memory 
    
    new_s->next = (*s);                     //
    *s = new_s;                             //
    
    e->modo = '0';                          // sets game mode to manual (0)
    e->peca = n;                            // sets inicial player to the paramater n
    e->botLVL = '0';
    
    boardInicial(e->grelha);                // sets board to inicial board
    
    update(e);                              // updates state parameters
    
    (*s)->e = *e;                           // adds state to history
}

// New game against computer adversary
void autoVSbot(VALOR piece, char lvl, ESTADO *e, LEST* s)
{
    LEST new_s = NULL;                      //
    
    newGame(s);                             // clear history from previous game
    
    new_s = malloc(sizeof(struct history)); // allocates new memory
    
    new_s->next = (*s);                     //
    *s = new_s;                             // 
    
    e->modo = '1';                          // stes game mode to manual (1)
    e->peca = piece;                        // sets inicial player X
    e->botLVL = lvl;
    
    boardInicial(e->grelha);                // sets board to inicial board
    
    update(e);                              // updates state parameters
    
    (*s)->e = *e;                           // adds state to history
    
    if (piece == VALOR_X)                   // 
        switch (lvl)
        {
            case '1':
                bot1(e, s);
                break;
            case '2':
                bot2(e, s);
                break;
            case '3':
                bot3(e, s);
                break;
        }
}

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

// Executa uma jogada
int reverse(int l, int c, ESTADO *e)
{
    if (!isValid(l, c, *e))                             // cheks if play is valid
        return 1;                                       // returns error
    
    e->grelha[l][c] = e->peca;                          // puts playing piece in the chosen position
    
    VALIDAS *valids = e->validas;                       // initializes valids to point to valid positions array
    POSICAO *valid = &valids->valida;                   // initializes valid to point to first valid position
    
    while (valid->l != l || valid->c != c)              // iterates over valid positions until finding the current one
        valid = &(++valids)->valida;                    // increments valids pointer by one
    
    POSICAO *reverse = valids->virar;                   // initializes reverse to point to reversable positions array
    int nReverse = valids->nVirar;                      // initializes nReverse to number of reversable positions
    
    for (; nReverse--; ++reverse)                       // iterates over reversable positions
        e->grelha[reverse->l][reverse->c] = e->peca;    // reverses reversable positions
    
    return stateUpdate(e);                              // returns error code from updating the state
}

// Updates game state
int stateUpdate(ESTADO *e)
{
    int i = -1;                   // initilizes i to -1
    
    do                            // checks if jump piece
    {
        switchPiece(&e->peca);    // switches current piece to oponent one
        update(e);                // updates current state
        
        if (++i)                  // checks if has been incremented more than once
            return 1;             // returns error code
    }
    while (!e->nValidas);         // loops while there's no valid play
    
    return 0;                     // return no errors
}

// Actually updates game state
void update(ESTADO *e)
{
    int nVirarHelp = 0;                         // initializes nVirarHelp to 0
    
    e->nValidas = e->scoreX = e->scoreO = 0;    // resets number of valid positions and score
    
    for (int l = 0; l < DIM; l++)               // iterates over board lines
        for (int c = 0; c < DIM; c++)           // iterates over board columns
        {
            scoreUpdate(e, l, c);               // updates the score
            
            if (surround(l, c, e))              // checks if current position is a valid play
            {
                helpUpdate(e, &nVirarHelp);     // updates suggested position
                e->nValidas++;                  // increments number of valid positions by one
            }
        }
}

//
int surround(int l, int c, ESTADO *e)
{
    if (!cerca(l, c, e))                      // checks if current position is a valid play
        return 0;                             // returns no errors
    
    POSICAO *valid = &VALID(e, nVALID(e));    // initializes valid to point to valid postion
    
    valid->l = l;                             // saves valid line to current position
    valid->c = c;                             // saves valid column to current positio
    
    return 1;                                 // return error code
}

//se no O ou no X ou no Vazia ou nao ha jogadas possiveis para ambos os jogadores
int isGameOver(ESTADO e)
{
    int nValids = e.nValidas;        // initializes nValids to number of valid plays
    
    update(&e);                      // updates state
    
    nValids += e.nValidas;           // sums number of valid plays before and after update
    
    if (nValids)                     // checks if there are valid plays for both pieces
        return 0;                    // returns no errors

    if (e.scoreX == e.scoreO)        // checks if score is tied
        return 1;                    // puts "Draw" message in CLI
    else if (e.scoreX > e.scoreO)    // checks if X has won
        return 1;                    // puts "X Won" message in CLI
    else                             // else O has won
        return 1;                    // puts "O Won" message in CLI
}

// Updates the score
void scoreUpdate(ESTADO *e, int l, int c)
{
    VALOR piece = e->grelha[l][c];    // initializes piece to current position value

    e->scoreX += piece == VALOR_X;    // increments X by one score if pos is equal to X
    e->scoreO += piece == VALOR_O;    // increments O by one score if pos is equal to O
}

// Updates the suggested position
void helpUpdate(ESTADO *e, int *nVirarHelp)
{
    VALIDAS *nReverse = &VALIDS(e, nVALID(e));    // initializes nReverse to number of reversable poriitons
    
    if (nReverse->nVirar > *nVirarHelp)           // checks if current positions will flip the most pieces
    {
        *nVirarHelp = nReverse->nVirar;           // updates counter
        e->help = nReverse->valida;               // saves current position as suggestion play
    }
}
 
// Checks if a postion is a valid play
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

// Checks if a position is a valid play in a direction and saves reversable positions and how many are they
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

// Checks if position (l, c) is in the game board //Pouca caracteres
int inBoard(int l, int c)
{
    return l >= 0 && l < DIM && c >= 0 && c < DIM;
}

// Switches piece //Torna obvio o que acontece
void switchPiece(VALOR *piece)
{
    *piece = 3 - *piece;
}

// Desfaz uma jogada
void popundo(ESTADO *e, LEST* s)
{
    pop(s);         //
    *e = (*s)->e;   //
    
    if (e->modo == '1')
    {
        pop(s);
        *e = (*s)->e;
    }
}

// Championship function
int playBot(char *file)
{
    FILE *fp;
    char file_txt[MAX_STR];
    
    sprintf(file_txt, "../../../../../../mnt/dav/%s.txt", file);    // 
    
    if (!(fp = fopen(file_txt, "r")))                               //
        return 1;                                                   //
    
    return 0;                                                       //
}

// Checks if the position (l,c) is a valid play
int isValid(int l, int c, ESTADO e)
{
    VALIDAS *valids = e.validas;                                // initializes valids to point to valid positions array
    POSICAO *valid = &valids->valida;                           // initializes valid to point to first valid posiiton
    
    while ((valid->l != l || valid->c != c) && --e.nValidas)    // iterates over valid positions
        valid = &(++valids)->valida;                            // increments valids pointer by one
    
    return valid->l == l && valid->c == c;                      // returns if (l,c) is a valid position
}
