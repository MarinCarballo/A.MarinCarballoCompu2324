#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double fMomentoPsi(double Phi, double MomentoPhi, double Psi, double MomentoPsi){
    double g=9.81;
    double ppsi;

    ppsi=((MomentoPsi*MomentoPhi*pow(cos(Psi-Phi),2)-(2*pow(MomentoPsi,2)+pow(MomentoPhi,2)*cos(Psi-Phi))+2*MomentoPhi*MomentoPsi)/(pow((2-pow(cos(Psi-Phi),2)),2)))*2*sin(Psi-Phi);
    ppsi=ppsi-g*sin(Psi);

    return ppsi;
}

double fPsi(double Phi, double MomentoPhi, double Psi, double MomentoPsi){
    double pesi;
    double g=9.81;

    pesi=(2*MomentoPsi-MomentoPhi*cos((Psi-Phi)));
    pesi=pesi/(2-pow(cos((Phi-Psi)),2));

    return pesi;
}

double fPhi(double Phi, double MomentoPhi, double Psi, double MomentoPsi){
    double fPhiaux;

    fPhiaux=(MomentoPhi-MomentoPsi*cos((Psi-Phi)));
    fPhiaux=fPhiaux/(2-pow(cos((Phi-Psi)),2));

    return fPhiaux;
}

double fMomentoPhi(double Phi, double MomentoPhi, double Psi, double MomentoPsi){
    double pphi;
    double g=9.81;

    pphi=((MomentoPsi*MomentoPhi*pow(cos(Psi-Phi),2)-(2*pow(MomentoPsi,2)+pow(MomentoPhi,2)*cos(Psi-Phi))+2*MomentoPhi*MomentoPsi)/(pow((2-pow(cos(Psi-Phi),2)),2)))*2*sin(Phi-Psi);
    pphi=pphi-2*g*sin(Phi);

    return pphi;
}