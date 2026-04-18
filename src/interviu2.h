#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void push( nod **top, float v );
float pop( nod **top );
void delete( nod **top );
queue *createqueue();
void enqueue( queue *q, float v );
void dequeue( queue *q );
void deletequeue( queue *q );
nod citire( const char* fisier, char *locatie, nod **top );