#include "estado.h"

/**
 * @brief Prints current state (mode, palyer, score, board and CLI)
 *
 * @param[in] e State beeing printed
 * @param[in] cli[DIM][MAX_STR] CLI beeing printed
 *
 * @see printFirstLine
 * @see showValid
 * @see shoeHelp
 */
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

/**
 * @brief Prints first line
 *
 * @param[in] e State from where first line is beeing printed
 */
void printFirstLine (ESTADO e)
{
    printf("  %c ", e.modo == HELP ? '?' : e.modo == '0' ? 'M' : 'A');      // prints game mode
    printf("%c ", e.peca == HELP ? '?' : e.peca == VALOR_X ? 'X' : 'O');    // prints piece of current player
    printf("%c ", e.botLVL);                                                // prints bot level
    printf("X:%02d O:%02d", e.scoreX, e.scoreO);                            // prints game score
    printf(" ┊ CLI\n");                                                     // prints "CLI" title
}

/**
 * @brief Cheks if valid positions are to be shown and adds them to the board
 *
 * @param[in] e State from where valid positions might be printed
 */
void showValid(ESTADO *e)
{
    POSICAO valida;
    
    if (e->showValid)                                  // checks if valid positions are to be shown
        for (int i = 0; i < e->nValidas; i++)          // iterates over valid positions
        {
            valida = e->validas[i].valida;             // sets valida to current valid position
            e->grelha[valida.l][valida.c] = VALIDA;    // changes current position do VALID (.)
        }
    
    e->showValid = 0;                                  // resets showValid print modifier to 0
}

/**
 * @brief Cheks if "help" position is to be shown and adds it to the board
 *
 * @param[in] e State from where help position might be printed
 */
void showHelp(ESTADO *e)
{
    if (e->showHelp)                               // checks if the "help" position is to be shown
        e->grelha[e->help.l][e->help.c] = HELP;    // changes "help" position to HELP (?)
    
    e->showHelp = 0;                               // resets showHelp print modifier to 0
}
