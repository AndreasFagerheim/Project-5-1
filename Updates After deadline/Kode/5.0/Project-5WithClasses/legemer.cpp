#include "legemer.h"
#include <armadillo>

Legemer::Legemer(vec nyPos, vec nyHas, double nyMasse){
    posisjon = nyPos;
    hastighet = nyHas;
    masse = nyMasse;
    angMoment = cross(posisjon,hastighet);
}


void Legemer::resetKraft(){
    pKraft = kraft;
    kraft <<0<<endr<<0<<endr<<0;
}
