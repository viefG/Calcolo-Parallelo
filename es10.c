/*
10. Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere
una matrice di dimensione N×M, quindi i core devo
collaborare per sommare in parallelo i vettori
corrispondenti alle righe dispari della matrice.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int N,M,np;
    printf("Quanto righe vuoi che abbia la matrice?\n");
    scanf("%d",&N);
    printf("Quante colonne vuoi che abbia la matrice?\n");
    scanf("%d",&M);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int** A = (int**) calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        A[i] = (int*) calloc (M,sizeof(int));
    }

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            A[i][j]=rand() % 9;
        }
    }

    int somma=0;

    double start = omp_get_wtime();


    #pragma omp parallel for num_threads(np) reduction(+:somma)
    
    for (int i=1;i<N;i+=2){
        for (int j=0;j<M;j++){
            somma+=A[i][j];
        }
    }
    

    double end = omp_get_wtime();

    printf("Tempo impiegato %f\n",end-start);

    printf("Questa è la matrice:\n");

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    printf("Questa è la somma di tutta la matrice di tutte le righe dispari della matrice: %d\n",somma);

    for (int i=0;i<N;i++){
        free(A[i]);
    }

    free(A);

    return 0;
}