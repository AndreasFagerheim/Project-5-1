#include "univers.h"
#include <iomanip>



Univers::Univers(){
    kinetiskEnergi = 0;
    potensiellEnergi = 0;
    konstantG = 4*(4*atan(1)*4*atan(1));  // 4pi^2

}
Univers::Univers(double nyG)
{
    kinetiskEnergi = 0;
    potensiellEnergi = 0;
    konstantG = nyG;
}

void Univers::lagLegeme(vec pos, vec has, double massen){
    legemer.push_back(Legemer(pos,has,massen));
}
void Univers::addLegeme(const Legemer &legeme){
    legemer.push_back(legeme);
}

//Finner kraft og energi til de to legemene (oppgave a,b,c,d) (funket ikke)
void Univers::finnKraftEnergiTo(){

}
// Finner den nåeværende kraften hver planet opplever og dens kinetiske og potensielle energi
// metoden kan brukes for systemer av ønsket antall legemer
void Univers::finnKraftEnergi(){
    kinetiskEnergi = 0;
    potensiellEnergi = 0;

    //setter kraften til hvert legeme i systemet til null
    for(Legemer &legeme:legemer){
        legeme.resetKraft();
    }

    for(int i = 0;i<getAntallLegemer();i++){
        Legemer &legeme2 = legemer[i];
        for(int j=i+1;j<getAntallLegemer();j++){
            //cout<<"setting forces"<<endl;
            Legemer &legeme3 = legemer[j];
            vec rVec = legeme2.posisjon -legeme3.posisjon; // for avstanden mellom to legemer
            double rNorm = norm(rVec);
            double kraft = konstantG*legeme2.masse*legeme3.masse/(rNorm*rNorm*rNorm);
            vec     kraftVec = kraft* rVec;

            // ikke relativistikk ->gjør følgende
            legeme2.kraft -= kraftVec;
            legeme3.kraft += kraftVec;
            potensiellEnergi -= kraft*rNorm;
        }
        double v2 = dot(legeme2.hastighet,legeme2.hastighet);

        kinetiskEnergi += legeme2.masse*0.5*v2;
    }
    //hvis solen er fast midtpunkt settes kraften til null for å hindre bevegelse
    if(isSunFixed()){
        legemer[0].kraft <<0<<0<<0;
    }
}
// må lages
void Univers::finnAngMoment(){
    vec angMomVec ;
    angMomVec <<0<<0<<0;

    for(Legemer &legeme:legemer){
        angMomVec+= legeme.masse*cross(legeme.posisjon,legeme.hastighet);
    }
    angMoment = norm(angMomVec);
}

double Univers::getTotEnergi() const{
    return kinetiskEnergi+potensiellEnergi;
}
double Univers::getKinetiskEnergi() const{
    return kinetiskEnergi;
}
double Univers::getPotensiellEnergi() const{
    return potensiellEnergi;
}

double Univers::getAngMoment() const{
    return angMoment;
}

int Univers::getAntallLegemer() const{
    legemer.size();
}
bool Univers::isSunFixed() const{
    return bFixedSun;
}
vector<Legemer> &Univers::getLegemer(){
    return legemer;
}
void Univers::setSunFixed(bool fixedSun){
    bFixedSun = fixedSun;
}
//må lages

void Univers::skrivTilFil(string filNavn){
    if(!filUnivers.good()||!filUnivers.is_open()){
        cout<<"opening file "<<filNavn<<endl;
        filUnivers.open(filNavn);
        if(!filUnivers.good()){
            cout<<"error opening file "<<endl;
            terminate();
        }
    }
    for(Legemer &legeme: legemer){
        for(int i = 0;i<3;i++){
            filUnivers<<setw(19)<<setprecision(10)<<legeme.posisjon(i);

        }

    }
    filUnivers<<endl;
   /* filUnivers.open(filNavn,ios_base::app);
    if(filUnivers.is_open()){

        for(Legemer &legeme:legemer){
            for(int i = 0;i<3;i++){
                cout<<setw(20)<<setprecision(10)<<legeme.posisjon[i];
                filUnivers <<setw(5)<<setprecision(15)<<3;//legeme.posisjon[i];
            }
            //legeme.posisjon.save(filUnivers,raw_binary);
        }
        filUnivers<<endl;
        cout<<endl;
    }else{
        cout<<"could not open file!"<<endl;
        exit(1);
    }*/
}
void Univers::closeFile(){
    filUnivers.close();
}
