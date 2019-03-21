#include "estado.h"

void something(ESTADO e)
{
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            if (cerca(i, j, e))
                e.grelha[i][j] = '.';
    
    printg(e);
}

int cerca(int i, int j, ESTADO e)
{
    return e.grelha[i][j] == VAZIA && (
           cercaDir(-1, -1, i, j, e) ||
           cercaDir(-1,  0, i, j, e) ||
           cercaDir(-1,  1, i, j, e) ||
           cercaDir( 0, -1, i, j, e) ||
           cercaDir( 0,  1, i, j, e) ||
           cercaDir( 1, -1, i, j, e) ||
           cercaDir( 1,  0, i, j, e) ||
           cercaDir( 1,  1, i, j, e) );
}

int cercaDir (int k, int l, int i, int j, ESTADO e)
{
    if (e.grelha[i+=k][j+=l] == e.peca)
        return 0;

    for (; i < DIM && i >= 0 && j < DIM && j >= 0; i+=k, j+=l)
        if (e.grelha[i][j] == e.peca)
            return 1;
        else if (e.grelha[i][j] == VAZIA || e.grelha[i][j] == '.')
            return 0;

    return 0;
}
