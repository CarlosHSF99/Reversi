#include "estado.h"

void menu()
{
    char opt; // menu option
    ESTADO e = {0};
    char file_name[MAX_LENGTH];
    int l,c,over=0;

    e.peca = VALOR_O;

    CLEAR;

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
                remove("../saves/default.txt");
                break;
            case 'n': case 'N':
                //Caso queiramos escolher quem começa primeiro temos de fazer;
                newVsHuman(&e);
                break;
            case 'a': case 'A':
                //newVsBot();
            case 'l': case 'L':
                printf("Introduza o nome do ficheiro: ");
                scanf("%s", file_name);
                
                while(getchar() != '\n');
                
                readFile(&e, file_name, READ);
                
                break;
            case 'e': case 'E':
                printf("Introduza o nome do ficheiro: ");
                scanf("%s", file_name);
                
                while(getchar() != '\n');
                
                saveFile(&e, file_name);
                
                break;
            case 'j': case 'J':
                if (!over){
                    printg(e,0,0);
        
                    printf("Introduza as coordenadas (linha,coluna) : ");
                    scanf("(%d,%d)", &l, &c);
                
                    while(getchar() != '\n');
                
                    putchar('\n');
                    play(l, c, &e,&over);
                
                    break;
                }
                else
                    break;
            case 's': case 'S':
                if(!over){
                    something(&e);
                    break;
                }
                else
                    break;
            case 'h': case 'H':
                if(!over){
                    //help()
                    break;
                }
                else
                    break;
                break;
            case 'u': case 'U':
                undo(&e,file_name);
                break;
            default:
                printf("Invalid option!");
                break;
        }

        putchar('\n');
    }
    while (opt != 'Q');
}
