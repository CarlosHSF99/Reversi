#include "estado.h"

void menu()
{
    char opt; // menu option
    char file_name[MAX_LENGTH];
    ESTADO e = {'1', VALOR_X};
    int l,c;

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;

    system("clear");

    printg(e, 0, 0);
    putchar('\n');

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
                //newVsHuman();
                //Caso queiramos escolher quem começa primeiro...
                e.modo=0;
                printg(e,0,0);
                
                break;
            case 'A':
                //newVsBot();
            case 'L':
                printf("Introduza o nome do ficheiro: ");
                scanf("%s", file_name);
                
                while(getchar() != '\n');
                
                readFile(&e, file_name);
                
                break;
            case 'E':
                printf("Introduza o nome do ficheiro: ");
                scanf("%s", file_name);
                
                while(getchar() != '\n');
                
                writeFile(&e, file_name);
                
                break;
            case 'J':
                printf("Introduza as coordenadas (linha,coluna) : ");
                scanf("(%d,%d)", &l, &c);
                
                while(getchar() != '\n');
                
                putchar('\n');
                play(l, c, &e);
                
                break;
            case 'S':
                something(&e);
                break;
            case 'H':
                //help()
                break;
            case 'U':
                //undo();
                break;
            default:
                printf("Invalid option!");
                break;
        }

        putchar('\n');
    }
    while (opt != 'Q');
}
