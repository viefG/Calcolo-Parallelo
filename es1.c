/*
1. Implementazione di un algoritmo parallelo (np core)
per il calcolo dell’operazione c=a+b con a,b vettori di
dimensione N, in ambiente openMP

Considerazioni personali:
La traccia mi sembra leggermente ambigua, non capisco se C è uno scalare e quindi devo sommare i vettori a+b e mettere un risultato
scalare in c o se fare anche c come vettore e quindi sommare le posizione. Per non far mancare nulla farò entrambe le versioni,
faccio la versione in cui c sia un vettore qui e nel file es1_v2.c farò la versione in cui c sia uno scalare.
*/


#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(){
    srand(time(NULL));
    int np,N;
    printf("Quanto devono essere grandi i vettori a e b?\n");
    scanf("%d",&N);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);
    

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
        c[i] = a[i] + b[i];
    }

    double end = omp_get_wtime();

    printf("Questo è il tempo impiegato %f\n",end-start);

    printf("Questo è il vettore a: ");

    for (int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    printf("\nQuesto è il vettore b: ");

    for (int i=0;i<N;i++){
        printf("%d ",b[i]);
    }

    printf ("\nQuesto è il vettore C uscito sommando i numeri nelle rispettive posizioni di a + b:\n");

    for (int i=0;i<N;i++){
        printf("%d ",c[i]);
    }

    printf("\n");

    free(a);
    free(b);
    free(c);





    return 0;
}