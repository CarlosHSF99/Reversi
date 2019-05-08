#include "estado.h"

// New game against human adversary
void manual(ESTADO *e, VALOR n, LEST* s)
{
    LEST new_s = NULL;                      //
    
    newGame(s);                             // clears history from previous game
    
    new_s = malloc(sizeof(struct history)); // allocates new memory 
    
    new_s->next = (*s);                     //
    s = &new_s;                             //
    
    e->modo = '0';                          // sets game mode to manual (0)
    e->peca = n;                            // sets inicial player to the paramater n
    
    boardInicial(e->grelha);                // sets board to inicial board
    
    update(e);                              // updates state parameters
    
    (*s)->e = *e;                           // adds state to history
}

// New game against computer adversary
void autoVSbot(ESTADO *e, VALOR n, LEST* s)
{
    LEST new_s = NULL;                      //

    newGame(s);                             // clear history from previous game
    
    new_s = malloc(sizeof(struct history)); // allocates new memory
    
    new_s->next = (*s);                     //
    s = &new_s;                             // 

    e->modo = '1';                          // stes game mode to manual (1)
    e->peca = VALOR_X;                      // sets inicial player X
    
    boardInicial(e->grelha);                // sets board to inicial board
    
    update(e);                              // updates state parameters
    
    (*s)->e = *e;                           // adds state to history

    if (n == VALOR_O)                       // if the human player is O
        miniMax(e, 0, 1, s);                // then the computer starts playing
}

// Sets board to inicial board
void boardInicial(VALOR grelha[DIM][DIM])
{
    for (int i = 0; i < DIM; i++)        // sets every position to empty (VAZIA)
        for (int j = 0; j < DIM; j++)    //
            grelha[i][j] = VAZIA;        //
    
    grelha[3][4] = VALOR_X;              // sets position (3,4) to X
    grelha[4][3] = VALOR_X;              // sets position (4,3) to X
    grelha[3][3] = VALOR_O;              // sets position (3,3) to O
    grelha[4][4] = VALOR_O;              // sets position (4,4) to O
}

//executa uma jogada
int reverse(int l, int c, ESTADO *e)
{
    if (!elem(l, c, *e))                                // cheks if play is valid
        return 1;                                       // returns error
    
    e->grelha[l][c] = e->peca;                          // puts playing piece in the chosen position
    
    VALIDAS *valids = e->validas;                       //
    POSICAO *valid = &valids->valida;                   // REVER
    
    while (valid->l != l || valid->c != c)              // iterates over valid positions until finding the current one
        valid = &(++valids)->valida;                    // REVER
    
    POSICAO *reverse = valids->virar;                   //
    int nReverse = valids->nVirar;                      //
    
    for (; nReverse--; ++reverse)                       // iterates over reversable positions
        e->grelha[reverse->l][reverse->c] = e->peca;    // reverses reversable positions
    
    return stateUpdate(e);                              //
}

// Updates game state
int stateUpdate(ESTADO *e)
{
    int i = -1;                   //
    
    do                            // checks if jump piece
    {
        switchPiece(&e->peca);    // 
        update(e);                //
        
        if (++i)                  //
            return 1;             //
    }
    while (!e->nValidas);         //

    return 0;                     //
}

// Actually updates game state
void update(ESTADO *e)
{
    int nVirarHelp = 0;                                  //
    
    e->nValidas = e->scoreX = e->scoreO = 0;             // resets number of valid positions and score
    
    for (int l = 0; l < DIM; l++)                        // iterates over board lines
        for (int c = 0; c < DIM; c++)                    // iterates over board columns
        {
            scoreUpdate(e, l, c);                        //
            
            if (cerca(l, c, e, e->nValidas))             // checks if current position is a valid play
            {
                e->validas[e->nValidas].valida.l = l;    // saves valid line to current position
                e->validas[e->nValidas].valida.c = c;    // saves valid column to current position
                
                helpFunc(e, &nVirarHelp);                //
            }
        }
}

//
void scoreUpdate(ESTADO *e, int l, int c)
{
    VALOR piece = e->grelha[l][c];    // initializes piece to current position value

    e->scoreX += piece == VALOR_X;    // increments X by one score if pos is equal to X
    e->scoreO += piece == VALOR_O;    // increments O by one score if pos is equal to O
}

//
void helpFunc(ESTADO *e, int *nVirarHelp)
{
    if (e->validas[e->nValidas].nVirar > *nVirarHelp)    // checks if current pos will flip the most pieces
    {
        *nVirarHelp = e->validas[e->nValidas].nVirar;    // 
        e->help = e->validas[e->nValidas].valida;        // saves current position as suggestion play
    }
    
    e->nValidas++;                                       // increments number of valid positions by one
}
 
// Checks if a postion is a valid play
int cerca(int l, int c, ESTADO *e, int n)
{
    e->validas[n].nVirar = 0;             // resets number of reversable pieces to zero
    
    if (e->grelha[l][c])                  // checks if current posiiton is empty
        return 0;                         // returns false
    
    return                                // returns true if the current position reverses any piece in the direction
        cercaDir(l, c, -1,  0, e, n) +    // up
        cercaDir(l, c,  1,  0, e, n) +    // down
        cercaDir(l, c,  0,  1, e, n) +    // right
        cercaDir(l, c,  0, -1, e, n) +    // left
        cercaDir(l, c, -1,  1, e, n) +    // up   right
        cercaDir(l, c, -1, -1, e, n) +    // up   left
        cercaDir(l, c,  1,  1, e, n) +    // down right
        cercaDir(l, c,  1, -1, e, n);     // down left
}

// Checks if a position is a valid play in a direction and saves reversable positions and how many are they
int cercaDir (int l, int c, int i, int j, ESTADO *e, int n)
{
    VALOR opnt = e->peca;                                                     // initializes onpt to current player piece
    
    switchPiece(&opnt);                                                       // sets onpt to oponent player piece
    
    POSICAO *reverse = e->validas[n].virar;                                   // initializes reverse pointing reversable positions array
    int *nReverse = &e->validas[n].nVirar;                                    // initializes nReverse pointing number reversable positions
    int counter = 0;                                                          // initializes counter to 0
   
    for (l+=i, c+=j; inBoard(l, c) && e->grelha[l][c] == opnt; l+=i, c+=j)    // iterates over board vector
    {
        reverse[*nReverse].l = l;                                             // adds coordenate l to reversable positions
        reverse[*nReverse].c = c;                                             // adds coordenate c to reversable positions
        (*nReverse)++;                                                          // increments number of reversable pieces by one
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
}

//se no O ou no X ou no Vazia ou nao ha jogadas possiveis para ambos os jogadores
int isGameOver(ESTADO e)
{
    int v = e.nValidas;              // 
    
    update(&e);                      // updates state
    
    v += e.nValidas;                 // sums number of valid plays before and after update
    
    if (v)                           // checks if there are valid plays for both pieces
        return 0;                    //

    if (e.scoreX == e.scoreO)        // checks if score is tied
        return 1;                    // puts "Draw" message in CLI
    else if (e.scoreX > e.scoreO)    // checks if X has won
        return 1;                    // puts "X Won" message in CLI
    else                             // else O has won
        return 1;                    // puts "O Won" message in CLI
}

//
int elem(int l, int c, ESTADO e)
{
    VALIDAS *valids = e.validas;                                //
    POSICAO *valid = &valids->valida;                           //
    
    while ((valid->l != l || valid->c != c) && --e.nValidas)    //
        valid = &(++valids)->valida;                            //
    
    return valid->l == l && valid->c == c;                      //
}
