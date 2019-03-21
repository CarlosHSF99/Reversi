#include "estado.h"

void menu()
{
    char opt; // menu option
    char file_name[MAX_LENGTH];
    ESTADO e = {VALOR_X};

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.grelha[4][5] = (int) '.';

    system("clear");

    printg(e);

    do
    {
        // prints the menu options
        printf("[N]ovo [L]er [E]screver [J]ogar [S]omething [H]elp [U]ndo [A]utomatico [Q]uit\n");
        
        // prints prompt
        printf("\n: ");
        
        // prompts for menu option
        opt = getchar();
        
        // cleans buffer
        while (getchar() != '\n');

        system("clear");        

        switch (opt)
        {
            case 'Q':
                break;
            case 'N':
                
                break;
            case 'L':
                printf("Introduza o nome do ficheiro");
                scanf("%s",file_name);
                readFile(e,file_name);
                break;
            case 'E':
                
                break;
            case 'J':
                
                break;
            case 'S':
                something(e);
                break;
            case 'H':
                
                break;
            case 'U':
                
                break;
            case 'A':
                
                break;
            default:
                printf("Invalid option!");
                break;
        }
    }
    while (opt != 'Q');
}
