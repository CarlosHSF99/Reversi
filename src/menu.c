#include "estado.h"

void menu()
{
    char opt; // menu option
    ESTADO e = {'1', VALOR_X};
    char file_name[MAX_LENGTH];
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
            case 'q': case 'Q':
                break;
            case 'n': case 'N':
                //newVsHuman();
                //Caso queiramos escolher quem começa primeiro...
                e.modo=0;
                printg(e,0,0);
                
                break;
            case 'a': case 'A':
                //newVsBot();
            case 'l': case 'L':
                printf("Introduza o nome do ficheiro: ");
                scanf("%s", file_name);
                
                while(getchar() != '\n');
                
                readFile(&e, file_name);
                
                break;
            case 'e': case 'E':
                printf("Introduza o nome do ficheiro: ");
                scanf("%s", file_name);
                
                while(getchar() != '\n');
                
                writeFile(&e, file_name);
                
                break;
            case 'j': case 'J':
                printf("Introduza as coordenadas (linha,coluna) : ");
                scanf("(%d,%d)", &l, &c);
                
                while(getchar() != '\n');
                
                putchar('\n');
                play(l, c, &e, file_name);
                
                break;
            case 's': case 'S':
                something(&e);
                break;
            case 'h': case 'H':
                //help()
                break;
            case 'u': case 'U':
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
