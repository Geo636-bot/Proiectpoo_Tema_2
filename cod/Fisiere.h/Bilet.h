
#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>

class Bilet {
protected:
    double pret;
    int valabilitateZile;

public:
    Bilet(double pret, int valabilitateZile);
    virtual ~Bilet() = default;
    
    virtual std::string getTip() const = 0;
    virtual double calculeazaPretFinal() const;
    
    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Bilet& bilet);
    
    // Getters
    double getPret() const { return pret; }
    int getValabilitateZile() const { return valabilitateZile; }

protected:
    virtual void afiseaza(std::ostream& os) const;
};

class BiletCopil : public Bilet {
private:
    int varstaCopil;

public:
    BiletCopil(double pret, int valabilitateZile, int varstaCopil);
    std::string getTip() const override { return "Bilet Copil"; }
    double calculeazaPretFinal() const override;
    int getVarstaCopil() const { return varstaCopil; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletAdult : public Bilet {
private:
    bool includeFastPass;

public:
    BiletAdult(double pret, int valabilitateZile, bool includeFastPass);
    std::string getTip() const override { return "Bilet Adult"; }
    double calculeazaPretFinal() const override;
    bool getIncludeFastPass() const { return includeFastPass; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletVIP : public Bilet {
private:
    bool accesLounge;

public:
    BiletVIP(double pret, int valabilitateZile, bool accesLounge);
    std::string getTip() const override { return "Bilet VIP"; }
    double calculeazaPretFinal() const override;
    bool getAccesLounge() const { return accesLounge; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
