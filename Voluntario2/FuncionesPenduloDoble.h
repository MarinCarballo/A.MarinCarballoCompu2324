#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double fMomentoR(double MomentoPhi, double r, double mu, double Phi, double w, double t, double Delta){
    double pr, rprima;
    rprima=(sqrt(1+r*r-2*r*cos(Phi-w*t)));
    pr=(MomentoPhi*MomentoPhi)/(pow(r, 3))-Delta*(1/(r*r)+(r-cos(Phi-w*t))*mu/(pow(rprima, 3)));
    return pr;
}

double fr(double MomentoR){
    double frr;
    frr=MomentoR;
    return frr;
}

double fPhi(double MomentoPhi, double r){
    double fPhiaux;
    fPhiaux=(MomentoPhi)/(r*r);
    return fPhiaux;
}

double fMomentoPhi(double r, double mu, double Delta, double Phi, double w, double t){
    double Fmont, rprima;
    rprima=(sqrt(1+r*r-2*r*cos(Phi-w*t)));
    Fmont=-(Delta*mu*r)/(pow(rprima,3))*sin(Phi-w*t);
    return Fmont;
}