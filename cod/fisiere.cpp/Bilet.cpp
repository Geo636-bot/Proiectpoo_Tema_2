


#include "../Fisiere.h/Bilet.h"
#include <iostream>

using namespace std;

// Inițializare atribut static
double Bilet::pretMediu = 50.0;

Bilet::Bilet(double pret, int valabilitateZile,int zi)
    : pret(pret), valabilitateZile(valabilitateZile) {
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



std::ostream& operator<<(std::ostream& os, const Bilet& bilet) {
    bilet.afiseaza(os);
    return os;
}

void Bilet::afiseaza(std::ostream& os) const {
    os << "🎫 " << getTip() << " - Pret: " << calculeazaPretFinal()
       << " RON (Valabil " << valabilitateZile << " zile)";
}

// BiletCopil implementation
BiletStandard::BiletStandard(double pret, int valabilitateZile)
    : Bilet(pret, valabilitateZile) {}

BiletStandard::BiletStandard(const BiletStandard& other)
=default;

BiletStandard& BiletStandard::operator=(const BiletStandard& other) {
    if (this != &other) {
        Bilet::operator=(other);
    }
    return *this;
}

std::unique_ptr<Bilet> BiletStandard::clone() const {
    return std::make_unique<BiletStandard>(*this);
}

double BiletStandard::calculeazaPretFinal() const {
    return pret * 0.5;
}
void BiletStandard::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
}


BiletPremium::BiletPremium(double pret, int valabilitateZile, bool includeAccesBufet)
    : Bilet(pret, valabilitateZile), includeAccesBufet(includeAccesBufet) {}

BiletPremium::BiletPremium(const BiletPremium& other)
=default;

BiletPremium& BiletPremium::operator=(const BiletPremium& other) {
    if (this != &other) {
        Bilet::operator=(other);

    }
    return *this;
}

std::unique_ptr<Bilet> BiletPremium::clone() const {
    return std::make_unique<BiletPremium>(*this);
}

double BiletPremium::calculeazaPretFinal() const {
    double pretFinal = pret;
    if (includeAccesBufet) {
        pretFinal += 30;
    }
    return pretFinal;
}

void BiletPremium::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
    if (includeAccesBufet) {
        os << " + Acces Bufet";
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
