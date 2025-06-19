#ifndef VIZITATOR_H
#define VIZITATOR_H

#include <string>
#include <iostream>
#include <memory>
#include "Bilet.h"
#include "Atractie.h"

class Vizitator {
protected:
    std::string nume;
    int varsta;
    int inaltime;
    std::unique_ptr<Bilet> bilet;

public:
    Vizitator(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet);
    virtual ~Vizitator() = default;

    virtual void print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out,const Vizitator& viz){
        viz.print(out);
        return out;
    }
    virtual std::string getTip() const = 0;
    virtual bool poateAccesaAtractia(Atractie& atractie) const;

    // Getters
    std::string getNume() const { return nume; }
    int getVarsta() const { return varsta; }
    int getInaltime() const { return inaltime; }
    const Bilet* getBilet() const { return bilet.get(); }
};

class Copil : public Vizitator {

public:
    Copil(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool insotitDeAdult);
    void print(std::ostream& out) const override{
         out << "Nume: " << nume << std::endl;
         out << "Varsta: " << varsta << " ani" << std::endl;
         out << "Inaltime: " << inaltime << " cm" << std::endl;
         if (bilet) {
           out << "Tip bilet: " << bilet->getTip() << std::endl;
           out << "Pret bilet: " << bilet->calculeazaPretFinal() << " RON" << std::endl;
         }
    }
    std::string getTip() const override { return "Copil"; }
    bool poateAccesaAtractia(Atractie& atractie) const override{
      return inaltime>=atractie.getInaltimeMinima();
    }

};

class Adolescent : public Vizitator {
private:
    bool areBuletin;

public:
    Adolescent(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool areBuletin);
    void print(std::ostream& out) const override{
        out << "Nume: " << nume << std::endl;
        out << "Varsta: " << varsta << " ani" << std::endl;
        out << "Inaltime: " << inaltime << " cm" << std::endl;
        if (bilet) {
            out << "Tip bilet: " << bilet->getTip() << std::endl;
            out << "Pret bilet: " << bilet->calculeazaPretFinal() << " RON" << std::endl;
        }
    }
    std::string getTip() const override { return "Adolescent"; }
    bool getAreBuletin() const { return areBuletin; }
};

class Adult : public Vizitator {
private:
    std::string ocupatie;

public:
    Adult(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, const std::string& ocupatie);
    void print(std::ostream& out) const override{
        out << "Nume: " << nume << std::endl;
        out << "Varsta: " << varsta << " ani" << std::endl;
        out << "Inaltime: " << inaltime << " cm" << std::endl;
        if (bilet) {
            out << "Tip bilet: " << bilet->getTip() << std::endl;
            out << "Pret bilet: " << bilet->calculeazaPretFinal() << " RON" << std::endl;
        }
    }
    std::string getTip() const override { return "Adult"; }
    std::string getOcupatie() const { return ocupatie; }
};

#endif

