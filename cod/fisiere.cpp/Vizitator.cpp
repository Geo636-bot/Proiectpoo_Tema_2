
#include <iostream>
#include "../Fisiere.h/Vizitator.h"
#include <algorithm>
#include <utility>

using namespace std;

// Inițializare atribut static
int Vizitator::numarTotalVizitatori = 0;

Vizitator::Vizitator(std::string  nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet)
    : nume(std::move(nume)), varsta(varsta), inaltime(inaltime), bilet(std::move(bilet)) {
    ++numarTotalVizitatori;
}

Vizitator::Vizitator(const Vizitator& other)
    : nume(other.nume), varsta(other.varsta), inaltime(other.inaltime) {
    ++numarTotalVizitatori;
    if (other.bilet) {
        bilet = other.bilet->clone();
    }
}

Vizitator& Vizitator::operator=(const Vizitator& other) {
    if (this != &other) {
        nume = other.nume;
        varsta = other.varsta;
        inaltime = other.inaltime;
        if (other.bilet) {
            bilet = other.bilet->clone();
        } else {
            bilet.reset();
        }
    }
    return *this;
}

void Vizitator::swap(Vizitator& other) noexcept {
    std::swap(nume, other.nume);
    std::swap(varsta, other.varsta);
    std::swap(inaltime, other.inaltime);
    bilet.swap(other.bilet);
}

bool Vizitator::poateAccesaAtractia(int inaltimeMinima, int varstaNecesara) const {
    return inaltime >= inaltimeMinima && varsta >= varstaNecesara;
}

std::ostream& operator<<(std::ostream& os, const Vizitator& vizitator) {
    vizitator.afiseaza(os);
    return os;
}

void Vizitator::afiseaza(std::ostream& os) const {
    os << "👤 " << getTip() << ": " << nume 
       << " (Varsta: " << varsta << ", Inaltime: " << inaltime << "cm)";
    if (bilet) {
        os << "\n   " << *bilet;
    }
}

// Copil implementation
Copil::Copil(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool insotitDeAdult)
    : Vizitator(nume, varsta, inaltime, std::move(bilet)), insotitDeAdult(insotitDeAdult) {}

Copil::Copil(const Copil& other)
    : Vizitator(other), insotitDeAdult(other.insotitDeAdult) {}

Copil& Copil::operator=(const Copil& other) {
    if (this != &other) {
        Vizitator::operator=(other);
        insotitDeAdult = other.insotitDeAdult;
    }
    return *this;
}

std::unique_ptr<Vizitator> Copil::clone() const {
    return std::make_unique<Copil>(*this);
}

bool Copil::poateAccesaAtractia(int inaltimeMinima, int varstaNecesara) const {
    if (!Vizitator::poateAccesaAtractia(inaltimeMinima, varstaNecesara)) {
        return false;
    }
    if (varsta < 8) {
        return insotitDeAdult;
    }
    return true;
}

void Copil::afiseaza(std::ostream& os) const {
    Vizitator::afiseaza(os);
    os << " - " << (insotitDeAdult ? "Insotit de adult" : "Neinsotit");
}

// Adolescent implementation
Adolescent::Adolescent(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool areBuletin)
    : Vizitator(nume, varsta, inaltime, std::move(bilet)), areBuletin(areBuletin) {}

Adolescent::Adolescent(const Adolescent& other)
    : Vizitator(other), areBuletin(other.areBuletin) {}

Adolescent& Adolescent::operator=(const Adolescent& other) {
    if (this != &other) {
        Vizitator::operator=(other);
        areBuletin = other.areBuletin;
    }
    return *this;
}

std::unique_ptr<Vizitator> Adolescent::clone() const {
    return std::make_unique<Adolescent>(*this);
}

void Adolescent::afiseaza(std::ostream& os) const {
    Vizitator::afiseaza(os);
    os << " - " << (areBuletin ? "Cu buletin" : "Fara buletin");
}

// Adult implementation
Adult::Adult(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, const std::string& ocupatie)
    : Vizitator(nume, varsta, inaltime, std::move(bilet)), ocupatie(ocupatie) {}

Adult::Adult(const Adult& other)
    : Vizitator(other), ocupatie(other.ocupatie) {}

Adult& Adult::operator=(const Adult& other) {
    if (this != &other) {
        Vizitator::operator=(other);
        ocupatie = other.ocupatie;
    }
    return *this;
}

std::unique_ptr<Vizitator> Adult::clone() const {
    return std::make_unique<Adult>(*this);
}

void Adult::afiseaza(std::ostream& os) const {
    Vizitator::afiseaza(os);
    os << " - Ocupatie: " << ocupatie;
}
