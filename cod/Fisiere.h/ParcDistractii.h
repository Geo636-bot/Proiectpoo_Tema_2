
#ifndef PARCDISTRACTII_H
#define PARCDISTRACTII_H

#include <vector>
#include <memory>
#include <string>
#include "Atractie.h"
#include "Angajat.h"
#include "Vizitator.h"

class ParcDistractii {
private:
    std::string nume;
    std::vector<std::unique_ptr<Atractie>> atractii;
    std::vector<std::unique_ptr<Angajat>> angajati;
    std::vector<std::unique_ptr<Vizitator>> vizitatori;

public:
    ParcDistractii(const std::string& nume);
    ~ParcDistractii() = default;

    // Metode pentru adaugare
    void adaugaAtractie(std::unique_ptr<Atractie> atractie);
    void adaugaAngajat(std::unique_ptr<Angajat> angajat);
    void adaugaVizitator(std::unique_ptr<Vizitator> vizitator);

    // Metode pentru afisare
    void afiseazaAtractii() const;
    void afiseazaAngajati() const;
    void afiseazaVizitatori() const;
    void afiseazaStatistici() const;

    // Metode pentru verificari
    void verificaAccesAtractie(const std::string& numeVizitator, const std::string& numeAtractie) const;
    double calculezaVenitTotal() const;
    double calculezaCosturiSalariale() const;

    // Getters
    std::string getNume() const { return nume; }
    size_t getNumarAtractii() const { return atractii.size(); }
    size_t getNumarAngajati() const { return angajati.size(); }
    size_t getNumarVizitatori() const { return vizitatori.size(); }
};

#endif
