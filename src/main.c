#include "estado.h"

int main()
{
    LEST* ss = NULL;
    LEST s = calloc(1, sizeof(struct history)); // allocs memory to the stack setting every bit to zero
    ESTADO e = {0};                             // declares a state "e" inicializing all its bits to zero

    if (!s)                                     // checks if there was an error allocing memory to s
        exit(0);                                // terminates program if there was an error allocing memory
    
    e.modo = HELP;                              // sets value of e.modo to ?
    e.peca = HELP;                              // sets value of e.peca to ?
    
    e.NX = 2;                                   // sets X score to 2
    e.NO = 2;                                   // sets O score to 2
    
    e.grelha[3][3] = VALOR_O;                   // sets posicion (3,3) to O;
    e.grelha[4][4] = VALOR_O;                   // sets posicion (4,4) to O;
    e.grelha[3][4] = VALOR_X;                   // sets posicion (3,4) to X;
    e.grelha[4][3] = VALOR_X;                   // sets posicion (4,3) to X;
    
    s->e=e;
    s->next=NULL;

    interpreter(e,&s);
    
    ss=&s;
    freeStack(ss);
    
    return 0;
}
