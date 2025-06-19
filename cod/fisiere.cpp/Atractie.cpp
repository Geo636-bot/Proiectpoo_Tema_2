

#include "Atractie.h"

// Clasa de baza Atractie
Atractie::Atractie(const std::string& nume, int inaltimeMinima, int capacitate)
    : nume(nume), inaltimeMinima(inaltimeMinima), capacitate(capacitate) {}

void Atractie::afiseaza(std::ostream& os) const {
    os << "Nume: " << nume << std::endl;
    os << "Inaltime minima: " << inaltimeMinima << " cm" << std::endl;
    os << "Capacitate: " << capacitate << " persoane" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Atractie& atractie) {
    atractie.afiseaza(os);
    return os;
}

// MontagneRusse
MontagneRusse::MontagneRusse(const std::string& nume, int inaltimeMinima, int capacitate, int vitezaMaxima)
    : Atractie(nume, inaltimeMinima, capacitate), vitezaMaxima(vitezaMaxima) {}

void MontagneRusse::afiseaza(std::ostream& os) const {
    os << "=== MONTAGNE RUSSE ===" << std::endl;
    Atractie::afiseaza(os);
    os << "Viteza maxima: " << vitezaMaxima << " km/h" << std::endl;
    os << "========================" << std::endl;
}

// Carusel
Carusel::Carusel(const std::string& nume, int inaltimeMinima, int capacitate, int numarCai)
    : Atractie(nume, inaltimeMinima, capacitate), numarCai(numarCai) {}

void Carusel::afiseaza(std::ostream& os) const {
    os << "=== CARUSEL ===" << std::endl;
    Atractie::afiseaza(os);
    os << "Numar cai: " << numarCai << std::endl;
    os << "===============" << std::endl;
}

// CasaGroazei
CasaGroazei::CasaGroazei(const std::string& nume, int inaltimeMinima, int capacitate, int nivelFrica)
    : Atractie(nume, inaltimeMinima, capacitate), nivelFrica(nivelFrica) {}

void CasaGroazei::afiseaza(std::ostream& os) const {
    os << "=== CASA GROAZEI ===" << std::endl;
    Atractie::afiseaza(os);
    os << "Nivel frica (1-10): " << nivelFrica << std::endl;
    os << "====================" << std::endl;
}

