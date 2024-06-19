#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "FuncionesPenduloDoble.h"
#define pi 3.14;

int main(){
    FILE *fichero_out;
    fichero_out=fopen("PenduloDoble.txt", "w");
    double g=9.8, MT=5.9736e24, ML=0.07349e24, dTL=3.844e8, w=2.6677e-6, RT=6.378160e6, RL=1.7374e6, Delta, mu, h, t, Tmax, m, xL, yL;
    double y[4];
    double k[4][4];
    double cordx, cordy, E;
    int i, j;
    mu=ML/MT;
    Tmax=1000000;
    t=0;
    //Condiciones iniciales
    E=1;
    y[0]=pi; //Psi
    y[1]=pi; //Phi
    y[2]=0; //Momento de Psi
    y[3]=sqrt(E-2*g*(1-cos(y[1]))-g*(1-cos(y[0]))); //Momento de Phi
    h=200;  
    while(t<Tmax){
        //Calculo de k1:
        k[0][0]=h*fr(y[2]);
        k[0][1]=h*fPhi(y[3], y[0]);
        k[0][2]=h*fMomentoR(y[3], y[0], mu, y[1], w, t, Delta);
        k[0][3]=h*fMomentoPhi(y[0], mu, Delta, y[1], w, t);
        
        //Calculo de k2:
        k[1][0]=h*fr(y[2]+k[0][2]/2);
        k[1][1]=h*fPhi(y[3]+k[0][3]/2, y[0]+k[0][0]/2);
        k[1][2]=h*fMomentoR(y[3]+k[0][3]/2, y[0]+k[0][0]/2, mu, y[1]+k[0][1]/2, w, t+h/2, Delta);
        k[1][3]=h*fMomentoPhi(y[0]+k[0][0]/2, mu, Delta, y[1]+k[0][1]/2, w, t+h/2);
        
        //Calculo de k3:
        k[2][0]=h*fr(y[2]+k[1][2]/2);
        k[2][1]=h*fPhi(y[3]+k[1][3]/2, y[0]+k[1][0]/2);
        k[2][2]=h*fMomentoR(y[3]+k[1][3]/2, y[0]+k[1][0]/2, mu, y[1]+k[1][1]/2, w, t+h/2, Delta);
        k[2][3]=h*fMomentoPhi(y[0]+k[1][0]/2, mu, Delta, y[1]+k[1][1]/2, w, t+h/2);   

        //Calculo de k4
        k[3][0]=h*fr(y[2]+k[2][2]);
        k[3][1]=h*fPhi(y[3]+k[2][3], y[0]+k[2][0]);
        k[3][2]=h*fMomentoR(y[3]+k[2][3], y[0]+k[2][0], mu, y[1]+k[2][1], w, t+h, Delta);
        k[3][3]=h*fMomentoPhi(y[0]+k[2][0], mu, Delta, y[1]+k[2][1], w, t+h);    
        
        //Calculo de la nueva y
        for(i=0;i<4;i++){
            y[i]=y[i]+(k[0][i]+2*k[1][i]+2*k[2][i]+k[3][i])/6;
        }
        cordx=y[0]*cos(y[1]);
        cordy=y[0]*sin(y[1]);
        xL=cos(w*t);
        yL=sin(w*t);
        t=t+h;
        fprintf(fichero_out, "%lf, %lf \n", 0, 0);
        fprintf(fichero_out, "%lf, %lf \n", cordx, cordy);
        fprintf(fichero_out, "%lf, %lf \n", xL, yL);
        fprintf(fichero_out, "\n");
        }
    fclose(fichero_out);


    return 0;
}