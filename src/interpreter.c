#include "estado.h"

// Interpretes
void interpreter(ESTADO e,LEST* s)
{
    char lines[DIM][MAX_STR];
    char line[MAX_STR];

    for (int i = 0; i < DIM; i++)               //
        strcpy(lines[i], "\n");                 //
    
    while (1)
    {
        printg(e, lines);                       //
        e.showValid = e.showHelp = 0;           //
        
        if (!fgets(line, MAX_STR, stdin))       //
            exit(0);                            //
        
        updateLines(lines);                     //

        sprintf(lines[7], "reversi> %s", line); //
        
        interpret(&e, line, s, lines);          //
    }
}

// 
void updateLines(char lines[DIM][MAX_STR])
{                                                                                                    
    for (int i = 0; i < 7; i++)         // iterates over CLI lines                                   
        strcpy(lines[i], lines[i+1]);   // climbs CLI                                                
} 

//
int interpret(ESTADO *e, char *line, LEST *s, char lines[DIM][MAX_STR])
{
    char *cmd[MAX_STR];                 //
    int l, c;                           //
    int i;                              //
    VALOR value;                        //
    
    cmd[0] = strtok(line, " \n");       //
    
    if (!cmd[0] || strlen(cmd[0]) > 1)  //
        return -1;                      //
    
    for (i = 0; cmd[i]; i++)            //
        cmd[i+1] = strtok(NULL, " \n"); //
    
    switch (cmd[0][0])                  //
    {
        case 'n': case 'N':                 //
        {
            if (i < 2)                      //
                return -1;                  //
            else if (i > 2)                 //
                return 1;                   //
            
            if (!strcmp(cmd[1], "X"))       //
                value = VALOR_X;            //
            else if (!strcmp(cmd[1], "O"))  //
                value = VALOR_O;            //
            else
                return -1;                  //
            
            manual(e, value, s);            //
            
            break;
        }
        case 'a': case 'A':                 //
        {
            if (i < 2)                      //
                return -1;                  //
            else if (i > 2)                 //
                return 1;                   //
            
            if (!strcmp(cmd[1], "X"))       //
                value = VALOR_X;            //
            else if (!strcmp(cmd[1], "O"))  //
                value = VALOR_O;            //
            else
                return -1;                  //
            
            automatic(e, value, s);         //
            
            break;
        }
        case 'l': case 'L':             //
        {
            if (i < 2)                  //
                return -1;              //
            else if (i > 2)             //
                return 1;               //
            
            readFile(e, cmd[1], READ);  //
            
            break;
        }
        case 'e': case 'E':             //
        {
            if (i < 2)                  //
                return -1;              //
            else if (i > 2)             //
                return 1;               //
            
            saveFile(e, cmd[1], *s);    //
            
            break;
        }
        case 'j': case 'J':                                 //
        {
            if (i < 3)                                      //
                return -1;                                  //
            else if (i > 3)                                 //
                return 1;                                   //
            
            if (!isdigit(cmd[1][0]) || !isdigit(cmd[2][0])) //
                return 2;                                   //
            
            l = cmd[1][0] - '0';                            //
            c = cmd[2][0] - '0';                            //
            
            if (e->modo == '0')                             //
                play(l, c, e, s, lines);                    //
            else if (e->peca == value)                      //
                play(l, c, e, s, lines);                    //
            else
                miniMax(e, 0, 2, s);                        //
            
            isGameOver(*e, lines);
            
            break;                                          //
        }
        case 's': case 'S':     //
        {
            if (i > 1)          //
                return 1;       //
            
            e->showValid = 1;   //
            
            break;              //
        }
        case 'h': case 'H':         //
        {
            if (i > 1)              //
                return 1;           //
            
            if (e->modo == HELP)    //if statment doesn't have realtion with previous if statment
                return 3;           //
            
            e->showHelp = 1;        //
            
            break;                  //
        }
        case 'u': case 'U': //
        {
            if (i > 1)      //
                return 1;   //
            
            undo(e,s);      //
            break;          //
        }
        case 'q': case 'Q': //
        {
            if (i > 1)      //
                return 1;   //
            
            CLEAR;          //
            exit(0);        //
            
            break;          //
        }
        default:            //
        {
            puts("RTFM");   //
            break;          //
        }
    }
    
    return 0;
}
