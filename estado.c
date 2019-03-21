#include <stdio.h>
#include "estado.h"

#define DIM 8

// exemplo de uma função para imprimir o estado (Tabuleiro)
void printg(ESTADO e)
{
    char c = ' ';
    
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            switch (e.grelha[i][j])
            {
                case VALOR_O:
                    c = 'O';
                    break;
                case VALOR_X:
                    c = 'X';
                    break;
                case VAZIA:
                    c = '-';
                    break;
                default:
                    c = '.';
                    break;
            }
            
            printf("%c ", c);
        }
        
        printf("\n");
    }
}
