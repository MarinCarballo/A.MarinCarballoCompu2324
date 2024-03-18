#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int random_int_number(int range, int seed);
int main()
{
    int m,i,n;

    printf("Numeros aleatorios:");
    scanf("%i", &m);
        for(i=0; i<m; i++)
        {
             n=random_int_number(100, 4322*i);
             printf("%i \n", n);
        }
    return 0;
}
int random_int_number(int range, int seed){
    // Establecer la semilla para la generación de números aleatorios
    srand(seed);

    // Generar un número aleatorio dentro del rango especificado
    int random_number = rand() % range;

    return random_number;
}