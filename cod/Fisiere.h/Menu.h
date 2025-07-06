

#ifndef MENU_H
#define MENU_H

#include "ParcDistractii.h"
#include <memory>

class Menu {
private:
    ParcDistractii& parc;

public:
    explicit Menu(ParcDistractii& parc);

    static void afiseazaMeniu();
    void ruleazaMeniu() const;

    static void simuleazaTrecereaZilei();

    // Metode pentru adaugare interactiva
    void adaugaAtractieInteractiv() const;
    void adaugaAngajatInteractiv() const;
    void adaugaVizitatorInteractiv() const;
    void verificaAccesInteractiv() const;

    // Metode de validare
    static int getValidInt(const std::string& prompt, int min = 0, int max = 1000);

    static double getValidDouble(const std::string& prompt, double min = 0.0, double max = 10000.0);

    static std::string getValidString(const std::string& prompt);

    static bool getValidBool(const std::string& prompt);
};

#endif
