#include "estado.h"

void menu()
{
    char opt; // menu option
    ESTADO e = {0};
    char file_name[MAX_LENGTH];
    int l, c;
    VALOR n;

    CLEAR;

    do
    {
        // prints the menu options
        printf("[N]ovo [L]er [E]screver [J]ogar [S]how [H]elp [U]ndo [A]utomatico [Q]uit\n");
        
        // prints prompt
        printf("\n: ");
        
        // prompts for menu option
        opt = getchar();
        
        if (opt == 'j' || opt == 'J')
            scanf(" %d %d", &l, &c);
        else if (opt == 'n' || opt == 'N')
        {
            getchar();
            n = getchar() == 'X' ? VALOR_X : VALOR_O;
        }
        else if (opt == 'a' || 'A')
        {
            getchar();
            n = getchar() == 'X' ? VALOR_X : VALOR_O;
        }
        else if (opt == 'l' || opt == 'L')
            scanf(" %s", &file_name);
        else if (opt == 'e' || opt == 'E')
            scanf(" %s", &file_name);
        
        // cleans buffer
        while (getchar() != '\n');
        
        CLEAR;
        
        switch (opt)
        {
            case 'q': case 'Q':
                remove("../saves/.default.txt");
                break;
            case 'n': case 'N':
                newVsHuman(&e, n);
                break;
            case 'a': case 'A':
                newVsBot(&e, n);
                break;
            case 'l': case 'L':
                readFile(&e, file_name, READ);
                break;
            case 'e': case 'E':
                saveFile(&e, file_name);
                break;
            case 'j': case 'J':
                play(l, c, &e);
                break;
            case 's': case 'S':
                printg(e, 1, 0);
                break;
            case 'h': case 'H':
                break;
            case 'u': case 'U':
                undo(&e);
                break;
            default:
                printf("Invalid option!");
                break;
        }
        
        if (opt != 'q' && opt != 'Q' && opt != 'e' && opt != 'E') 
            putchar('\n');
    }
    while (opt != 'Q' && opt != 'q');
}
