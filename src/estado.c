#include "estado.h"

// imprime um estado (Tabuleiro)
void printg(ESTADO e, int validas, int ajuda)
{
    putchar(e.modo == '0' ? 'M' : 'A');
    putchar(' ');
    putchar(e.peca == VALOR_X ? 'X' : 'O');
    printf("   X:%02d O:%02d\n", e.NX, e.NO);
    
    if (validas)
        for (int i = 0; i < e.nValidas; i++)
            e.grelha[e.validas[i].valida.l][e.validas[i].valida.c] = VALIDA;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++){
            switch (e.grelha[i][j])
            {
                case VAZIA:
                    putchar('-');
                    break;
                case VALOR_X:
                    putchar('X');
                    break;
                case VALOR_O:
                    putchar('O');
                    break;
                case VALIDA:
                    putchar('.');
                    break;
                case HELP:
                    putchar('?');
                    break;
                default:
                    putchar('E');
                    break;
            }
            
            putchar(j < DIM-1 ? ' ' : '\n');
        }
}
