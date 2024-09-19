/*
16. Implementare un programma parallelo per
l’ambiente multicore con nq×np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve costruire
una matrice A, di dimensione M×N, i cui blocchi sono
generati casualmente e in parallelo da ogni core.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int M,N,np,nq;
    printf("Quanti thread vuoi sulle righe?\n");
    scanf("%d",&nq);
    printf("Quanti thread vuoi sulle colonne?\n");
    scanf("%d",&np);
    printf("QUante righe vuoi?\n");
    scanf("%d",&M);
    printf("QUante colonne vuoi?\n");
    scanf("%d",&N);

    int** A = (int**) calloc (M,sizeof(int*));
    for (int i=0;i<M;i++){
        A[i]=(int*) calloc (N,sizeof(int));
    }

    

    double start= omp_get_wtime();

    #pragma omp parallel for num_threads(nq*np)
    for (int bi=0;bi<nq;bi++){
        for (int bj=0;bj<np;bj++){
            int start_rige=bi*nq;
            int start_colonne=bj*np;
            int end_righe=(bi+1)*nq;
            int end_colonne=(bj+1)*np;
            if (bi==np-1){
                end_righe=M;
            }
            if (bj==np-1){
                end_colonne=N;
            }
            for (int i=start_rige;i<end_righe;i++){
                for (int j=start_colonne;j<end_colonne;j++){
                    A[i][j] = rand() % 9;
                }
            }
        }
    }

    double end=omp_get_wtime();

    printf("Tempo impiegato: %f\n",end-start);

    printf("Questa è la matrice:\n");

    for (int i=0;i<M;i++){
        for (int j=0;j<N;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<M;i++){
        free(A[i]);
    }

    free(A);
    printf("\n");

    return 0;
}