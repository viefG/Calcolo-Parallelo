/*
14. Implementare un programma parallelo per
l’ambiente multicore con np×np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere
una matrice A di dimensione M×M. Quindi, ogni core
deve estrarre un blocco della matrice A di dimensione
(M/np)×(M/np), conservando i valori in np×np matrici.
Infine, i core devono collaborare per calcolare la
somma di tali matrici.

Considerazioni personali:
La traccia mi chede di prendere i valore di un blocco M/np x M/np e di conservarli in una matrice np x np ma il mi dubbio è:
se per esempio M vale 6 e np 2 allora dovrei conservare i valore del blocco 6/2= 3x3 in un blocco 2x2 quindi impossibile
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int M,np;
    printf("Quanto la vuoi grande la matrice?\n");
    scanf("%d",&M);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int** A=(int**) calloc (M,sizeof(int*));
    for (int i=0;i<M;i++){
        A[i] = (int*) calloc (M,sizeof(int));
    }

    int** B=(int**) calloc (np,sizeof(int*));
    for (int i=0;i<np;i++){
        B[i] = (int*) calloc (np,sizeof(int));
    }


    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            A[i][j] = (rand() % 8)+1;
        }
    }

    int size= M/np;

    double start= omp_get_wtime();
    int somma=0;

    #pragma omp parallel for num_threads(np) private (somma)
    for (int bi=0;bi<np;bi++){
        for (int bj=0;bj<np;bj++){
            int start_riga=bi*size;
            int start_colonne=bj*size;
            int end_riga=(bi+1)*size;
            int end_colonna=(bj+1)*size;
            if (bi == np - 1) {
            end_riga = M;
            }
            if (bj == np - 1) {
                end_colonna = M;
            }
            for (int i=start_riga;i<end_riga;i++){
                for (int j=start_colonne;j<end_colonna;j++){
                    B[bi][bj]+=A[i][j];
                }
            }
        }
    }

    double end = omp_get_wtime();

     printf("Il tempo impiegato è: %f\n",end-start);

     printf("Qursta è la matrice A:\n");

    for (int i=0;i<M;i++){
        for (int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }   


    printf("Questa è la matrice B:\n");

    for (int i=0;i<np;i++){
        for (int j=0;j<np;j++){
            printf("%d ",B[i][j]);
        }
        printf("\n");
    }

    for (int i=0;i<M;i++){
        free(A[i]);
    }

    for (int i=0;i<np;i++){
        free(B[i]);
    }

    free(A);
    free(B);
    printf("\n");




    return 0;
}