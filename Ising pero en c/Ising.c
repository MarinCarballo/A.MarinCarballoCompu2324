#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main (){
clock_t begin= clock();
srand(time(NULL));
int N,n,m,i,j, k, Tmax, t, a, b, c, d;
FILE* fichero_out;
fichero_out=fopen("datos.txt", "w");
N=120;
int s[N][N];
double E, T,p;
p=rand()%2;
E=0;
T=1;
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
for(t=0;t<Tmax;t++){
    for(k=0;k<N*N;k++){
        n=rand()%(N);
        m=rand()%(N);

        a = (n + 1) % N;
        b = (n - 1 + N) % N;
        c = (m + 1) % N;
        d = (m - 1 + N) % N;

        E=2*s[n][m]*(s[a][m]+s[b][m]+s[n][c]+s[n][d]);

        if(exp(-E/T)>1){
            p=1.;
        }
        else 
            p=exp(-E/T);

        double x;
        x=rand();
        x/=RAND_MAX;
        if(p>x){
            s[n][m]=-s[n][m];
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