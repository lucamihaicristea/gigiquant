#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    double val;
    double rand;     
    struct Node* next;
};

struct Node *citire( const char *fisier, int *n );
void freee( struct Node *head );
void calcul_rand( struct Node *head );
double calcul_rm( struct Node *head, int nrrand );
double calcul_sigma( struct Node *head, double rm, int nrrand );