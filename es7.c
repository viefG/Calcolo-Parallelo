/*
7. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×M. Quindi, i core
devono collaborare per calcolare il minimo tra gli
elementi delle colonne di propria competenza e
conservare tale valore in un vettore c di dimensione M.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(){
srand(time(NULL));
    int N,M,np;
    printf("Quante righe vuoi che abbia la tua matrice?\n");
    scanf("%d",&N);
    printf("Quante colonne vuoi che abbia la tua matrice?\n");
    scanf("%d",&M);
    printf("QUanti thread vuoi usare?\n");
    scanf("%d",&np);

    int** A=(int**) calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        A[i]=(int*) calloc (N,sizeof(int));
    }

    int* c=(int*) calloc (M,sizeof(int));

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            A[i][j] = (rand() % 8)+1;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np)
    for (int j=0;j<M;j++){
        c[j]=A[j][0];
        for (int i=0;i<N;i++){
            if (c[j]>A[i][j]){
                c[j]=A[i][j];
            }
        }
    }

    double end = omp_get_wtime();

    printf("Tempo impiegato: %f\n",end-start);

    printf("Matrice iniziale:\n");

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    printf("\nVettore finale:");
    for (int i=0;i<M;i++){
        printf("%d ",c[i]);
    }

    for (int i=0;i<N;i++){
        free(A[i]);
    }

    free(A);
    free(c);
    printf("\n");

    return 0;
}