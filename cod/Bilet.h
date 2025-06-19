#ifndef BILET_H
#define BILET_H

#include <iostream>
#include <string>
using namespace std;

// Clasa de baza


class Bilet {
protected:
    double pret;
    int valabilitateZile;

public:
    Bilet(double pret, int valabilitateZile)
        : pret(pret), valabilitateZile(valabilitateZile) {}

    virtual void print(ostream& out) const = 0;

    friend ostream& operator<<(ostream& out,const Bilet& bil){
        bil.print(out);
        return out;
    }

    virtual ~Bilet() {}
};

// Clasa derivata BiletCopil
class BiletCopil : public Bilet {
private:
    int varstaCopil;

public:
    BiletCopil(double pret, int valabilitateZile, int varstaCopil)
        : Bilet(pret, valabilitateZile), varstaCopil(varstaCopil) {}

    double calculeazaReducere() const{
        if (varstaCopil <= 5)
            return 50.0; // reducere 50%
        else if (varstaCopil <= 12)
            return 30.0; // reducere 30%
        else if (varstaCopil<=15){
            return 10.0; // reducere 10%
            }
         return 0.0;
    }
    void print(ostream& out) const override{
        out << "Tip Bilet: Bilet Copil"<<endl;
        out << "Pret: " << pret << " RON" << endl;
        out << "Valabilitate: " << valabilitateZile << " zile" << endl;
        out << "Varsta copil: " << varstaCopil << " ani" << endl;
        out << "Reducere: " << calculeazaReducere() << "%" << endl;

    }

};

// Clasa derivata BiletAdult
class BiletAdult : public Bilet {
private:
    bool Platitavans;

public:
    BiletAdult(double pret, int valabilitateZile, bool Platitavans)
        : Bilet(pret, valabilitateZile), Platitavans(Platitavans) {}

    void print(ostream& out) const override{
        out << "Tip Bilet: Bilet Adult"<<endl;
        out << "Pret: " << pret << " RON" << endl;
        out << "Valabilitate: " << valabilitateZile << " zile" << endl;
        out << "Platit avans: " << (Platitavans ? "Da":"Nu")<< endl;
    }

};

// Clasa derivata BiletVIP
class BiletAllfamily : public Bilet {
private:
    bool accesLounge;

public:
    BiletAllfamily(double pret, int valabilitateZile, bool accesLounge)
        : Bilet(pret, valabilitateZile), accesLounge(accesLounge) {}

    void print(ostream& out) const override{
        out << "Tip Bilet: Bilet VIP"<<endl;
        out << "Pret: " << pret << " RON" << endl;
        out << "Valabilitate: " << valabilitateZile << " zile" << endl;
        out << "Acces Lounge: " << (accesLounge ? "Da":"Nu")<< endl;
    }
};

#endif