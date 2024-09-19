/*
6. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere
una matrice A di dimensione N×N ed uno scalare alpha.
Quindi, i core devono collaborare per calcolare il
prodotto tra lo scalare alpha e la matrice A, sfruttano
una strategia di parallelizzazione che usi la
distribuzione per colonne della matrice A come
decomposizione del dominio.

Considerazioni personali:
Anche in questo esercizio come l'esercizio numero 1 c'e' un'ambiguità, non ci capesce se il risultato dato dal prodotto del vettore A
con lo scalare alpha debba essere uno sclare o una matrice; come ho fatto per l'esercizio numero 1 farò entrambe le implementazioni,
in questo file farò l'implementazione nel caso in cui il risultato sia una matrice es B[0][0] = A[0][0] * alpha; mentre nel file es6_v2.c
farò la versinoe nel caso in cui il risultato fosse uno scalare.
*/





#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int N,alpha,np;
    printf("Quanto vuoi che sia grande la matrice?\n");
    scanf("%d",&N);
    printf("Quanto vale lo scalare alpha\n");
    scanf("%d",&alpha);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int** A = (int**) calloc (N,sizeof(int*));
    for (int i = 0; i < N; i++){
        A[i] = (int*) calloc (N,sizeof(int));
    }

    int** B = (int**) calloc (N,sizeof(int*));
    for (int i = 0; i < N; i++){
        B[i] = (int*) calloc (N,sizeof(int));
    }

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            A[i][j] = rand() % 9;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads (np)
    for (int j=0;j<N;j++){
        for (int i=0;i<N;i++){
            B[i][j] = A[i][j] * alpha;
        }
    }

    double end = omp_get_wtime();
    printf("Il tempo impiegato è: %f\n",end-start);

    printf("Questa è la matrice A:\n");

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    printf("Questa è la matrice finale ottenuta moltiplicando A con lo scalare %d:\n",alpha);

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("%d ",B[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<N;i++){
        free(A[i]);
        free(B[i]);
    }

    free(A);
    free(B);
    printf("\n");


    

    return 0;
}