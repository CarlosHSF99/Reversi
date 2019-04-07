#include "estado.h"

int main()
{
    ESTADO e = {0};

    printf("%d\n", sizeof(e));
    
    e.modo = HELP;
    e.peca = HELP;
    
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    
    interpreter(e);

    return 0;
}
