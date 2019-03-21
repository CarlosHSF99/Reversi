#include "estado.h"

//mostrar jogadas possiveis.

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
        else if (e.grelha[i][j] == VAZIA || e.grelha[i][j] == VALOR_DOT)
            return 0;

    return 0;
}


//ler ficheiro. 

void readFile(ESTADO e,char *file_name){
    FILE *file;
    char file_txt[MAX_LENGTH];
    int l,c,controlo=0;

    sprintf(file_txt,"./saves/%s.txt",file_name);

    file=fopen(file_txt,"a+");
    
    fseek(file,-74,SEEK_END);
    
    for(l=0;l<10;l++)
        for(c=0;c!='\n';c++)
            switch(getchar()){
                case 'M':
                    e.modo = 0;
                case 'A':
                    e.modo = 1;
                case 'X':
                    if(controlo==0){
                        e.peca=VALOR_X;
                        controlo++;
                    }
                    else
                        e.grelha[l][c] = VALOR_X;
                case '-':
                    e.grelha[l][c] = VAZIA;
                case 'O':
                    if(controlo==0){
                        e.peca=VALOR_O;
                        controlo++;
                    }
                    else
                        e.grelha[l][c] = VALOR_O;
            }
}
