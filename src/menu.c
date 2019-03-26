#include "estado.h"

void menu()
{
    char opt; // menu option
    ESTADO e = {0};
    char file_name[MAX_LENGTH];
    int l,c;

    CLEAR;

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
        
        CLEAR;

        switch (opt)
        {
            case 'q': case 'Q':
                break;
            case 'n': case 'N':
                //Caso queiramos escolher quem começa primeiro temos de fazer;

                newVsHuman(e);
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
                
                
                if (e.peca == VALOR_X && e.modo == '0')
                    e.peca=VALOR_O;
                else e.peca=VALOR_X;

                printg(e,0,0);
                
                printf("Introduza as coordenadas (linha,coluna) : ");
                scanf("(%d,%d)", &l, &c);
                
                while(getchar() != '\n');
                
                putchar('\n');
                play(l, c, &e);
                
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
