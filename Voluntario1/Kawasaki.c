#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "FuncionesKawasaki.h"

int main (){
clock_t begin= clock();
srand(time(NULL));
int N,n,m,i,j, k, Tmax, t, a, b, c, d;
FILE* fichero_out;
fichero_out=fopen("Kawasaki.txt", "w");
N=64;
int s[N][N], r;
double EC1, ECI, ECA, ECO, ECD, E, T,p;
E=0;
T=0.1;
Tmax=1000;
//Lleno la matriz de 1 y -1.
for(i=0;i<N;i++){
    for(j=0;j<N;j++){
        s[i][j]=rand()%2;
    if(s[i][j]==0){
        s[i][j]=-1;
        }
    }
}
//Empiezo a hacer cosas
int* sp=s[0];
for(t=0;t<Tmax;t++){
    for(k=0;k<N*N;k++){
        n=rand()%(N);
        m=rand()%(N);

        //Condiciones de contorno
        a = (n + 1) % N;
        b = (n - 1 + N) % N;
        c = (m + 1) % N;
        d = (m - 1 + N) % N;

        EC1=-0.5*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d]);

        r=rand()%4;

        //ROTACIÓN ARRIBA
        if(r==0){
        ECA=-0.5*s[b][m]*(s[n][m]+s[b-1][m]+s[b][c]+s[b][d]);
        E=EC1-ECA;
        }
        //ROTACIÓN ABAJO
        if(r==1){
        ECO=-0.5*s[a][m]*(s[a+1][m]+s[n][m]+s[a][c]+s[a][d]);
        E=EC1-ECO;
        }
        //ROTACIÓN DERECHA
        if(r==2){
        ECD=-0.5*s[n][c]*(s[a][c]+s[b][c]+s[n][c+1]+s[n][m]);
        E=EC1-ECD;
        }
        //ROTACIÓN IZQUIERDA
        if(r==3){
        ECI=-0.5*s[n][d]*(s[a][d]+s[b][d]+s[n][m]+s[n][d-1]);
        E=EC1-ECI;
        }

        if(exp(-E/T)>1){
            p=1;
        }
        else 
            p=exp(-E/T);
        
        
        double x;
        x=rand();
        x/=RAND_MAX;
        if(p>x){
            IntercambiarPosiciones(sp, r, N, n, m, a, b, c, d);
        }
    }
      for(i=0;i<N;i++){
            for(j=0;j<N-1;j++){
                fprintf(fichero_out, "%d, ", s[i][j]);
            }
            fprintf(fichero_out, "%d", s[i][N-1]);
            fprintf(fichero_out, "\n");
        }
    fprintf(fichero_out, "\n");
}

fclose(fichero_out);
clock_t end=clock();//Tiempo que ha tardado en ejecutarse
double tiempo= (double) (end-begin)/ CLOCKS_PER_SEC;
    printf("Tiempo de compilacion=%lf \n", tiempo);
return 0;
}