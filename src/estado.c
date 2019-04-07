#include "estado.h"

//novo jogo contra adversario humano
void newVsHuman(ESTADO *e, VALOR n)
{
    FILE *file;
    
    //free_estado(e);
    
    //if (!(e = (ESTADO*)malloc(sizeof(ESTADO))))
    //    exit(0);
    
    e->modo = '0';
    e->peca = n;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            e->grelha[i][j] = VAZIA;
    
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    
    validate(e);
    
    //for (int i = 0; i < e->nValidas; i++)
    //    printf("(%d,%d)\n", e->validas[i].valida.l, e->validas[i].valida.c);
    
    file = fopen("../saves/.default.txt", "w"); //só para limpar o ficheiro
    fclose(file);
    
    writeEstado(e);
}

//
void newVsBot(ESTADO *e, VALOR n)
{
    FILE *file;
    
    e->modo = '1';
    e->peca = VALOR_X;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
            e->grelha[i][j] = VAZIA;
    
    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;
    
    validate(e);
    
    //printg(*e);
    
    file = fopen("../saves/.default.txt", "w"); //só para limpar o ficheiro
    fclose(file);
    
    writeEstado(e);
    
    if (n == VALOR_O)
        miniMax(e, 0, 1);
}

//ler ficheiro
int readFile(ESTADO *e, char *file_name, int tipo)
{
    FILE *file;
    char file_txt[MAX_STR];
    int peca;
    
    sprintf(file_txt, "../saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    if (file == NULL)
    {
        printf("Save file %s doens't exist!\n", file_name);
        return 1;
    }
    
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
    
    validate(e);
}

//copia do default para o ficheiro destino defenido pelo jogador
void saveFile(ESTADO *e, char *file_name)
{
    FILE *file;
    FILE *def_file;
    char ch;
    char file_pos_name[MAX_STR];
    
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
    int j = 0;
    
    if(elem(l, c, *e))
    {
        e->grelha[l][c] = e->peca;
        
        for (i = 0; (e->validas[i].valida.l != l || e->validas[i].valida.c != c) && i < e->nValidas; i++);
        
        for (int j = 0; j < e->validas[i].nVirar; j++)
            e->grelha[e->validas[i].virar[j].l][e->validas[i].virar[j].c] = e->peca;
        
        do
        {
            e->peca = 3 - e->peca;
            validate(e);
            j++;
        }
        while (!e->nValidas && j<2);
        
        writeEstado(e);
        
        isGameOver(*e);
    }
    else
        printf("Jogada invalida!\n");
}

//coloca pontos nas posicoes das jogadas validas
void validate(ESTADO *e)
{
    int nVirarHelp = 0;
    
    e->nValidas = e->NX = e->NO = 0;
    
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        {
            e->grelha[i][j] != VAZIA ? e->grelha[i][j] == VALOR_X ? e->NX++ : e->NO++ : 0 ;
            
            if (cerca(i, j, e, e->nValidas))
            {
                e->validas[e->nValidas].valida.l = i;
                e->validas[e->nValidas].valida.c = j;
                
                if (e->validas[e->nValidas].nVirar > nVirarHelp)
                {
                    nVirarHelp = e->validas[e->nValidas].nVirar;
                    e->help = e->validas[e->nValidas].valida;
                }
                
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
void isGameOver(ESTADO e)
{
    int v = e.nValidas;
    
    validate(&e);
    
    v += e.nValidas;
    
    if (!v && e.NX == e.NO)
        printf("Empate\n");
    else if (!v && e.NX > e.NO)
        printf("X ganhou\n");
    else if (!v && e.NX < e.NO)
        printf("O ganhou\n");
}

int elem(int l, int c, ESTADO e)
{
    int i;
    
    for (i = 0; (e.validas[i].valida.l != l || e.validas[i].valida.c != c) && i+1 < e.nValidas; i++);
    
    return e.validas[i].valida.l == l && e.validas[i].valida.c == c ? 1 : 0;
}

// imprime um estado (Tabuleiro)
void printg(ESTADO e, char lines[DIM][MAX_STR])
{
    CLEAR;
    
    printf("  ");
    putchar(e.modo == '2' ? '?' : e.modo == '0' ? 'M' : 'A');
    putchar(' ');
    putchar(e.peca == HELP ? '?' : e.peca == VALOR_X ? 'X' : 'O');
    printf("   X:%02d O:%02d", e.NX, e.NO);
    printf(" ┊ %s", lines[0]);
    
    if (e.showValid)
        for (int i = 0; i < e.nValidas; i++)
            e.grelha[e.validas[i].valida.l][e.validas[i].valida.c] = VALIDA;
    
    if (e.showHelp)
        e.grelha[e.help.l][e.help.c] = HELP;
    
    for (int i = 0; i < DIM; i++)
    {
        printf("%d ", i);
        
        for (int j = 0; j < DIM; j++)
        {
            switch (e.grelha[i][j])
            {
                case VAZIA:
                    printf("- ");
                    break;
                case VALOR_X:
                    printf("X ");
                    break;
                case VALOR_O:
                    printf("O ");
                    break;
                case VALIDA:
                    printf(". ");
                    break;
                case HELP:
                    printf("? ");
                    break;
                default:
                    printf("E ");
                    break;
            }
        }
        
        printf("┊ %s", lines[i+1]);
    }
    
    printf("  0 1 2 3 4 5 6 7 ┊ reversi> ");
}
