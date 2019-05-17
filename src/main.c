#include "estado.h"

int main()
{
    LEST* ss = NULL;                               //
    LEST s = calloc(1, sizeof(struct history));    // allocs memory to the stack setting every bit to zero
    ESTADO e = {0};                                // declares a state "e" inicializing all its bits to zero

    if (!s)                                        // checks if there was an error allocing memory to s
        exit(0);                                   // terminates program if there was an error allocing memory
    
    e.modo = HELP;                                 // sets value of e.modo to ?
    e.peca = HELP;                                 // sets value of e.peca to ?
    e.botLVL = ' ';
    e.bot = HELP;                                  //
    
    e.scoreX = 2;                                  // sets X score to 2
    e.scoreO = 2;                                  // sets O score to 2
    
    boardInicial(e.grelha);                        // sets board to its inicial state
    
    s->e = e;                                      //
    s->next = NULL;                                //
    
    interpreter(e, s);                             //
    
    ss = &s;                                       //
    freeStack(ss);                                 //
    
    return 0;                                      //
}
