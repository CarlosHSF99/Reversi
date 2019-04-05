#include "estado.h"

void free_estado(ESTADO e)
{
    while (e)
    {
        ESTADO tmp = e->next;
        free(e);
        e = tmp;
    }
}
