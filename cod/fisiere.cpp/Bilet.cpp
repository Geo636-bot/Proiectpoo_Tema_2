

#include "../Fisiere.h/Bilet.h"
#include <iostream>

using namespace std;

// Inițializare atribute statice
double Bilet::pretMediu = 75.0;
ZiSaptamana Bilet::ziCurenta = ZiSaptamana::Luni;

Bilet::Bilet(double pretBaza, int valabilitateZile)
    : pretBaza(pretBaza), valabilitateZile(valabilitateZile) {
    actualizarePretMediu(calculeazaPretFinal());
}

Bilet::Bilet(const Bilet& other)
    : pretBaza(other.pretBaza), valabilitateZile(other.valabilitateZile) {}

Bilet& Bilet::operator=(const Bilet& other) {
    if (this != &other) {
        pretBaza = other.pretBaza;
        valabilitateZile = other.valabilitateZile;
    }
    return *this;
}

void Bilet::swap(Bilet& other) noexcept {
    std::swap(pretBaza, other.pretBaza);
    std::swap(valabilitateZile, other.valabilitateZile);
}

void Bilet::scadeValabilitate() {
    if (valabilitateZile > 0) {
        valabilitateZile--;
    }
}

double Bilet::calculeazaPretFinal() const {
    return calculeazaPretCuWeekend();
}

double Bilet::calculeazaPretCuWeekend() const {
    double pretTotal = pretBaza * valabilitateZile;
    if (esteWeekend(ziCurenta)) {
        pretTotal *= 1.25; // scumpire cu 25% in weekend
    }
    return pretTotal;
}

bool Bilet::esteWeekend(ZiSaptamana zi) {
    return zi == ZiSaptamana::Sambata || zi == ZiSaptamana::Duminica;
}

void Bilet::trecutZi() {
    int ziInt = static_cast<int>(ziCurenta);
    ziInt++;
    if (ziInt > 7) {
        ziInt = 1;
    }
    ziCurenta = static_cast<ZiSaptamana>(ziInt);
}

std::string Bilet::getNumeZi(ZiSaptamana zi) {
    switch (zi) {
        case ZiSaptamana::Luni: return "Luni";
        case ZiSaptamana::Marti: return "Marti";
        case ZiSaptamana::Miercuri: return "Miercuri";
        case ZiSaptamana::Joi: return "Joi";
        case ZiSaptamana::Vineri: return "Vineri";
        case ZiSaptamana::Sambata: return "Sambata";
        case ZiSaptamana::Duminica: return "Duminica";
        default: return "Necunoscut";
    }
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
    if (valabilitateZile == 0) {
        os << " [EXPIRAT]";
    } else if (esteWeekend(ziCurenta)) {
        os << " [Weekend +25%]";
    }
}

// BiletStandard implementation
BiletStandard::BiletStandard(int valabilitateZile)
    : Bilet(50.0, valabilitateZile) {}

BiletStandard::BiletStandard(const BiletStandard& other)
    : Bilet(other) {}

BiletStandard& BiletStandard::operator=(const BiletStandard& other) {
    if (this != &other) {
        Bilet::operator=(other);
    }
    return *this;
}

std::unique_ptr<Bilet> BiletStandard::clone() const {
    return std::make_unique<BiletStandard>(*this);
}

void BiletStandard::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
}

// BiletPremium implementation
BiletPremium::BiletPremium(int valabilitateZile, bool includeAccesBufet)
    : Bilet(75.0, valabilitateZile), includeAccesBufet(includeAccesBufet) {}

BiletPremium::BiletPremium(const BiletPremium& other)
    : Bilet(other), includeAccesBufet(other.includeAccesBufet) {}

BiletPremium& BiletPremium::operator=(const BiletPremium& other) {
    if (this != &other) {
        Bilet::operator=(other);
        includeAccesBufet = other.includeAccesBufet;
    }
    return *this;
}

std::unique_ptr<Bilet> BiletPremium::clone() const {
    return std::make_unique<BiletPremium>(*this);
}

double BiletPremium::calculeazaPretFinal() const {
    double pretTotal = pretBaza * valabilitateZile;
    if (includeAccesBufet) {
        pretTotal += 30;
    }
    if (esteWeekend(ziCurenta)) {
        pretTotal *= 1.25;
    }
    return pretTotal;
}

void BiletPremium::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
    if (includeAccesBufet) {
        os << " + Acces Bufet";
    }
}

// BiletVIP implementation
BiletVIP::BiletVIP(int valabilitateZile, bool accesPiscina)
    : Bilet(100.0, valabilitateZile), accesPiscina(accesPiscina) {}

BiletVIP::BiletVIP(const BiletVIP& other)
    : Bilet(other), accesPiscina(other.accesPiscina) {}

BiletVIP& BiletVIP::operator=(const BiletVIP& other) {
    if (this != &other) {
        Bilet::operator=(other);
        accesPiscina = other.accesPiscina;
    }
    return *this;
}

std::unique_ptr<Bilet> BiletVIP::clone() const {
    return std::make_unique<BiletVIP>(*this);
}

double BiletVIP::calculeazaPretFinal() const {
    double pretTotal = pretBaza * valabilitateZile;
    if (accesPiscina) {
        pretTotal += 50;
    }
    if (esteWeekend(ziCurenta)) {
        pretTotal *= 1.25;
    }
    return pretTotal;
}

void BiletVIP::afiseaza(std::ostream& os) const {
    Bilet::afiseaza(os);
    if (accesPiscina) {
        os << " + Acces Piscina";
    }
}
