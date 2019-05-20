#include "reversi.h"

/**
 * @brief 
 *
 * @param e
 * @param s
 *
 * @return 
 */
int bot1(ESTADO *e, LState *s)
{
    int random = rand() % e->nValids;
    
    POSITION play = e->valids[random].valid;
    
    return doPlay(play, e, s);
}

/**
 * @brief 
 *
 * @param e
 * @param s
 *
 * @return 
 */
int bot2(ESTADO *e, LState* s)
{
    return doPlay(e->help, e, s);
}

/**
 * @brief 
 *
 * @param e
 * @param s
 *
 * @return 
 */
int bot3(ESTADO *e, LState* s)
{
    NEGAMAX mm;
    
    mm = negaMax(*e, 5, 1);
    
    return doPlay(mm.play, e, s);
}

/**
 * @brief 
 *
 * @param father
 * @param depth
 * @param player
 *
 * @return 
 */
NEGAMAX negaMax(ESTADO father, int depth, int player)
{
    NEGAMAX mm;
    
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

/**
 * @brief 
 *
 * @param e
 *
 * @return 
 */
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
