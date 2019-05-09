#include "estado.h"

int main()   //MUDAR AS FUNÇOES DO INTERPRET PARA RECEBEREM TRIPEL POINTER; 
{
    LEST* ss=NULL;
    LEST s = calloc(1,sizeof(struct history));
    ESTADO e={0};

    if (!s)
        exit(0);
    
    e.modo = HELP;
    e.peca = HELP;
    
    e.NX = 2;
    e.NO = 2;
    
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    
    s->e=e;
    s->next=NULL;

    interpreter(e,s);
    
    ss=&s;
    freeStack(ss);
    
    return 0;
}
