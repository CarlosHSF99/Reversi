#include "reversi.h"

//
/**
 * @brief 
 *
 * @param s
 */
void freeStack(LState *s)
{
    LState* temp = s;         //
    
    while (*s)              //
    {
        *temp = (*s);        //
        *s = (*s)->next;    //
        free(*temp);         //
        *temp = NULL;
    }
}

//
/**
 * @brief 
 *
 * @param s
 */
void newGame(LState *s)
{
    LState temp = *s;       //
    
    while ((*s)->next)      //
    {
        temp = *s;        //
        *s = (*s)->next;    //
        free(temp);         //
    }
}

//
/**
 * @brief 
 *
 * @param e
 * @param s
 */
void push(ESTADO e, LState *s)
{
    LState new_s = malloc(sizeof(struct history));    //
    new_s->e = e;                                   //
    new_s->next = *s;                             //
    *s = new_s;                                     //
}

//
/**
 * @brief 
 *
 * @param s
 */
void pop(LState *s)
{
    LState temp = *s;                 //
    
    if((*s)->next == NULL)            //
        printf("\nStack vazia\n");    //
    else                              //
    {
        *s = (*s)->next;              //
        free(temp);                   //
    }
}

/**
 * @brief 
 *
 * @param e
 * @param s
 */
void altPush(ESTADO e, LState* s)
{  
    if(!(*s))
    {
        *s = malloc(sizeof(struct history));
        (*s)->e = e;
        (*s)->next=NULL;
    }
    else
    {
        LState new_s = malloc(sizeof(struct history));
        new_s->e = e;
        new_s->next = NULL;
        
        while((*s)->next)
            s = &((*s)->next);
        
        (*s)->next = new_s;
    }
}
