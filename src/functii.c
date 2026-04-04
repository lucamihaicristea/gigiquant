#include "interviu1.h"

struct Node* citire( const char* fisier, int *n)
{
    int i;
    double pret;
    FILE* fin = fopen( fisier, "r" );
    if( fin == NULL )
        return NULL;

    if( fscanf( fin, "%d", n ) != 1 || *n < 2 )
    {
        fclose(fin);
        return NULL;
    }

    struct Node *head = NULL, *tail = NULL;
    for( i = 0; i < *n; i++)
    {
        fscanf( fin, "%lf", &pret );
        struct Node* nod = ( struct Node* )malloc( sizeof( struct Node ) );
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

double calcul_rm( struct Node *head, int nrrand )
{
    double sumrand = 0.0;
    struct Node *curr = head;
    while( curr != NULL )
    {
        sumrand = sumrand + curr->rand;
        curr = curr->next;
    }
    return sumrand / nrrand;
}

double calcul_sigma( struct Node *head, double rm, int nrrand )
{
    double sump = 0.0;
    struct Node *curr = head->next;
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