/*
15. Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere un
vettore a, di dimensione M, e uno scalare alpha. Quindi
i core devono collaborare per costruire una matrice A,
di dimensione M×M, la cui diagonale principale ha per
elementi quelli del vettore a moltiplicati per lo scalare
alpha.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int M,alpha,np;
    printf("Quanto vuoi che si grande il vettore?\n");
    scanf("%d",&M);
    printf("dai un valore ad alpha\n");
    scanf("%d",&alpha);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int** A=(int**) calloc (M,sizeof(int*));
    for (int i=0;i<M;i++){
        A[i] = (int*) calloc (M,sizeof(int));
    }

    int* a = (int*) calloc (M,sizeof(int));


    for (int i=0;i<M;i++){
        a[i]=rand()%9;
        for (int j=0;j<M;j++){
            A[i][j] = (rand() % 8)+1;
        }
    }


    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np)
    for (int i=0;i<M;i++){
        A[i][i] = a[i] * alpha;
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è: %f\n",end-start);

    printf("Vettore a: ");
    for (int i=0;i<M;i++){
        printf("%d ",a[i]);
    }

    printf("Matrice A con la diagonale che è uguale la vettore a per lo scalare %d\n",alpha);

    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<M;i++){
        free(A[i]);
    }

    free(A);
    free(a);
    printf("\n");


    return 0;
}