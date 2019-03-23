#include "estado.h"

//novo jogo contra um adversario humano

void newVsHuman();

//novo jogo contra um bot

void newVsBot();


//ler ficheiro. 

void readFile(ESTADO *e,char *file_name) {
    FILE *file;
    char file_txt[MAX_LENGTH];
    int l, c, peca;
    
    sprintf(file_txt, "./saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    fseek(file, -133, SEEK_END);
    
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
}

//escreve num ficheiro

void writeFile(ESTADO *e,char *filename)
{}

//executa uma jogada

void play(int l,int c,ESTADO *e) {
    if(cerca(l, c, *e)) {
        e->grelha[l][c] = e->peca;
        if((e->peca) == VALOR_O)
            e->peca = VALOR_X;
        else
            e->peca = VALOR_O;
    }
    else
        printf("Jogada invalida");
}

//coloca pontos nas posicoes das jogadas validas

void something(ESTADO e)
{
    for (int i=0; i < DIM; i++)
        for (int j=0; j < DIM; j++)
            if (cerca(i, j, e))
                e.grelha[i][j] = '.';
    
    printg(e);
}
 
//verifica jogadas validas

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

//funcao auxiliar da funcao cerca

int cercaDir (int k, int l, int i, int j, ESTADO e)
{
    if (e.grelha[i+=k][j+=l] == e.peca)
         return 0;
 
    for (; i < DIM && i>=0 && j < DIM && j>=0; i+=k, j+=l)
         if (e.grelha[i][j] == e.peca)
            return 1;
         else if (e.grelha[i][j] == VAZIA || e.grelha[i][j] == VALOR_DOT)
            return 0;
 
    return 0;
}

//coloca um '?' na jogada aconselhada
 
void help()
{}

//desfaz uma jogada

void undo()
{}
