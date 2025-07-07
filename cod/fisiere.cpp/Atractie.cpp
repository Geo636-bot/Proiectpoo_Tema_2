

#include "../Fisiere.h/Atractie.h"
#include <iostream>

using namespace std;

// Initializare atribut static
int Atractie::numarTotalAtractii = 0;

Atractie::Atractie(const std::string& nume, int inaltimeMinima, int varstaNecesara)
    : nume(nume), inaltimeMinima(inaltimeMinima), varstaNecesara(varstaNecesara) {
    ++numarTotalAtractii;
}

Atractie::Atractie(const Atractie& other)
    : nume(other.nume), inaltimeMinima(other.inaltimeMinima), varstaNecesara(other.varstaNecesara) {
    ++numarTotalAtractii;
}

Atractie& Atractie::operator=(const Atractie& other) {
    if (this != &other) {
        nume = other.nume;
        inaltimeMinima = other.inaltimeMinima;
        varstaNecesara = other.varstaNecesara;
    }
    return *this;
}

void Atractie::swap(Atractie& other) {
    std::swap(nume, other.nume);
    std::swap(inaltimeMinima, other.inaltimeMinima);
    std::swap(varstaNecesara, other.varstaNecesara);
}

std::ostream& operator<<(std::ostream& os, const Atractie& atractie) {
    atractie.afiseaza(os);
    return os;
}

void Atractie::afiseaza(std::ostream& os) const {
    os << "🎢 " << getTip() << ": " << nume
       << " (Inaltime min: " << inaltimeMinima << "cm"
       << ", Varsta min: " << varstaNecesara << " ani)";
}

// MontagneRusse implementation
MontagneRusse::MontagneRusse(const std::string& nume, int inaltimeMinima, int varstaNecesara, int vitezaMaxima)
    : Atractie(nume, inaltimeMinima, varstaNecesara), vitezaMaxima(vitezaMaxima) {}

MontagneRusse::MontagneRusse(const MontagneRusse& other)
    : Atractie(other), vitezaMaxima(other.vitezaMaxima) {}

MontagneRusse& MontagneRusse::operator=(const MontagneRusse& other) {
    if (this != &other) {
        Atractie::operator=(other);
        vitezaMaxima = other.vitezaMaxima;
    }
    return *this;
}

std::unique_ptr<Atractie> MontagneRusse::clone() const {
    return std::make_unique<MontagneRusse>(*this);
}

void MontagneRusse::afiseaza(std::ostream& os) const {
    Atractie::afiseaza(os);
    os << " - Viteza maxima: " << vitezaMaxima << " km/h";
}

// Carusel implementation
Carusel::Carusel(const std::string& nume, int inaltimeMinima, int varstaNecesara, int numarCai)
    : Atractie(nume, inaltimeMinima, varstaNecesara), numarCai(numarCai) {}

Carusel::Carusel(const Carusel& other)
    : Atractie(other), numarCai(other.numarCai) {}

Carusel& Carusel::operator=(const Carusel& other) {
    if (this != &other) {
        Atractie::operator=(other);
        numarCai = other.numarCai;
    }
    return *this;
}

std::unique_ptr<Atractie> Carusel::clone() const {
    return std::make_unique<Carusel>(*this);
}

void Carusel::afiseaza(std::ostream& os) const {
    Atractie::afiseaza(os);
    os << " - Numar cai: " << numarCai;
}

// CasaGroazei implementation
CasaGroazei::CasaGroazei(const std::string& nume, int inaltimeMinima, int varstaNecesara, int nivelFrica)
    : Atractie(nume, inaltimeMinima, varstaNecesara), nivelFrica(nivelFrica) {}

CasaGroazei::CasaGroazei(const CasaGroazei& other)
    : Atractie(other), nivelFrica(other.nivelFrica) {}

CasaGroazei& CasaGroazei::operator=(const CasaGroazei& other) {
    if (this != &other) {
        Atractie::operator=(other);
        nivelFrica = other.nivelFrica;
    }
    return *this;
}

std::unique_ptr<Atractie> CasaGroazei::clone() const {
    return std::make_unique<CasaGroazei>(*this);
}

void CasaGroazei::afiseaza(std::ostream& os) const {
    Atractie::afiseaza(os);
    os << " - Nivel frica: " << nivelFrica << "/10";
}
