#include "reversi.h"

/**
 * @brief Interprets player command
 *
 * @param[in,out] e State beeing played
 * @param[int,out] s History stack
 * @param[in] input Player's input
 *
 * @return Erro code
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
int interpreter(ESTADO *e, LState *s, char *input)
{
    char *cmd[MAX_STR];
    int i;
    
    cmd[0] = strtok(input, " \n");              // saves command to first index of cmd array
    
    if (!cmd[0])                                // checks if there's a command
        return 0;                               // returns error code
    else if (strlen(cmd[0]) > 1)                // else checks if the command is more than one character long
        return 1;                               // returns error code
    
    for (i = 0; cmd[i]; i++)                    // iterates over cmd array
        cmd[i+1] = strtok(NULL, " \n");         // saves arguments to cmd array
    
    switch (cmd[0][0])                          // tests command
    {
        case 'n': case 'N':                     // in case it is [N]ew
            return newMode(i, cmd[1], e, s);    // validates command and returns error code
        case 'a': case 'A':                     // in case it is [A]utomatic
            return autoMode(i, cmd, e, s);      // validates command and returns error code
        case 'l': case 'L':                     // in case it is [L]oad
            return load(i, cmd[1], e, s);       // validates command and returns error code
        case 'e': case 'E':                     // in case it is [E]ngrave
            return save(i, cmd[1], *e, s);      // validates command and returns error code
        case 'j': case 'J':                     // in case it is [J]est
            return play(i, cmd, e, s);          // validates command and returns error code
        case 's': case 'S':                     // in case it is [S]ave
            return valid(i, e);                 // validates command and returns error code
        case 'h': case 'H':                     // in case it is [H]elp
            return help(i, e);                  // validates command and returns error code
        case 'u': case 'U':                     // in case it is [U]ndo
            return undo(i, e, s);               // validates command and returns error code
        case 'c': case 'C':                     // in case it is [C]hampionship
            return championship(i, cmd[1], e, s);    // validates command and returns error code
        case 'q': case 'Q':                     // in case it is [Q]uit
            return quit(i, s);                  // validates command and returns error code
        default:                                // by default
            return 1;                           // returns Invalid Command error code
    }
}

/**
 * @brief Validates [N]ew command
 *
 * @param[in] i Number of command arguments plus the command itself
 * @param[in] cmd Command beeing validated
 * @param[in,out] e State being played
 * @param[in,out] s Hostory stack
 *
 * @return Error code
 *
 * @see start
 */
int newMode(int nCmd, char *cmd, ESTADO *e, LState *s)
{
    if (nCmd < 2)                    // checks if there are too few arguments
        return 3;                    // returns error code
    if (nCmd > 2)                    // checks if there are too many arguments
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
 * @brief Validates [A]utomatic command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in] cmd[MAX_STR] Command beeing validated
 * @param[in,out] e State being played
 * @param[in,out] s Hostory stack
 *
 * @return Error code
 *
 * @see start
 */
int autoMode(int nCmd, char *cmd[MAX_STR], ESTADO *e, LState *s)
{
    if (nCmd < 3)                     // checks if there are too few arguments
        return 3;                     // returns error code
    if (nCmd > 3)                     // checks if there are too many arguments
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
 * @brief Validates [L]oad command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in] cmd Command beeing validated
 * @param[in,out] e State being played
 * @param[in,out] s Hostory stack
 *
 * @return Error code
 *
 * @see readFile
 */
int load(int nCmd, char *cmd, ESTADO *e, LState *s)
{
    if (nCmd < 2)                  // checks if there are too few arguments
        return 3;                  // returns error code
    if (nCmd > 2)                  // checks if there are too many arguments
        return 4;                  // returns error code
    
    return readFile(cmd, e, s);    //
}

/**
 * @brief Validates [E]ngrave command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in] cmd Command beeing validated
 * @param[in,out] e State being played
 * @param[in,out] s Hostory stack
 *
 * @return Error code
 *
 * @see saveState
 */
int save(int nCmd, char *cmd, ESTADO e, LState *s)
{
    if (e.modo == HELP)       // checks if the game has started
        return 2;             // returns error code
    if (nCmd < 2)             // checks if there are too few arguments
        return 3;             // returns error code
    if (nCmd > 2)             // checks if there are too many arguments
        return 4;             // returns error code
    
    writeFile(0, cmd, *s);    //
    
    return 0;                 //
}

/**
 * @brief Validates [J]est command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in] cmd[MAX_STR] Command beeing validated
 * @param[in,out] e State being played
 * @param[in,out] s Hostory stack
 *
 * @return Error code
 *
 * @see doPlay
 */
int play(int nCmd, char *cmd[MAX_STR], ESTADO *e, LState *s)
{
    if (e->modo == HELP)          // checks if the game has started
        return 2;                 // returns error code
    if (!e->nValids)              // checks if the game has ended
        return 13;                // returns error code
    if (nCmd < 3)                 // checks if there are too few arguments
        return 3;                 // returns error code
    if (nCmd > 3)                 // checks if there are too many arguments
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
    
    POSITION play;
    
    play.l = cmd[1][0] - '0';     // initializes l to the first argument
    play.c = cmd[2][0] - '0';     // initializes c to the second argument
    
    return doPlay(play, e, s);    //
}

/**
 * @brief Validates [S]how command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in,out] e State being played
 *
 * @return Error code
 */
int valid(int nCmd, ESTADO *e)
{
    if (e->modo == HELP)    // checks if the game has started
        return 2;           // returns error code
    if (!e->nValids)        // checks if the game has ended
        return 13;          // returns error code
    if (nCmd > 1)           // checks if there are too many arguments
        return 4;           // returns error code
    
    e->showValid = 1;       //
    
    return 0;               //
}

/**
 * @brief Validates [H]elp command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in,out] e State being played
 *
 * @return Error code
 */
int help(int nCmd, ESTADO *e)
{
    if (e->modo == HELP)    // checks if the game has started
        return 2;           // returns error code
    if (!e->nValids)        // checks if the game has ended
        return 13;          // returns error code
    if (nCmd > 1)           // checks if there are too many arguments
        return 4;           // returns error code
    
    e->showHelp = 1;        //
    
    return 0;               //
}

/**
 * @brief Validates [U]ndo command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 * @param[in,out] e State being played
 * @param[in,out] s Hostory stack
 *
 * @return Error code
 *
 * @see popundo
 */
int undo(int nCmd, ESTADO *e, LState *s)
{
    if (e->modo == HELP)    // checks if the game has started
        return 2;           // returns error code
    if (!(*s)->next)        // 
        return -1;          // 
    if (!e->nValids)        // checks if the game has ended
        return 13;          // returns error code
    if (nCmd > 1)           // checks if there are too many arguments
        return 4;           // returns error code
    
    popUndo(e, s);          //
    
    return 0;               //
}

/**
 * @brief Validates [C]hampionship command
 *
 * @param nCmd Number of command arguments plus the command itself
 * @param cmd Command beeing validated
 * @param e Gaem state
 * @param s History Stack
 *
 * @return Error code
 */
int championship(int nCmd, char *cmd, ESTADO *e, LState *s)
{
    if (nCmd < 1)      // checks if there are too few arguments
        return 3;      // returns error code
    if (nCmd > 2)      // checks if there are too many arguments
        return 4;      // returns error code
    
    if (nCmd == 1)
        cmd = NULL;
    
    return playChamp(cmd, e, s);
}

/**
 * @brief Validates [Q]uit command
 *
 * @param[in] nCmd Number of command arguments plus the command itself
 *
 * @return Error code
 */
int quit(int nCmd, LState *s)
{
    if (nCmd > 1)    // checks if there are too many arguments
        return 4;    // returns error code
    
    freeStack(s);    //
    CLEAR;           //
    exit(0);         //
}

/**
 * @brief Handles erro codes
 *
 * @param error Error code
 * @param cli[CLI][MAX_STR] CLI where error message will be displayed
 *
 * @see updateCLI
 */
void errorHandling(int error, char cli[CLI][MAX_STR])
{
    updateCLI(cli);
    
    switch (error)
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
        case -7:
            strcpy(cli[CLI], "reversi: Championship file created\n");
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
