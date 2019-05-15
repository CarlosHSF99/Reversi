#include "estado.h"

int readFile(ESTADO *e, char *file_name, LEST* s)
{
    FILE *file;
    char file_txt[MAX_STR], ch;
    int peca;
    
    sprintf(file_txt, "../saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    freeStack(s);

    if (file == NULL)
        return 7;
    
    fseek(file, 0, SEEK_END);
    
    while(fgetc(file) != EOF)
    {
        ch = fgetc(file);
        e->modo = (ch == 'M' ? '0' : ch == 'A' ? '1' : HELP);
        fseek(file, -1, SEEK_CUR);
        
        ch=fgetc(file);
        e->peca= (ch == 'X' ? VALOR_X : ch == 'O'? VALOR_O: HELP);
        fseek(file, -1, SEEK_CUR);
        
        for(int l = 0; l < DIM; l++)
            for(int c = 0; c < DIM; c++)
            {
                e->grelha[l][c] = (peca = fgetc(file)) == '-' ? VAZIA : peca == 'X' ? VALOR_X : VALOR_O;
                fseek(file, -1, SEEK_CUR);
            }
        
        update(e);
        altPush(*e, s);
    }
    
    fclose(file);
    
    return 0;
}

//
void saveState(char* file, LEST s)
{
    FILE *fp;
    int l, c;
    char file_path[MAX_STR];
    
    sprintf(file_path, "../saves/%s.txt", file);    // adds path and ".txt" extension to file name
    
    fp = fopen(file_path, "w");                     // opens file on write mode
    
    for (; s; s = s->next)                          // iterates over game history
    {
        saveFirstLine(&fp, s);                      // prints current first line (mode, piece and level) in file
        
        for(l = 0; l < DIM; l++)                    // iterates over board lines
            for(c = 0; c < DIM; c++)                // iterates over board columns
            {
                switch(s->e.grelha[l][c])           // tests current board piece
                {
                    case VALOR_O:                   // in case it is a 'O' (VALOR_O)
                        fputc('O', fp);             // prints 'O' in file
                        break;
                    case VALOR_X:                   // in case it is a 'X' (VALOR_X)
                        fputc('X', fp);             // prints 'X' in file
                        break;
                    case VAZIA:                     // in case it is a '-' (VAZIA)
                        fputc('-', fp);             // prints '-' in file
                        break;
                    default:                        // by default
                        fputc('E', fp);             // prints 'E' in file signaling an error
                        break;
                }
                
                fputc(c < CLI ? ' ' : '\n', fp);    // prints a blank space or a line break to separate columns and lines
            }
        
        fputc('\n', fp);                            // prints a blank line in file to separate states
    }
    
    fclose(fp);                                     // closes file
}

void saveFirstLine(FILE **fp, LEST s)
{
    fprintf(*fp, "%c ", s->e.modo == '0' ? 'M' : 'A');        // prints game mode in file
    fprintf(*fp, "%c ", s->e.peca == VALOR_X ? 'X' : 'O');    // prints playing piece in file
    fprintf(*fp, "%c\n", s->e.botLVL);                        // prints bot level in file
}
