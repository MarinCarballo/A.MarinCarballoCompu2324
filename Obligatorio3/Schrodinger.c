#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#define PI 3.1415

int main (){
    FILE* fichero_out;
    FILE* ficheronorma;
    fichero_out=fopen("Schrodinger.txt", "w");
    ficheronorma=fopen("Norma.txt", "w");
    int N,T, n, j, nc;//T dimension de tiempos
    double lambda;
    N=100;
    T=200;
    double k, s, h;
    double V[N];
    double complex Phi[T][N];
    double complex Alpha[N];
    double complex b[T][N];   
    double complex betha[T][N];
    double complex X[T][N];
    double PhiM[T][N];
    double Norma[T];
    nc=N/4;
    double Nalt;
    Nalt=N;
    h=1/Nalt;
    k=(2*PI*nc)/N;
    s=1/(4*k*k);
    lambda=0.3;
    //Se define la función de onda
    for(j=0; j<N; j++){
            Phi[0][j]=cexp(1*I*k*j)*exp(-8*pow((4*j-N),2)/(N*N));
    }
    //Contorno
    Phi[0][0]=0;
    Phi[0][N-1]=0;
    //Se define potencial
    for(j=0; j<N; j++){
        if(j>=2*N/5 && j<=3*N/5){
            V[j]=lambda*k*k;
        }
        else
            V[j]=0;
    }
    //Calculo de Alpha
    //A-=1, A0=-2+2i/s-Vj, A+=1
    Alpha[N-1]=0;
    for(j=N-1; j>=0; j--){
        Alpha[j-1]=-1/(-2+2*1*I/s-V[j]+Alpha[j]);
    }
    for(n=0; n<T-1; n++){
        betha[n][N-1]=0;
        X[n][N-1]=0;
        X[n][0]=0;
        for(j=0;j<N-1;j++){
            Norma[n]=0;
        }
        for(j=0; j<N-1; j++){
            b[n][j]=(4*I*Phi[n][j])/s;
        }
        for(j=N-2; j>=0; j--){
            betha[n][j-1]=(b[n][j]-betha[n][j])/(-2+2*I/s-V[j]+Alpha[j]);
        }
        for(j=0;j<N;j++){
            X[n][j+1]=Alpha[j]*X[n][j]+betha[n][j];
            Phi[n+1][j]=X[n][j]-Phi[n][j];
            PhiM[n][j]=cabs(Phi[n][j])*cabs(Phi[n][j]);
            Norma[n]=Norma[n]+(1/Nalt)*PhiM[n][j];
            }
        //ESCRIBO        
            for(j=0;j<N;j++){
                fprintf(fichero_out, "%d, %lf, %lf \n", j, PhiM[n][j], V[j]);
                fprintf(ficheronorma, "%d, %lf \n", j, Norma[n]);
            }
            fprintf(fichero_out, "\n");
            fprintf(ficheronorma, "\n");
    }
fclose(fichero_out);
fclose(ficheronorma);
return 0;
}

