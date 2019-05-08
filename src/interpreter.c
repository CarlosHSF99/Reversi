#include "estado.h"

// Interpretes
void interpreter(ESTADO e, LEST* s)
{
    int num;
    char error;
    char cli[DIM][MAX_STR];
    char input[INPUT];

    for (int i = 0; i < DIM; i++)                       //
        strcpy(cli[i], "\n");                           //
    
    while (1)
    {
        printg(e, cli);                                 //
        e.showValid = e.showHelp = 0;                   //
        
        if (!fgets(input, MAX_STR, stdin))              //
            exit(0);                                    //
        
        updateCLI(cli);                                 //
        
        sprintf(cli[CLI], "reversi> %s", input);        //
        
        if ((num = interpret(&e, s, input, &error)))    // parenteses a mais sugeridos pelo -Wall ... parece estupido
            errorHandling(num, error, cli);
    }
}

void errorHandling(int num, char error, char cli[CLI][MAX_STR])
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

// Actually interpretes
int interpret(ESTADO *e, LEST *s, char *input, char *error)
{
    char *cmd[MAX_STR];                    //
    int l, c;                              //
    int i;                                 //
    VALOR value;                           //
    
    cmd[0] = strtok(input, " \n");         //
    
    if (!cmd[0])                           //
        return 0;                          //
    else if (strlen(cmd[0]) > 1)
        return 1;
    
    for (i = 0; cmd[i]; i++)               //
        cmd[i+1] = strtok(NULL, " \n");    //
    
    switch (cmd[0][0])                     //
    {
        case 'n': case 'N':                   //
        {
            if (i < 2)                        //
            {
                *error = 'N';
                return -1;
            }
            else if (i > 2)                   //
            {
                *error = 'N';
                return 1;
            }
            
            if (!strcmp(cmd[1], "X"))         //
                value = VALOR_X;              //
            else if (!strcmp(cmd[1], "O"))    //
                value = VALOR_O;              //
            else
                return 1;                     //
            
            manual(e, value, s);              //
            
            break;
        }
        case 'a': case 'A':                   //
        {
            if (i < 2)                        //
                return 1;                     //
            else if (i > 2)                   //
                return 1;                     //
            
            if (!strcmp(cmd[1], "X"))         //
                value = VALOR_X;              //
            else if (!strcmp(cmd[1], "O"))    //
                value = VALOR_O;              //
            else
                return 1;                     //
            
            automatic(e, value, s);           //
            
            break;
        }
        case 'l': case 'L':               //
        {
            if (i < 2)                    //
                return 1;                 //
            else if (i > 2)               //
                return 1;                 //
            
            readFile(e, cmd[1], READ);    //
            
            break;
        }
        case 'e': case 'E':             //
        {
            if (i < 2)                  //
                return 1;               //
            else if (i > 2)             //
                return 1;               //
            
            saveFile(e, cmd[1], *s);    //
            
            break;
        }
        case 'j': case 'J':                                    //
        {
            if (i < 3)                                         //
                return 1;                                      //
            else if (i > 3)                                    //
                return 1;                                      //
            
            if (!isdigit(cmd[1][0]) || !isdigit(cmd[2][0]))    //
                return 1;                                      //
            
            l = cmd[1][0] - '0';                               //
            c = cmd[2][0] - '0';                               //
            
            if (!play(l, c, e))
            {
                push(*e, s);
                return 0;
            }
            
            /*
            if (e->modo == '0')                                //
                return (play(l, c, e, s, cli));                //
            else if (e->peca == value)                         //
                return (play(l, c, e, s, cli));                //
            else
                miniMax(e, 0, 2, s);                           //
            */
            
            return isGameOver(*e);                             //
            
            break;                                             //
        }
        case 's': case 'S':      //
        {
            if (i > 1)           //
                return 1;        //
            
            e->showValid = 1;    //
            
            break;               //
        }
        case 'h': case 'H':         //
        {
            if (i > 1)              //
                return 1;           //
            
            if (e->modo == HELP)    //
                return 1;           //
            
            e->showHelp = 1;        //
            
            break;                  //
        }
        case 'u': case 'U':    //
        {
            if (i > 1)         //
                return 1;      //
            
            undo(e,s);         //
            
            break;             //
        }
        case 'q': case 'Q':    //
        {
            if (i > 1)         //
                return 1;      //
            
            CLEAR;             //
            exit(0);           //
            
            break;             //
        }
        default:         //
        {
            return 1;    //
        }
    }

    return 0;
}

// 
void updateCLI(char cli[DIM][MAX_STR]/*, int n*/)
{
    //for (; n_times > 0; n_times--)         // iterates over n times
        for (int i = 0; i < CLI; i++)        // iterates over CLI lines                                   
            strcpy(cli[i], cli[i+1]);        // climbs CLI                                                
}
