

#ifndef MENU_H
#define MENU_H

#include "ParcDistractii.h"
#include <memory>

class Menu {
private:
    ParcDistractii& parc;
    
    void clearInput();
    int getValidInt(const std::string& prompt, int min = 0, int max = 999999);
    double getValidDouble(const std::string& prompt, double min = 0.0, double max = 999999.0);
    std::string getValidString(const std::string& prompt);
    bool getYesNo(const std::string& prompt);

public:
    Menu(ParcDistractii& parc);
    
    void afiseazaMeniu();
    void ruleazaMeniu();
    
    // Metode pentru gestionarea datelor
    void adaugaAtractieInteractiv();
    void adaugaAngajatInteractiv();
    void adaugaVizitatorInteractiv();
    void verificaAccesInteractiv();
    
    // Metode pentru crearea obiectelor
    std::unique_ptr<Atractie> creeazaAtractie();
    std::unique_ptr<Angajat> creeazaAngajat();
    std::unique_ptr<Vizitator> creeazaVizitator();
    std::unique_ptr<Bilet> creeazaBilet();
};

#endif
