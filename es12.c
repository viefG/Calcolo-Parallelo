/*
12. Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master generare una
matrice di dimensione N×M. Quindi, ogni core deve
estrarre la riga della matrice con indice uguale al
proprio identificativo e conservarla in un vettore locale;
successivamente deve sommare gli elementi di tale
vettore e conservare il risultato in un vettore c di
dimensione np. Infine, i core devo collaborare per
individuare in massimo tra gli elementi del vettore c.

Considerazioni personali:
nel #pragma omp parallel ho messo l'if perchè mi sono accorto che quando l'utente inserisce un numero maggiore ai thread che alle
righe della matrice, il programma da seg fault, con l'if mi sono assicurato che non accasa, nella stampa del vettore c ho messo come
size N invece di np perchè nel caso in cui np fosse maggire di N stamperebbe degli 0 inutili, con questo metodo si previene quel
comportamento.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int N,M,np;
    printf("Scegli il numero di righe:\n");
    scanf("%d",&N);
    printf("Scegli il numero di colonne:\n");
    scanf("%d",&M);
    printf("Quanti thread vuoi?:\n");
    scanf("%d",&np);

    int** A = (int**) calloc (N,sizeof(int*));
    for (int i=0;i<N;i++){
        A[i] = (int*) calloc (M,sizeof(int));
    }

    int* c = (int*)  calloc (np,sizeof(int));

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            A[i][j] = rand() % 9;
        }
    }

    int valore=0;

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(np)
    {   
        int id = omp_get_thread_num();
        if (id<N){
            int somma=0;
            int* temp = (int*) calloc (M,sizeof(int));
            for (int j=0;j<M;j++){
                temp[j]=A[id][j];
            }
            for (int i=0;i<M;i++){
                somma+=temp[i];
            }
            c[id]=somma;
        }
    }

    #pragma omp parallel for reduction (max:valore)
    for (int i=0;i<N;i++){
        if (valore<c[i]){
            valore=c[i];
        }
    }

    double end = omp_get_wtime();
    printf("Il tempo impiegato è: %f",end-start);

    printf("Questo è la matrice iniziale:\n");
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    printf("QUesto è il vettore c:\n");
    for (int i=0;i<N;i++){
        printf("%d ",c[i]);
    }

    printf("\nQuesto è il valore massimo: %d",valore);

    for (int i=0;i<N;i++){
        free(A[i]);
    }

    free(A);
    free(c);
    printf("\n");


    return 0;
}