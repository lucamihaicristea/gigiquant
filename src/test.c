    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>

    struct Node {
        double val;
        double rand;
        struct Node* next;
    };

    int main( int argc, char *argv[] )
    {
        int n, i, nrrand = 0;
        double pret, sumrand = 0.0, rm, sump = 0.0, sharpe, sigma;
        struct Node *head = NULL, *tail = NULL;

        FILE *fin = fopen( argv[ 1 ], "r" );
        fscanf( fin, "%d", &n );

        if( n < 2 )
            return 1;

        for( i = 0; i < n; i++ )
        {
            fscanf( fin, "%lf", &pret );
            struct Node* nod = (struct Node*)malloc(sizeof( struct Node ) );
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

        struct Node *prev = head;
        struct Node *curr = head->next;

        while( curr != NULL )
        {
            curr->rand = ( curr->val - prev->val ) / prev->val;
            sumrand = sumrand + curr->rand;
            nrrand++;
            prev = curr;
            curr = curr->next;
        }

        rm = sumrand / nrrand;

        curr=head->next;
        while( curr != NULL )
        {
            sump = sump + ( curr->rand - rm ) * ( curr->rand - rm );
            curr = curr->next;
        }

        sigma = sqrt( sump / nrrand );
        sharpe = rm / sigma;

        rm = trunc( rm * 1000.0 ) / 1000.0;
        sigma = trunc( sigma * 1000.0 ) / 1000.0;
        sharpe = trunc( sharpe * 1000.0 ) / 1000.0;

        FILE *fout = fopen( argv[ 2 ], "w" );
        if( fout == NULL )
            return 1;

        fprintf( fout, "%.3lf\n", rm );
        fprintf( fout, "%.3lf\n", sigma );
        fprintf( fout, "%.3lf\n", sharpe );
        
        curr = head;
        while( curr != NULL )
        {
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }

        fclose(fin);
        fclose( fout );

        return 0;
    }