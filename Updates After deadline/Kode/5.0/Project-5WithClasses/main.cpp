#include <iostream>
#include <iomanip>
#include <fstream>
// egne klasser
#include <univers.h>
#include <integrand.h>

using namespace std;


// henter fart og posisjon fra fil (x,y,z,vx,vy,vz)
void hentPosFart(string fil, int antallLegemer);


int main()
{
    cout << "Starting program!" << endl;
    Univers *universet = new Univers();
    // massen til sol og jorden ( kun disse som er av interesse i første omgang
    double masse_Sol        = 2*pow(10,30);
    double masse_Jord       = 6*pow(10,24);
    // masse andre planeter
    double masse_Jupiter    = 1.9*pow(10,27);
    double masse_Mars       = 6.6*pow(10,23);
    double masse_Venus      = 4.9*pow(10,24);
    double masse_Saturn     = 5.5*pow(10,26);
    double masse_Merkus     = 3.3*pow(10,23);
    double masse_Uranus     = 8.8*pow(10,25);
    double masse_Neptun     = 1.03*pow(10,26);
    double masse_Pluto      = 1.31*pow(10,22);


    //int antallÅr, stegÅr, antallSteg;;

    //først sette opp systemet vårt
    // ser først på sirkelbevegelse med fiksert sol og jorden i bane rundt solen. vy = 2pi, x = 1.0, y = 0 for jorden.
    // vil finne ut stabiliteten til euler og verlet ved å se på avviket etter et år og den avhengighet med størrelsen på tidssteg.

    double pi = 4*atan(1);
    vec posSol      = {0.,0.,0.};
    vec hasSol      = {0.,0.,0.};
    vec posJord     = {1.0,0.,0.};
    vec hasJord     = {0.,2*pi,0.};
    universet->setSunFixed(true);

    double masseRatioSol = masse_Sol/masse_Sol;
    cout<< masseRatioSol<<endl;
    double masseRatioJord = masse_Jord/masse_Sol;
    cout<< masseRatioJord<<endl;

    universet->lagLegeme(posSol,hasSol,masseRatioSol);
    universet->lagLegeme(posJord,hasJord,masseRatioJord);

    //settter opp tid og steg for integrasjon og hvilken metode som skal brukes
    double tid = 20.0;  // antall år
    int antallStegPerAAR = 10000;
    int stegTotalt = tid*antallStegPerAAR;
    double dt = tid/stegTotalt;
    bool euler = false;  //bruke euler = true

    //Så gjøres beregninger med euler eller verlet
    Integrand *integrandEuler = new Integrand(dt, euler);
   // Integrand *integrandVerlet = new Integrand(dt, false);
    universet->finnKraftEnergi();
    //universet->finnAngMoment();

    //lager fil for total energi
    double totalEnergi = universet->getTotEnergi();
    double Ek = universet->getKinetiskEnergi();
    double Ep = universet->getPotensiellEnergi();
    double aMoment = universet->getAngMoment();
    ofstream filEnergi;
    filEnergi.open("C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/energiVerlet.txt");
    // double au = 1.5*pow(10,11);
    filEnergi <<setprecision(15)<<setw(25)<<Ek<<" ";
    filEnergi <<setprecision(15)<<setw(25)<<Ep<<" ";
    filEnergi <<setprecision(15)<<setw(25)<<totalEnergi<<" ";
    filEnergi <<setprecision(15)<<setw(25)<<aMoment<<endl;

    // skriver startposisjon til file
    string filNavn = "C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/SolJordFixedEuler.txt";
    universet->skrivTilFil(filNavn);

    /*
    //integrasjon starter her
    for(int i = 1;i<stegTotalt;i++){
        integrandEuler->intEtSteg(*universet);
        //skriver posisjon til fil
        universet->skrivTilFil(filNavn);
        totalEnergi = universet->getTotEnergi();
        Ek = universet->getKinetiskEnergi();
        Ep = universet->getPotensiellEnergi();
        aMoment = universet->getAngMoment();
        filEnergi <<setprecision(15)<<setw(25)<<Ek<<" ";
        filEnergi <<setprecision(15)<<setw(25)<<Ep<<" ";
        filEnergi <<setprecision(15)<<setw(25)<<totalEnergi<<" ";
        filEnergi <<setprecision(15)<<setw(25)<<aMoment<<endl;
    }
*/
    universet->closeFile();
    filEnergi.close();
    Integrand *verletInt = new Integrand(dt, false);
    string filJupiter = "C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/Class/JupiterEnters1000LowDT.txt";

    cout<<"Finished!"<<endl;
    double mRatioJupiter = 1000*masse_Jupiter/masse_Sol;
    double year = 365.0;
    cout<<"Adding jupiter!!"<<endl;
    posSol              = {0.,0.,0.};
    posJord             = {4.058232396538186E-03,9.911461178042031E-01,0.};
    vec posJupiter          = {4.481370147216546E-01,-5.204194188487151E+00,0.};
    hasSol              = {0.,0.,0.};
    hasJord             = {-1.749740782984867E-02*year,7.470265326996520E-05*year,0.};
    vec hasJupiter          = {7.427047094225371E-03*year,1.007031787971608E-03*year,0.};
    universet->lagLegeme(posJupiter,hasJupiter,mRatioJupiter);
    universet->finnKraftEnergi();
    universet->skrivTilFil(filJupiter);

    for(int i = 0;i<stegTotalt;i++){
        verletInt->intEtSteg(*universet);
        universet->skrivTilFil(filJupiter);
    }
    universet->closeFile();
    return 0;
}
// finner ikke filene så venter med å ta i bruk lesing av fil
//metode for å lese posisjon og fart til legemer fra egenprodusert fil med format (x,y,z,vx,vy,vz)
void hentPosFart(string filNavn,int antallLegemer){
    ifstream fil;
    string linje;
    fil.open(filNavn);

    if(fil.is_open()){
        for(int i = 0;i<antallLegemer;i++){
            string linje;
            getline(fil,linje);
            cout<<linje;
        }
    }else{
        cout<<"Could not open the file!! ("<<filNavn<<")"<<endl;
    }
}
