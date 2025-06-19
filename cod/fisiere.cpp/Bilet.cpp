
#include "Bilet.h"

// Clasa de baza Bilet
Bilet::Bilet(double pret, int valabilitateZile)
    : pret(pret), valabilitateZile(valabilitateZile) {}

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

void BiletCopil::afiseaza(std::ostream& os) const {
    os << "=== BILET COPIL ===" << std::endl;
    Bilet::afiseaza(os);
    os << "Varsta copil: " << varstaCopil << " ani" << std::endl;
    os << "Pret final: " << calculeazaPretFinal() << " RON" << std::endl;
    os << "===================" << std::endl;
}

double BiletCopil::calculeazaPretFinal() const {
    // Reducere pentru copii
    if (varstaCopil < 5) {
        return 0; // Gratuit pentru sub 5 ani
    } else if (varstaCopil < 12) {
        return pret * 0.5; // 50% reducere
    }
    return pret;
}

// BiletAdult
BiletAdult::BiletAdult(double pret, int valabilitateZile, bool includeFastPass)
    : Bilet(pret, valabilitateZile), includeFastPass(includeFastPass) {}

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
        pretFinal += 50; // Taxa pentru Fast Pass
    }
    return pretFinal;
}

// BiletVIP
BiletVIP::BiletVIP(double pret, int valabilitateZile, bool accesLounge)
    : Bilet(pret, valabilitateZile), accesLounge(accesLounge) {}

void BiletVIP::afiseaza(std::ostream& os) const {
    os << "=== BILET VIP ===" << std::endl;
    Bilet::afiseaza(os);
    os << "Acces Lounge: " << (accesLounge ? "Da" : "Nu") << std::endl;
    os << "Pret final: " << calculeazaPretFinal() << " RON" << std::endl;
    os << "================" << std::endl;
}

double BiletVIP::calculeazaPretFinal() const {
    double pretFinal = pret * 2; // VIP costa dublu
    if (accesLounge) {
        pretFinal += 100; // Taxa pentru lounge
    }
    return pretFinal;
}
