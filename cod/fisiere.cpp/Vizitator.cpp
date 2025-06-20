
#include <iostream>
#include "../Fisiere.h/Vizitator.h"
#include <algorithm>

using namespace std;

// Inițializare atribut static
int Vizitator::numarTotalVizitatori = 0;

// Clasa de baza Vizitator
Vizitator::Vizitator(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet)
    : nume(nume), varsta(varsta), inaltime(inaltime), bilet(std::move(bilet)) {
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
        Vizitator temp(other);
        swap(temp);
    }
    return *this;
}

void Vizitator::swap(Vizitator& other) {
    std::swap(nume, other.nume);
    std::swap(varsta, other.varsta);
    std::swap(inaltime, other.inaltime);
    bilet.swap(other.bilet);
}

void Vizitator::afiseaza(std::ostream& os) const {
    os << "Nume: " << nume << std::endl;
    os << "Varsta: " << varsta << " ani" << std::endl;
    os << "Inaltime: " << inaltime << " cm" << std::endl;
    if (bilet) {
        os << "Tip bilet: " << bilet->getTip() << std::endl;
        os << "Pret bilet: " << bilet->calculeazaPretFinal() << " RON" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Vizitator& vizitator) {
    vizitator.afiseaza(os);
    return os;
}

bool Vizitator::poateAccesaAtractia(int inaltimeMinima, int varstaNecesara) const {
    return inaltime >= inaltimeMinima && varsta >= varstaNecesara;
}

// Copil
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

void Copil::afiseaza(std::ostream& os) const {
    os << "=== VIZITATOR COPIL ===" << std::endl;
    Vizitator::afiseaza(os);
    os << "Insotit de adult: " << (insotitDeAdult ? "Da" : "Nu") << std::endl;
    os << "=======================" << std::endl;
}

bool Copil::poateAccesaAtractia(int inaltimeMinima, int varstaNecesara) const {
    bool conditiiDeBase = Vizitator::poateAccesaAtractia(inaltimeMinima, varstaNecesara);
    if (varsta < 8 && !insotitDeAdult) {
        return false;
    }
    return conditiiDeBase;
}

// Adolescent
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
    os << "=== VIZITATOR ADOLESCENT ===" << std::endl;
    Vizitator::afiseaza(os);
    os << "Are buletin: " << (areBuletin ? "Da" : "Nu") << std::endl;
    os << "============================" << std::endl;
}

// Adult
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
    os << "=== VIZITATOR ADULT ===" << std::endl;
    Vizitator::afiseaza(os);
    os << "Ocupatie: " << ocupatie << std::endl;
    os << "=======================" << std::endl;
}
