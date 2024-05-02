#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

double DeltaEnergia(int n, int m,int a,int b,int c,int d, int * s, int N){
    double E;
    E=2*(*(s+n*N+m))*(*(s+a*N+m)+*(s+b*N+m)+*(s+n*N+c)+*(s+n*N+d));
    return E;
}