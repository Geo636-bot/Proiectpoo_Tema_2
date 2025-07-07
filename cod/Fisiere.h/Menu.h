

#ifndef MENU_H
#define MENU_H

#include "ParcDistractii.h"
#include <memory>

class Menu {
private:
    ParcDistractii& parc;

public:
    explicit Menu(ParcDistractii& parc);

    void afiseazaMeniu();
    void ruleazaMeniu();
    void simuleazaTrecereaZilei();
    void afiseazaProfitSaptamanal();

    // Metode pentru adaugare interactiva
    void adaugaAtractieInteractiv();
    void adaugaAngajatInteractiv();
    void adaugaVizitatorInteractiv();
    void verificaAccesInteractiv();

    // Noua metoda pentru demonstrarea template-urilor
    void demonstreazaTemplatesSiPatterns();

    // Metode de validare
    int getValidInt(const std::string& prompt, int min = 0, int max = 1000);
    std::string getValidString(const std::string& prompt);
    bool getValidBool(const std::string& prompt);

    // Metode pentru validari angajati
    double calculezaSalariuCuExperienta(double salariuBaza, int experientaAni);
    std::string gasesteAtractieFaraOperator();
    bool verificaAtractieDisponibila(const std::string& numeAtractie);
    int getNumarPaznici();
    bool verificaZonaOcupata(const std::string& zona);
    std::string getValidZona(const std::string& prompt);
    std::string getValidInterval(const std::string& prompt);
};

#endif
