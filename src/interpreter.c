#include "estado.h"

// Interpretes
void interpreter(ESTADO e, LEST s)
{
    int num = 0;
    char input[INPUT], cli[DIM][MAX_STR];

    for (int i = 0; i < DIM; i++)                   // iterates over CLI lines
        strcpy(cli[i], "\n");                       // sets current CLI line to "\n" (blank)
    
    while (1)                                       // loops infinitely
    {
        printInterface(e, cli);                     // prints state and CLI
        e.showValid = e.showHelp = 0;               // resets showValid and showHelp print modifiers to 0
        
        if (e.modo == '1' && e.peca == e.botPiece && e.nValidas)
        {
            fflush(stdout);
            sleep(1);
            
            switch (e.botLVL)
            {
                case '1':
                    num = bot1(&e, &s);
                    break;
                case '2':
                    num = bot2(&e, &s);
                    break;
                case '3':
                    num = bot3(&e, &s);
                    break;
                
                if (num)
                    errorHandling(num, cli);
            }
        }
        else
        {
            updateCLI(cli);                             // updates CLI
            
            if (!fgets(input, MAX_STR, stdin))          // recieves input command
                exit(0);                                // terminates program if there's an error getting input
            
            sprintf(cli[CLI], "reversi> %s", input);    // concatenates prompt with input
            
            if ((num = interpret(&e, &s, input)))       // interpretes command and checks if an error code is returne
                errorHandling(num, cli);                // handles error codes
        }
    }
}

// Actually interpretes
int interpret(ESTADO *e, LEST *s, char *input)
{
    char *cmd[MAX_STR];                        //
    int i;                                     //
    
    cmd[0] = strtok(input, " \n");             //
    
    if (!cmd[0])                               //
        return 0;                              //
    else if (strlen(cmd[0]) > 1)               //
        return 1;                              //
    
    for (i = 0; cmd[i]; i++)                   //
        cmd[i+1] = strtok(NULL, " \n");        //
    
    switch (cmd[0][0])                         //
    {
        case 'n': case 'N':                    //
            return new(i, cmd[1], e, s);       //
        case 'a': case 'A':                    //
            return automatic(i, cmd, e, s);    //
        case 'l': case 'L':                    //
            return load(i, cmd[1], e, s);      //
        case 'e': case 'E':                    //
            return save(i, cmd[1], e, s);      //
        case 'j': case 'J':                    //
            return play(i, cmd, e, s);         //
        case 's': case 'S':                    //
            return valid(i, e);                //
        case 'h': case 'H':                    //
            return help(i, e);                 //
        case 'u': case 'U':                    //
            return undo(i, e, s);              //
        case 'c': case 'C':                    //
            return championship(i, cmd[1]);    //
        case 'q': case 'Q':                    //
            return quit(i);                    //
        default:                               //
            return 1;                          //
    }
}

//
int new(int i, char *cmd, ESTADO *e, LEST *s)
{
    VALOR value;
    
    if (i < 2)                     //
        return -1;                 //
    if (i > 2)                     //
        return 1;                  //
    
    if (!strcmp(cmd, "X"))         //
        value = VALOR_X;           //
    else if (!strcmp(cmd, "O"))    //
        value = VALOR_O;           //
    else                           //
        return 1;                  //
    
    manual(e, value, s);           //

    return 0;                      //
}

//
int automatic(int i, char *cmd[MAX_STR], ESTADO *e, LEST *s)
{
    if (i < 3)                        //
        return 1;                     //
    if (i > 3)                        //
        return 1;                     //
    
    VALOR piece;
    
    if (!strcmp(cmd[1], "X"))         //
        piece = VALOR_X;              //
    else if (!strcmp(cmd[1], "O"))    //
        piece = VALOR_O;              //
    else                              //
        return 1;                     //
    
    if (strlen(cmd[2]) > 1)           //
        return 1;                     //
    if (!isdigit(cmd[2][0]))          //
        return 1;                     //
    
    char lvl = cmd[2][0];             //
    
    if (!(lvl - '0') || lvl > '3')    //
        return 1;                     //
    
    autoVSbot(piece, lvl, e, s);      //
    
    return 0;                         //
}

//
int load(int i, char *cmd, ESTADO *e, LEST *s)
{
    if (i < 2)                     //
        return 1;                  //
    if (i > 2)                     //
        return 1;                  //
    
    return readFile(e, cmd, s);    //
}

//
int save(int i, char *cmd, ESTADO *e, LEST *s)
{
    if (e->modo == HELP)      //
        return 1;             //
    if (i < 2)                //
        return 1;             //
    if (i > 2)                //
        return 1;             //
    
    saveState(e, cmd, *s);    //
    
    return 0;                 //
}

//
int play(int i, char *cmd[MAX_STR], ESTADO *e, LEST *s)
{
    if (e->modo == HELP)                               //
        return 1;                                      //
    if (i < 3)                                         //
        return 1;                                      //
    if (i > 3)                                         //
        return 1;                                      //
    if (strlen(cmd[1]) > 1 || strlen(cmd[2]) > 1)      //
        return 1;                                      //
    if (!isdigit(cmd[1][0]) || !isdigit(cmd[2][0]))    //
        return 1;                                      //
    if (cmd[1][0] > '7' || cmd[1][1] > '7')            //
        return 1;                                      //
    
    int l = cmd[1][0] - '0';                           //
    int c = cmd[2][0] - '0';                           //
    
    return doPlay(l, c, e, s);
    /*
    int num;
    
    if ((num = reverse(l, c, e)) <= 1)                 //
        push(*e, s);                                   //
    
    return num;
    */
}

//
int valid(int i, ESTADO *e)
{
    if (e->modo == HELP)    //
        return 1;           //
    if (i > 1)              //
        return 1;           //
    
    e->showValid = 1;       //
    
    return 0;               //
}

//
int help(int i, ESTADO *e)
{
    if (e->modo == HELP)    //
        return 1;           //
    if (i > 1)              //
        return 1;           //
    
    e->showHelp = 1;        //
    
    return 0;               //
}

//
int undo(int i, ESTADO *e, LEST *s)
{
    if (e->modo == HELP)    //
        return 1;           //
    if (i > 1)              //
        return 1;           //
    
    popundo(e, s);          //
    
    return 0;               //
}

//
int quit(int i)
{
    if (i > 1)       //
        return 1;    //
    
    CLEAR;           //
    exit(0);         //
}

//
int championship(int i, char *cmd)
{
    if (i < 2)              //
        return 1;           //
    if (i > 2)              //
        return 1;           //
    
    return playBot(cmd);    //
}

//
void errorHandling(int num, char cli[CLI][MAX_STR])
{
    updateCLI(cli);
    strcpy(cli[CLI], "reversi: error\n");
    /*
    if (num * num == 1)
    {
        sprintf(cli[CLI], "%s: Too %s arguments\n", error == 'N' ? "New" : "" , num > 0 ? "many" : "few");
        updateCLI(cli);
        
        switch(error)
        {
            case 'N':
                strcpy(cli[CLI], "New: N <piece>\n");
                break;
        }
    }
    */
}

// 
void updateCLI(char cli[DIM][MAX_STR]/*, int n*/)
{
    //for (; n_times > 0; n_times--)     // iterates over n times
        for (int i = 0; i < CLI; i++)    // iterates over CLI lines                                   
            strcpy(cli[i], cli[i+1]);    // climbs CLI                                                
}
