#include "interviuri.h"

struct Node* citire1( FILE *fin, int n )
{
    int i;
    double pret;

    struct Node *head = NULL, *tail = NULL;
    for( i = 0; i < n; i++)
    {
        fscanf( fin, "%lf", &pret );
        struct Node* nod = ( struct Node* )malloc( sizeof( struct Node ) );
        if( nod == NULL )
            return head;
        nod->val = pret;
        nod->rand = 0.0;
        nod->next = NULL;

        if( head == NULL )
        {
            head = nod;
            tail = nod;
        }
        else 
            {
                tail->next = nod;
                tail = nod;
            }
    }
    fclose(fin);
    return head;
}

void calcul_rand( struct Node *head )
{
    struct Node const *prev = head;
    struct Node *curr = head->next;
    while( curr != NULL )
    {
        curr->rand = ( curr->val - prev->val ) / prev->val;
        prev = curr;
        curr = curr->next;
    }
}

double calcul_rm( const struct Node *head, int nrrand )
{
    double sumrand = 0.0;
    const struct Node *curr = head;
    while( curr != NULL )
    {
        sumrand = sumrand + curr->rand;
        curr = curr->next;
    }
    return sumrand / nrrand;
}

double calcul_sigma( const struct Node *head, double rm, int nrrand )
{
    double sump = 0.0;
    const struct Node *curr = head->next;
    while( curr != NULL )
    {            
        sump = sump + ( curr->rand - rm ) * ( curr->rand - rm );
        curr = curr->next;
    }
    return sqrt( sump / nrrand );
}

void freee( struct Node *head )
{
    while( head != NULL )
    {
        struct Node *temp = head;
        head = head->next;
        free( temp );
    }
}

static void push( nod **top, float v )
{
    nod *newnod = (nod*)malloc( sizeof( nod ) );
    if( newnod == NULL )
        return;
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
    while( *top != NULL )
    {
        nod *temp = *top;
        *top=(*top)->next;
        free(temp);
    }
}

void citire2( FILE *fin, char *locatie, nod **top )
{
    char lin[ 40 ];
    *top = NULL;
    float valo;
    if( fgets( lin, sizeof( lin ), fin ) )
    {
        lin[ strlen( lin ) - 1 ]= '\0';
        strcpy( locatie, lin );
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

void enqueue( queue *q, float v, int ziua, const char *local )
{
    opor *newnod = ( opor*)malloc( sizeof( opor ) );
    if( newnod == NULL )
        return;
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
    while( q->front != NULL )
    {
        opor *aux = q->front;
        q->front=q->front->next;
        free(aux);
    }
    free(q);
}