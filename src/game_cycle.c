#include "reversi.h"

/**
 * @brief Loops game turns infinitely
 *
 * In each iterarion, the loop prints the game state and CLI and either starts a bot turn or a player turn to give a command.
 *
 * @param[in] e Starter state of the game
 * @param[in] s History stack
 *
 * @see printInterface
 * @see botTurn
 * @see playerTurn
 * @see errorHandling
 */
void gameCycle(ESTADO e, LState *s)
{
    int num;
    char cli[DIM][MAX_STR];

    for (int i = 0; i < DIM; i++)                             // iterates over CLI lines
        strcpy(cli[i], "\n");                                 // sets current CLI line to "\n" (blank)
    
    while (1)                                                 // loops infinitely. Every iteration curresponds to a command or a bot turn
    {
        printInterface(e, cli);                               // prints state and CLI
        e.showValid = e.showHelp = 0;                         // resets showValid and showHelp print modifiers to 0
        
        if (e.modo == '1' && e.peca == e.bot && e.nValids)    // checks if it's a bot turn
            num = botTurn(&e, s);                             // bot playes and returns error code
        else                                                  // else it is a player turn
            num = playerTurn(cli, &e, s);                     // lets player input command and returns error code

        if (num)                                              // if there's an error
            errorHandling(num, cli);                          // handles error code
    }
}

/**
 * @brief Bot's turn to play
 *
 * @param[in,out] e State beeing played
 * @param[in,out] s History stack
 *
 * @return Error codes
 *
 * @see bot1
 * @see bot2
 * @see bot3
 */
int botTurn(ESTADO *e, LState *s)
{
    fflush(stdout);               // flushes the output buffer before sleep() functions
    
    switch (e->botLVL)            // tests the bot level
    {
        case '1':                 // in case it is 1
            sleep(1);             // waits one second to give time to visualize player move
            return bot1(e, s);    // playes level 1 bot and returns error code
        case '2':                 // in case it is 2
            sleep(1);             // waits one second to give time to visualize player move
            return bot2(e, s);    // playes level 2 bot and returns error code
        case '3':                 // in case it is 3
            return bot3(e, s);    // playes level 3 bot and returns error code
        default:                  // by default
            return -1;            // returns undefined error code
    }
}

/**
 * @brief Player's turn to give command
 *
 * @param[out] cli[DIM][MAX_STR] CLI lines
 * @param[in,out] e State beeing played
 * @param[in,out] s History stack
 *
 * @return Error code
 *
 * @see updateCLI
 * @see interpreter
 */
int playerTurn(char cli[DIM][MAX_STR], ESTADO *e, LState *s)
{
    char input[INPUT];
    
    updateCLI(cli);                             // updates CLI
    
    if (!fgets(input, MAX_STR, stdin))          // recieves input command
        exit(0);                                // terminates program if there's an error getting input
    
    sprintf(cli[CLI], "reversi> %s", input);    // concatenates prompt with input
    
    return interpreter(e, s, input);            // interpretes command and checks if an error code is returne
}
