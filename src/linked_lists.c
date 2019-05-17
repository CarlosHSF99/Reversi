#include "estado.h"

//
void freeStack(LEST *s)
{
    LEST* temp = s;         //
    
    while (*s)              //
    {
        *temp = (*s);        //
        *s = (*s)->next;    //
        free(*temp);         //
        *temp=NULL;
    }
}

//
void newGame(LEST *s)
{
    LEST temp = (*s);       //
    
    while ((*s)->next)      //
    {
        temp = (*s);        //
        *s = (*s)->next;    //
        free(temp);         //
    }
}

//
void push(ESTADO e, LEST *s)
{
    LEST new_s = malloc(sizeof(struct history));    //
    new_s->e = e;                                   //
    new_s->next = (*s);                             //
    *s = new_s;                                     //
}

//
void pop(LEST *s)
{
    LEST temp = (*s);                 //
    
    if((*s)->next == NULL)            //
        printf("\nStack vazia\n");    //
    else                              //
    {
        *s = (*s)->next;              //
        free(temp);                   //
    }
}

void altPush(ESTADO e,LEST* s)  
{  
    if((*s)==NULL){
        *s = malloc(sizeof(struct history));
        (*s)->e=e;
        (*s)->next=NULL;
    }
    else{
        LEST new_s = malloc(sizeof(struct history));
        new_s->e = e;
        new_s->next = NULL;
        
        while((*s)->next!=NULL)
            s=&((*s)->next);

        (*s)->next = new_s;
    }
}
