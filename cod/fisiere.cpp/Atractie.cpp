

#include "../Fisiere.h/Atractie.h"
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

// Inițializare atribut static
int Atractie::numarTotalAtractii = 0;

Atractie::Atractie(std::string  nume, int inaltimeMinima, int capacitate,int varstanecesara)
    : nume(std::move(nume)), inaltimeMinima(inaltimeMinima), capacitate(capacitate), varstanecesara(varstanecesara) {
    ++numarTotalAtractii;
}

Atractie::Atractie(const Atractie& other)
    : nume(other.nume), inaltimeMinima(other.inaltimeMinima), capacitate(other.capacitate), varstanecesara(other.varstanecesara) {
    ++numarTotalAtractii;
}

Atractie& Atractie::operator=(const Atractie& other) {
    if (this != &other) {
        nume = other.nume;
        inaltimeMinima = other.inaltimeMinima;
        varstanecesara = other.varstanecesara;
        capacitate = other.capacitate;
    }
    return *this;
}

void Atractie::swap(Atractie& other) noexcept {
    std::swap(nume, other.nume);
    std::swap(inaltimeMinima, other.inaltimeMinima);
    std::swap(varstanecesara, other.varstanecesara);
    std::swap(capacitate, other.capacitate);
}

std::ostream& operator<<(std::ostream& os, const Atractie& atractie) {
    atractie.afiseaza(os);
    return os;
}

void Atractie::afiseaza(std::ostream& os) const {
    os << "🎢 " << getTip() << ": " << nume
       << " (Inaltime min: " << inaltimeMinima << "cm, Capacitate: " << capacitate << " Varsta necesara: "<<varstanecesara<<" ani)"<<endl;
}



// MontagneRusse implementation
MontagneRusse::MontagneRusse(const std::string& nume, int inaltimeMinima, int capacitate,int varstanecesara, int vitezaMaxima)
    : Atractie(nume, inaltimeMinima, capacitate, varstanecesara), vitezaMaxima(vitezaMaxima) {
}

MontagneRusse::MontagneRusse(const MontagneRusse& other)
    = default;

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
Carusel::Carusel(const std::string& nume, int inaltimeMinima, int capacitate,int varstanecesara, int numarCai)
    : Atractie(nume, inaltimeMinima, capacitate,varstanecesara), numarCai(numarCai) {}

Carusel::Carusel(const Carusel& other)
    = default;

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
CasaGroazei::CasaGroazei(const std::string& nume, int inaltimeMinima, int capacitate,int varstanecesara, int nivelFrica)
    : Atractie(nume, inaltimeMinima, capacitate,varstanecesara), nivelFrica(nivelFrica) {}

CasaGroazei::CasaGroazei(const CasaGroazei& other)
    = default;

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
