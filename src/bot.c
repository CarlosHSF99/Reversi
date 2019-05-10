#include "estado.h"

int botEasy (ESTADO *e, LEST *s)
{
    /*
    int i, r, min=0;
    int max = e->nValidas;
    
    if (max == 0)
    {
        
    }
    r = (rand() % (max + 1));
    
    reverse(e->validas[MAX_POS].virar[r].l, e->validas[MAX_POS].virar[r].c, e, s);
    */
    
    return 0;
}

int botMedium (ESTADO *e, LEST* s)
{
    /*
    if ((e->validas->valida.l != 0) && (e->validas->valida.c != 0))
    {
        reverse(e->validas[MAX_POS].valida.l != 0, e->validas[MAX_POS].valida.c != 0, e, s);
    }
    else 
    {
        //passa o turno?
    }
    */

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
