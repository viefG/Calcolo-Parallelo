/*
11. Implementare un programma parallelo per
l’ambiente multicore con np×np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve generare
una matrice A di dimensione N×N. Quindi, ogni core
deve sommare tra loro gli elementi di un blocco
quadrato della matrice A di dimensione (N/np)×(N/np),
conservando i valori in un vettore b.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int N,np;
    printf("Quanto la vuoi grande la matrice?\n");
    scanf("%d",&N);
    printf("Quanti thread vuoi?\n");
    scanf("%d",&np);

    int** A = (int**) calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        A[i] = (int*) calloc (N,sizeof(int));
    }

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            A[i][j]=rand() % 9;
        }
    }

    int* b=(int*) calloc (np*2,sizeof(int));
    

    int size=N/np;

    double start=omp_get_wtime();

    

    #pragma omp parallel for num_threads(np)
    for (int bi=0;bi<np;bi++){
        for (int bj=0;bj<np;bj++){
            int start_riga=bi*size;
            int start_colonne=bj*size;
            int end_riga=(bi+1)*size;
            int end_colonne=(bj+1)*size;
            for (int i=start_riga;i<end_riga;i++){
                for (int j=start_colonne;j<end_colonne;j++){
                    int indice_b = bi * np + bj; 
                    b[indice_b]+=A[i][j];
                }
            }
        }
    }
        
    double end=omp_get_wtime();

    printf("Questo è il tempo impiegato: %f\n",end-start);

    printf("Questa è la matrice iniziale:\n");

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    printf("Questo è il vettore finale contenente la somma di ogni blocco:\n");

    for (int i=0;i<np*2;i++){
        printf("%d ",b[i]);
    }

    for (int i=0;i<N;i++){
        free(A[i]);
    }

    printf("\n");

    free(A);
    free(b);

    return 0;
}