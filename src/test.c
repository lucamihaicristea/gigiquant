#include "interviu1.h"

int main( int argc, const char *argv[] )
{
    int n, nrrand;
    double rm, sigma, sharpe;
    struct Node *head = citire( argv[ 1 ], &n );
    nrrand = n - 1;

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

    return 0;
}