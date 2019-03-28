#include "estado.h"

//novo jogo contra adversario humano
void newVsHuman(ESTADO *e, VALOR n)
{
    FILE *file;
    
    e->modo = '0';
    e->peca = n;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            e->grelha[i][j] = VAZIA;
    
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    
    something(e);
    
    file = fopen("../saves/.default.txt", "w"); //só para limpar o ficheiro
    fclose(file);
    
    writeEstado(e);
    
    printg(*e, 0, 0);
}

void newVsBot(ESTADO *e)
{
    e->modo = '1';
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            e->grelha[i][j] = VAZIA;
    
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    
    printg(*e, 0, 0);
}

//ler ficheiro. 
void readFile(ESTADO *e, char *file_name, int tipo)
{
    FILE *file;
    char file_txt[MAX_LENGTH];
    int peca;
    
    sprintf(file_txt, "../saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    fseek(file, tipo, SEEK_END);
    
    e->modo = fgetc(file) == 'M' ? '0' : '1';
    fseek(file, 1, SEEK_CUR);
	e->peca = fgetc(file) == 'X' ? VALOR_X : VALOR_O;
    fseek(file, 1, SEEK_CUR);
    
    for(int l = 0; l < DIM; l++)
        for(int c = 0; c < DIM; c++)
        {
            e->grelha[l][c] = (peca = fgetc(file)) == '-' ? VAZIA : peca == 'X' ? VALOR_X : VALOR_O;
            fseek(file, 1, SEEK_CUR);
        }
    
    fclose(file);
    
    something(e);
    
    printg(*e, 0, 0);
}

//copia do default para o ficheiro destino defenido pelo jogador
void saveFile(ESTADO *e, char *file_name)
{
    FILE *file;
    FILE *def_file;
    char ch;
    char file_pos_name[MAX_LENGTH];
    
    sprintf(file_pos_name, "../saves/%s.txt", file_name);
    
    file=fopen(file_pos_name,"w");
    
    def_file=fopen("../saves/.default.txt","r");
    
    while((ch=fgetc(def_file)) != EOF)
        fputc(ch,file);
    
    fclose(file);
    fclose(def_file);
}

//Guarda jogadas
void writeEstado(ESTADO *e)
{
    FILE *file;
    
    file = fopen("../saves/.default.txt", "a+");
    
    fprintf(file, "%c %c\n", e->modo == '0' ? 'M' : 'A', e->peca == VALOR_X ? 'X' : 'O');
    
    for (int l = 0; l < DIM; l++)
        for (int c = 0; c < DIM; c++)
        {
            switch(e->grelha[l][c])
            {
                case (VALOR_O):
                    fprintf(file, "O");
                    break;
                case (VALOR_X):
                    fprintf(file, "X");
                    break;
                case (VAZIA):
                    fprintf(file, "-");
                    break;
                default:
                    fprintf(file, "E");
                    break;
            }
            
            fprintf(file, c < DIM-1 ? " " : "\n");
        }
    
    fprintf(file, "\n");

    fclose(file);
}

//executa uma jogada
void play(int l, int c, ESTADO *e)
{
    int i;

    if(elem(l, c, *e))
    {
        e->grelha[l][c] = e->peca;
        
        for (i = 0; (e->validas[i].valida.l != l || e->validas[i].valida.c != c) && i < e->nValidas; i++);
        
        for (int j = 0; j < e->validas[i].nVirar; j++)
            e->grelha[e->validas[i].virar[j].l][e->validas[i].virar[j].c] = e->peca;
        
        do
        {
            e->peca = 3 - e->peca;
            something(e);
        }
        while (!e->nValidas);
        
        writeEstado(e);
        
        //isGameOver(*e);
    }
    else
        printf("Jogada invalida!\n");
    
    printg(*e, 0, 0);
}

//coloca pontos nas posicoes das jogadas validas
void something(ESTADO *e)
{
    e->nValidas = e->NX = e->NO = 0;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        {
            e->grelha[i][j] != VAZIA ? e->grelha[i][j] == VALOR_X ? e->NX++ : e->NO++ : 0 ;
            
            if (cerca(i, j, e, e->nValidas))
            {
                e->validas[e->nValidas].valida.l = i;
                e->validas[e->nValidas].valida.c = j;
                e->nValidas++;
            }
        }
}
 
//verifica jogadas valida
int cerca(int i, int j, ESTADO *e, int n)
{
    e->validas[n].nVirar = 0;
    
    if (e->grelha[i][j] != VAZIA)
        return 0;
    
    return cercaDir(-1, -1, i, j, e, n) +
           cercaDir(-1,  0, i, j, e, n) +
           cercaDir(-1,  1, i, j, e, n) +
           cercaDir( 0, -1, i, j, e, n) +
           cercaDir( 0,  1, i, j, e, n) +
           cercaDir( 1, -1, i, j, e, n) +
           cercaDir( 1,  0, i, j, e, n) +
           cercaDir( 1,  1, i, j, e, n);
}

//funcao auxiliar da funcao cerca
int cercaDir (int k, int l, int i, int j, ESTADO *e, int n)
{
    int counter = 0;
    
    VALOR opnt = 3 - e->peca;
    
    if (e->grelha[i+=k][j+=l] == e->peca)
        return 0;
    
    for (; i < DIM && i>=0 && j < DIM && j>=0 && (e->grelha[i][j] == opnt); i+=k, j+=l) //fazer nao puro
    {
        e->validas[n].virar[e->validas[n].nVirar].l = i;
        e->validas[n].virar[e->validas[n].nVirar].c = j;
        e->validas[n].nVirar++;
        counter++;
    }
    
    if (e->grelha[i-k][j-l] == opnt && e->grelha[i][j] != e->peca)
        e->validas[n].nVirar -= counter;
    
    return e->grelha[i][j] == e->peca && i < DIM && i>=0 && j < DIM && j>=0 ? 1 : 0;
}

//coloca um '?' na jogada aconselhada
void help()
{}

//desfaz uma jogada
void undo(ESTADO *e)
{
    FILE *file;
    
    readFile(e, ".default", UNDO);
    
    file = fopen("../saves/.default.txt", "a");
    
    ftruncate(fileno(file), ftell(file) + READ);
    
    fclose(file);
}

//se no O ou no X ou no Vazia ou nao ha jogadas possiveis para ambos os jogadores
/*void isGameOver(ESTADO *e)
{
    int v = e->nValidas;

    something(e);

    v += e->nValidas;
    
    return !v ? e->NX == e->NO ? 3 : e->NX > e->NO ? VALOR_X : VALOR_O : 0;
}*/

int elem(int l, int c, ESTADO e)
{
    for (int i = 0; i < e.nValidas; i++)
        if (e.validas[i].valida.l == l && e.validas[i].valida.c == c)
            return 1;

    return 0;
}
