#include "estado.h"

int bot1(ESTADO *e, LEST *s)
{
    int randomi = rand() % e->nValidas;
    int l = e->validas[randomi].valida.l;
    int c = e->validas[randomi].valida.c;
    
    return doPlay(l, c, e, s);
}

int bot2(ESTADO *e, LEST* s)
{
    return doPlay(e->help.l, e->help.c, e, s);
}

int bot3(ESTADO *e, LEST* s)
{
    POSICAO play;
    //MINIMAX mm;
    
    play.l = 0;
    play.c = 0;
    
    //miniMax(*e, 3, 1, &play);
    negaMax(*e, 7, 1, &play);
    //mm = negaMax(*e, 3, 1);
    
    //printf("(%d,%d)\n", play.l, play.c);
    //printf("(%d,%d)\n", mm.play.l, mm.play.c);
    
    return doPlay(play.l, play.c, e, s);
    //return doPlay(mm.play.l, mm.play.c, e, s);
}

void print(ESTADO e);

int miniMax(ESTADO father, int depth, int minmax, POSICAO *play)
{
    if (!depth || isGameOver(father))
        return father.peca == VALOR_O ? father.scoreX : father.scoreO;
    
    VALIDAS *valids = father.validas;
    POSICAO *valid = &valids->valida;
    int nValids = father.nValidas;
    
    if (minmax)
    {
        double maxEval = -INFINITY;
        
        for (; nValids--; valid = &(++valids)->valida)
        {
            ESTADO child = father;
            reverse(valid->l, valid->c, &child);
            switchPiece(&child.peca);
            update(&child);
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
            ESTADO child = father;
            reverse(valid->l, valid->c, &child);
            switchPiece(&child.peca);
            update(&child);
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

int negaMax(ESTADO father, int depth, int player, POSICAO *play)
{
    if (!depth || isGameOver(father))
    {
        if (isGameOver(father))
        {
            if (father.botPiece == VALOR_X ? father.scoreX > father.scoreO : father.scoreX < father.scoreO)
                return (int)INFINITY;
            else if (father.botPiece == VALOR_X ? father.scoreX < father.scoreO : father.scoreX > father.scoreO)
                return (int)-INFINITY;
            else
                return 0;
        }
        
        return player * (father.botPiece == VALOR_X ? father.scoreX - father.scoreO : father.scoreO - father.scoreX);
    }
    
    VALIDAS *valids = father.validas;
    POSICAO *valid = &valids->valida;
    int nValids = father.nValidas;
    double value = -INFINITY;
    
    for (; nValids--; valid = &(++valids)->valida)
    {
        ESTADO child = father;
        reverse(valid->l, valid->c, &child);
        switchPiece(&child.peca);
        update(&child);
        int newValue = -negaMax(child, depth - 1, -player, play);
        
        if (newValue > value)
        {
            value = newValue;
            
            if (depth == 7)
            {
                play->l = valid->l;
                play->c = valid->c;
            }
        }
    }
    
    return value;
}

MINIMAX negaMax2(ESTADO father, int depth, int player)
{
    MINIMAX mm;
    
    if (!depth || isGameOver(father))
    {
        if (isGameOver(father))
        {
            if (father.scoreX > father.scoreO)
            {
                mm.score = (int)INFINITY;
                return mm;
            }
            else if (father.scoreX < father.scoreO)
            {
                mm.score = (int)-INFINITY;
                return mm;
            }
            else
            {
                mm.score = 0;
                return mm;
            }
        }
        
        mm.score = player * (father.botPiece == VALOR_X ? father.scoreX - father.scoreO : father.scoreO - father.scoreX);
        
        return mm;
    }
    
    VALIDAS *valids = father.validas;
    POSICAO *valid = &valids->valida;
    int nValids = father.nValidas;
    mm.score = (int)-INFINITY;
    
    for (; nValids--; valid = &(++valids)->valida)
    {
        ESTADO child = father;
        reverse(valid->l, valid->c, &child);
        switchPiece(&child.peca);
        update(&child);
        int newValue = -negaMax2(child, depth - 1, -player).score;
        
        if (newValue > mm.score)
        {
            mm.score = newValue;
            mm.play.l = valid->l;
            mm.play.c = valid->c;
        }
    }
    
    return mm;
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
