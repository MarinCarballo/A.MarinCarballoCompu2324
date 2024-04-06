//Simulación de la dinámica del sistema solar:
//1.- Simulación t
//2.- Calculo periodo
//3.- Conservación energía y momento angular
//4.- Heliocéntrico -> Geocéntrico r'=r-r_T
//CONSEJOS DE LA PROFE:
    //h=1/1000. Uson de funciones y proteus.
//Problemas posibles:
    //Calcular conservación energía y momento pronto en el código, para poder identificar problemas.
    //Orbitas no se cierran -> reducir precisión o usar t más largo.
    //Los vídeos pesan mucho-> reducir precisión o tirar los puntos impares.
//Librerías
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "FuncionesSistemaSolar.h"

int main()
{
    int i,j,n,d;//n es el número de planetas, d es la dimensión, para d=2 (x,y).
    n=2;
    d=2;
    double a[n][d], r[n][d], v[n][d], m[n];
    double h, t;
    //REESCALAMIENTO
    m[0]=0.000003;
    m[1]=1;

    r[0][0]=1;
    r[0][1]=0;

    r[1][0]=0;
    r[1][1]=0;

    v[0][0]=0;
    v[0][1]=1;

    v[1][0]=0;
    v[1][1]=0;
 
    FILE* fichero;
    fichero=fopen("datos.txt","w");
    fprintf(fichero, "%f, %f \n", r[0][0], r[0][1]);
    fprintf(fichero, "%f, %f \n", r[1][0], r[1][1]);

    double* ap=a[0];
    double* rp=r[0];
    double* mp=m;
    double* vp=v[0];
    Aceleracion(ap, rp, mp, 2, 2);
    h=0.01;//PASO
    for(t=0; t<100; t=t+h){
    fprintf(fichero, "\n");
    Verlet(ap, mp, rp, vp, n, d, h);

    fprintf(fichero, "%f, %f \n", r[0][0], r[0][1]);
    fprintf(fichero, "%f, %f \n", r[1][0], r[1][1]);
    }
    return 0;
    }   

