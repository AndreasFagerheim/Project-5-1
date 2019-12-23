#include <iostream>
#include <cmath>
#include <armadillo>
#include <iomanip>


using namespace std;
using namespace arma;



void eulerForwardMat(mat &pos,mat &has, int n, double dt, double masse );
void eulerForward(vec &posX,vec &posY,vec &hasX,vec &hasY, int n, double dt,double masse);
//void verletMatMat(mat &pos,mat &has, int n, double dt, double masse );
void verlet(vec &posX,vec &posY,vec &hasX,vec &hasY, int n, double dt,double masse);
void toFile(string filNavn, vec x, vec y, vec t,int n);

int main(int argc, char *argv[])
{
    double start = 0;
    double stop = 1.0;
    int n = atoi(argv[1]);
    double dt = (stop-start)/(n);
    cout<< "dt = "<<dt<<endl;
    cout<<argc<<endl;

    //delt opp i vektor for x,y,z komponenter
    vec posX = zeros<vec>(n);
    vec hasX = zeros<vec>(n);

    vec posY = zeros<vec>(n);
    vec hasY = zeros<vec>(n);

    //matriser test
    mat pos(n,2);
    mat has(n,2);

    //setter opp vector for tid
    vec t = zeros<vec>(n);
    for(int i = 0;i<n;i++){
        t[i] = i*dt;
    }
    //startbetingelser
    double masse = 1.0;
    posX[0] = 1.0;// jorden er 1 Au fra solen;
    posY[0] = 0.0;// velged selv å sette den her slik at det kun er fart i y retning
    hasX[0] = 0.0;
    hasY[0] = 2*4*atan(1); //2pi

    // starte beregninger av posisjon til jorden med solen stille i sentrum.
    eulerForward(posX,posY,hasX,hasY,n,dt,masse);
    string path = "C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward.txt";
    toFile(path,posX,posY,t,n);
    verlet(posX,posY,hasX,hasY,n,dt,masse);
    toFile("C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet.txt",posX,posY,t,n);
    cout<<"Ferdig beregnet!"<<endl;

    //sjekkestabilitet som funksjon av dt oppgave b)
    vec antallSteg = {10,100,500,1000,10000}; //antall steg
    dt = (start-stop)/n;
    double steg = 1/10.;
    for(int k = 0;k<5;k++){
        vec t2 = zeros<vec>(antallSteg(k));

        steg = 1./antallSteg(k);
        t2[k] = k*steg;
        eulerForward(posX,posY,hasX,hasY,antallSteg(k),steg,masse);
        ostringstream path ;
        path <<"C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/EulerForward"<<steg<<".txt";
        toFile(path.str(),posX,posY,t2,antallSteg(k));

        verlet(posX,posY,hasX,hasY,antallSteg(k),steg,masse);
        ostringstream path2 ;
        path2 <<"C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verlet"<<steg<<".txt";
        toFile(path2.str(),posX,posY,t2,antallSteg(k));
    }
    double pi = 4*atan(1);
    vec startfartY = {2.6*pi,2.7*pi,2.8*pi,2.82*pi,2.9*pi};
    for(int i= 0;i<5;i++){
        cout<<"escaping?"<<endl;
        hasY[0] = startfartY(i);
        verlet(posX,posY,hasX,hasY,n,dt,masse);
        ostringstream path3 ;
        path3 <<"C:/Users/Andreas/Documents/Project 5/Project-5/Updates After deadline/Data/NoClass/verletUnslippe"<<i<<".txt";
        toFile(path3.str(),posX,posY,t,n);

    }
    return 0;
}

//using vectors
void eulerForward(vec &posX, vec &posY,vec &hasX, vec &hasY, int n, double dt, double masse ){
    double dis, a;
    double massePI = masse*4*(4*atan(1)*4*atan(1));
    for(int i = 0;i<(n-1);i++){
        dis = sqrt(posX[i]*posX[i] +posY[i]*posY[i]);
        a = - (massePI)/(dis*dis*dis);
        //x-komponent
        hasX[i+1] = hasX[i] + dt* a*posX[i];
        posX[i+1] = posX[i] + dt*hasX[i];
        //y-komponent
        hasY[i+1] = hasY[i] + dt* a*posY[i];
        posY[i+1] = posY[i] + dt*hasY[i];
    }
}
void eulerForwardMat(mat &pos,mat &has, int n, double dt, double masse ){
    double dis, a;
    double massePI = masse*4*(4*atan(1)*4*atan(1));
    for(int i = 0;i<(n-1);i++){
        dis = sqrt(pos(i,0)*pos(i,0) +pos(i,1)*pos(i,1));
        a = - (massePI)/(dis*dis*dis);
        //x-komponent
        has(i+1,0) = has(i,0) + dt* a*pos(i,0);
        pos(i+1,0) = pos(i,0) + dt*has(i,0);
        //y-komponent
        has(i+1,1) = has(i,1) + dt* a*pos(i,1);
        pos(i+1,1) = pos(i,1) + dt*has(i,1);
    }
}
void verlet(vec &posX, vec &posY,vec &hasX, vec &hasY, int n, double dt, double masse ){
    double dis, a;
    double massePI = masse*4*(4*atan(1)*4*atan(1));
    for(int i = 0; i<(n-1);i++){
        dis = sqrt(posX[i]*posX[i] +posY[i]*posY[i]);
        a = - (massePI)/(dis*dis*dis);
        //x-komponent
        posX[i+1] = posX[i] + dt*hasX[i]+ 0.5*(dt*dt*a*posX[i]);
        hasX[i+1] = hasX[i] + 0.5*dt* (a*(posX[i]+posX[i+1]));
        //y-komponent
        posY[i+1] = posY[i] + dt*hasY[i]+ 0.5*(dt*dt*a*posY[i]);
        hasY[i+1] = hasY[i] + 0.5*dt* (a*(posY[i]+posY[i+1]));
    }
}

void toFile(string filNavn, vec x, vec y, vec t,int n){
    ofstream outfile;
    outfile.open(filNavn);
    if(outfile.is_open()){
        cout<<"writing to file..."<<endl;
        outfile <<"t"<<setw(15) <<"x"<<setw(15) <<"y"<<endl;
        outfile <<setprecision(10);
        for(int j=0;j<n;j++){
            outfile << setw(5)<<t[j]<<" " << setw(15) << x[j]<<" " << setw(15)<< y[j] << endl;
        }
    }else{
        cout<<"could not open file"<<filNavn<<endl;
        exit(1);
    }
    outfile.close();
    cout<<"done writing to file"<<endl;
}
