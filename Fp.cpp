#include <iostream>
#include <cmath>
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
  n=n_%p;
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