#include "estado.h"

// imprimie um estado (Tabuleiro)
void printg(ESTADO e, int validas, int ajuda)
{
    if (validas)
        for (int i = 0; i < e.nValidas; i++)
            e.grelha[e.validas[i].l][e.validas[i].c] = VALOR_DOT;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++){
            switch (e.grelha[i][j])
            {
                case VALOR_O:
                    putchar('O');
                    break;
                case VALOR_X:
                    putchar('X');
                    break;
                case VAZIA:
                    putchar('-');
                    break;
                case VALOR_DOT:
                    putchar('.');
                    break;
                case VALOR_HELP:
                    putchar('?');
                    break;
                default:
                    putchar('E');
                    break;
            }
            
            putchar(j < DIM-1 ? ' ' : '\n');
        }
}
