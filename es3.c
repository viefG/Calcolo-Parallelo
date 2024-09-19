/*
3. Implementazione di un algoritmo parallelo (np core)
per il calcolo degli elementi di un vettore c, i cui valori
sono ottenuti moltiplicando l’identificativo del core per
gli elementi di un vettore a di dimensione N, in
ambiente openMP
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int np,N;
    printf("Quanto vuoi che sia grande il vettore N\n");
    scanf("%d",&N);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int* a = (int*) calloc (N,sizeof(int));
    int* c = (int*) calloc (N,sizeof(int));

    for (int i=0;i<N;i++){
        a[i]=rand()%9;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np)
    for (int i=0;i<N;i++){
        int id = omp_get_thread_num();
        c[i] = a[i] * id;
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è %f\n",end-start);

    printf("Questo è il vettore a: ");

    for (int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    printf("\nQuesto è il vettore c: ");

    for (int i=0;i<N;i++){
        printf("%d ",c[i]);
    }

    printf("\n");

    free(a);
    free(c);



    return 0;
}