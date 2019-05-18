#include "estado.h"

/**
 * @brief 
 *
 * @param[in] e
 * @param[in] s
 */
void interpreter(ESTADO e, LEST s)
{
    int num;
    char cli[DIM][MAX_STR];

    for (int i = 0; i < DIM; i++)                              // iterates over CLI lines
        strcpy(cli[i], "\n");                                  // sets current CLI line to "\n" (blank)
    
    while (1)                                                  // loops infinitely. Every iteration curresponds to a command or a bot turn
    {
        printInterface(e, cli);                                // prints state and CLI
        e.showValid = e.showHelp = 0;                          // resets showValid and showHelp print modifiers to 0
        
        if (e.modo == '1' && e.peca == e.bot && e.nValidas)    // checks if it's a bot turn
            num = botTurn(&e, &s);                             // bot playes and returns error code
        else                                                   // else it is a player turn
            num = playerTurn(cli, &e, &s);                     // lets player input command and returns error code

        if (num)                                               // if there's an error
            errorHandling(num, cli);                           // handles error code
    }
}

/**
 * @brief Bot's turn to play
 *
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 */
int botTurn(ESTADO *e, LEST *s)
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
 * @param[out] cli[DIM][MAX_STR]
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 */
int playerTurn(char cli[DIM][MAX_STR], ESTADO *e, LEST *s)
{
    char input[INPUT];
    
    updateCLI(cli);                             // updates CLI
    
    if (!fgets(input, MAX_STR, stdin))          // recieves input command
        exit(0);                                // terminates program if there's an error getting input
    
    sprintf(cli[CLI], "reversi> %s", input);    // concatenates prompt with input
    
    return interpret(e, s, input);              // interpretes command and checks if an error code is returne
}

/**
 * @brief Interpretes player command
 *
 * @param[in,out] e
 * @param[int,out] s
 * @param[in] input
 *
 * @return 
 *
 * @see new
 * @see automatic
 * @see load
 * @see save
 * @see play
 * @see valid
 * @see help
 * @see undo
 * @see championship
 * @see quit
 */
int interpret(ESTADO *e, LEST *s, char *input)
{
    char *cmd[MAX_STR];
    int i;
    
    cmd[0] = strtok(input, " \n");             // saves command to first index of cmd array
    
    if (!cmd[0])                               // checks if there's a command
        return 0;                              // returns error code
    else if (strlen(cmd[0]) > 1)               // else checks if the command is more than one character long
        return 1;                              // returns error code
    
    for (i = 0; cmd[i]; i++)                   // iterates over cmd array
        cmd[i+1] = strtok(NULL, " \n");        // saves arguments to cmd array
    
    switch (cmd[0][0])                         // tests command
    {
        case 'n': case 'N':                    // in case it is [N]ew
            return new(i, cmd[1], e, s);       // validates command and returns error code
        case 'a': case 'A':                    // in case it is [A]utomatic
            return automatic(i, cmd, e, s);    // validates command and returns error code
        case 'l': case 'L':                    // in case it is [L]oad
            return load(i, cmd[1], e, s);      // validates command and returns error code
        case 'e': case 'E':                    // in case it is [E]ngrave
            return save(i, cmd[1], *e, s);     // validates command and returns error code
        case 'j': case 'J':                    // in case it is [J]est
            return play(i, cmd, e, s);         // validates command and returns error code
        case 's': case 'S':                    // in case it is [S]ave
            return valid(i, e);                // validates command and returns error code
        case 'h': case 'H':                    // in case it is [H]elp
            return help(i, e);                 // validates command and returns error code
        case 'u': case 'U':                    // in case it is [U]ndo
            return undo(i, e, s);              // validates command and returns error code
        case 'c': case 'C':                    // in case it is [C]hampionship
            return championship(i, cmd[1], e, s);    // validates command and returns error code
        case 'q': case 'Q':                    // in case it is [Q]uit
            return quit(i, s);                 // validates command and returns error code
        default:                               // by default
            return 1;                          // returns Invalid Command error code
    }
}

/**
 * @brief Validates [N]ew commnad
 *
 * @param[in] i
 * @param[in] cmd
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see start
 */
int new(int i, char *cmd, ESTADO *e, LEST *s)
{
    if (i < 2)                       // checks if there are too few arguments
        return 3;                    // returns error code
    if (i > 2)                       // checks if there are too many arguments
        return 4;                    // returns error code
    
    VALOR piece;
    
    if (!strcmp(cmd, "X"))           // checks if first argument is valid
        piece = VALOR_X;             // initializes piece to X (VALOR_X)
    else if (!strcmp(cmd, "O"))      // checks if second argument is valid
        piece = VALOR_O;             // initializes piece to O (VALOR_O)
    else                             // else (if first argument is invalid)
        return 5;                    // returns error code
    
    start('0', piece, ' ', e, s);    //

    return 0;                        // returns error code
}

/**
 * @brief Validates [A]utomatic commnad
 *
 * @param[in] i
 * @param[in] cmd[MAX_STR]
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see start
 */
int automatic(int i, char *cmd[MAX_STR], ESTADO *e, LEST *s)
{
    if (i < 3)                        // checks if there are too few arguments
        return 3;                     // returns error code
    if (i > 3)                        // checks if there are too many arguments
        return 4;                     // returns error code
    
    VALOR piece;
    
    if (!strcmp(cmd[1], "X"))         // checks if first argument is valid
        piece = VALOR_X;              // initializes piece to X (VALOR_X)
    else if (!strcmp(cmd[1], "O"))    // checks if first argument is valid
        piece = VALOR_O;              // initializes piece to O (VALOR_O)
    else                              // else (if first argument is invalid)
        return 5;                     // returns error code
    
    if (strlen(cmd[2]) > 1)           // checks if second argument is too long
        return 6;                     // returns error code
    if (!isdigit(cmd[2][0]))          // checks if second argument is a digit
        return 6;                     // returns error code
    
    char lvl = cmd[2][0];             // initializes lvl to second argument
    
    if (!(lvl - '0') || lvl > '3')    // checks if lvl is between 1 and 3 inclusive
        return 6;                     // returns error code
    
    start('1', piece, lvl, e, s);
    
    return 0;                         //
}

/**
 * @brief Validates [L]oad commnad
 *
 * @param[in] i
 * @param[in] cmd
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see readFile
 */
int load(int i, char *cmd, ESTADO *e, LEST *s)
{
    if (i < 2)                        // checks if there are too few arguments
        return 3;                     // returns error code
    if (i > 2)                        // checks if there are too many arguments
        return 4;                     // returns error code
    
    return readFile(cmd, 1, e, s);    //
}

/**
 * @brief Validates [E]ngrave commnad
 *
 * @param[in] i
 * @param[in] cmd
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see saveState
 */
int save(int i, char *cmd, ESTADO e, LEST *s)
{
    if (e.modo == HELP)    // checks if the game has started
        return 2;          // returns error code
    if (i < 2)             // checks if there are too few arguments
        return 3;          // returns error code
    if (i > 2)             // checks if there are too many arguments
        return 4;          // returns error code
    
    saveState(cmd, *s);    //
    
    return 0;              //
}

/**
 * @brief Validates [J]est commnad
 *
 * @param[in] i
 * @param[in] cmd[MAX_STR]
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see doPlay
 */
int play(int i, char *cmd[MAX_STR], ESTADO *e, LEST *s)
{
    if (e->modo == HELP)          // checks if the game has started
        return 2;                 // returns error code
    if (!e->nValidas)             // checks if the game has ended
        return 13;                // returns error code
    if (i < 3)                    // checks if there are too few arguments
        return 3;                 // returns error code
    if (i > 3)                    // checks if there are too many arguments
        return 4;                 // returns error code
    if (strlen(cmd[1]) > 1)       // checks if first argument is too long
        return 5;                 // returns error code
    if (strlen(cmd[2]) > 1)       // checks if second argument is too long
        return 6;                 // returns error code
    if (!isdigit(cmd[1][0]))      // checks if first argument isn't a digit
        return 5;                 // returns error code
    if (!isdigit(cmd[2][0]))      // checks if second argument isn't a digit
        return 6;                 // returns error code
    if (cmd[1][0] > '7')          // checks if fisrt argument is bigger than 7
        return 5;                 // returns error code
    if (cmd[1][1] > '7')          // checks if second argument is bigger than 7
        return 6;                 // returns error code
    
    POSICAO play;
    
    play.l = cmd[1][0] - '0';     // initializes l to the first argument
    play.c = cmd[2][0] - '0';     // initializes c to the second argument
    
    return doPlay(play, e, s);    //
}

/**
 * @brief Validates [S]how commnad
 *
 * @param[in] i
 * @param[in,out] e
 *
 * @return 
 */
int valid(int i, ESTADO *e)
{
    if (e->modo == HELP)    // checks if the game has started
        return 2;           // returns error code
    if (!e->nValidas)       // checks if the game has ended
        return 13;          // returns error code
    if (i > 1)              // checks if there are too many arguments
        return 4;           // returns error code
    
    e->showValid = 1;       //
    
    return 0;               //
}

/**
 * @brief Validates [H]elp commnad
 *
 * @param[in] i
 * @param[in,out] e
 *
 * @return 
 */
int help(int i, ESTADO *e)
{
    if (e->modo == HELP)    // checks if the game has started
        return 2;           // returns error code
    if (!e->nValidas)       // checks if the game has ended
        return 13;          // returns error code
    if (i > 1)              // checks if there are too many arguments
        return 4;           // returns error code
    
    e->showHelp = 1;        //
    
    return 0;               //
}

/**
 * @brief Validates [U]ndo commnad
 *
 * @param[in] i
 * @param[in,out] e
 * @param[in,out] s
 *
 * @return 
 *
 * @see popundo
 */
int undo(int i, ESTADO *e, LEST *s)
{
    if (e->modo == HELP)    // checks if the game has started
        return 2;           // returns error code
    if (!(*s)->next)        // 
        return -1;          // 
    if (!e->nValidas)       // checks if the game has ended
        return 13;          // returns error code
    if (i > 1)              // checks if there are too many arguments
        return 4;           // returns error code
    
    popundo(e, s);          //
    
    return 0;               //
}

/**
 * @brief Validates [C]hampionship commnad
 *
 * @param[in] i
 * @param[in] cmd
 *
 * @return 
 *
 * @see playBot
 */
int championship(int i, char *cmd, ESTADO *e, LEST *s)
{
    if (i < 1)              // checks if there are too few arguments
        return 3;           // returns error code
    if (i > 2)              // checks if there are too many arguments
        return 4;           // returns error code
    
    if (i == 1)
        cmd = NULL;
    
    return playChamp(cmd, e, s);
}

/**
 * @brief Validates [Q]uit commnad
 *
 * @param[in] i
 *
 * @return 
 */
int quit(int i, LEST *s)
{
    if (i > 1)       // checks if there are too many arguments
        return 4;    // returns error code
    
    freeStack(s);    //
    CLEAR;           //
    exit(0);         //
}

/**
 * @brief Handles erro codes
 *
 * @param num
 * @param cli[CLI][MAX_STR]
 *
 * @see updateCLI
 */
void errorHandling(int num, char cli[CLI][MAX_STR])
{
    updateCLI(cli);
    
    switch (num)
    {
        case 1:
            strcpy(cli[CLI], "reversi: Invalid Command\n");
            break;
        case 2:
            strcpy(cli[CLI], "reversi: Not in a Game Mode\n");
            break;
        case 3:
            strcpy(cli[CLI], "reversi: Too few arguments\n");
            break;
        case 4:
            strcpy(cli[CLI], "reversi: Too many arguments\n");
            break;
        case 5:
            strcpy(cli[CLI], "reversi: Invalid first argument\n");
            break;
        case 6:
            strcpy(cli[CLI], "reversi: Invalid second argument\n");
            break;
        case 7:
            strcpy(cli[CLI], "reversi: Invalid file name\n");
            break;
        case 8:
            strcpy(cli[CLI], "reversi: Invalid position\n");
            break;
        case 9:
            strcpy(cli[CLI], "reversi: State jumped\n");
            break;
        case 10:
            strcpy(cli[CLI], "reversi: Draw\n");
            break;
        case 11:
            strcpy(cli[CLI], "reversi: X Won\n");
            break;
        case 12:
            strcpy(cli[CLI], "reversi: O Won\n");
            break;
        case 13:
            strcpy(cli[CLI], "reversi: Game has ended\n");
            break;
        default:
            strcpy(cli[CLI], "reversi: error\n");
            break;
    }
}

/**
 * @brief Updates CLI
 *
 * @param cli[DIM][MAX_STR]
 */
void updateCLI(char cli[DIM][MAX_STR]/*, int n*/)
{
    //for (; n_times > 0; n_times--)     // iterates over n times
        for (int i = 0; i < CLI; i++)    // iterates over CLI lines                                   
            strcpy(cli[i], cli[i+1]);    // climbs CLI                                                
}
