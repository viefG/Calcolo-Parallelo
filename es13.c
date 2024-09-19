/*
13. Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master generare una
matrice A di dimensione M×M. Quindi, i core devo
collaborare valutare il minimo valore tra gli elementi di
A e successivamente costruire la matrice B i cui
elementi sono dati dalla somma di tale valore minimo
per gli elementi di posto corrispondente della matrice
di partenza.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int M,np;
    printf("Quanto vuoi che sia grande la matrice?\n");
    scanf("%d",&M);
    printf("Quanti thread vuoi?\n");
    scanf("%d",&np);

    int** A=(int**) calloc (M,sizeof(int*));
    for (int i=0;i<M;i++){
        A[i] = (int*) calloc (M,sizeof(int));
    }

    int** B=(int**) calloc (M,sizeof(int*));
    for (int i=0;i<M;i++){
        B[i] = (int*) calloc (M,sizeof(int));
    }

    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            A[i][j] = (rand() % 8)+1;
        }
    }

    int minimo=A[0][0];

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np) reduction (min:minimo)
    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            if (A[i][j]<minimo){
                minimo=A[i][j];
            }
        }
    }

    #pragma omp parallel for num_threads(np)
    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            B[i][j]=A[i][j]+minimo;
        }
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è: %f\n",end-start);

    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }   

    printf("Qursto è il valore minimo trovato: %d\n",minimo);

    printf("Questa è la matrice B, ottenuta sommando la matrice A con il valore minimo:\n");

    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            printf("%d ",B[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<M;i++){
        free(A[i]);
        free(B[i]);
    }

    free(A);
    free(B);
    printf("\n");

    return 0;
}