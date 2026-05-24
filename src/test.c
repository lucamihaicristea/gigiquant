#include "interviuri.h"

int main( int argc, const char *argv[] )
{
    if( argc < 3 )
        return 1;

    FILE *fin = fopen( argv[ 1 ], "r" );
    if( fin == NULL )
        return 1;

    char primalin[ 100 ];
    fgets( primalin, sizeof( primalin), fin );
    fseek( fin, 0, SEEK_SET);

    if( primalin[ 0 ] >= '0' && primalin[ 0 ] <= '9' )
    {
        int n, nrrand;
        fscanf( fin, "%d", &n );
        int cnt = 0;
        float temp;
        while( fscanf( fin, "%f", &temp ) == 1 )
            cnt++;
        fseek( fin, 0, SEEK_SET );
        if( cnt == n )
        {
            fscanf( fin, "%d", &n );
            double rm, sigma, sharpe;
            struct Node *head = citire1( fin, n );
            nrrand = n - 1;
            fclose( fin );
    
            calcul_rand( head );
            rm = calcul_rm( head, nrrand );
            sigma = calcul_sigma( head, rm, nrrand );
            sharpe = rm / sigma;
    
            rm = trunc( rm * 1000.0 ) / 1000.0;
            sigma = trunc( sigma * 1000.0 ) / 1000.0;
            sharpe = trunc( sharpe * 1000.0 ) / 1000.0;
    
            FILE *fout = fopen( argv[ 2 ], "w" );
            if( fout == NULL )
            {
                freee( head );
                return 1;
            }
    
            fprintf( fout, "%.3lf\n", rm );
            fprintf( fout, "%.3lf\n", sigma );
            fprintf( fout, "%.3lf\n", sharpe );
                
            freee( head );
            fclose( fout );
        }
        else
            {
                FILE *fout = fopen( argv[ 2 ], "w" );
                if( fout == NULL )
                {
                    fclose( fin );
                    return 1;
                }
                int n, k, minim, maxim, nr;
                float d, pstart, ptarget;
                int *v = secv( fin, &n, &d, &minim, &maxim, &pstart, &ptarget, &k);
                frac **map = mat_tranzitie( v, n, d, minim, maxim, &nr);
                probabilitati( fout, map, nr, k, pstart, ptarget, d, minim );
                eliberare( v, map, nr );
                fclose( fin );
                fclose( fout );
            }
    }
    else if ( strchr( primalin, ',' ) != NULL )
        {
            TreeNode *root = NULL;
            TreeNode *poz[ 10 ];
            creare_arbore( fin, &root, poz );
            fclose( fin );

            FILE *fout = fopen( argv[ 2 ], "w" );
            if( fout == NULL )
            {
                free_arbore( root );
                return 1;
            }
            oglindite( root, fout );

            fclose( fout );
            free_arbore( root );
        }
        else
            {
                nod *s1 = NULL, *s2 = NULL, *s3 = NULL;
                char loc1[ 20 ], loc2[ 20 ], loc3[ 20 ], loc[ 20 ];
                queue *q = createqueue();
                int zi = 1, z;
                float vl;
                
                citire2( fin, loc1, &s1 );
                citire2( fin, loc2, &s2 );
                citire2( fin, loc3, &s3 );
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
                while( q->front != NULL )
                {
                    dequeue( q, &vl, &z, loc );
                    fprintf( fout, "ziua %d - %.2f - %s\n", z, vl, loc );
                }
                fclose( fout );

                delete( &s1 );
                delete( &s2 );
                delete( &s3 );
                deletequeue( q );
            }

    return 0;
}

