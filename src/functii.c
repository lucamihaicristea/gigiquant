#include "interviu2.h"

void push( nod **top, float v )
{
    nod *newnod = (nod*)malloc( sizeof( nod ) );
    newnod->val = v;
    newnod->next = *top;
    *top = newnod;
}

float pop( nod **top )
{
    if( *top == NULL )
        return -1;
    nod *cop = *top;
    float aux = (*top)->val;
    *top = (*top)->next;
    free( cop );
    return aux;
}

void delete( nod **top )
{
    nod *temp;
    while( *top != NULL )
    {
        temp = *top;
        *top=(*top)->next;
        free(temp);
    }
}

void citire( FILE *fin, char *locatie, nod **top )
{
    *top = NULL;
    float valo;
    if( fscanf( fin, "%s", locatie ) != 1 )
    {
        fclose(fin);
        return;
    }
    while( fscanf( fin, "%f", &valo) == 1 )
    {
        push( top, valo );
    }
}

queue *createqueue()
{
    queue *q = (queue *)malloc( sizeof( queue ));
    if( q == NULL )
        return NULL;
    q->front=q->rear=NULL;
    return q;
}

void enqueue( queue *q, float v, int ziua, char *local )
{
    opor *newnod = ( opor*)malloc( sizeof( opor ) );
    newnod->val = v;
    newnod->zi = ziua;
    strcpy( newnod->loc, local );
    newnod->next = NULL;
    if( q->rear == NULL )
        q->rear = newnod;
    else
        {
            q->rear->next = newnod;
            q->rear = newnod;
        }
    if( q->front == NULL )
        q->front=q->rear;
}

void dequeue( queue *q, float *v, int *ziua, char *local )
{
    if( q->front == NULL )
        return;
    opor *aux = q->front;
    *v = q->front->val;
    *ziua = q->front->zi;
    strcpy( local, q->front->loc );
    q->front = q->front->next;
    if( q->front == NULL )
        q->rear = NULL;
    free(aux);
}

void deletequeue( queue *q )
{
    opor *aux;
    while( q->front != NULL )
    {
        aux = q->front;
        q->front=q->front->next;
        free(aux);
    }
    free(q);
}