/*
5. Implementare un programma parallelo per l’ambiente
multicore con np unità processanti che impieghi la
libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice di dimensione N×N, ogni core deve
estrarre N/np righe e calcolare il prodotto puntuale tra
i vettori corrispondenti alle righe estratte.
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

    int size=N/np;

    int** matrice = (int**) calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        matrice[i] = (int*) calloc (N,sizeof(int));
    }

    int* vettore = (int*) calloc (N,sizeof(int));

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            matrice[i][j] = (rand() % 8) + 1;
        }
    }

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("%d ",matrice[i][j]);
        }
        printf("\n");
    }

    double start = omp_get_wtime();

    

    #pragma omp parallel num_threads(np)
    {
        int* vettore = (int*) calloc (N,sizeof(int));
        long long int prodotto=1;
        int id = omp_get_thread_num();
        int start_riga = id*size;
        int end_riga = (id+1)*size;
        if (id==np-1){
            end_riga=N;
        }
        for (int i=start_riga;i<end_riga;i++){
            for (int j=0;j<N;j++){
                vettore[j] = matrice[i][j];
            }
            for(int i=0;i<N;i++){
                prodotto=prodotto*vettore[i];
            }
        }
        
        printf("sono il thread %d e questo è il prodtto %lld\n",id,prodotto);
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è: %f\n",end-start);



    




    return 0;
}