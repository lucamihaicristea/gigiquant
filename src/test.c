#include "interviu2.h"

int main( int argc, const char *argv[] )
{
    nod *s1, *s2, *s3;
    char loc1[ 20 ], loc2[ 20 ], loc3[ 20 ];
    queue *q = createqueue();

    FILE *fin = fopen( argv[ 1 ], "r" );
    if( fin == NULL )
        return 1;

    citire( fin, loc1, &s1 );
    citire( fin, loc2, &s2 );
    citire( fin, loc3, &s3 );
    fclose( fin );
    while( s1 != NULL && s2 != NULL && s3 != NULL )
    {
        float v1, v2, v3;
        v1 = pop( &s1 );
        v2 = pop( &s2 );
        v3 = pop( &s3 );
        if( p1 == p2 && p2 != p3 )
        {
            if( p2 > p3 )
        }

    }

    return 0;
}

