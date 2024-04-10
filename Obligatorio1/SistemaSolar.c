//Simulación de la dinámica del sistema solar:
//1.- Simulación t, READY
//2.- Calculo periodo, READY
//3.- Conservación energía y momento angular, READY
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
    //DECLARACION DE VARIABLES
    int i,j,n,d, b, cont;//n es el número de planetas, d es la dimensión, para d=2 (x,y). 
    //Los demás son int para bucles.
    int total;
    double c=1.496e11, G=6.67e-11, M=1.99e30; //Constantes de reescalamiento
    n=7;//Numero de planetas que se quiere simular.
    d=2;//Dimensiones
    double a[n][d], r[n][d], v[n][d], m[n], T[n], U[n], x[n][d], r_geo[n][d];//Vectores aceleracion, posicion, 
    //velocidad, masa, energia cinetica, potencial y vector auxiliar para el periodo
    double h, t, P, tper;//Paso, tiempo, periodo, tiempo del periodo

    FILE *fichero_ent, *fichero_sal,*fichero_energia, *fichero_geo;//Declaracion de ficheros usados.
    fichero_ent = fopen("Iniciales.txt", "r");  //Se dan los datos iniciales

    //Se apuntan los punteros a los vectores
    double* ap=a[0];
    double* rp=r[0];
    double* mp=m;
    double* vp=v[0];
    double* Tp=T;
    double* Up=U;
    double* r_geo_p=r_geo[0];
    //Se escanean los datos iniciales.
    i = 0;
    while (fscanf(fichero_ent, "%lf, %lf, %lf, %lf, %lf", &m[i], &r[i][0], &r[i][1], &v[i][0], &v[i][1])!= EOF)
    {
        i++;
    }

    //Tiempo: Se eligen durante cuanto años se quiere simular el sistema solar
    double tmax;
    tmax=6;
    tmax=tmax*(365*24*3600);//Se pasa a segundos
    ReescaladoSolar(rp, tmax, vp, mp, n, d);//Se reescalan todas las variables
    tmax=sqrt((G*M)/(pow(c,3)))*tmax;

    //Abro ficheros de posicion, geocentricos y energias.
    fichero_sal=fopen("datos.txt","w");
    fichero_geo=fopen("datos_geocentricos.txt", "w");
    fichero_energia=fopen("energias.txt", "w");

    Aceleracion(ap, rp, mp, 2, 2);//Se calculan aceleraciones iniciales.
    cont=0;
    h=0.01;//PASO
    for(t=0; t<tmax; t=t+h){
        x[1][1]=r[1][1];//Se almacena el vector anterior a Verlet en x, para despues calcular si se ha dado una vuelta. 
        //En el primer corchete se elige el planeta del que se quiere saber el periodo.

        fprintf(fichero_sal, "\n");//Esto me deja espacios entre cada nueva iteracion de t.
        fprintf(fichero_geo, "\n");

        Verlet(ap, mp, rp, vp, n, d, h);
        Energia(Tp, Up, rp, mp, vp, n, d);
        Geocentrico(rp, r_geo_p, n, d);
        for(b=0;b<n;b++){
        fprintf(fichero_sal, "%f, %f \n", r[b][0], r[b][1]);
        }
        for(b=0;b<n;b++){
        fprintf(fichero_geo, "%f, %f \n", r_geo[b][0], r_geo[b][1]);
        }
        if(r[1][1]*x[1][1]<0 && r[1][1]>=0){//Condicional que me mira si se dio una vuelta.
        //Multiplica la posicion y anterior con la actual, Si <0, es que se dio una vuelta entera.
        //Se apunta en tper el tiempo donde se ha realizado el periodo (vuelta) completo.
            cont++;
            tper=t;
        }
        //Aquí eligo el planeta del que quiero ver la energía, asi es más fácil.
        fprintf(fichero_energia, "%f, %f, %f, %f \n", T[1], U[1], U[1]+T[1], t);
    }
    tper=tper/(sqrt((G*M)/(pow(c,3))));//Reescalo el tiempo de vuelta.
    tper=tper/(24*3600);//Lo paso a días.
    P=cont/tper;//PERIODO: vuelta/dias.
    P=1/P;//dias para dar una vuelta.
    printf("%lf, ", P);//Enseño mi periodo
    //CIERRO FICHEROS
    fclose(fichero_energia);
    fclose(fichero_ent);
    fclose(fichero_sal);
    fclose(fichero_geo);
    return 0;
    }

