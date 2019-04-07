#include "estado.h"

int main()
{
    ESTADO *e = calloc(1, sizeof(ESTADO));
    
    if (!e)
        exit(0);

    e->modo = HELP;
    e->peca = HELP;
    
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    
    interpreter(*e);

    free(e);

    return 0;
}
