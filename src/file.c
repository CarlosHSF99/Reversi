#include "estado.h"

/**
 * @brief 
 *
 * @param e
 * @param file_name
 * @param s
 *
 * @return 
 */
int readFile(char *file, int type, ESTADO *e, LEST* s)
{
    FILE *fp;
    char ch, file_path[MAX_STR];
    
    if (type)
        sprintf(file_path, "../saves/%s.txt", file);
    else
        sprintf(file_path, "../../../../../../mnt/dav/%s.txt", file);
    
    if (!(fp = fopen(file_path, "r")))
        return 7;
    
    freeStack(s);
    
    do
    {
        e->modo = fgetc(fp) == 'M' ? '0' : '1';
        fseek(fp, 1, SEEK_CUR);
        
        e->peca = fgetc(fp) == 'X' ? VALOR_X : VALOR_O;
        fseek(fp, 1, SEEK_CUR);
        
        e->botLVL = fgetc(fp);
        fseek(fp, 1, SEEK_CUR);
        
        for (int l = 0; l < DIM; l++)
            for (int c = 0; c < DIM; c++)
            {
                ch = fgetc(fp);
                e->grelha[l][c] = ch == '-' ? VAZIA : ch == 'X' ? VALOR_X : ch == 'O' ? VALOR_O : ERROR;
                fseek(fp, 1, SEEK_CUR);
            }
        
        update(e);
        altPush(*e, s);
        *e = (*s)->e;
    }
    while (fgetc(fp) != EOF);
    
    fclose(fp);
    
    return 0;
}

/**
 * @brief 
 *
 * @param file
 * @param s
 */
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
        
        if (s->next)
            fputc('\n', fp);                        // prints a blank line in file to separate states
    }
    
    fclose(fp);                                     // closes file
}

/**
 * @brief 
 *
 * @param fp
 * @param s
 */
void saveFirstLine(FILE **fp, LEST s)
{
    fprintf(*fp, "%c ", s->e.modo == '0' ? 'M' : 'A');        // prints game mode in file
    fprintf(*fp, "%c ", s->e.peca == VALOR_X ? 'X' : 'O');    // prints playing piece in file
    fprintf(*fp, "%c\n", s->e.botLVL);                        // prints bot level in file
}
