#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 32 // Numero de spins.
#define Tmax 1000000 // Pasos Montecarlo

void initialize_spins(int s[N][N]) {
    for(int i = 1; i < N-1; i++) {
        for(int j = 0; j < N; j++) {
            s[i][j] = (i % 2 == 0) ? 1 : -1; // Spins alternantes.
        }
    }
}

void fill_boundaries(int s[N][N]) {//Condiciones de contorno en y 
    for(int j = 0; j < N; j++) {
        s[0][j] = 1;
        s[N-1][j] = -1;
    }
}

double calculate_energy(int s[N][N]) {
    double energy = 0.0;
    for(int n = 1; n < N-1; n++) {
        for(int m = 0; m < N; m++) {
            int a = (n + 1);
            int b = (n - 1);
            int c = (m + 1) % N;
            int d = (m - 1 + N) % N;
            energy += 0.5 * s[n][m] * (s[a][m] + s[b][m] + s[n][c] + s[n][d]);
        }
    }
    return energy;
}

void swap_spins(int s[N][N], int w, int z, int r) {
    int temp;
    switch(r) {
        case 0: temp = s[w][z]; s[w][z] = s[w-1][z]; s[w-1][z] = temp; break;
        case 1: temp = s[w][z]; s[w][z] = s[w+1][z]; s[w+1][z] = temp; break;
        case 2: temp = s[w][z]; s[w][z] = s[w][(z+1)%N]; s[w][(z+1)%N] = temp; break;
        case 3: temp = s[w][z]; s[w][z] = s[w][(z-1+N)%N]; s[w][(z-1+N)%N] = temp; break;
    }
}

int Checking(int s[N][N], int r, int w, int z){
    int a;
    a=0;
    if(r==0 && s[w][z]==s[w-1][z]){
        a=1;
    }
    if(r==1 && s[w][z]==s[w+1][z]){
        a=1;
    }
    if(r==2 && s[w][z]==s[w-1][(z+1)%N]){
        a=1;
    }
    if(r==3 && s[w][z]==s[w-1][(z-1+N)%N]){
        a=1;
    }
    return a;
}

int main () {                         
    clock_t begin = clock(); // Tiempo de compilacion
    srand(time(NULL)); // Semilla aleatoria

    FILE* fichero_out = fopen("Kawasaki.txt", "w");
    FILE* ficheroMag = fopen("Magnetizacion.txt", "w");
    FILE* ficheroDensidad = fopen("Densidad.txt", "w");

    //double magSuperior[Tmax] = {0};
    //double magInferior[Tmax] = {0};
    double T;
    int s[N][N];
    initialize_spins(s);
    fill_boundaries(s);
    T=1;
  //  for (double T = 1; T < 2; T++) {
        initialize_spins(s);
        fill_boundaries(s);
        double conta;
        conta=0;
        for (int t = 0; t < Tmax; t++) {
            double sumSuperior = 0;
            double sumInferior = 0;

            #pragma omp parallel for
            for (int k = 0; k < N * N; k++) {
                int w = rand() % (N-2) + 1; // Posición aleatoria, excluyendo primera y última fila.
                int z = rand() % N; 
                int r;
                //Rotación aleatoria.
                if(w==1){
                    r=rand()%3+1;
                 }
                else if(w==N-2){
                    r=rand()%3;
                if(r==1){
                    r=3;
                    }
                }
                else{
                    r=rand()%4;
                }

                int l=Checking(s, r, w, z);
                if(l==0){
                    double EC1 = calculate_energy(s);//Calculo energía sin cambiar
                    swap_spins(s, w, z, r);//Cambio spins
                    double EC2 = calculate_energy(s);//Calculo energia cambiada

                    double E = EC1 - EC2;
                    double p = (exp(-E/T) > 1) ? 1 : exp(-E/T);

                    if ((double)rand() / RAND_MAX > p) {
                        swap_spins(s, w, z, r); // Si el cambio NO es favorable, revierto el cambio.
                    }
                }
            }
            if(t==999999){
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N-1; j++) {
                        fprintf(fichero_out, "%d, ", s[i][j]);
                    }
                    fprintf(fichero_out, "%d \n",  s[i][N-1]);
                }
                fprintf(fichero_out, "\n");
            }
        if(t>1000){//Dejo al sistema evolucionar 1000 pasos montecarlo para obtener resultados mas fiables.
            for (int i = 1; i < N-1; i++) {
                for (int j = 0; j < N; j++) {
                    if (i < N/2) {
                        sumSuperior += s[i][j];
                    } else {
                        sumInferior += s[i][j];
                    }
                }
            }

            //magSuperior[t] = sumSuperior / (((N-1)/2) * N);
            //magInferior[t] = sumInferior / (((N-1)/2) * N);
            }
        double contplus, contminus,PromedioDensidadPlus, PromedioDensidadMinus;
        double densidadplus[N], densidadminus[N];
        PromedioDensidadPlus=0;
        PromedioDensidadMinus=0;
        contplus=0;
        contminus=0;
    for(int j=0;j<N;j++){
            contplus=0;
            contminus=0;
            for(int i=0;i<N;i++){
                if(s[i][j]==1){
                    contplus+=1;
                }
                else{
                    contminus+=1;
                }
            }//DENSIDAD POR COLUMNA:
            densidadplus[j]=contplus/N;
            densidadminus[j]=contminus/N;
        }
            // for(j=0;j<N;j++){//Promedio de columnas
            //     PromedioDensidadPlus+=densidadplus[j]/N;
            //     PromedioDensidadMinus+=densidadminus[j]/N;
        // }
        conta=conta+densidadplus[0];
        }//FinMontecarlo

        double MediaSuperior = 0;
        double MediaInferior = 0;
        double varianzaSup = 0;
        double varianzaInf = 0;
        double a=100;
        for (int t = a; t < Tmax; t++) {
            //MediaSuperior += magSuperior[t] /(Tmax-a);
            //MediaInferior += magInferior[t] /(Tmax-a);
        }

        for (int t = a; t < Tmax; t++) {
            //varianzaSup += pow(magSuperior[t] - MediaSuperior, 2) / (Tmax-a);
            //varianzaInf += pow(magInferior[t] - MediaInferior, 2) / (Tmax-a);
        }

        double errorSup = sqrt(varianzaSup) / sqrt(Tmax-a);
        double errorInf = sqrt(varianzaInf) / sqrt(Tmax-a);
        conta=conta/Tmax;//Densidad promediada

        fprintf(ficheroMag, "%lf, %lf, %lf, %lf, %lf\n", MediaSuperior, 3*errorSup, MediaInferior, 3*errorInf, T);
        fprintf(ficheroDensidad, "%lf, %lf, %lf \n", conta, 1-conta, T); //DensidadPlus, DensidadMinus, T
        printf("Temperatura terminada");
   // }

    fclose(fichero_out);
    fclose(ficheroMag);
    fclose(ficheroDensidad);

    clock_t end = clock(); // Tiempo que ha tardado en ejecutarse
    double tiempo = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de compilacion = %lf\n", tiempo);

    return 0;
}
