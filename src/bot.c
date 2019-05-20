#include "estado.h"

int bot1(ESTADO *e, LState *s)
{
    int random = rand() % e->nValids;
    
    POSITION play = e->valids[random].valid;
    
    return doPlay(play, e, s);
}

int bot2(ESTADO *e, LState* s)
{
    return doPlay(e->help, e, s);
}

int bot3(ESTADO *e, LState* s)
{
    MINIMAX mm;
    //POSITION play;
    
    //puts("");
    
    //play.l = 0;
    //play.c = 0;
    
    mm = negaMax(*e, 5, 1);
    //miniMax(*e, 5, 1, &play);
    //negaMax(*e, 5, 1, &play);
    //miniMaxAB(*e, 7, (int)-INFINITY, (int)INFINITY, 1, &play);
    
    printf("\n(%d,%d)\n", mm.play.l, mm.play.c);
    //printf("\n(%d,%d)\n", play.l, play.c);
    
    return doPlay(mm.play, e, s);
    //return doPlay(play, e, s);
}

MINIMAX negaMax(ESTADO father, int depth, int player)
{
    MINIMAX mm;
    
    if (!depth || gameOver(father))
    {
        if (gameOver(father))
        {
            if (father.bot == VALOR_X ? father.scoreX > father.scoreO : father.scoreX < father.scoreO)
            {
                mm.score = INFINITY;
                return mm;
            }
            else if (father.bot == VALOR_O ? father.scoreX < father.scoreO : father.scoreX > father.scoreO)
            {
                mm.score = -INFINITY;
                return mm;
            }
            else
            {
                mm.score = 0;
                return mm;
            }
        }
        
        mm.score = player * evalFunc(father);
        
        return mm;
    }
    
    VALIDS *valids = father.valids;
    POSITION *valid = &valids->valid;
    int nValids = father.nValids;
    mm.score = -INFINITY;
    
    for (; nValids--; valid = &(++valids)->valid)
    {
        ESTADO child = father;
        reverse(valids, &child);
        switchPiece(&child.peca);
        update(&child);
        double newValue = -negaMax(child, depth - 1, -player).score;
        
        if (newValue >= mm.score)
        {
            mm.score = newValue;
            mm.play = *valid;
        }
    }
    
    return mm;
}

int evalFunc(ESTADO e)
{
    int bot_pieces, opp_pieces, bot_front_pieces, opp_front_pieces, x, y;
    double d, p, f, c, l, m;
    
    bot_pieces = opp_pieces = bot_front_pieces = opp_front_pieces = 0;
    d = p = f = c = l = m = 0;
    
    int X1[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    int Y1[] = { 0,  1, 1, 1, 0, -1, -1, -1};
    int weight[DIM][DIM] = {{20, -3, 11,  8,  8, 11, -3, 20},
                            {-3, -7, -4,  1,  1, -4, -7, -3},
                            {11, -4,  2,  2,  2,  2, -4, 11},
                            { 8,  1,  2, -3, -3,  2,  1,  8},
                            { 8,  1,  2, -3, -3,  2,  1,  8},
                            {11, -4,  2,  2,  2,  2, -4, 11},
                            {-3, -7, -4,  1,  1, -4, -7, -3},
                            {20, -3, 11,  8,  8, 11, -3, 20}};
    
    for (int l = 0; l < DIM; l++)
        for (int c = 0; c < DIM; c++)
        {
            if (e.grelha[l][c] == e.bot)
            {
                d += weight[l][c];
                bot_pieces++;
            }
            else if (e.grelha[l][c] == 3 - e.bot)
            {
                d -= weight[l][c];
                opp_pieces++;
            }
            
            if (e.grelha[l][c] != VAZIA)
            {
                for (int i = 0; i < DIM; i++)
                {
                    x = l + X1[i];
                    y = c + Y1[i];
                    
                    if (x >= 0 && x < DIM && y >= 0 && y < DIM && e.grelha[x][y] == VAZIA)
                    {
                        if (e.grelha[l][c] == e.bot)
                            bot_front_pieces++;
                        else
                            opp_front_pieces++;
                        break;
                    }
                }
            }
        }
    
    if (bot_pieces > opp_pieces)
        p = (100.0 * bot_pieces) / (bot_pieces + opp_pieces);
    else if (bot_pieces < opp_pieces)
        p = -(100.0 * opp_pieces) / (bot_pieces + opp_pieces);
    else
        p = 0;
    
    if (bot_front_pieces > opp_front_pieces)
        f = -(100.0 * bot_front_pieces) / (bot_front_pieces + opp_front_pieces);
    else if (bot_front_pieces < opp_front_pieces)
        f = (100.0 * opp_front_pieces) / (bot_front_pieces + opp_front_pieces);
    else
        f = 0;
    
    // Corners
    bot_pieces = opp_pieces = 0;
    if (e.grelha[0][0] == e.bot)
        bot_pieces++;
    else if (e.grelha[0][0] == 3 - e.bot)
        opp_pieces++;
    if (e.grelha[0][7] == e.bot)
        bot_pieces++;
    else if (e.grelha[0][7] == 3 - e.bot)
        opp_pieces++;
    if (e.grelha[7][0] == e.bot)
        bot_pieces++;
    else if (e.grelha[7][0] == 3 - e.bot)
        opp_pieces++;
    if (e.grelha[7][7] == e.bot)
        bot_pieces++;
    else if (e.grelha[7][7] == 3 - e.bot)
        opp_pieces++;
    
    c = 25 * (bot_pieces - bot_pieces);
    
    // Corner closeness
    bot_pieces = opp_pieces = 0;

	if(e.grelha[0][0] == VAZIA)
    {
		if (e.grelha[0][1] == e.bot)
            bot_pieces++;
		else if(e.grelha[0][1] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[1][1] == e.bot)
            bot_pieces++;
		else if (e.grelha[1][1] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[1][0] == e.bot)
            bot_pieces++;
		else if (e.grelha[1][0] == 3 - e.bot)
            opp_pieces++;
	}
	if(e.grelha[0][7] == VAZIA)
    {
		if (e.grelha[0][6] == e.bot)
            bot_pieces++;
		else if (e.grelha[0][6] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[1][6] == e.bot)
            bot_pieces++;
		else if (e.grelha[1][6] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[1][7] == e.bot)
            bot_pieces++;
		else if (e.grelha[1][7] == 3 - e.bot)
            opp_pieces++;
	}
	if (e.grelha[7][0] == VAZIA)
    {
		if (e.grelha[7][1] == e.bot)
            bot_pieces++;
		else if (e.grelha[7][1] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[6][1] == e.bot)
            bot_pieces++;
		else if (e.grelha[6][1] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[6][0] == e.bot)
            bot_pieces++;
		else if (e.grelha[6][0] == 3 - e.bot)
            opp_pieces++;
	}
	if (e.grelha[7][7] == VAZIA)
    {
		if (e.grelha[6][7] == e.bot)
            bot_pieces++;
		else if (e.grelha[6][7] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[6][6] == e.bot)
            bot_pieces++;
		else if (e.grelha[6][6] == 3 - e.bot)
            opp_pieces++;
		if (e.grelha[7][6] == e.bot)
            bot_pieces++;
		else if (e.grelha[7][6] == 3 - e.bot)
            opp_pieces++;
    }
    
    l = -12.5 * (bot_pieces - opp_pieces);
    
    //mobility
    bot_pieces = e.nValids;
    
    switchPiece(&e.peca);
    update(&e);
    
    opp_pieces = e.nValids;
    
    if (bot_pieces > opp_pieces)
        m = (100.0 * bot_pieces) / (bot_pieces + opp_pieces);
    else if (bot_pieces < opp_pieces)
        m = -(100.0 * opp_pieces) / (bot_pieces + opp_pieces);
    else
        m = 0;

    //final weighted score
    double score = (10 * p) + (801.724 * c) + (382.026 * l) + (78.922 * m) + (74.396 * f) + (10 * d);
    
    return score;
}




















void print(ESTADO e);

int miniMax(ESTADO father, int depth, int minmax, POSITION *play)
{
    if (!depth || gameOver(father))
        return father.peca == VALOR_O ? father.scoreX : father.scoreO;
    
    VALIDS *valids = father.valids;
    POSITION *valid = &valids->valid;
    int nValids = father.nValids;
    
    if (minmax)
    {
        double maxEval = -INFINITY;
        
        for (; nValids--; valid = &(++valids)->valid)
        {
            ESTADO child = father;
            reverse(valids, &child);
            switchPiece(&child.peca);
            update(&child);
            int eval = miniMax(child, depth - 1, 1/*!minmax*/, play);
            
            if (eval >= maxEval)
            {
                maxEval = eval;
                
                if (depth == 5)
                    *play = *valid;
            }
        }
        
        return maxEval;
    }
    else
    {
        double minEval = INFINITY;
        
        for (; nValids--; valid = &(++valids)->valid)
        {
            ESTADO child = father;
            reverse(valids, &child);
            switchPiece(&child.peca);
            update(&child);
            int eval = miniMax(child, depth - 1, 0/*!minmax*/, play);
            
            if (eval <= minEval)
            {
                minEval = eval;
                
                if (depth == 5)
                    *play = *valid;
            }
        }
        
        return minEval;
    }
}

int negaMax2(ESTADO father, int depth, int player, POSITION *play)
{
    if (!depth || gameOver(father))
    {
        if (gameOver(father))
        {
            if (father.bot == VALOR_X ? father.scoreX > father.scoreO : father.scoreX < father.scoreO)
                return (int)INFINITY;
            else if (father.bot == VALOR_X ? father.scoreX < father.scoreO : father.scoreX > father.scoreO)
                return (int)-INFINITY;
            else
                return 0;
        }
        
        //return player * (father.bot == VALOR_X ? father.scoreX - father.scoreO : father.scoreO - father.scoreX);
        return player * (father.bot == VALOR_X ? father.scoreX : father.scoreO);
    }
    
    VALIDS *valids = father.valids;
    POSITION *valid = &valids->valid;
    int nValids = father.nValids;
    double value = -INFINITY;
    
    for (; nValids--; valid = &(++valids)->valid)
    {
        ESTADO child = father;
        reverse(valids, &child);
        switchPiece(&child.peca);
        update(&child);
        int newValue = -negaMax2(child, depth - 1, -player, play);
        
        if (newValue >= value)
        {
            value = newValue;
            
            if (depth == 5)
                *play = *valid;
        }
    }
    
    return value;
}

int negaScout(ESTADO father, int depth, int A, int B, int player, POSITION *play)
{
    if (!depth || gameOver(father))
    {
        if (gameOver(father))
        {
            if (father.bot == VALOR_X ? father.scoreX > father.scoreO : father.scoreX < father.scoreO)
                return (int)INFINITY;
            else if (father.bot == VALOR_X ? father.scoreX < father.scoreO : father.scoreX > father.scoreO)
                return (int)-INFINITY;
            else
                return 0;
        }
        
        return player * (father.bot == VALOR_X ? father.scoreX - father.scoreO : father.scoreO - father.scoreX);
    }
    
    VALIDS *valids = father.valids;
    POSITION *valid = &valids->valid;
    int nValids = father.nValids;
    double value = -INFINITY;
    
    for (; nValids--; valid = &(++valids)->valid)
    {
        ESTADO child = father;
        reverse(valids, &child);
        switchPiece(&child.peca);
        update(&child);
        int newValue = -negaMax2(child, depth - 1, -player, play);
        
        if (newValue >= value)
        {
            value = newValue;
            
            if (depth == 7)
                *play = *valid;
        }
    }
    
    return value;
}

//
int miniMaxAB(ESTADO father, int depth, int A, int B, int minmax, POSITION *play)
{
    if (!depth || gameOver(father))
        return father.peca == VALOR_O ? father.scoreX : father.scoreO;
    
    VALIDS *valids = father.valids;
    POSITION *valid = &valids->valid;
    int nValids = father.nValids;
    
    if (minmax)
    {
        double maxEval = -INFINITY;
        
        for (; nValids--; valid = &(++valids)->valid)
        {
            ESTADO child = father;
            reverse(valids, &child);
            switchPiece(&child.peca);
            update(&child);
            int eval = miniMax(child, depth - 1, 1, play);
            
            if (eval >= maxEval)
            {
                maxEval = eval;
                
                if (depth == 7)
                    *play = *valid;
            }
            
            A = A > maxEval ? A : maxEval;
            
            if (A >= B)
                break;
        }
        
        return maxEval;
    }
    else
    {
        double minEval = INFINITY;
        
        for (; nValids--; valid = &(++valids)->valid)
        {
            ESTADO child = father;
            reverse(valids, &child);
            switchPiece(&child.peca);
            update(&child);
            int eval = miniMax(child, depth - 1, 0, play);
            
            if (eval <= minEval)
            {
                minEval = eval;
                
                if (depth == 7)
                    *play = *valid;
            }
            
            B = B > minEval ? B : minEval;
            
            if (A >= B)
                break;
        }
        
        return minEval;
    }
}

void print(ESTADO e)
{
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
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
        puts("");
    }
}
/*
>>>>>>> 52ec3ceb2f596622988a823687b1904987e37866
{
    int score = 0, new_score;
    ESTADO *c;

    MINMAX bot_output = {0};

    if (depth == max_depth)
    {
//<<<<<<< HEAD
        score = (c->NX - c->NO);
    }
    else if (e->peca == VALOR_X) // Maximizing Player
    {
        if (depth == 0)
        {
            c = e;
            new_score = -64;
        }

//=======
        c = e;
        score = (c->scoreX - c->scoreO);
    }
    else if (e->peca == VALOR_X) // Maximizing Player
    {
        new_score = -64;
//>>>>>>> 52ec3ceb2f596622988a823687b1904987e37866
        while ( e->nValids != 0 )
        {
            c = e;
            
            //play(e->valids->valid.l,e->valids->valid.c,c,s);
            new_score = miniMax(e,depth+1,max_depth,s);
//<<<<<<< HEAD
        
            if ( new_score > score )
//=======
            
            if (new_score > score)
//>>>>>>> 52ec3ceb2f596622988a823687b1904987e37866
            {
                score = new_score;
                bot_output.grid.l = e->valids->valid.l;
                bot_output.grid.c = e->valids->valid.c;
            }
        }
    }
    else // Minimizing Player
    {
        while (e->nValids != 0)
        {
            new_score = 64;
            
            while ( e->nValids != 0 )
            {
                c = e;
                //play(e->valids->valid.l,e->valids->valid.c,c,s);
                new_score = miniMax( e, depth+1, max_depth, s);
                
                if (new_score < score)
                {
                    score = new_score;
                    bot_output.grid.l = c->valids->valid.l;
                    bot_output.grid.c = c->valids->valid.c;
                }
            }
        }
    }
    
    //play(bot_output.grid.l, bot_output.grid.c, e,s);

    bot_output.score = score;
    
    return bot_output.score;
}*/
