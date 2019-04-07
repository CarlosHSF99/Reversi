#include "estado.h"

void interpreter(ESTADO e)
{
    char line[MAX_STR];
    
    //CLEAR;
    
    while (1)
    {
        printg(e);
        e.showValid = e.showHelp = 0;
        
        if (!fgets(line, MAX_STR, stdin))
            exit(0);
        
        interpret(&e, line);
    }
}

int interpret(ESTADO *e, char *line)
{
    char option;
    char file_name[MAX_STR];
    char *cmd[MAX_STR];
    int l, c;
    int i;
    VALOR value;
    
    //CLEAR;
    
    cmd[0] = strtok(line, " \n");
    
    if (!cmd[0] || strlen(cmd[0]) > 1)
        return -1;
    
    for (i = 0; cmd[i]; i++)
        cmd[i+1] = strtok(NULL, " \n");
    
    //for (int j = 0; cmd[j]; j++)
    //    printf("/%s/", cmd[j]);
    
    //CLEAR;
    
    switch (cmd[0][0])
    {
        case 'n': case 'N':
        {
            if (i < 2)
                return -1;
            else if (i > 2)
                return 1;
            
            if (!strcmp(cmd[1], "X"))
                value = VALOR_X;
            else if (!strcmp(cmd[1], "O"))
                value = VALOR_O;
            else
                return -1;
            
            newVsHuman(e, value);
            
            break;
        }
        case 'a': case 'A':
        {
            if (i < 2)
                return -1;
            else if (i > 2)
                return 1;
            
            if (!strcmp(cmd[1], "X"))
                value = VALOR_X;
            else if (!strcmp(cmd[1], "O"))
                value = VALOR_O;
            else
                return -1;
            
            newVsBot(e, value);
            
            break;
        }
        case 'l': case 'L':
        {
            if (i < 2)
                return -1;
            else if (i > 2)
                return 1;
            
            readFile(e, cmd[1], READ);
            
            break;
        }
        case 'e': case 'E':
        {
            if (i < 2)
                return -1;
            else if (i > 2)
                return 1;
            
            saveFile(e, cmd[1]);
            
            break;
        }
        case 'j': case 'J':
        {
            if (i < 3)
                return -1;
            else if (i > 3)
                return 1;
            
            if (!isdigit(cmd[1][0]) || !isdigit(cmd[2][0]))
                return 2;
            
            l = cmd[1][0] - '0';
            c = cmd[2][0] - '0';
            
            if (e->modo == '0')
                play(l, c, e);
            else if (e->peca == value)
                play(l, c, e);
            else
                miniMax(e, 0, 2);
            
            break;
        }
        case 's': case 'S':
        {
            if (i > 1)
                return 1;
            
            e->showValid = 1;
            
            break;
        }
        case 'h': case 'H':
        {
            if (i > 1)
                return 1;
            
            e->showHelp = 1;
            
            break;
        }
        case 'u': case 'U':
        {
            if (i > 1)
                return 1;
            
            undo(e);
            break;
        }
        case 'q': case 'Q':
        {
            if (i > 1)
                return 1;
            
            exit(0);
            
            break;
        }
        default:
        {
            puts("RTFM");
            break;
        }
    }

    return 0;
}
