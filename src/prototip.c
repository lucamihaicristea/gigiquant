#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StockList {
    char symbol[ 5 ];
    float val; //pretul din ziua precedenta, care va fi actualizat la fiecare zi
    int traseu; //traseul pe care il face stock ul in arbore, pentru a gasi mai usor oglinditul
    struct StockList *next;
} StockList;

typedef struct TreeNode {
    StockList *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

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

void creare_arbore(char *fisier, TreeNode **root, TreeNode *poz[ 10 ] ) 
{
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    (*root)->stocks = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;
    FILE *fin = fopen( fisier, "r" );
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
    fclose( fin );
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

void oglindite( TreeNode *root )
{
    StockList *initial = root->stocks;
    while( initial != NULL )
    {
        int tras = transformare( initial->traseu );
        StockList *cautare = initial->next;
        while( cautare != NULL )
        {
            if( tras == cautare->traseu )
                printf( "%s-%s\n", initial->symbol, cautare->symbol );
            cautare=cautare->next;
        }
        initial = initial->next;
    }

}

int main()
{
    TreeNode *root = NULL;
    TreeNode *poz[ 10 ];
    creare_arbore( "date.in", &root, poz );
    oglindite( root );

    return 0;
}