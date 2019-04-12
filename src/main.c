#include "estado.h"

int main()
{
    LEst e = calloc(1, sizeof(LEST));
    
    if (!e)
        exit(0);
    
    e->e.modo = HELP;
    e->e.peca = HELP;
    
    e->e.NX = 2;
    e->e.NO = 2;
    
    e->e.grelha[3][3] = VALOR_O;
    e->e.grelha[4][4] = VALOR_O;
    e->e.grelha[3][4] = VALOR_X;
    e->e.grelha[4][3] = VALOR_X;
    
    interpreter(e->e);
    
    freeEstado(e);
    
    return 0;
}
