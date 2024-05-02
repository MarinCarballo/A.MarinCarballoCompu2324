#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#define PI 3.1415

int main (){
    int N, n, j;
    double lambda;
    N=5;
    double k, s, V[N];
    double complex Phi[N];
    n=2;
    k=(2*PI*n)/N;
    s=1/(4*k*k);
    
    //Se define la función de onda
    for(j=0; j<N; j++){
        Phi[j]=exp(1i*k*j)*exp(-8*pow((4*j-N),2)/(N*N));
    }
    //Se define potencial
    for(j=0; j<N; j++){
        if(j>=2*N/2 && j<=3*N/2){
            V[j]=lambda*k*k;
        }
        else
            V[j]=0;
    }








return 0;
}