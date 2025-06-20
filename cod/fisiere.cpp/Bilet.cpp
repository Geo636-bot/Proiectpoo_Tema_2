
#include "Bilet.h"
#include <algorithm>

using namespace std;

// Inițializare atribut static
double Bilet::pretMediu = 85.0;

// Clasa de baza Bilet
Bilet::Bilet(double pret, int valabilitateZile)
    : pret(pret), valabilitateZile(valabilitateZile) {}

Bilet::Bilet(const Bilet& other)
    : pret(other.pret), valabilitateZile(other.valabilitateZile) {}

Bilet& Bilet::operator=(const Bilet& other) {
    if (this != &other) {
        Bilet temp(other);
        swap(temp);
    }
    return *this;
}

void Bilet::swap(Bilet& other) {
    std::swap(pret, other.pret);
    std::swap(valabilitateZile, other.valabilitateZile);
}

void Bilet::actualizarePretMediu(double nouPret) {
    pretMediu = (pretMediu + nouPret) / 2.0;
}

void Bilet::afiseaza(std::ostream& os) const {
    os << "Pret: " << pret << " RON" << std::endl;
    os << "Valabilitate: " << valabilitateZile << " zile" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Bilet& bilet) {
    bilet.afiseaza(os);
    return os;
}

double Bilet::calculeazaPretFinal() const {
    return pret;
}

// BiletCopil
BiletCopil::BiletCopil(double pret, int valabilitateZile, int varstaCopil)
    : Bilet(pret, valabilitateZile), varstaCopil(varstaCopil) {}

BiletCopil::BiletCopil(const BiletCopil& other)
    : Bilet(other), varstaCopil(other.varstaCopil) {}

BiletCopil& BiletCopil::operator=(const BiletCopil& other) {
    if (this != &other) {
        Bilet::operator=(other);
        varstaCopil = other.varstaCopil;
    }
    return *this;
}

std::unique_ptr<Bilet> BiletCopil::clone() const {
    return std::make_unique<BiletCopil>(*this);
}

void BiletCopil::afiseaza(std::ostream& os) const {
    os << "=== BILET COPIL ===" << std::endl;
    Bilet::afiseaza(os);
    os << "Varsta copil: " << varstaCopil << " ani" << std::endl;
    os << "Pret final: " << calculeazaPretFinal() << " RON" << std::endl;
    os << "===================" << std::endl;
}

double BiletCopil::calculeazaPretFinal() const {
    if (varstaCopil < 5) {
        return 0;
    } else if (varstaCopil < 12) {
        return pret * 0.5;
    }
    return pret;
}

// BiletAdult
BiletAdult::BiletAdult(double pret, int valabilitateZile, bool includeFastPass)
    : Bilet(pret, valabilitateZile), includeFastPass(includeFastPass) {}

BiletAdult::BiletAdult(const BiletAdult& other)
    : Bilet(other), includeFastPass(other.includeFastPass) {}

BiletAdult& BiletAdult::operator=(const BiletAdult& other) {
    if (this != &other) {
        Bilet::operator=(other);
        includeFastPass = other.includeFastPass;
    }
    return *this;
}

std::unique_ptr<Bilet> BiletAdult::clone() const {
    return std::make_unique<BiletAdult>(*this);
}

void BiletAdult::afiseaza(std::ostream& os) const {
    os << "=== BILET ADULT ===" << std::endl;
    Bilet::afiseaza(os);
    os << "Fast Pass: " << (includeFastPass ? "Da" : "Nu") << std::endl;
    os << "Pret final: " << calculeazaPretFinal() << " RON" << std::endl;
    os << "===================" << std::endl;
}

double BiletAdult::calculeazaPretFinal() const {
    double pretFinal = pret;
    if (includeFastPass) {
        pretFinal += 50;
    }
    return pretFinal;
}

// BiletVIP
BiletVIP::BiletVIP(double pret, int valabilitateZile, bool accesLounge)
    : Bilet(pret, valabilitateZile), accesLounge(accesLounge) {}

BiletVIP::BiletVIP(const BiletVIP& other)
    : Bilet(other), accesLounge(other.accesLounge) {}

BiletVIP& BiletVIP::operator=(const BiletVIP& other) {
    if (this != &other) {
        Bilet::operator=(other);
        accesLounge = other.accesLounge;
    }
    return *this;
}

std::unique_ptr<Bilet> BiletVIP::clone() const {
    return std::make_unique<BiletVIP>(*this);
}

void BiletVIP::afiseaza(std::ostream& os) const {
    os << "=== BILET VIP ===" << std::endl;
    Bilet::afiseaza(os);
    os << "Acces Lounge: " << (accesLounge ? "Da" : "Nu") << std::endl;
    os << "Pret final: " << calculeazaPretFinal() << " RON" << std::endl;
    os << "================" << std::endl;
}

double BiletVIP::calculeazaPretFinal() const {
    double pretFinal = pret * 2;
    if (accesLounge) {
        pretFinal += 100;
    }
    return pretFinal;
}
