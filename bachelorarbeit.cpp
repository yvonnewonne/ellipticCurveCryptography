#include <iostream>
#include <cmath>
//#include <vector>
#include <string>
using namespace std;


bool isPrime(int n_)
{
    int n=n_;
    if(n<0){
        n=-n;
    }
    if(n==1 || n==0){
        return false;
    }
    for (int p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (n%p==0) {
            return false;
        }
    }
    return true;
}

class Fp{
    // Klasse, die Elemente aus Fp verwaltet
    private:
    int p=5;
    int n=0;

    public:
    // Konstruktor
    Fp(int n_, int p_){
        // if(!p.isPrime){
        //     std::cout<<"p ist keine Primzahl! ";
        //     throw invalid_argument("p ist keine Primzahl.");
        // }
        p=p_;
        n=n%p;
        if(n<0){
            n=n+p;
        }
    }

    Fp(){
        p=5;
        n=0;
    }

    // Operatoren Overload
    Fp operator + (const Fp& m) const{
        if(p != m.getP()){
            throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
        }
        return Fp(n+m.get(), p);
    }

    Fp operator - (const Fp& m) const{
        if(p != m.getP()){
            throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
        }
        return Fp(n-m.get(),p);
    }

    Fp operator * (const Fp& m) const{
        if(p != m.getP()){
            throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
        }
        return Fp((n%p)*(m.get()%p),p);
    }

    bool operator == (const Fp& m) const {
        if(p != m.getP()){
            throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
        }
        return (n-m.get())%p==0;
    }

    Fp operator - () const{
        return Fp(-n,p);  
    }

    Fp operator ^ (const int& k) const{
        if(k<0){
            throw invalid_argument("Für negative Werte funktioniert Potenzieren noch nicht.");
        }
        return Fp(n^k,p);
    }
    //Nach Fermat a/b=a*b^-1=a*b^(p-2)
    Fp operator / (const Fp& b) const{
        if(p != b.getP()){
            throw invalid_argument("n und m sind in verschiedenen Körpern (unterschiedliches p)");
        } 
        return (*this)*(b^(p-2));
    }

    // get-Funktionen
    int get() const{
        return n;
    }
    int getP() const{
        return p;
    }

    // toString-Funktionen
    string stringify() {
        return to_string(n);
    }
};

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
    
    point(bool inf_){
        if(inf_){
            x=Fp(0,5);
            y=Fp(0,5);
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
        return point(true);
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
