#ifndef INTEGRAND_H
#define INTEGRAND_H


class Integrand
{
public:
    double  tidsSteg;
    double  tidsSteg2;
    bool    bEuler;     //avgjør hvilken metode som skal brukes
    Integrand(double dt);
    Integrand(double dt, bool euler);

    void intEtSteg(class Univers &univers);
    void intEtStegEuler(class Univers &univers);
    void intEtStegVerlet(class Univers &univers);

};

#endif // INTEGRAND_H
