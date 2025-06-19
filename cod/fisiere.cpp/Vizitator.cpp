

#include "Vizitator.h"

// Clasa de baza Vizitator
Vizitator::Vizitator(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet)
    : nume(nume), varsta(varsta), inaltime(inaltime), bilet(std::move(bilet)) {}

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

void Copil::afiseaza(std::ostream& os) const {
    os << "=== VIZITATOR COPIL ===" << std::endl;
    Vizitator::afiseaza(os);
    os << "Insotit de adult: " << (insotitDeAdult ? "Da" : "Nu") << std::endl;
    os << "=======================" << std::endl;
}

bool Copil::poateAccesaAtractia(int inaltimeMinima, int varstaNecesara) const {
    bool conditiiDeBase = Vizitator::poateAccesaAtractia(inaltimeMinima, varstaNecesara);
    // Copiii sub 8 ani trebuie insotiti de adult pentru unele atractii
    if (varsta < 8 && !insotitDeAdult) {
        return false;
    }
    return conditiiDeBase;
}

// Adolescent
Adolescent::Adolescent(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool areBuletin)
    : Vizitator(nume, varsta, inaltime, std::move(bilet)), areBuletin(areBuletin) {}

void Adolescent::afiseaza(std::ostream& os) const {
    os << "=== VIZITATOR ADOLESCENT ===" << std::endl;
    Vizitator::afiseaza(os);
    os << "Are buletin: " << (areBuletin ? "Da" : "Nu") << std::endl;
    os << "============================" << std::endl;
}

// Adult
Adult::Adult(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, const std::string& ocupatie)
    : Vizitator(nume, varsta, inaltime, std::move(bilet)), ocupatie(ocupatie) {}

void Adult::afiseaza(std::ostream& os) const {
    os << "=== VIZITATOR ADULT ===" << std::endl;
    Vizitator::afiseaza(os);
    os << "Ocupatie: " << ocupatie << std::endl;
    os << "=======================" << std::endl;
}
