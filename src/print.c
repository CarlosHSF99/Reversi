#include "estado.h"

// Prints current state (mode, palyer, score, board and CLI)
void printInterface(ESTADO e, char cli[DIM][MAX_STR])
{
    CLEAR;                                      // clears screen
    
    printFirstLine(e);                          // prints first line (mode, score and CLI title)
    
    showValid(&e);                              // cheks if valid positions are to be shown and adds them to the board
    showHelp(&e);                               // cheks if "help" position is to be shown and adds it to the board
    
    for (int i = 0; i < DIM; i++)               // iterates over board lines
    {
        printf("%d ", i);                       // prints current line index
        
        for (int j = 0; j < DIM; j++)           // iterates over board columns
        {
            switch (e.grelha[i][j])             // tests current position
            {
                case VAZIA:                     // if it's VAZIA
                    printf("- ");               // prints "- "
                    break;
                case VALOR_X:                   // if it's VALOR_X
                    printf("X ");               // prints "X "
                    break;
                case VALOR_O:                   // if it's VALOR_O
                    printf("O ");               // prints "O"
                    break;
                case VALIDA:                    // if it's VALIDA
                    printf(". ");               // prints ". "
                    break;
                case HELP:                      // if it's HELP
                    printf("? ");               // prints "? "
                    break;
                default:                        // by default
                    printf("E ");               // prints "E" to detect erros
                    break;
            }
        }
        
        printf("┊ %s", cli[i]);                 // prints current CLI line
    }
    
    printf("  0 1 2 3 4 5 6 7 ┊ reversi> ");    // prints columns indexes and prompt line (last line)
}

// Prints first line
void printFirstLine (ESTADO e)
{
    printf("  ");                                                     // prints blanck spaces for alignment
    putchar(e.modo == HELP ? '?' : e.modo == '0' ? 'M' : 'A');        // prints current game mode
    putchar(' ');                                                     // prints blanck spaces for alignment
    putchar(e.peca == HELP ? '?' : e.peca == VALOR_X ? 'X' : 'O');    // prints piece of current player
    printf("   X:%02d O:%02d", e.scoreX, e.scoreO);                   // prints game score
    printf(" ┊ CLI\n");                                               // prints "CLI" title
}

// Cheks if valid positions are to be shown and adds them to the board
void showValid(ESTADO *e)
{
    POSICAO valida;
    
    if (e->showValid)                                  // checks if valid positions are to be shown
        for (int i = 0; i < e->nValidas; i++)          // iterates over valid positions
        {
            valida = e->validas[i].valida;             // sets valida to current valid position
            e->grelha[valida.l][valida.c] = VALIDA;    // changes current position do VALID (.)
        }
}

// Cheks if "help" position is to be shown and adds it to the board
void showHelp(ESTADO *e)
{
    if (e->showHelp)                               // checks if the "help" position is to be shown
        e->grelha[e->help.l][e->help.c] = HELP;    // changes "help" position to HELP (?)
}

    /*
    puts("");
    
    for (int i = 0; i < e.nValidas; i++)
    {
        printf("Valida: (%d , %d)\n", e.validas[i].valida.l, e.validas[i].valida.c);
        
        for (int j = 0; j < e.validas[i].nVirar; j++)
            printf("\t(%d , %d)\n", e.validas[i].virar[j].l, e.validas[i].virar->c);
        
        puts("");
    }
    */
