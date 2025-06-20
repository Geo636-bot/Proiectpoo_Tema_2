
#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>
#include <memory>

class Bilet {
protected:
    double pret;
    int valabilitateZile;
    static double pretMediu; // atribut static

public:
    Bilet(double pret, int valabilitateZile);
    Bilet(const Bilet& other);
    Bilet& operator=(const Bilet& other);
    virtual ~Bilet() = default;
    
    // Constructor virtual (clone pattern)
    virtual std::unique_ptr<Bilet> clone() const = 0;
    
    virtual std::string getTip() const = 0;
    virtual double calculeazaPretFinal() const;
    
    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Bilet& bilet);
    
    // Funcții statice
    
    static void actualizarePretMediu(double nouPret);
    

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Bilet& other);
};

class BiletCopil : public Bilet {
private:
    int varstaCopil;

public:
    BiletCopil(double pret, int valabilitateZile, int varstaCopil);
    BiletCopil(const BiletCopil& other);
    BiletCopil& operator=(const BiletCopil& other);
    
    std::unique_ptr<Bilet> clone() const override;
    std::string getTip() const override { return "Bi Let Copil"; }
    double calculeazaPretFinal() const override;
    
protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletAdult : public Bilet {
private:
    bool includeFastPass;

public:
    BiletAdult(double pret, int valabilitateZile, bool includeFastPass);
    BiletAdult(const BiletAdult& other);
    BiletAdult& operator=(const BiletAdult& other);
    
    std::unique_ptr<Bilet> clone() const override;
    std::string getTip() const override { return "Bilet Adult"; }
    double calculeazaPretFinal() const override;
    

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletVIP : public Bilet {
private:
    bool accesLounge;

public:
    BiletVIP(double pret, int valabilitateZile, bool accesLounge);
    BiletVIP(const BiletVIP& other);
    BiletVIP& operator=(const BiletVIP& other);
    
    std::unique_ptr<Bilet> clone() const override;
    std::string getTip() const override { return "Bilet VIP"; }
    double calculeazaPretFinal() const override;
    

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
