#ifndef BILET_H
#define BILET_H

#include <stdexcept>
#include <string>
#include <iostream>

class Bilet {
protected:
    double pret;
    int valabilitateZile;

public:
    Bilet(double pret, int valabilitateZile): pret(pret), valabilitateZile(valabilitateZile) {}
    virtual ~Bilet() = default;

    virtual void print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out,const Bilet& bil){
        bil.print(out);
        return out;
    }
    virtual double calculeazaPretFinal() const=0;
    virtual std::string getTip() const = 0;
    virtual double calculeazaReducere() const;

    // Getters
    double getPret() const { return pret; }
    int getValabilitateZile() const { return valabilitateZile; }
};

class BiletCopil : public Bilet {
private:
    int varstaCopil;

public:
    BiletCopil(int valabilitateZile, int varstaCopil): Bilet(45, valabilitateZile), varstaCopil(varstaCopil) {
    if (varstaCopil > 15) {
        throw std::invalid_argument("Copilul e prea mare, trebuie sa cumparati un bilet adult.");
    }
    }

    void print(std::ostream& out) const override{
        out << "Tip Bilet: Bilet Copil"<<std::endl;
        out << "Valabilitate: " << valabilitateZile << " zile" << std::endl;
        out << "Varsta copil: " << varstaCopil << " ani" << std::endl;
        out << "Reducere: " << calculeazaReducere() << "%" << std::endl;
        out << "Pret bilet: "<< calculeazaPretFinal()<<"RON"<<std::endl;

    }
    std::string getTip() const override { return "Bilet Copil"; }
    int getVarstaCopil() const { return varstaCopil; }

    double calculeazaReducere() const override{
        if (varstaCopil <= 5)
            return 50.0; // reducere 50%
        else if (varstaCopil <= 12)
            return 30.0; // reducere 30%
        else if (varstaCopil<=15){
            return 10.0; // reducere 10%
        }
        return 0.0;
    }
    double calculeazaPretFinal()const override{
      double reducere=calculeazaReducere();
      return pret-pret/reducere;
    }
};

class BiletAdult : public Bilet {
private:
    bool Platitavans;

public:
    BiletAdult(int valabilitateZile, bool Platitavans): Bilet(85, valabilitateZile), Platitavans(Platitavans) {}

    void print(std::ostream& out) const override{
        out << "Tip Bilet: Bilet Adult"<<std::endl;
        out << "Valabilitate: " << valabilitateZile << " zile" << std::endl;
        out << "Platit avans: " << (Platitavans ? "Da":"Nu")<< std::endl;
        out << "Pret bilet: "<< calculeazaPretFinal()<<"RON"<<std::endl;
    }

    std::string getTip() const override { return "Bilet Adult"; }

    bool getPlatitavans() const { return Platitavans; }
    double calculeazaPretFinal() const override{
      if(Platitavans)return pret+50;
      return pret;
    }
};

class BiletAllfamily : public Bilet {
private:
    bool accesLounge;

public:
    BiletAllfamily(int valabilitateZile, bool accesLounge): Bilet(240, valabilitateZile), accesLounge(accesLounge) {}

    void print(std::ostream& out) const override{
        out << "Tip Bilet: Bilet All family"<<std::endl;
        out << "Valabilitate: " << valabilitateZile << " zile" << std::endl;
        out << "Acces Lounge: " << (accesLounge ? "Da":"Nu")<< std::endl;
        out << "Pret bilet: "<< calculeazaPretFinal()<<"RON"<<std::endl;
    }
    std::string getTip() const override { return "Bilet VIP"; }
    double calculeazaPretFinal() const override{
        if(accesLounge)return pret+100;
        return pret;
    }

    bool getAccesLounge() const { return accesLounge; }
};

#endif
