#include "estado.h"

//novo jogo contra um adversario humano
void newVsHuman()
{}

//novo jogo contra um bot
void newVsBot()
{}

//ler ficheiro. 
void readFile(ESTADO *e,char *file_name)
{
    FILE *file;
    char file_txt[MAX_LENGTH];
    int l, c, peca;
    
    sprintf(file_txt, "../saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    fseek(file, -134, SEEK_END);
    
    e->modo = fgetc(file) == 'M' ? '0' : '1';
    fseek(file, 1, SEEK_CUR);
    e->peca = fgetc(file) == 'X' ? VALOR_X : VALOR_O;
    fseek(file, 1, SEEK_CUR);
    
    for(l=0; l < DIM; l++)
        for(c=0; c < DIM; c++)
        {
            e->grelha[l][c] = (peca = fgetc(file)) == '-' ? VAZIA : peca == 'X' ? VALOR_X : VALOR_O;
            fseek(file, 1, SEEK_CUR);
        }

    printg(*e, 0, 0);
}

//escreve num ficheiro
void writeFile(ESTADO *e,char *filename)
{}

//executa uma jogada
void play(int l, int c, ESTADO *e)
{
    if(cerca(l, c, *e)) 
    {
        e->grelha[l][c] = e->peca;
        e->peca = 3 - e->peca;
    }
    else
        printf("Jogada invalida!\n");

    printg(*e, 0, 0);
}

//coloca pontos nas posicoes das jogadas validas
void something(ESTADO *e)
{
    e->nValidas = 0;
    
    for (int i=0; i < DIM; i++)
        for (int j=0; j < DIM; j++)
            if (cerca(i, j, *e))
            {
                e->validas[e->nValidas].l = i;
                e->validas[e->nValidas].c = j;
                e->nValidas++;
            }
    
    printg(*e, 1, 0);
}
 
//verifica jogadas valida
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
           cercaDir( 1,  1, i, j, e));
}

//funcao auxiliar da funcao cerca
int cercaDir (int k, int l, int i, int j, ESTADO e)
{
    VALOR opnt = 3 - e.peca;
    
    if (e.grelha[i+=k][j+=l] == e.peca)
        return 0;
    
    for (; i < DIM-1 && i>0 && j < DIM-1 && j>0 && (e.grelha[i][j] == opnt); i+=k, j+=l);
    
    return e.grelha[i][j] == e.peca ? 1 : 0;
}

//coloca um '?' na jogada aconselhada
void help()
{}

//desfaz uma jogada
void undo()
{}
