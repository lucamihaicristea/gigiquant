#include "interviuri.h"

// citeste 'n' preturi din fisier si salveaza intr o lista
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

// calculeaza randamentul pentru fiecare zi
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

// calculeaza randamentul mediu
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

// calculeaza deviatia standard
double calcul_sigma( const struct Node *head, double rm, int nrrand )
{
    double sump = 0.0;
    const struct Node *curr = head->next;
    while( curr != NULL )
    {            
        sump = sump + ( curr->rand - rm ) * ( curr->rand - rm ); // suma patratelor diferentelor dintre pret si medie
        curr = curr->next;
    }
    return sqrt( sump / nrrand );
}

// elibereaza memoria alocata
void freee( struct Node *head )
{
    while( head != NULL )
    {
        struct Node *temp = head;
        head = head->next;
        free( temp );
    }
}

// push pret in stiva
static void push( nod **top, float v )
{
    nod *newnod = (nod*)malloc( sizeof( nod ) );
    if( newnod == NULL )
        return;
    newnod->val = v;
    newnod->next = *top;
    *top = newnod;
}

// pop pret din stiva
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

// elibereaza memoria alocata stivei
void delete( nod **top )
{
    while( *top != NULL )
    {
        nod *temp = *top;
        *top=(*top)->next;
        free(temp);
    }
}

// citeste locatia si preturile si le pune intr o stiva
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

// creare coada
queue *createqueue()
{
    queue *q = (queue *)malloc( sizeof( queue ));
    if( q == NULL )
        return NULL;
    q->front=q->rear=NULL;
    return q;
}

// adaugare oportunitate in coada
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

// extragerea oportunitatii din coada
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

// elibereaza memoria alocata cozii
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

// adaugarea unei noi actiuni in lista unui nod din arbore
static void insert( StockList **head, const char stock[] )
{
    StockList *aux = *head;
    StockList *new = (StockList*)malloc( sizeof( StockList ));
    if( new == NULL )
        return;
    strncpy( new->symbol, stock, 9 );
    new->symbol[ 9 ] = '\0';
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

// crearea ramurii 
static TreeNode *calibrare_nod( TreeNode *root, int d )
{
    if( d == 1 )
    {
        if( root->left == NULL )
        {
            root->left = (TreeNode*)malloc(sizeof(TreeNode));
            if( root->left == NULL )
                return NULL;
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
                if( root->right == NULL )
                    return NULL;
                root->right->left = NULL;
                root->right->right = NULL;
                root->right->stocks = NULL;
            }
            return root->right;
        }
    return NULL;
}

// crearea arborelui in functie de preturile actiunilor in timp
void creare_arbore(FILE *fin, TreeNode **root, TreeNode *poz[ 10 ] ) 
{
    *root = (TreeNode*)malloc(sizeof(TreeNode));
    if(*root == NULL )
        return;
    (*root)->stocks = NULL;
    (*root)->left = NULL;
    (*root)->right = NULL;
    char nume_stockuri[ 100 ];
    fgets( nume_stockuri, sizeof( nume_stockuri ), fin );
    //separam numele actiunilor
    char *p = strtok( nume_stockuri, ",\n" );
    while( p != NULL )
    {
        insert( &((*root)->stocks), p );
        p = strtok( NULL, ",\n" );
    }
    float pret;
    int ok = 0; //flag prima zi
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
                //calculam drumul actiunilor prin arbore
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
                // repetam operatia pentru toate celelalte actiuni
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

// simetricul unui traseu
static int transformare( int nr )
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

// gaseste si afiseaza perechile de actiuni care au evoluat in mod perfect invers
void oglindite( const TreeNode *root, FILE *fout )
{
    if( root == NULL )
        return;
    const StockList *initial = root->stocks;
    int p = 1;
    while( initial != NULL )
    {
        int tras = transformare( initial->traseu );
        const StockList *cautare = initial->next;
        while( cautare != NULL )
        {
            if( tras == cautare->traseu )
            {
                if( p == 0 )
                    fprintf( fout, "\n" );
                
                fprintf( fout, "%s-%s", initial->symbol, cautare->symbol );
                p = 0;
            }
            cautare=cautare->next;
        }
        initial = initial->next;
    }

}

// eliberare lista de actiuni
static void free_lista( StockList *head )
{
    while( head != NULL )
    {
        StockList *aux = head;
        head = head->next;
        free(aux);
    }
}

// eliberare arbore post-ordine
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

// cel mai mare divizor comun
static int cmmdc( int a, int b )
{
    while( b != 0 )
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// aducerea la fractie ireductibila
static void simplificare( frac *f )
{
    int d = cmmdc( f->numarator, f->numitor );
    f->numarator  = f->numarator / d;
    f->numitor  = f->numitor / d;
}

// inmulteste doua fractii
static frac inmultire( frac a, frac b )
{
    frac c;
    c.numarator = a.numarator * b.numarator;
    c.numitor = a.numitor * b.numitor;
    simplificare( &c );
    return c;
}

// aduna doua fractii
static frac adunare( frac a, frac b )
{
    frac c;
    c.numarator = a.numarator * b.numitor + b.numarator * a.numitor;
    c.numitor = a.numitor * b.numitor;
    simplificare( &c );
    return c;
}

//citeste si grupeaza preturile in intervale
int *secv( FILE *fin, int *n, float *d, int *minim, int *maxim, float *pstart, float *ptarget, int *k)
{
    fscanf( fin, "%d", n );
    fscanf( fin, "%f", d );
    fscanf( fin, "%d", k );
    fscanf( fin, "%f", pstart );
    fscanf( fin, "%f", ptarget );

    int *v = (int*)malloc( (*n) * sizeof( int));
    if( v == NULL )
        return NULL;
    *minim = 999999999;
    *maxim = 0;
    for( int i = 0; i < *n; i++ )
    {
        float x;
        fscanf( fin, "%f", &x );
        int y = (int)( x / (*d))*(int)(*d); // transformarea in int
        v[ i ] = y;
        if( y > *maxim )
            *maxim = y;
        if( y < *minim)
            *minim = y;
    }
    return v;
}

// crearea matricei de tranzitie a starilor
frac **mat_tranzitie( const int *v, int n, float d, int minim, int maxim, int *nr)
{
    int i, j;
    *nr = ( maxim - minim ) / (int)(d) + 1; // nr total de stari
    frac **map = (frac**)malloc( (*nr) * sizeof( frac*));
    if( map == NULL )
        return NULL;
    for( i = 0; i < (*nr); i++ )
    {
        map[ i ] = (frac*)malloc( (*nr) * sizeof( frac ) );
        if( map[ i ] == NULL )
            return NULL;
        for( j = 0; j < (*nr); j++ )
        {
            map[ i ][ j ].numarator = 0;
            map[ i ][ j ].numitor = 1;
        }
    }

    int *iesiri = calloc( (*nr), sizeof( int )); // calculam cate iesire eista din fiecare stare
    if( iesiri == NULL )
        return NULL;
    for( i = 0; i < n - 1; i++ )
    {
        int a = ( v[ i ] - minim ) / (int)d; // stare azi
        int m = ( v[ i + 1 ] - minim ) / (int)d; // stare maine
        map[ a ][ m ].numarator += 1; // intrari in acel nod 
        iesiri[ a ] += 1; // total iesiri nod
    }

    // transformam intrarile in fractii
    for( i = 0; i < (*nr); i++ )
    {
        if( iesiri[ i ] > 0 )
            for( j = 0; j < (*nr); j++ )
            {
                if( map[ i ][ j ].numarator > 0 )
                    {
                        map[ i ][ j ].numitor = iesiri[ i ]; // intrari din nodul i in j / nr total iesiri
                        simplificare( &map[ i ][ j ] );
                    }
            }
    }
    free( iesiri );
    return map;
}

// aflarea probabilitatii atingerii unui pret tinta
void probabilitati( FILE *fout, frac **map, int nr, int k, float pstart, float ptarget, float d, int minim )
{
    int i, j;
    // index start si target
    int pst = ((int)(pstart/d)* (int)d - minim) / (int)d;
    int pta = ((int)(ptarget/d)* (int)d - minim) / (int)d;

    int ok1, ok2;
    if( pst >= 0 && pst < nr )
        ok1 = 1;
    else
        ok1 = 0;
    if( pta >= 0 && pta < nr )
            ok2 = 1;
        else
            ok2 = 0;
    //vector cu stari curente si precedente pentru fiecare zi
    stare *prob = (stare*)calloc( nr, sizeof( stare));
    if( prob == NULL )
        return;
    for( i = 0; i < nr; i++ )
    {
        prob[ i ].precedent.numarator = 0;
        prob[ i ].precedent.numitor = 1;
        prob[ i ].curent.numarator = 0;
        prob[ i ].curent.numitor = 1;
    }
    if( ok1 == 1 )
        prob[ pst ].precedent.numarator = 1; // probabilitatea starii initiale 1
    
    int a = 0;
    int b = 1;
    if( ok1 && ok2 )
    {
        a = prob[ pta ].precedent.numarator;
        b = prob[ pta ].precedent.numitor;
    }
    if( !ok1 || !ok2 || a == 0 )
        fprintf( fout, "0\n" );
    else if( a == b )
        fprintf( fout, "1\n");
    else
        fprintf(fout, "%d/%d\n", a, b );

    // k zile
    for( int z = 1; z < k; z++ )
    {   
        if( ok1 == 1 )
        {

            for( i = 0; i < nr; i++ )
            {
                if( prob[ i ].precedent.numarator > 0 )
                {
                    for( j = 0; j < nr; j++ )
                        if( map[ i ][ j ].numarator > 0 )
                            {
                                frac tran = inmultire( prob[ i ].precedent, map[ i ][ j ] );
                                prob[ j ].curent = adunare( prob[ j ].curent, tran );
                            }
                }
            }
            // pregatim starea precedenta pentru urmatoarea zi
            for( i = 0; i < nr; i++ )
            {
                prob[ i ].precedent = prob[ i ].curent;
                prob[ i ].curent.numarator = 0;
                prob[ i ].curent.numitor = 1;
    
            }
        }
        
        // afisarea probabilitatii target
        a = 0;
        b = 1;
        if( ok1 && ok2 )
        {
            a = prob[ pta ].precedent.numarator;
            b = prob[ pta ].precedent.numitor;
        }
        if( !ok1 || !ok2 || a == 0 )
            fprintf( fout, "0" );
        else if( a == b )
            fprintf( fout, "1");
        else
            fprintf(fout, "%d/%d", a, b );

        if( z != k - 1 )
            fprintf( fout, "\n" );
    }

    free( prob );      
}

// eliberare matrice de tranzitii si vectorul ce continea secventa
void eliberare( int *v, frac **map, int nr )
{
    free( v );
    for( int i = 0; i < nr; i++ )
        free( map[ i ]);
    free( map );
}
