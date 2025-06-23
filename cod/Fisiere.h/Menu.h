
#ifndef MENU_H
#define MENU_H

#include "ParcDistractii.h"
#include "Observer.h"
#include <memory>

class Menu {
private:
    ParcDistractii& parc;
    std::shared_ptr<LogObserver> logObserver;
    std::shared_ptr<StatisticsObserver> statsObserver;
    
    static void clearInput();

    static int getValidInt(const std::string& prompt, int min = 0, int max = 999999);

    static double getValidDouble(const std::string& prompt, double min = 0.0, double max = 999999.0);

    static std::string getValidString(const std::string& prompt);
    static bool getYesNo(const std::string& prompt);

public:
    explicit Menu(ParcDistractii& parc);
    
    static void afiseazaMeniu();
    void ruleazaMeniu() const;
    
    // Metode pentru gestionarea datelor
    void adaugaAtractieInteractiv() const;
    void adaugaAtractieFactory() const;
    void adaugaAngajatInteractiv() const;
    void adaugaVizitatorInteractiv() const;
    void verificaAccesInteractiv() const;
    
    // Metode pentru crearea obiectelor
    static std::unique_ptr<Atractie> creeazaAtractie();

    static std::unique_ptr<Angajat> creeazaAngajat();

    static std::unique_ptr<Vizitator> creeazaVizitator();

    static std::unique_ptr<Bilet> creeazaBilet();
};

#endif