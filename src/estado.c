#include "estado.h"

// imprime um estado (Tabuleiro)
void printg(ESTADO e, int validas, int ajuda)
{
    int nx, no;

    nx = no = 0;

    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            e.grelha[i][j] != VAZIA ? e.grelha[i][j] == VALOR_X ? nx++ : no++ : 0 ;

    //e.modo = '0' ? putchar('M') : putchar('A');
    putchar(e.modo == '0' ? 'M' : 'A');
    putchar(' ');
    //e.peca = VALOR_X ? putchar('X') : putchar('O');
    putchar(e.peca == VALOR_X ? 'X' : 'O');
    printf("   X:%02d O:%02d\n", nx, no);
    
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
