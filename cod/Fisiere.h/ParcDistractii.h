
#ifndef PARCDISTRACTII_H
#define PARCDISTRACTII_H

#include <vector>
#include <memory>
#include <string>
#include "Atractie.h"
#include "Angajat.h"
#include "Vizitator.h"
#include "Bilet.h"

// Declaratie înainte pentru functia de demonstratie
void demonstreazaTemplatesSiPatterns();

class ParcDistractii {
private:
    std::string nume;
    std::vector<std::unique_ptr<Atractie>> atractii;
    std::vector<std::unique_ptr<Angajat>> angajati;
    std::vector<std::unique_ptr<Vizitator>> vizitatori;
    static int numarParcuri;
    double profitSaptamanal;

public:
    explicit ParcDistractii(const std::string& nume);
    ParcDistractii(const ParcDistractii& other);
    ParcDistractii& operator=(const ParcDistractii& other);
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

    // Noua metoda pentru demonstrarea template-urilor
    void demonstreazaFunctionalitatiAvansate() const;

    double calculezaVenitTotal() const;
    double calculezaCosturiSalariale() const;

    // Metoda pentru verificarea existentei atractiei
    bool existaAtractie(const std::string& numeAtractie) const;

    // Metoda pentru scaderea valabilitatii biletelor
    void scadeValabilitateBilete();

    // Metoda pentru actualizarea profitului saptamanal
    void actualizeazaProfitSaptamanal();

    // Metode pentru validari angajati
    std::string gasesteAtractieFaraOperator() const;
    bool atractieAreOperator(const std::string& numeAtractie) const;
    int getNumarPaznici() const;
    bool verificaZonaOcupata(const std::string& zona) const;

    // Functii statice
    static int getNumarParcuri() { return numarParcuri; }
    static void resetContorParcuri() { numarParcuri = 0; }

    // Getters
    const std::string& getNume() const { return nume; }
    double getProfitSaptamanal() const { return profitSaptamanal; }

    // Metode pentru incarcarea datelor din CSV
    void incarcaAtractiiDinCSV();
    void incarcaAngajatiDinCSV();
    void incarcaVizitatoriDinCSV();
    void incarcaToateDatale();

private:
    void swap(ParcDistractii& other);
    void copiazaAtractii(const std::vector<std::unique_ptr<Atractie>>& sursa);
    void copiazaAngajati(const std::vector<std::unique_ptr<Angajat>>& sursa);
    void copiazaVizitatori(const std::vector<std::unique_ptr<Vizitator>>& sursa);
};

#endif