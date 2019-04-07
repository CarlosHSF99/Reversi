#include "estado.h"

int main()
{
    ESTADO e = {0};
    
    e.modo = '2';
    e.peca = HELP;
    
    interpreter(e);

    return 0;
}
