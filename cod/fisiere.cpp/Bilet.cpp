


#include "../Fisiere.h/Bilet.h"
#include <iostream>

using namespace std;


Bilet::Bilet(double pret, int valabilitateZile)
    : pret(pret), valabilitateZile(valabilitateZile) {
    actualizarePretMediu(pret);
}

Bilet::Bilet(const Bilet& other)
=default;

Bilet& Bilet::operator=(const Bilet& other) {
    if (this != &other) {
        pret = other.pret;
        valabilitateZile = other.valabilitateZile;
    }
    return *this;
}

void Bilet::swap(Bilet& other) noexcept {
    std::swap(pret, other.pret);
    std::swap(valabilitateZile, other.valabilitateZile);
}

double Bilet::calculeazaPretFinal() const {
    return pret;
}

void Bilet::actualizarePretMediu(double nouPret) {
    pretMediu = (pretMediu + nouPret) / 2.0;
}

std::ostream& operator<<(std::ostream& os, const Bilet& bilet) {
    bilet.afiseaza(os);
    return os;
}

void Bilet::afiseaza(std::ostream& os) const {
    os << "🎫 " << getTip() << " - Pret: " << calculeazaPretFinal()
       << " RON (Valabil " << valabilitateZile << " zile)";
}

// BiletCopil implementation
BiletCopil::BiletCopil(double pret, int valabilitateZile, int varstaCopil)
    : Bilet(pret, valabilitateZile), varstaCopil(varstaCopil) {}

BiletCopil::BiletCopil(const BiletCopil& other)
=default;

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

double BiletCopil::calculeazaPretFinal() const {
    return pret * 0.5; // 50% reducere pentru copii
}

void BiletCopil::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
    os << " - Varsta copil: " << varstaCopil;
}

// BiletAdult implementation
BiletAdult::BiletAdult(double pret, int valabilitateZile, bool includeFastPass)
    : Bilet(pret, valabilitateZile), includeFastPass(includeFastPass) {}

BiletAdult::BiletAdult(const BiletAdult& other)
=default;

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

double BiletAdult::calculeazaPretFinal() const {
    double pretFinal = pret;
    if (includeFastPass) {
        pretFinal += 30; // taxa Fast Pass
    }
    return pretFinal;
}

void BiletAdult::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
    if (includeFastPass) {
        os << " + Fast Pass";
    }
}

// BiletVIP implementation
BiletVIP::BiletVIP(double pret, int valabilitateZile, bool accesLounge)
    : Bilet(pret, valabilitateZile), accesLounge(accesLounge) {}

BiletVIP::BiletVIP(const BiletVIP& other)
=default;

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

double BiletVIP::calculeazaPretFinal() const {
    double pretFinal = pret * 2; // VIP costa dublu
    if (accesLounge) {
        pretFinal += 50; // taxa lounge
    }
    return pretFinal;
}

void BiletVIP::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
    if (accesLounge) {
        os << " + Acces Lounge VIP";
    }
}
