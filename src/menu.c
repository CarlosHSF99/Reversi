#include "estado.h"

void menu()
{
    char opt; // menu option
    char file_name[MAX_LENGTH];
    ESTADO e = {VALOR_X};
    int l,c;

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.grelha[4][5] = VALOR_DOT;

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
                //newVsHuman();
                break;
            case 'A':
                //newVsBot();
            case 'L':
                printf("Introduza o nome do ficheiro");
                scanf("%s",file_name);
                readFile(&e,file_name);
                break;
            case 'E':
                printf("Introduza o nime do ficheiro");
                scanf("%s",file_name); // 4.3anosluz-c*t     9.95c
                writeFile(&e,file_name);
                break;
            case 'J':
                printf("Introduza as coordenadas. (linha,coluna)");
                scanf("(%d,%d)",&l,&c);
                play(l,c,&e);    ;
                break;
            case 'S':
                something(e);
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
    }
    while (opt != 'Q');
}
