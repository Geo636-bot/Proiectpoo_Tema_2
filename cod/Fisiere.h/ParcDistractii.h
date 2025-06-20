
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
    static int numarParcuri; // atribut static

public:
    explicit ParcDistractii(const std::string& nume);
    ParcDistractii(const ParcDistractii& other); // copy constructor
    ParcDistractii& operator=(const ParcDistractii& other); // assignment operator
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

    // Metode pentru verificari cu dynamic_cast
    void verificaAccesAtractie(const std::string& numeVizitator, const std::string& numeAtractie) const;
    void demonstratieDynamicCast() const;
    double calculezaVenitTotal() const;
    double calculezaCosturiSalariale() const;

    // Funcții statice
    static int getNumarParcuri() { return numarParcuri; }
    static void resetContorParcuri() { numarParcuri = 0; }

    // Getters
    const std::string& getNume() const { return nume; }
    size_t getNumarAtractii() const { return atractii.size(); }
    size_t getNumarAngajati() const { return angajati.size(); }
    size_t getNumarVizitatori() const { return vizitatori.size(); }

private:
    void swap(ParcDistractii& other);
    void copiazaAtractii(const std::vector<std::unique_ptr<Atractie>>& sursa);
    void copiazaAngajati(const std::vector<std::unique_ptr<Angajat>>& sursa);
    void copiazaVizitatori(const std::vector<std::unique_ptr<Vizitator>>& sursa);
};

#endif
