#include "estado.h"

int readFile(ESTADO *e, char *file_name, LEST* s)
{
    FILE *file;
    char file_txt[MAX_STR], ch;//*teste="teste";

    sprintf(file_txt, "../saves/%s.txt", file_name);
    
    file = fopen(file_txt, "r");
    
    if (file == NULL)
        return 7;

    freeStack(s);
    
    //if(*s==NULL)
      //  printf("stackfreed");
    
    while(fgetc(file) != EOF)
    {
        fseek(file, -1, SEEK_CUR);

        ch = fgetc(file);
        //printf("%c",ch);
        e->modo = (ch == 'M' ? '0' : ch == 'A' ? '1' : ch == '?' ? HELP: ERROR);
        fseek(file, 1, SEEK_CUR);
        
        ch = fgetc(file);
        //printf("%c",ch);
        e->peca= (ch == 'X' ? VALOR_X : ch == 'O'? VALOR_O: ch == '?' ? HELP: ERROR);
        fseek(file, 1, SEEK_CUR);
        
        ch=fgetc(file);
        e->botLVL = (ch == ' ' ? 1 : ch);
        fseek(file, 1, SEEK_CUR);
        
        for(int l = 0; l < DIM; l++)
            for(int c = 0; c < DIM; c++)
            {
                ch=fgetc(file);
                e->grelha[l][c] = ch == '-' ? VAZIA : ch == 'X' ? VALOR_X : ch == 'O' ? VALOR_O : ERROR;
                fseek(file, 1, SEEK_CUR);
            }
        fseek(file, 1, SEEK_CUR);
        
        update(e);
        altPush(*e, s);
       // saveState(teste,*s);
        *e=(*s)->e;
    }
    
    fclose(file);
    return 0;
}

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
