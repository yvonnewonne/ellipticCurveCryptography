#include <iostream>
#include <cmath>
//#include <vector>
#include <string>
#include "EllipticFunction.cpp"
using namespace std;

void testFp() {
    int p=17;
    std::cout<<"Wir betrachten den Körper F"<<p<<".\n";
    Fp a=Fp(6,p);
    Fp b=Fp(15,p);
    std::cout<<a.stringify()<<"+"<<b.stringify()<<"="<<(a+b).stringify()<<"\n";
    std::cout<<a.stringify()<<"*"<<b.stringify()<<"="<<(a*b).stringify()<<"\n";
    std::cout<<a.stringify()<<"-"<<b.stringify()<<"="<<(a-b).stringify()<<"\n";
    std::cout<<"a^3="<<(a^(3)).stringify()<<"\n";
}

int main() {
    std::cout<<"Programm läuft.\n";
    testFp();
    return 0;
}

