/*
8. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×M. Quindi, ogni core
deve estrarre N/p colonne ed effettuare localmente la
somma degli elementi delle sottomatrici estratte,
conservando il risultato in un vettore b di dimensione
M.

Considerazioni personali:
L'output del codice stampa degli 0 quando il numero di thread (np) è inferiore al numero di colonne (M), il codice funziona
correttamente, ma la traccia dovrebbe essere con b di dimensioni np e non con b di dimensione M.
Motivo:
    STESSA SITUAZIONE DELL'ES7.C
    Se ogni thread prende un gruppo do colonne e ne fa la somma, ogni thread genererà un numero, quindi avrò n numeri
    tanto quanti sono i thread, quindi nel vettore b posso mettere np (numeor dei thread) numeri, gli altri non posso inventarmeli.
    per questo motivo b dovrebbe avere come size np.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
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

    int* b = (int*) calloc (M,sizeof(int));

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            A[i][j] = (rand() % 9) + 1;
        }
    }

    int size=N/np;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(np)
    {
        int id = omp_get_thread_num();
        int somma=0;
        int start = id*size;
        int end = (id+1)*size;
        if (id==np-1){
            end=M;
        }
        for (int j=start;j<end;j++){
            for (int i=0;i<N;i++){
                somma+=A[i][j];
                printf("Test somma: %d\n",somma);
            }
        }
        b[id] = somma;
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

    printf("Questo è il vettore b: ");

    for (int i=0;i<M;i++){
        printf("%d ",b[i]);
    }

    for (int i=0;i<N;i++){
        free(A[i]);
    }

    free(A);
    free(b);

    printf("\n");

    return 0;
}