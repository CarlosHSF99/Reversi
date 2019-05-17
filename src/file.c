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

    while(fgetc(file)!=EOF)
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

void saveState(char* file_name, LEST s)
{
    FILE *file;
    int l, c;
    char file_pos_name[MAX_STR];
    
    sprintf(file_pos_name, "../saves/%s.txt", file_name);
    
    file = fopen(file_pos_name, "w");
    
    while(s!=NULL){
        fprintf(file, "%c %c %c\n", s->e.modo == '0' ? 'M' : s->e.modo == '1' ? 'A' : '?', s->e.peca == VALOR_X ? 'X' : s->e.peca == VALOR_O ? 'O' : '?', s->e.modo== 'A' ? s->e.botLVL : ' ');
        
        for(l = 0; l < DIM; l++)
            for(c = 0; c < DIM; c++)
            {
                switch(s->e.grelha[l][c])
                {
                    case VALOR_O:
                        fputc('O', file);
                        break;
                    case VALOR_X:
                        fputc('X', file);
                        break;
                    case VAZIA:
                        fputc('-', file);
                        break;
                    default:
                        fputc('E', file);
                        break;
                }
                
                fputc(c < DIM-1 ? ' ' : '\n', file);
            }
        
        fputc('\n', file);
        
        s = s->next;
    }
    fclose(file);
}

