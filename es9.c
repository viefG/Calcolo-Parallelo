/*
9. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
due vettori casuali di dimensione N. Ogni core deve
sommare ad ogni elemento dei due vettori il proprio
identificativo e collaborare alla costruzione di una
matrice, di dimensione N×M, con M=2np, le cui
colonne, a due a due, sono i due vettori ottenuti nella
fase precedente.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int N,np;
    printf("Segli la dimensione deli vettori: \n");
    scanf("%d",&N);
    printf("Scegli quanti thread usare:\n");
    scanf("%d",&np);

    int* a = (int*) calloc (N,sizeof(int));

    int* b = (int*) calloc (N,sizeof(int));

    int M=np*2;

    int** matrice = calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        matrice[i]=(int*) calloc (M,sizeof(int));
    }

    for (int i=0;i<N;i++){
        a[i]=rand()%9;
        b[i]=rand()%9;
    }

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(np)
    {
        int id = omp_get_thread_num();
        int start= id*2;
        for (int i=0;i<N;i++){
            matrice[i][start]=a[i]+id;
            matrice[i][start+1]=b[i]+id;
        }    
    }

    double end=omp_get_wtime();

    printf("Il tempo impiegato è: %f\n",end-start);

    printf("Il vettore a: ");

    for (int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    printf("\nIl vettore b: ");

    for (int i=0;i<N;i++){
        printf("%d ",b[i]);
    }

    printf("\nLa matrice finale:\n");

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            printf("%d ",matrice[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<N;i++){
        free(matrice[i]);
    }

    free(matrice);
    free(a);
    free(b);

    printf("\n");

    return 0;
}