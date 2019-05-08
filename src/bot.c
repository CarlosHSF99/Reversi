#include "estado.h"

int miniMax(ESTADO *e, int depth, int max_depth,LEST* s)
{
    int score = 0, new_score;
    ESTADO *c;

    MINMAX bot_output = {0};

    if (depth == max_depth)
    {
        c = e;
        score = (c->scoreX - c->scoreO);
    }
    else if (e->peca == VALOR_X) // Maximizing Player
    {
        new_score = -64;
        while ( e->nValidas != 0 )
        {
            c = e;
            
            //play(e->validas->valida.l,e->validas->valida.c,c,s);
            new_score = miniMax(e,depth+1,max_depth,s);
            
            if (new_score > score)
            {
                score = new_score;
                bot_output.grid.l = e->validas->valida.l;
                bot_output.grid.c = e->validas->valida.c;
            }
        }
    }
    else // Minimizing Player
    {
        while (e->nValidas != 0)
        {
            new_score = 64;
            
            while ( e->nValidas != 0 )
            {
                c = e;
                //play(e->validas->valida.l,e->validas->valida.c,c,s);
                new_score = miniMax( e, depth+1, max_depth, s);
                
                if (new_score < score)
                {
                    score = new_score;
                    bot_output.grid.l = c->validas->valida.l;
                    bot_output.grid.c = c->validas->valida.c;
                }
            }
        }
    }
    
    //play(bot_output.grid.l, bot_output.grid.c, e,s);

    bot_output.score = score;
    
    return bot_output.score;
}
