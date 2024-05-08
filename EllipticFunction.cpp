#include <iostream>
#include <cmath>
#include <string>
#include "Point.cpp"
using namespace std;

class ellipticFunction{
    private:
    // Für die Funktion f=x^3+ax+b im Raum Fp
     Fp a = Fp(0,5);
     Fp b = Fp(0,5);

    public:
    // Konstruktor
    ellipticFunction(Fp a_, Fp b_){
        if(a_.getP()!=b_.getP()){
             throw invalid_argument("a und b sind nicht im gleichen Körper (verschiedene p) ");
        }
        int p=a_.getP();
        if(!(((Fp(4,p)*(a_^3)) + (Fp(27,p)*(b^2))) == Fp(0,p))){
            throw invalid_argument("Keine elliptische Kurve: Term hat mehrfache Nullstellen. ");
        }
        a=a_;
        b=b_;
    }

    // get-Funktionen
    Fp getA(){
        return a;
    }
    Fp getB(){
        return b;
    }


    // Rechenoperationen
    point add(point P, point Q){
        Fp x1=P.getX();
        Fp x2=Q.getX();
        Fp y1=P.getY();
        Fp y2=Q.getY();
        bool inf1=P.getInf();
        bool inf2=Q.getInf();
        int p=x1.getP();
        if(inf1){ // Fall 1: P oder Q ist inf
            return Q.copy();
        } else if(inf2){
            return P.copy();
        } else if(x1==x2 && y1==-y2){ // Fall 2: x1 = x2 ∧ y1 = −y2
            return point(Fp(), Fp(), true);
        } else if(P==Q){ // Fall 3: Addition mit sich selbst (falls y1 ̸ = 0, sonst selbstinvers)
            Fp x3 = ((((Fp(3,p)*(x1^2))+a)/(Fp(2,p)*y1))^2)-(Fp(2,p)*x1);
            Fp y3 = -y1+((Fp(3,p)*(x1^2)+a)/(Fp(2,p)*y1))*(x1-x3);
            return point(x3,y3);
        } else { // Fall 4: Addition verschiedener Punkte
            Fp x3 = ((((y2-y1)/(x2-x1))^2)-x1)-x2;
            Fp y3 = -y1+((y2-y1)/(x2-x1))*(x1-x3);
            return point(x3,y3);
        }    
    }

    point mult(int k, point P){
        if(k==0){
            return point(true);
        } 
        if(k==1){
            return P.copy();
        }
        point Q=P.copy();
        for(int i=1;i<k;i++){
            Q=add(P,Q);
        }
        return Q;
    } //geht auch logarithmisch aber naja

    // Funktionsrückgabe
    Fp f(Fp x){
        return ((x^3)+(a*x))+b;
    }

    // Eulers criterion
    bool quadRes(Fp a){
        Fp l=a^((a.getP()-1)/2);
        Fp k=Fp(1,a.getP());
        if( (a^((a.getP()-1)/2))== Fp(1,a.getP()) ){
            return true;
        } else if((a^((a.getP()-1)/2))== Fp(a.getP()-1,a.getP())){
            return false;
        } else {
            std::cout << "Eulers Kriterium ergibt fuer "<<a.stringify()<<" "<< (a^((a.getP()-1)/2)).stringify()<<". "<< "\n";
            return false;
        }
    }

    
};