#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "FuncionesKawasaki.h"

int main (){
clock_t begin= clock();//Tiempo de compilacion
srand(time(NULL));//Semilla aleatoria
int N,n,m,i,j, k, Tmax, t, a, b, c, d, w, z;//Variables de iteracion
FILE* fichero_out;
fichero_out=fopen("Kawasaki.txt", "w");
N=32;//Numero de spins.
int s[N][N], r;
double EC1, EC2, E, T,p;
E=0;
T=5;//Temperatura
Tmax=1000;//Pasos Montecarlo
//Lleno la matriz de 1 y -1. Menos la primera y la última fila
for(i=1;i<N-1;i++){
    for(j=0;j<N;j++){
        s[i][j]=rand()%2;
    if(s[i][j]==0){
        s[i][j]=-1;
        }
    }
}
for(j=0;j<N;j++){//Lleno la última fila de -1 y la primera de 1.
        s[0][j]=1;
        s[N-1][j]=-1;
}
      for(i=0;i<N;i++){
            for(j=0;j<N-1;j++){
                fprintf(fichero_out, "%d, ", s[i][j]);
            }
            fprintf(fichero_out, "%d", s[i][N-1]);
            fprintf(fichero_out, "\n");
        }
    fprintf(fichero_out, "\n");
//Empiezo a hacer cosas
int* sp=s[0];

for(t=0;t<Tmax;t++){
    for(k=0;k<N*N;k++){
        EC1=0;
        EC2=0;
        //Posición w, z aleatoria de la malla.
        w=rand()%(N-2)+1;//Entre N-2 para que no acceda a la última ni penúltima fila.
        z=rand()%(N);
        //Rotación aleatoria.
        r=rand()%4;
            for(n=1;n<N-2;n++){//Calculo la energía de toda la malla (menos las fijas, fila 1 y N-1)
                for(m=0;m<N;m++){
                //Condiciones de contorno
                    a = (n + 1) % N;
                    b = (n - 1 + N) % N;
                    c = (m + 1) % N;
                    d = (m - 1 + N) % N;

                    EC1+=0.5*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d]);

                }
            }
        IntercambiarPosiciones(sp,r,N,w,z,a,b,c,d);//Intercambio posiciones con un spin vecino (elegido por r aleatorio)

            for(n=1;n<N-2;n++){//Vuelvo a calcular las energias para mi nueva malla intercambiada
                for(m=0;m<N;m++){
                //Condiciones de contorno
                    a = (n + 1) % N;
                    b = (n - 1 + N) % N;
                    c = (m + 1) % N;
                    d = (m - 1 + N) % N;

                    EC2+=0.5*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d]);
        
                }
            }

        E=EC1-EC2;//Calculo la diferencia entre estas dos mallas
        //Busco minimo
        if(exp(-E/T)>1){
            p=1;
        }
        else 
            p=exp(-E/T);
        
        //Genero numero aleatorio
        double x;
        x=rand();
        x/=RAND_MAX;
        //Si mi cambio NO es favorable, vuelvo a dejar las cosas como estaban, en caso contrario,
        //el cambio estaba bien hecho.
        if(p<x){
            IntercambiarPosiciones(sp, r, N, w, z, a, b, c, d);
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