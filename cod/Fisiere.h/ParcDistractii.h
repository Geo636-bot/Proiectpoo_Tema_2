

#ifndef PARCDISTRACTII_H
#define PARCDISTRACTII_H

#include <vector>
#include <memory>
#include <string>
#include "Atractie.h"
#include "Angajat.h"
#include "Vizitator.h"
#include "Observer.h"
#include "StatisticsManager.h"
#include "AtractieFactory.h"

class ParcDistractii : public Subject {
private:
    std::string nume;
    std::vector<std::unique_ptr<Atractie>> atractii;
    std::vector<std::unique_ptr<Angajat>> angajati;
    std::vector<std::unique_ptr<Vizitator>> vizitatori;
    static int numarParcuri; // atribut static
    
    // Template statistici pentru diferite tipuri
    StatisticsManager<double> statisticiPreturi;
    StatisticsManager<int> statisticiVarste;
    StatisticsManager<int> statisticiInaltimi;
    
    // Factory pentru atractii
    AtractieFactoryManager factoryManager;

public:
    explicit ParcDistractii(const std::string& nume);
    ParcDistractii(const ParcDistractii& other); // copy constructor
    ParcDistractii& operator=(const ParcDistractii& other); // assignment operator
    ~ParcDistractii() = default;

    [[nodiscard]]bool atractieExista(const std::string& nume) const;


    // Metode pentru adaugare
    void adaugaAtractie(std::unique_ptr<Atractie> atractie);
    void adaugaAngajat(std::unique_ptr<Angajat> angajat);
    void adaugaVizitator(std::unique_ptr<Vizitator> vizitator);

    std::unique_ptr<Atractie> creeazaAtractieFactory(
        const std::string& tip,
        const std::string& nume,
        int inaltimeMinima,
        int capacitate,
        int parametruSpecific);

    // Metode pentru afisare
    void afiseazaAtractii() const;
    void afiseazaAngajati() const;
    void afiseazaVizitatori() const;
    void afiseazaStatistici() const;
    void afiseazaStatisticiTemplate() const;



    // Metode pentru verificari cu dynamic_cast
    void verificaAccesAtractie(const std::string& numeVizitator, const std::string& numeAtractie) const;
    void demonstratieDynamicCast() const;
    [[nodiscard]] double calculezaVenitTotal() const;
    [[nodiscard]] double calculezaCosturiSalariale() const;

    // Funcții statice
    static int getNumarParcuri() { return numarParcuri; }
    //static void resetContorParcuri() { numarParcuri = 0; }

    // Getters
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] size_t getNumarAtractii() const { return atractii.size(); }
    //[[nodiscard]] size_t getNumarAngajati() const { return angajati.size(); }
    [[nodiscard]] size_t getNumarVizitatori() const { return vizitatori.size(); }
    
    // Getters pentru statistici template
    const StatisticsManager<double>& getStatisticiPreturi() const { return statisticiPreturi; }
    const StatisticsManager<int>& getStatisticiVarste() const { return statisticiVarste; }
    const StatisticsManager<int>& getStatisticiInaltimi() const { return statisticiInaltimi; }

private:
    void swap(ParcDistractii& other) noexcept;
    void copiazaAtractii(const std::vector<std::unique_ptr<Atractie>>& sursa);
    void copiazaAngajati(const std::vector<std::unique_ptr<Angajat>>& sursa);
    void copiazaVizitatori(const std::vector<std::unique_ptr<Vizitator>>& sursa);
};

#endif
