

#include "Angajat.h"

// Clasa de baza Angajat
Angajat::Angajat(const std::string& nume, int varsta, int experientaAni, double salariu)
    : nume(nume), varsta(varsta), experientaAni(experientaAni), salariu(salariu) {}

void Angajat::afiseaza(std::ostream& os) const {
    os << "Nume: " << nume << std::endl;
    os << "Varsta: " << varsta << " ani" << std::endl;
    os << "Experienta: " << experientaAni << " ani" << std::endl;
    os << "Salariu: " << salariu << " RON" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Angajat& angajat) {
    angajat.afiseaza(os);
    return os;
}

double Angajat::calculeazaSalariuTotal() const {
    return salariu;
}

// OperatorAtractie
OperatorAtractie::OperatorAtractie(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& atractieDeservita)
    : Angajat(nume, varsta, experientaAni, salariu), atractieDeservita(atractieDeservita) {}

void OperatorAtractie::afiseaza(std::ostream& os) const {
    os << "=== OPERATOR ATRACTIE ===" << std::endl;
    Angajat::afiseaza(os);
    os << "Atractie deservita: " << atractieDeservita << std::endl;
    os << "Salariu total: " << calculeazaSalariuTotal() << " RON" << std::endl;
    os << "=========================" << std::endl;
}

double OperatorAtractie::calculeazaSalariuTotal() const {
    // Bonus pentru experienta
    return salariu + (experientaAni * 100);
}

// AgentPaza
AgentPaza::AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& zonaAsignata)
    : Angajat(nume, varsta, experientaAni, salariu), zonaAsignata(zonaAsignata) {}

void AgentPaza::afiseaza(std::ostream& os) const {
    os << "=== AGENT PAZA ===" << std::endl;
    Angajat::afiseaza(os);
    os << "Zona asignata: " << zonaAsignata << std::endl;
    os << "Salariu total: " << calculeazaSalariuTotal() << " RON" << std::endl;
    os << "==================" << std::endl;
}

double AgentPaza::calculeazaSalariuTotal() const {
    // Bonus pentru responsabilitate
    return salariu + 200;
}

// Casier
Casier::Casier(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& interval)
    : Angajat(nume, varsta, experientaAni, salariu), interval(interval) {}

void Casier::afiseaza(std::ostream& os) const {
    os << "=== CASIER ===" << std::endl;
    Angajat::afiseaza(os);
    os << "Interval: " << interval << std::endl;
    os << "==============" << std::endl;
}
