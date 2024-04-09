//Simulación de la dinámica del sistema solar:
//1.- Simulación t
//2.- Calculo periodo
//3.- Conservación energía y momento angular
//4.- Heliocéntrico -> Geocéntrico r'=r-r_T
//CONSEJOS DE LA PROFE:
    //h=1/1000. Uso de funciones y proteus.
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
    int i,j,n,d, b;//n es el número de planetas, d es la dimensión, para d=2 (x,y).
    int total;
    n=7;
    d=2;
    double a[n][d], r[n][d], v[n][d], m[n], T[n], U[n];
    double h, t;
    //REESCALAMIENTO
    FILE *fichero_ent, *fichero_sal,*fichero_energia;

    fichero_ent = fopen("Iniciales.txt", "r");  
    double* ap=a[0];
    double* rp=r[0];
    double* mp=m;
    double* vp=v[0];
    double* Tp=T;
    double* Up=U;
    
    i = 0;
    while (fscanf(fichero_ent, "%lf, %lf, %lf, %lf, %lf", &m[i], &r[i][0], &r[i][1], &v[i][0], &v[i][1])!= EOF)
    {
        i++;
    }

    ReescaladoSolar(rp, t, vp, mp, n, d);

    fichero_sal=fopen("datos.txt","w");
    fichero_energia=fopen("energias.txt", "w");
        for(b=0;b<n;b++){
             fprintf(fichero_sal, "%f, %f \n", r[b][0], r[b][1]);
            }

    Aceleracion(ap, rp, mp, 2, 2);
    h=0.1;//PASO
    for(t=0; t<200; t=t+h){
        fprintf(fichero_sal, "\n");
        Verlet(ap, mp, rp, vp, n, d, h);
        Energia(Tp, Up, rp, mp, vp, n, d);
        for(b=0;b<n;b++){
        fprintf(fichero_sal, "%f, %f \n", r[b][0], r[b][1]);
        }
        //Aquí eligo el planeta del que quiero ver la energía, asi es más fácil.
        fprintf(fichero_energia, "%f, %f, %f, %f \n", T[1], U[1], U[1]+T[1], t);
    }
    fclose(fichero_ent);
    fclose(fichero_sal);
    return 0;
    }   

