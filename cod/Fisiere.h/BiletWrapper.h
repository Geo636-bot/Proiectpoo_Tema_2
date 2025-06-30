#ifndef BILETWRAPPER_H
#define BILETWRAPPER_H

#include <memory>
#include <iostream>
#include "Bilet.h"

// Clasă șablon care adaugă funcționalitate generică pentru orice tip de extra info
template<typename T>
class BiletWrapper {
private:
    std::shared_ptr<Bilet> biletOriginal;
    T extraInfo; // poate fi orice: string, int, bool, etc.

public:
    BiletWrapper(std::shared_ptr<Bilet> bilet, T extraInfo)
        : biletOriginal(std::move(bilet)), extraInfo(extraInfo) {}

    void afiseaza() const {
        std::cout << "Bilet tip: " << biletOriginal->getTip()
                  << " | Pret final: " << biletOriginal->calculeazaPretFinal()
                  <<std::endl;
    }

    std::shared_ptr<Bilet> getBilet() const {
        return biletOriginal;
    }
};

#endif

