/*
2. Implementazione di un algoritmo parallelo (np core)
per il calcolo dell’operazione c=alpha*a+b, con a,b
vettori di dimensione N e alpha uno scalare, in
ambiente openMP
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int N,np,alpha;

    printf("Quanto vuoi che siano grandi i vettori 'a' e 'b'?\n");
    scanf("%d",&N);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);
    printf("Dai un valore ad alpha\n");
    scanf("%d",&alpha);

    int* a = (int*) calloc (N,sizeof(int));
    int* b = (int*) calloc (N,sizeof(int));
    int* c = (int*) calloc (N,sizeof(int));

    for (int i=0;i<N;i++){
        a[i] = rand() % 9;
        b[i] = rand() % 9;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np)
    for (int i=0;i<N;i++){
        c[i] = (alpha*a[i])+b[i];
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è %f\n",end-start);

    printf("Questo è il vettore a: ");

    for (int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    printf("\nQuesto è il vettore b: ");

    for (int i=0;i<N;i++){
        printf("%d ",b[i]);
    }

    printf ("\nQuesto è il vettore C (alpha*a)+b\n");

    for (int i=0;i<N;i++){
        printf("%d ",c[i]);
    }

    printf("\n");

    free(a);
    free(b);
    free(c);





    return 0;
}