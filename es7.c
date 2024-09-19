/*
7. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×M. Quindi, i core
devono collaborare per calcolare il minimo tra gli
elementi delle colonne di propria competenza e
conservare tale valore in un vettore c di dimensione M.

Considerazioni personali:
L'output del codice stampa degli 0 quando il numero di thread (np) è inferiore al numero di colonne (M), il codice funziona
correttamente, ma la traccia dovrebbe essere con c di dimensioni np e non con c di dimensione M.
Motivo:
    Se ogni thread prende un gruppo do colonne e salva il numero minimo, ogni thread genererà un numero, quindi avrò n numeri
    tanto quanti sono i thread, quindi nel vettore c posso mettere np (numeor dei thread) numeri, gli altri non posso inventarmeli.
    per questo motivo c dovrebbe avere come size np.
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

    int* c = (int*) calloc (M,sizeof(int));

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            A[i][j] = (rand() % 9) + 1;
        }
    }

    int size=M/np;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(np)
    {   
        int elemento_minimo;
        int id = omp_get_thread_num();
        int start_righe=id*size;
        int end_righe=(id+1)*size;
        elemento_minimo=A[start_righe][0];
        if (id == np - 1) {
            end_righe = M;
        }
        for (int j=start_righe;j<end_righe;j++){
            for (int i=0;i<N;i++){
                if (A[i][j]<elemento_minimo){
                    elemento_minimo=A[i][j];
                }
            }
            
        }
       c[id] = elemento_minimo;

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

    printf("QUesto è il vettore c: ");

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