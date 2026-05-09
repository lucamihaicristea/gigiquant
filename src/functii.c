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

void insert( StockList **head, char stock[] )
{
    StockList *aux = *head;
    StockList *new = (StockList*)malloc( sizeof( StockList ));
    strcpy( new->symbol, stock );
    new->next = NULL;
    if( *head == NULL )
        *head = new;
    else
        {
            while( aux->next != NULL )
                aux = aux->next;
            aux->next = new;
        }
}

TreeNode *calibrare_nod( TreeNode *root, int d )
{
    if( d == 1 )
    {
        if( root->left == NULL )
        {
            root->left = (TreeNode*)malloc(sizeof(TreeNode));
            root->left->left = NULL;
            root->left->right = NULL;
            root->left->stocks = NULL;
        }
        return root->left;
    }
    else if( d == 2 )
        {
            if( root->right == NULL )
            {
                root->right = (TreeNode*)malloc(sizeof(TreeNode));
                root->right->left = NULL;
                root->right->right = NULL;
                root->right->stocks = NULL;
            }
            return root->right;
        }
    return NULL;
}

void creare_arbore(FILE *fin, TreeNode **root, TreeNode *poz[ 10 ] ) 
{
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    (*root)->stocks = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;
    char nume_stockuri[ 100 ];
    fgets( nume_stockuri, sizeof( nume_stockuri ), fin );
    char *p = strtok( nume_stockuri, ",\n" );
    while( p != NULL )
    {
        insert( &((*root)->stocks), p );
        p = strtok( NULL, ",\n" );
    }
    float pret;
    int ok = 0;
    while( fscanf( fin, "%f,", &pret ) == 1 )
    {
        if( ok == 0 )
        {
            StockList *aux = (*root)->stocks;
            aux->val = pret;
            aux->traseu = 0;
            aux = aux->next;
            poz[ 0 ] = *root;
            for( int i = 1; i < 10; i++ )
            {
                fscanf( fin, "%f,", &pret );
                aux->val = pret;
                aux->traseu = 0;
                aux = aux->next;
                poz[ i ] = *root;
            }
            ok = 1;
        }
        else
            {
                StockList *curr = (*root)->stocks;
                int d;
                if( curr->val > pret )
                    d = 1; // pentru stanga 1
                else
                    d = 2; // pentru dreapta 2
                // traseul va fi de forma 1212 spre exemplu
                curr->traseu = (curr->traseu)*10 + d;
                poz[ 0 ] = calibrare_nod( poz[ 0 ], d );
                curr->val = pret;
                insert( &(poz[0]->stocks), curr->symbol );
                curr = curr->next;
                for( int i = 1; i < 10; i++ )
                {
                    fscanf( fin, "%f,", &pret );
                    if( curr->val > pret )
                    d = 1;
                    else
                    d = 2;
                    
                    curr->traseu = (curr->traseu)*10 + d;
                    poz[ i ] = calibrare_nod( poz[ i ], d );
                    curr->val = pret;
                    insert( &(poz[i]->stocks), curr->symbol );
                    curr = curr->next;
                }
            }
    }
}

int transformare( int nr )
{
    int x = 0, p = 1;
    while( nr != 0 )
    {
        x = x + ( 3 - ( nr % 10 ) ) * p;
        p = p * 10;
        nr = nr / 10;
    }
    return x;
}

void oglindite( TreeNode *root, FILE *fout )
{
    StockList *initial = root->stocks;
    while( initial != NULL )
    {
        int tras = transformare( initial->traseu );
        StockList *cautare = initial->next;
        while( cautare != NULL )
        {
            if( tras == cautare->traseu )
                fprintf( fout, "%s-%s\n", initial->symbol, cautare->symbol );
            cautare=cautare->next;
        }
        initial = initial->next;
    }
}

void free_lista( StockList *head )
{
    StockList *aux;
    while( head != NULL )
    {
        aux = head;
        head = head->next;
        free(aux);
    }
}

void free_arbore( TreeNode *root )
{
    if( root == NULL )
        return;
    free_arbore( root->left );
    free_arbore( root->right );
    if( root->stocks != NULL )
        free_lista( root->stocks );
    free( root );
}