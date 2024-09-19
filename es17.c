/*
17. Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere
quattro valori scalari a0, a1, a2, a3, quindi i core devono
collaborare per costruire un vettore di dimensione 4np
i cui elementi sono dati dalla somma di tali valori con il
proprio identificativo.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int a0,a1,a2,a3,np;
    printf("Dai un valore allo scalare a0:\n");
    scanf("%d",&a0);
    printf("Dai un valore allo scalare a1:\n");
    scanf("%d",&a1);
    printf("Dai un valore allo scalare a2:\n");
    scanf("%d",&a2);
    printf("Dai un valore allo scalare a3:\n");
    scanf("%d",&a3);
    printf("Quanti thread vuoi usare?\n");
    scanf("%d",&np);

    int* vettore = (int*) calloc (4*np,sizeof(int));

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(np)
    {
        int id=omp_get_thread_num();
        int posizione=id*4;
        vettore[posizione]=a0+id;
        vettore[posizione+1]=a1+id;
        vettore[posizione+2]=a2+id;
        vettore[posizione+3]=a3+id;
    }

    double end = omp_get_wtime();

    printf("Tempo impiegato: %f \n",end-start);

    printf("Questo è il vettore finale: ");
    for (int i=0;i<4*np;i++){
        printf("%d ",vettore[i]);
    }

    free(vettore);

    printf("\n");


    return 0;
}