#include <stdio.h>
#include "estado.h"

int main()
{
    ESTADO e = {0};

    // estado inicial do tabuleiro
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    
    // printa grelha
    printf("\n");
    printg(e);
    printf("\n");
    
    menu();
    
    return 0;
}
