#include <iostream>
#include <cmath>
#include <string>
#include "Fp.cpp"
using namespace std;

class point{
    private:
    Fp x=Fp(0,5);
    Fp y=Fp(0,5);
    bool inf=false; 
    
    public:
    // Konstruktor
    point(Fp x_, Fp y_, bool inf_){
        if(inf_){ // ist unendlich
            x=x_;
            y=y_;
            inf=true;
        } else { // ist nicht unendlich
            x=x_;
            y=y_;
            inf=false;
        }        
    }

    point(Fp x_, Fp y_){
        x=x_;
        y=y_;
        inf=false;      
    }
    
    point(int p, bool inf_){
        if(inf_){
            x=Fp(0,p);
            y=Fp(0,p);
            inf=true;
        } else {
            throw invalid_argument("Weder ein Punkt noch inf übergeben");
        }
    }

    // Operator-Overload
    bool operator == (const point& Q) const {
        if( inf!=Q.getInf()){
            return false;
        } else if (inf) {
            return true; 
        } else if (x==Q.getX() && y==Q.getY()){
            return true; 
        } else {
            return false;
        }
    }

    point operator - () const{
       if(inf){
        return point(x.getP(), true);
       } else {
        return point(x,-y);
       } 
    }

    // Get-Funktionen
    Fp getX() const{
        return x;
    }

    Fp getY() const{
        return y;
    }

    bool getInf() const{
        return inf;
    }

    // Sonstiges

    point inverse(){
        return point(x,-y,inf);
    }

    point copy(){
        return point(x, y, inf);
    }

    string stringify(){
        if(inf){
            return " inf  ";
        }  else {
            return "("+x.stringify()+", "+y.stringify()+")";
        }
    }
};