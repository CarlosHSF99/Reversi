#include "estado.h"

/**
 * @brief Prints current state (mode, palyer, score, board) and CLI
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
    
    printFirstLine(e);
    
    showValid(&e);
    showHelp(&e);
    
    for (int i = 0; i < DIM; i++)               // iterates over board lines
    {
        printf("%d ", i);                       // prints current line index
        
        for (int j = 0; j < DIM; j++)           // iterates over board columns
        {
            switch (e.grelha[i][j])             // tests current position
            {
                case VAZIA:
                    printf("- ");
                    break;
                case VALOR_X:
                    printf("X ");
                    break;
                case VALOR_O:
                    printf("O ");
                    break;
                case VALIDA:
                    printf(". ");
                    break;
                case HELP:
                    printf("? ");
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
 * @brief Prints first lin
 *
 * Prints the mode, playing piece, bot level, game score and CLI title
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
    POSITION valid;
    
    if (e->showValid)                                // checks if valid positions are to be shown
        for (int i = 0; i < e->nValids; i++)         // iterates over valid positions
        {
            valid = e->valids[i].valid;              // sets valida to current valid position
            e->grelha[valid.l][valid.c] = VALIDA;    // changes current position do VALID (.)
        }
}

/**
 * @brief Cheks if the help position is to be shown and adds it to the board
 *
 * @param[in] e State from where the help position might be printed
 */
void showHelp(ESTADO *e)
{
    if (e->showHelp)                               // checks if the help position is to be shown
        e->grelha[e->help.l][e->help.c] = HELP;    // changes help position to HELP (?)
}
