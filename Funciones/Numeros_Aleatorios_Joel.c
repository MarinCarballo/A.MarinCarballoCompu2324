#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

int random_int_number(int range, int seed);
int main() {
    const gsl_rng_type * T;
    gsl_rng * r;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc(T);

    printf("Generando 10 números aleatorios:\n");
    for (int i = 0; i < 10; ++i) {
        double u = gsl_rng_uniform(r);
        printf("%f\n", u);
    }

    gsl_rng_free(r);
    return 0;
}
