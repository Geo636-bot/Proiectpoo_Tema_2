#define MENIU_H

#include "ParcDistractii.h"
#include "Observer.h"
#include <memory>

class Menu {
private:
    ParcDistractii& parc;
    std::shared_ptr<LogObserver> logObserver;
    std::shared_ptr<StatisticsObserver> statsObserver;

    void clearInput();
    int getValidInt(const std::string& prompt, int min = 0, int max = 999999);


    // Metode pentru gestionarea datelor
    void adaugaAtractieInteractiv();
    void adaugaAtractieFactory();
    void adaugaAngajatInteractiv();
    void adaugaVizitatorInteractiv();
    void verificaAccesInteractiv();
    void afiseazaStatisticiTemplate();

    // Metode pentru crearea obiectelorAdd commentMore actions
    std::unique_ptr<Atractie> creeazaAtractie();
