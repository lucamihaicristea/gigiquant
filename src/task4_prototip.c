#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int numarator;
    int numitor;
}frac;

typedef struct{
    frac precedent;
    frac curent;
}stare;

int cmmdc( int a, int b )
{
    while( b != 0 )
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void simplificare( frac *f )
{
    int d = cmmdc( f->numarator, f->numitor );
    f->numarator  = f->numarator / d;
    f->numitor  = f->numitor / d;
}

frac inmultire( frac a, frac b )
{
    frac c;
    c.numarator = a.numarator * b.numarator;
    c.numitor = a.numitor * b.numitor;
    simplificare( &c );
    return c;
}

frac adunare( frac a, frac b )
{
    frac c;
    c.numarator = a.numarator * b.numitor + b.numarator * a.numitor;
    c.numitor = a.numitor * b.numitor;
    simplificare( &c );
    return c;
}

int main()
{
    int n, minim = 999999999, maxim = 0, nr, i, j, k;
    float x, pstart, ptarget, d;
    scanf( "%d", &n );
    int *v = (int*)malloc( n * sizeof( int ) );
    scanf( "%f", &d );
    scanf( "%d", &k );
    scanf( "%f", &pstart );
    scanf( "%f", &ptarget );
    for( i = 0; i < n; i++ )
    {
        scanf( "%f", &x );
        int y = (int)(x / d);
        y = y * (int)(d);
        v[ i ] = y;
        if( maxim < y )
            maxim = y;
        if( minim > y )
            minim = y; 
    }
    nr = (maxim-minim)/(int)(d) + 1;
    frac **map = (frac**)malloc( nr * sizeof( frac*));
    for( i = 0; i < nr; i++ )
    {
        map[ i ] = (frac*)malloc( nr * sizeof( frac ));
        for( j = 0; j < nr; j++ )
            {
                map[ i ][ j ].numarator = 0;
                map[ i ][ j ].numitor = 1;
            }
    }
    int *iesiri = calloc( nr, sizeof( int));
    for( i = 0; i < n - 1; i++ )
    {
        int a = (v[ i ] - minim) / (int)d;
        int m = ( v[ i + 1 ] - minim ) / (int)d;

        map[ a ][ m ].numarator +=1;
        iesiri[ a ] += 1;
    }

    for( i = 0; i < nr; i++ )
    {
        if( iesiri[ i ] > 0 )
        {
            for( j = 0; j < nr; j++ )
            {
                if( map[ i ][ j ].numarator > 0 )
                {
                    map[ i ][ j ].numitor = iesiri[ i ];
                    simplificare( &map[ i ][ j ] );
                }
            }
        }
    }
    
    int pst = ((int)(pstart/d)* (int)d - minim) / (int)d;
    int pta = ((int)(ptarget/d)* (int)d - minim) / (int)d;

    stare *prob = (stare*)malloc( nr * sizeof( stare));
    for( i = 0; i < nr; i++ )
    {
        prob[ i ].precedent.numarator = 0;
        prob[ i ].precedent.numitor = 1;
        prob[ i ].curent.numarator = 0;
        prob[ i ].curent.numitor = 1;
    }

    prob[ pst ].precedent.numarator = 1;

    if( prob[ pta ].precedent.numarator == 0 && prob[ pta ].precedent.numitor == 1 )
        printf( "0\n");
    else if( prob[ pta ].precedent.numarator == prob[ pta ].precedent.numitor )
            printf( "1\n");
        else
            {
                printf( "%d/%d\n", prob[ pta ].precedent.numarator, prob[ pta ].precedent.numitor);
            }
    for( int z = 1; z < k; z++ )
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
        for( i = 0; i < nr; i++ )
        {
            prob[ i ].precedent = prob[ i ].curent;
            prob[ i ].curent.numarator = 0;
            prob[ i ].curent.numitor = 1;

        }
        if( prob[ pta ].precedent.numarator == 0 && prob[ pta ].precedent.numitor == 1 )
            printf( "0\n");
        else if( prob[ pta ].precedent.numarator == prob[ pta ].precedent.numitor )
                printf( "1\n");
            else
                {
                    printf( "%d/%d\n", prob[ pta ].precedent.numarator, prob[ pta ].precedent.numitor);
                }
    }

    return 0;
}