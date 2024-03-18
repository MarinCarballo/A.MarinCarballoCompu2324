#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//funcion para sumar dos vectores
void Sumar_Vec(double* v1, double* v2, int n);

int main()
{
    double m1[2]={0,1};
    double m2[2]={1,3};//defino vectores,
    double*v1=m1;
    double*v2=m2;//apunto los punteros al valor 0 del vector.
    Sumar_Vec(v1,v2, 2);//llamo a la funcion.
    int i;
    for(i=0; i<2; i++){
        printf("%lf, ", m1[i]);//compruebo el vector
    }
return 0;
}

void Sumar_Vec(double* v1, double* v2, int n){
    int i;
    for(i=0; i<n; i++){
        *(v1+i)=*(v1+i)+*(v2+i);//Esto hace que vaya aumentando las posiciones del puntero v1, mientras le voy sumando a cada posición el valor de v2.
    }
}