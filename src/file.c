#include "estado.h"

int readFile(ESTADO *e, char *file_name, int tipo)
{
    FILE *file;
    char file_txt[MAX_STR];
    int peca;
    
    sprintf(file_txt, "../saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    if (!file)
        return 1;
    
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
    
    update(e);

    return 0;
}

void saveState(ESTADO* e, char* file_name, LEST s)
{
    FILE *file;
    int l,c;
    char file_pos_name[MAX_STR];
    
    sprintf(file_pos_name, "../saves/%s.txt", file_name);
    
    file=fopen(file_pos_name, "w");
    
    
    while(s)
    {
        fprintf(file, "%c %c\n", (s->e.modo == '0') ? 'M' : (s->e.modo == '1') ? 'A' : '?', (s->e.peca == VALOR_X) ? 'X' : (s->e.peca == VALOR_O) ? 'O' : '?');
        
        for(l=0;l<DIM;l++){
            for(c=0;c<DIM;c++)
                switch(s->e.grelha[l][c]){
                    case VALOR_O:
                        fputc('O',file);
                        break;
                    case VALOR_X:
                        fputc('X',file);
                        break;
                    case VAZIA:
                        fputc('-',file);
                        break;
                    default:
                        fputc('E',file);
                        break;
                }
            fputc((c < DIM-1) ? ' ' : '\n', file);
        }
        s = s->next;
    }
    
    fclose(file);
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
