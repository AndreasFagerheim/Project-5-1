#ifndef LEGEMER_H
#define LEGEMER_H
#include <armadillo>

using namespace arma;

class Legemer
{
public:
    double  masse;
    vec     posisjon;
    vec     hastighet;
    vec     kraft;
    vec     pKraft;
    vec     angMoment;

    Legemer(vec nyPos,vec nyHas, double nyMasse);
    void resetKraft();
};

#endif // LEGEMER_H
