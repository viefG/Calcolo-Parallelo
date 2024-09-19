/*
18. Implementare un programma parallelo per
l’ambiente multicore con np unità processanti che
impieghi la libreria OpenMP. Il programma deve essere
organizzato come segue: il core master deve leggere un
vettore a, di dimensione N ed uno scalare beta. Quindi
i core devo collaborare per verificare se nel vettore
esista almeno un elemento uguale al valore beta.
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

int main (){
    srand(time(NULL));
    int N,beta,np;
    printf("Quanto vuoi che sia lungo il vettore?\n");
    scanf("%d",&N);
    printf("Dai un valore allo scalare beta:\n");
    scanf("%d",&beta);
    printf("Quanti thread vuoi?\n");
    scanf("%d",&np);

    int* a = (int*) calloc (N,sizeof(int));

    for (int i=0;i<N;i++){
        a[i] = rand() % 9;
    }

    int controllo=0;

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(np)
    for (int i=0;i<N;i++){
        if (a[i]==beta){
            controllo=1;
        }
    }

    double end = omp_get_wtime();

    printf("Il tempo impiegato è: %f\n",end-start);

    printf("Questo è il vettore: ");

    for (int i=0;i<N;i++){
        printf("%d ",a[i]);
    }

    if (controllo==1){
        printf("\nLo scalare %d è presente all'interno del vettore",beta);
    } else{
        printf("\nLo scalare %d non è presente all'interno del vettore",beta);
    }

    free(a);
    printf("\n");

    return 0;
}