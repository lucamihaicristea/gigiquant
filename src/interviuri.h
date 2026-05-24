#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// task 1
struct Node {
    double val; //pretul actiunii
    double rand; //randamentul
    struct Node* next;
};

struct Node *citire1( FILE *fin, int n );
void freee( struct Node *head );
void calcul_rand( struct Node *head );
double calcul_rm( const struct Node *head, int nrrand );
double calcul_sigma( const struct Node *head, double rm, int nrrand );

// task 2
struct nod{ 
    float val;
    struct nod *next;
};
typedef struct nod nod; //structura pentru stiva 

struct opor{
    float val;
    int zi;
    char loc[ 20 ];
    struct opor *next;
};
typedef struct opor opor;
// structura pentru coada
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

// task 3
typedef struct StockList {
    char symbol[ 10 ];
    float val; //pretul din ziua precedenta, care va fi actualizat la fiecare zi
    int traseu; //traseul pe care il face stock ul in arbore, pentru a gasi mai usor oglinditul
    struct StockList *next;
} StockList;

typedef struct TreeNode {
    StockList *stocks; // lista de actiuni la fiecare nod
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode; // structura pentru arbore

void creare_arbore( FILE *fin, TreeNode **root, TreeNode *poz[ 10 ] );
void oglindite( const TreeNode *root, FILE *fout );
void free_arbore( TreeNode *root );

// task 4
typedef struct{
    int numarator;
    int numitor;
}frac; // structura pentru fractie

typedef struct{
    frac precedent;
    frac curent;
}stare; // structura pentru starea curenta si cea precedenta

int *secv( FILE *fin, int *n, float *d, int *minim, int *maxim, float *pstart, float *ptarget, int *k);
frac **mat_tranzitie( const int *v, int n, float d, int minim, int maxim, int *nr);
void probabilitati( FILE *fout, frac **map, int nr, int k, float pstart, float ptarget, float d, int minim );
void eliberare( int *v, frac **map, int nr );