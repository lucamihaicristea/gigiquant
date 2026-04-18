#include "interviu2.h"

int main( int argc, const char *argv[] )
{
    nod *s1 = NULL, *s2 = NULL, *s3 = NULL;
    char loc1[ 20 ], loc2[ 20 ], loc3[ 20 ], loc[ 20 ];
    queue *q = createqueue();
    int zi = 1, z;
    float vl;

    if( argc < 3 )
        return 1;

    FILE *fin = fopen( argv[ 1 ], "r" );
    if( fin == NULL )
        return 1;
    printf( "incep citirea ");
    citire( fin, loc1, &s1 );
    printf( "citit prima stiva ");
    citire( fin, loc2, &s2 );
    printf( "citit prima stiva ");
    citire( fin, loc3, &s3 );
    printf( "citit prima stiva ");
    fclose( fin );
    while( s1 != NULL && s2 != NULL && s3 != NULL )
    {
        float v1, v2, v3;
        v1 = pop( &s1 );
        v2 = pop( &s2 );
        v3 = pop( &s3 );
        if( v1 == -1 || v2 == -1 || v3 == -1 )
            break;

        if( v1 == v2 && v2 != v3 )
        {
            enqueue( q, fabsf( v2 - v3 ), zi, loc3 );
        }
        else if( v2 == v3 && v1 != v2 )
        {
            enqueue( q, fabsf( v1 - v2 ), zi, loc1 );
        }
        else if( v1 == v3 && v1 != v2 )
        {
            enqueue( q, fabsf( v2 - v1 ), zi ,loc2 );
        }
        zi++;
    }
    FILE *fout = fopen( argv[ 2 ], "w" );
    if( fout == NULL )
    {
        delete( &s1 );
        delete( &s2 );
        delete( &s3 );
        deletequeue( q );
        return 1;
    }
    printf( "citit prima stiva ");
    while( q->front != NULL )
    {
        dequeue( q, &vl, &z, loc );
        fprintf( fout, "ziua %d - %.2f - %s\n", z, vl, loc );
    }
    printf( "citit prima stiva ");
    fclose( fout );

    delete( &s1 );
    delete( &s2 );
    delete( &s3 );
    deletequeue( q );

    return 0;
}

