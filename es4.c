/*
4. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti impieghi la libreria
OpenMP. Il programma deve essere organizzato come
segue: il core master deve leggere una matrice di
dimensione N×N, quindi i core devo collaborare per
ricopiare in parallelo gli elementi della diagonale
principale in un vettore di lunghezza N. Infine, i core
devono effettuare la somma degli elementi di tale
vettore in parallelo.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int N,np;
    printf("Quanto deve essere grande la matrice?\n");
    scanf("%d",&N);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int** matrice = (int**) calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        matrice[i] = (int*) calloc (N,sizeof(int));
    }

    int* vettore = (int*) calloc (N,sizeof(int));

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrice[i][j] = rand() % 9;
        }
    }
    int somma=0;

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np)
    for (int i=0;i<N;i++){
        vettore[i] = matrice[i][i];
    }
    #pragma omp parallel for reduction (+:somma)
    for (int i=0;i<N;i++){
        somma+=vettore[i];
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è %f",end-start);

    printf("QUesta è la matrice: \n");

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("%d ",matrice[i][j]);
        }
        printf("\n");
    }

    printf("Questo è il vettore ricopiato dalla diagonale della matrice:\n");

    for (int i=0;i<N;i++){
        printf("%d ",vettore[i]);
    }

    printf("\nQuesta è la somma di tutto il vettore: %d\n",somma);

    printf("\n");

    for (int i=0;i<N;i++){
        free(matrice[i]);
    }

    free(matrice);
    free(vettore);


    return 0;
}