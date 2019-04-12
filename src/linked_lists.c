#include "estado.h"

void freeEstado(LEst e)
{
    LEst new = NULL;
    
    while (e)
    {
        new = e->next;
        free(e);
        e = new;
    }
}
/*
void push(LEst e, ESTADO new_e)
{
    LEst new_estado;
    new_estado = calloc(1, sizeof(ESTADO));
    
    new_estado->new_e = new_e;
    new_estado->next = e;
    e = new_node;
}

ESTADO pop(LEst *e)
{
    
}
*/
