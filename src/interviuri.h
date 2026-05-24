#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Node {
    double val;
    double rand;     
    struct Node* next;
};

struct Node *citire1( FILE *fin, int n );
void freee( struct Node *head );
void calcul_rand( struct Node *head );
double calcul_rm( const struct Node *head, int nrrand );
double calcul_sigma( const struct Node *head, double rm, int nrrand );

struct nod{
    float val;
    struct nod *next;
};
typedef struct nod nod;

struct opor{
    float val;
    int zi;
    char loc[ 20 ];
    struct opor *next;
};
typedef struct opor opor;

struct Q{
    opor *front, *rear;
};
typedef struct Q queue;

static void push( nod **top, float v );
float pop( nod **top );
void delete( nod **top );
queue *createqueue();
void enqueue( queue *q, float v, int ziua, const char *local );
void dequeue( queue *q, float *v, int *ziua, char *local );
void deletequeue( queue *q );
void citire2( FILE *fin, char *locatie, nod **top );

typedef struct StockList {
    char symbol[ 10 ];
    float val; //pretul din ziua precedenta, care va fi actualizat la fiecare zi
    int traseu; //traseul pe care il face stock ul in arbore, pentru a gasi mai usor oglinditul
    struct StockList *next;
} StockList;

typedef struct TreeNode {
    StockList *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void creare_arbore( FILE *fin, TreeNode **root, TreeNode *poz[ 10 ] );
void oglindite( const TreeNode *root, FILE *fout );
void free_arbore( TreeNode *root );

typedef struct{
    int numarator;
    int numitor;
}frac;

typedef struct{
    frac precedent;
    frac curent;
}stare;

int cmmdc( int a, int b );
void simplificare( frac *f );
frac inmultire( frac a, frac b );
frac adunare( frac a, frac b);
int *secv( FILE *fin, int *n, float *d, int *minim, int *maxim, float *pstart, float *ptarget, int *k);
frac **mat_tranzitie( int *v, int n, float d, int minim, int maxim, int *nr);
void probabilitati( FILE *fout, frac **map, int nr, int k, float pstart, float ptarger, float d, int minim );
void eliberare( int *v, frac **map, int nr );