#include "estado.h"

int bot1(ESTADO *e, LEST *s)
{
    int randomi = rand() % e->nValidas;
    int l = e->validas[randomi].valida.l;
    int c = e->validas[randomi].valida.c;
    
    reverse(l, c, e);
    push(*e, s);
    
    return 0;
}

int bot2(ESTADO *e, LEST* s)
{
    reverse(e->help.l, e->help.c, e);
    push(*e, s);

    return 0;
}

int bot3(ESTADO *e, LEST* s)
{
    return 0;
}

int miniMax(ESTADO *e, int depth, int max_depth,LEST* s)
{
    return 0;
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
        while ( e->nValidas != 0 )
        {
            c = e;
            
            //play(e->validas->valida.l,e->validas->valida.c,c,s);
            new_score = miniMax(e,depth+1,max_depth,s);
//<<<<<<< HEAD
        
            if ( new_score > score )
//=======
            
            if (new_score > score)
//>>>>>>> 52ec3ceb2f596622988a823687b1904987e37866
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
}*/
