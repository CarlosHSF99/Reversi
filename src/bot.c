#include "estado.h"

int bot1(ESTADO *e, LEST *s)
{
    int randomi = rand() % e->nValidas;
    int l = e->validas[randomi].valida.l;
    int c = e->validas[randomi].valida.c;
    
    return doPlay(l, c, e, s);//reverse(l, c, e);
}

int bot2(ESTADO *e, LEST* s)
{
    return doPlay(e->help.l, e->help.c, e, s);//reverse(e->help.l, e->help.c, e);
}

int bot3(ESTADO *e, LEST* s)
{
    POSICAO play;
    
    miniMax(*e, 2, 1, &play);
    
    return doPlay(play.l, play.c, e, s);//reverse(play.l, play.c, e);
}

void print();

int miniMax(ESTADO e, int depth, int minmax, POSICAO *play)
{
    
    printf("\ndepth: %d, scoreX: %d, scoreO: %d\n", depth, e.scoreX, e.scoreO);
    if (depth < 0)
        puts("FFS...");
    fflush(stdout);
    //sleep(2);
    
    if (!depth)
    {
        //puts("FFS...");
        return minmax ? e.botPiece == VALOR_X ? e.scoreX : e.scoreO : e.botPiece == VALOR_X ? e.scoreO : e.scoreX;
    }
    
    VALIDAS *valids = e.validas;
    POSICAO *valid = &valids->valida;
    int nValids = e.nValidas;
   
    if (minmax)
    {
        double maxEval = -INFINITY;
        
        for (; nValids--; valid = &(++valids)->valida)
        {
            ESTADO child = e;
            print(child);
            reverse(valid->l, valid->c, &child);
            //update(&child);
            print(child);
            int eval = miniMax(child, depth - 1, !minmax, play);
            if (eval > maxEval)
            {
                maxEval = eval;
                play->l = valid->l;
                play->c = valid->c;
            }
        }
        
        return maxEval;
    }
    else
    {
        double minEval = INFINITY;
        
        for (; nValids--; valid = &(++valids)->valida)
        {
            ESTADO child = e;
            print(child);
            reverse(valid->l, valid->c, &child);
            //update(&child);
            print(child);
            int eval = miniMax(child, depth - 1, !minmax, play);
            if (eval < minEval)
            {
                minEval = eval;
                play->l = valid->l;
                play->c = valid->c;
            }
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
