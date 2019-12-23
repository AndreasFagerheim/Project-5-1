#include "integrand.h"

#include "univers.h"
#include <iostream>
using namespace std;
Integrand::Integrand(double dt)
{
    tidsSteg = dt;
    tidsSteg2 = dt*dt;
    bEuler = false;         // bruker verlet som standard
}

Integrand::Integrand(double dt, bool euler){
    tidsSteg= dt;
    tidsSteg2 = dt*dt;
    bEuler = euler;         // bestemmer intergrasjonesmetode
}


void Integrand::intEtSteg(class Univers &univers){
    if(bEuler){
        Integrand::intEtStegEuler(univers);
        //cout <<"Forward Euler chosen"<<endl;
    }else{
        Integrand::intEtStegVerlet(univers);
        //cout <<"Verlet chosen"<<endl;
    }
}

void Integrand::intEtStegEuler(class Univers &univers){
    univers.finnKraftEnergi();
    for(Legemer &legeme : univers.getLegemer()){
        legeme.posisjon +=  tidsSteg*legeme.hastighet;  // s[i+1] = s[i]+dt*v[i]
        legeme.hastighet +=  (legeme.kraft/legeme.masse) *tidsSteg;   // v[i+1] = v[i]+a[i]*dt,    f= ma;
    }
    // hvis systemet har solen i ro i sentrum settes posisjonen til (0,0,0)
    if(univers.isSunFixed()){
        Legemer sol = univers.getLegemer()[0];
        sol.posisjon<<0<<0<<0;
    }
}

void Integrand::intEtStegVerlet(class Univers &univers){

    for(Legemer &legeme:univers.getLegemer()){
        legeme.posisjon += legeme.hastighet*tidsSteg+0.5*tidsSteg2*(legeme.kraft/legeme.masse);
        //s[i+1] = s[i}+v[i]*dt+0.5*dt*dt(a[i])
    }
    univers.finnKraftEnergi();
    for(Legemer &legeme:univers.getLegemer()){
        legeme.hastighet+= 0.5*tidsSteg*(legeme.kraft+legeme.pKraft)/legeme.masse;
        //v[i+1] = v[i] +0.5*dt*(a[i]+a[i-1])
    }

    if(univers.isSunFixed()){
        Legemer sol = univers.getLegemer()[0];
        sol.posisjon<<0<<0<<0;
    }
}
