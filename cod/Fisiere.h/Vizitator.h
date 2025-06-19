

#ifndef VIZITATOR_H
#define VIZITATOR_H

#include <string>
#include <iostream>
#include <memory>
#include "Bilet.h"

class Vizitator {
protected:
    std::string nume;
    int varsta;
    int inaltime;
    std::unique_ptr<Bilet> bilet;

public:
    Vizitator(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet);
    virtual ~Vizitator() = default;
    
    virtual std::string getTip() const = 0;
    virtual bool poateAccesaAtractia(int inaltimeMinima, int varstaNecesara = 0) const;
    
    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Vizitator& vizitator);
    
    // Getters
    std::string getNume() const { return nume; }
    int getVarsta() const { return varsta; }
    int getInaltime() const { return inaltime; }
    const Bilet* getBilet() const { return bilet.get(); }

protected:
    virtual void afiseaza(std::ostream& os) const;
};

class Copil : public Vizitator {
private:
    bool insotitDeAdult;

public:
    Copil(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool insotitDeAdult);
    std::string getTip() const override { return "Copil"; }
    bool poateAccesaAtractia(int inaltimeMinima, int varstaNecesara = 0) const override;
    bool getInsotitDeAdult() const { return insotitDeAdult; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Adolescent : public Vizitator {
private:
    bool areBuletin;

public:
    Adolescent(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool areBuletin);
    std::string getTip() const override { return "Adolescent"; }
    bool getAreBuletin() const { return areBuletin; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Adult : public Vizitator {
private:
    std::string ocupatie;

public:
    Adult(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, const std::string& ocupatie);
    std::string getTip() const override { return "Adult"; }
    std::string getOcupatie() const { return ocupatie; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
