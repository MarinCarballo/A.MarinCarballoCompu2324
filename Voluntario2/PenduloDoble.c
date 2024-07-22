#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "FuncionesPenduloDoble.h"
#define pi 3.14

int main(){
    FILE *fichero_out;
    fichero_out=fopen("PenduloDoble.txt", "w");
    FILE* ficheroAngulo = fopen("AnguloAngulo.txt", "w");
    FILE* ficheroVelocidad = fopen("VelocidadAngulo.txt", "w");
    FILE* ficheroVelocidad2 = fopen("VelocidadAngulo2.txt", "w");
    FILE* ficheroLyapunov = fopen("Lyapunov.txt", "w");
    FILE* ficheroOptimizacion = fopen("Optimizacion.txt", "w");
    double g=9.81, h, t, Tmax;//Declaracion de constantes
    double y[4], x[4];//Vectores Runge-Kutta
    double k[4][4], q[4][4];//Vectores auxiliares Runge-Kutta
    double E;//Energia
    int i, j;
    double x1, y1, x2, y2;//Posiciones del péndulo
    x1=0;
    y1=0;
    x2=0;
    y2=0;

    double Lyapunov;//Coeficiente de Lyapunov
    double distancia, distanciainicial, cont;//Variables de Lyapunov

Tmax=10;//Tiempo simulación Runge-Kutta
h=0.001;//Paso
//for(Tmax=100; Tmax<1000; Tmax=Tmax+10){ //Esto se activa si se quiere hacer Lyapunov
    clock_t begin = clock(); // Tiempo de compilacion
    t=0;
    Lyapunov=0;
    distancia=0;
    distanciainicial=0;
    cont=0;
    //Condiciones iniciales 1
    E=1;
    y[0]=0.3; //Psi
    y[1]=0.1; //Phi
    y[3]=sqrt(E-2*g*(1-cos(y[1]))-g*(1-cos(y[0]))); //Velocidad de Phi
    y[2]=y[3]*cos(y[0]-y[1]); //Momento de Psi

    y[3]=2*y[3];//Momento phi

    //Lyapunov
    //double E2=15.5;
    //Otras condiciones iniciales, para calcular el coeficiente de Lyapunov.
    //x[0]=0.3; //Psi
    //x[1]=0.3; //Phi
    //x[3]=sqrt(E2-2*g*(1-cos(x[1]))-g*(1-cos(x[0]))); //Velocidad de Phi
    //x[2]=x[3]*cos(x[0]-x[1]); //Momento de Psi

    //x[3]=2*x[3];//Momento phi

    while(t<Tmax){
        //Calculo de k1:
        k[0][0]=h*fPsi(y[1], y[3], y[0], y[2]);
        k[0][1]=h*fPhi(y[1], y[3], y[0], y[2]);
        k[0][2]=h*fMomentoPsi(y[1], y[3], y[0], y[2]);
        k[0][3]=h*fMomentoPhi(y[1], y[3], y[0], y[2]);
    
        //Calculo de k2:
        k[1][0]=h*fPsi(y[1]+k[0][1]/2, y[3]+k[0][3]/2, y[0]+k[0][0]/2, y[2]+k[0][2]/2);
        k[1][1]=h*fPhi(y[1]+k[0][1]/2, y[3]+k[0][3]/2, y[0]+k[0][0]/2, y[2]+k[0][2]/2);
        k[1][2]=h*fMomentoPsi(y[1]+k[0][1]/2, y[3]+k[0][3]/2, y[0]+k[0][0]/2, y[2]+k[0][2]/2);
        k[1][3]=h*fMomentoPhi(y[1]+k[0][1]/2, y[3]+k[0][3]/2, y[0]+k[0][0]/2, y[2]+k[0][2]/2);
        
        //Calculo de k3:
        k[2][0]=h*fPsi(y[1]+k[1][1]/2, y[3]+k[1][3]/2, y[0]+k[1][0]/2, y[2]+k[1][2]/2);
        k[2][1]=h*fPhi(y[1]+k[1][1]/2, y[3]+k[1][3]/2, y[0]+k[1][0]/2, y[2]+k[1][2]/2);
        k[2][2]=h*fMomentoPsi(y[1]+k[1][1]/2, y[3]+k[1][3]/2, y[0]+k[1][0]/2, y[2]+k[1][2]/2);
        k[2][3]=h*fMomentoPhi(y[1]+k[1][1]/2, y[3]+k[1][3]/2, y[0]+k[1][0]/2, y[2]+k[1][2]/2);   

        //Calculo de k4
        k[3][0]=h*fPsi(y[1]+k[2][1], y[3]+k[2][3], y[0]+k[2][0], y[2]+k[2][2]);
        k[3][1]=h*fPhi(y[1]+k[2][1], y[3]+k[2][3], y[0]+k[2][0], y[2]+k[2][2]);
        k[3][2]=h*fMomentoPsi(y[1]+k[2][1], y[3]+k[2][3], y[0]+k[2][0], y[2]+k[2][2]);
        k[3][3]=h*fMomentoPhi(y[1]+k[2][1], y[3]+k[2][3], y[0]+k[2][0], y[2]+k[2][2]);    
        
        //Calculo de la nueva y
        for(i=0;i<4;i++){
            y[i]=y[i]+(k[0][i]+2*k[1][i]+2*k[2][i]+k[3][i])/6;
        }
        
        x1=sin(y[1]);
        y1=-cos(y[1]);
        x2=x1+sin(y[0]);
        y2=y1-cos(y[0]);

        //****************************LYAPUNOV: //Esto se activa si se quiere hacer Lyapunov*********
        //Lo que hace esto es calcular otra trayectoria con otro runge-kutta para las otras condicones de contorno
        //Después va calculando las distancias entre trayectorias en cada paso de Tmax.
        //Calculo de q1:
        // q[0][0]=h*fPsi(x[1], x[3], x[0], x[2]);
        // q[0][1]=h*fPhi(x[1], x[3], x[0], x[2]);
        // q[0][2]=h*fMomentoPsi(x[1], x[3], x[0], x[2]);
        // q[0][3]=h*fMomentoPhi(x[1], x[3], x[0], x[2]);

        // //Calculo de q2:
        // q[1][0]=h*fPsi(x[1]+q[0][1]/2, x[3]+q[0][3]/2, x[0]+q[0][0]/2, x[2]+q[0][2]/2);
        // q[1][1]=h*fPhi(x[1]+q[0][1]/2, x[3]+q[0][3]/2, x[0]+q[0][0]/2, x[2]+q[0][2]/2);
        // q[1][2]=h*fMomentoPsi(x[1]+q[0][1]/2, x[3]+q[0][3]/2, x[0]+q[0][0]/2, x[2]+q[0][2]/2);
        // q[1][3]=h*fMomentoPhi(x[1]+q[0][1]/2, x[3]+q[0][3]/2, x[0]+q[0][0]/2, x[2]+q[0][2]/2);

        // //Calculo de q3:
        // q[2][0]=h*fPsi(x[1]+q[1][1]/2, x[3]+q[1][3]/2, x[0]+q[1][0]/2, x[2]+q[1][2]/2);
        // q[2][1]=h*fPhi(x[1]+q[1][1]/2, x[3]+q[1][3]/2, x[0]+q[1][0]/2, x[2]+q[1][2]/2);
        // q[2][2]=h*fMomentoPsi(x[1]+q[1][1]/2, x[3]+q[1][3]/2, x[0]+q[1][0]/2, x[2]+q[1][2]/2);
        // q[2][3]=h*fMomentoPhi(x[1]+q[1][1]/2, x[3]+q[1][3]/2, x[0]+q[1][0]/2, x[2]+q[1][2]/2);

        // //Calculo de q4
        // q[3][0]=h*fPsi(x[1]+q[2][1], x[3]+q[2][3], x[0]+q[2][0], x[2]+q[2][2]);
        // q[3][1]=h*fPhi(x[1]+q[2][1], x[3]+q[2][3], x[0]+q[2][0], x[2]+q[2][2]);
        // q[3][2]=h*fMomentoPsi(x[1]+q[2][1], x[3]+q[2][3], x[0]+q[2][0], x[2]+q[2][2]);
        // q[3][3]=h*fMomentoPhi(x[1]+q[2][1], x[3]+q[2][3], x[0]+q[2][0], x[2]+q[2][2]);

        // //Calculo de la nueva x
        // for(i=0;i<4;i++){
        //     x[i]=x[i]+(q[0][i]+2*q[1][i]+2*q[2][i]+q[3][i])/6;
        // }
        
        // cont+=1;//Número de datos
        // if(t==0){ //DISTANCIA INICIAL
        //     distanciainicial=sqrt(pow(y[1]-x[1],2)+pow(fPhi(y[1],y[3], y[0], y[2])-fPhi(x[1],x[3], x[0], x[2]),2));
        // }

        t=t+h;
        //Calculo de la distancia entre trayectorias
        //distancia+=sqrt(pow(y[1]-x[1],2)+pow(fPhi(y[1],y[3], y[0], y[2])-fPhi(x[1],x[3], x[0], x[2]),2));
        //Lyapunov+=log(distancia/distanciainicial);

        fprintf(fichero_out, "%lf, %lf \n", x1, y1);
        fprintf(fichero_out, "%lf, %lf \n", x2, y2);
        fprintf(fichero_out, "\n");
        fprintf(ficheroAngulo, "%lf, %lf \n", y[1], y[0]);//Angulo-Angulo para mapa Poincare
        fprintf(ficheroVelocidad, "%lf, %lf \n", y[1], fPhi(y[1],y[3], y[0], y[2]));//Velocidad-Angulo PHI
        fprintf(ficheroVelocidad2, "%lf, %lf \n", y[0], fPsi(y[1],y[3], y[0], y[2]));//Velocidad-Angulo PSI
     }
    clock_t end = clock(); // Tiempo que ha tardado en ejecutarse
    double tiempo = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de compilacion = %lf\n", tiempo);
    printf("%lf \n", h);
    fprintf(ficheroOptimizacion, "%lf, %lf \n", tiempo, h);

    //Lyapunov=(Lyapunov)/(Tmax);
    //fprintf(ficheroLyapunov, "%lf, %lf \n", Lyapunov, Tmax);
    //}//Activar este corchete de abajo si se activa Lyapunov

    fclose(fichero_out);
    fclose(ficheroAngulo);
    fclose(ficheroVelocidad);
    fclose(ficheroVelocidad2);
    fclose(ficheroLyapunov);
    fclose(ficheroOptimizacion);

    return 0;
}