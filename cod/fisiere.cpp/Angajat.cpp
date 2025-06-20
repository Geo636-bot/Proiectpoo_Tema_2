
#include "Angajat.h"
#include <algorithm>

using namespace std;

// Inițializare atribut static
double Angajat::salariuMediu = 3000.0;

// Clasa de baza Angajat
Angajat::Angajat(const std::string& nume, int varsta, int experientaAni, double salariu)
    : nume(nume), varsta(varsta), experientaAni(experientaAni), salariu(salariu) {}

Angajat::Angajat(const Angajat& other)
    : nume(other.nume), varsta(other.varsta), experientaAni(other.experientaAni), salariu(other.salariu) {}

Angajat& Angajat::operator=(const Angajat& other) {
    if (this != &other) {
        Angajat temp(other);
        swap(temp);
    }
    return *this;
}

void Angajat::swap(Angajat& other) {
    std::swap(nume, other.nume);
    std::swap(varsta, other.varsta);
    std::swap(experientaAni, other.experientaAni);
    std::swap(salariu, other.salariu);
}

void Angajat::actualizareSalariuMediu(double nouSalariu) {
    salariuMediu = (salariuMediu + nouSalariu) / 2.0;
}

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

OperatorAtractie::OperatorAtractie(const OperatorAtractie& other)
    : Angajat(other), atractieDeservita(other.atractieDeservita) {}

OperatorAtractie& OperatorAtractie::operator=(const OperatorAtractie& other) {
    if (this != &other) {
        Angajat::operator=(other);
        atractieDeservita = other.atractieDeservita;
    }
    return *this;
}

std::unique_ptr<Angajat> OperatorAtractie::clone() const {
    return std::make_unique<OperatorAtractie>(*this);
}

void OperatorAtractie::afiseaza(std::ostream& os) const {
    os << "=== OPERATOR ATRACTIE ===" << std::endl;
    Angajat::afiseaza(os);
    os << "Atractie deservita: " << atractieDeservita << std::endl;
    os << "Salariu total: " << calculeazaSalariuTotal() << " RON" << std::endl;
    os << "=========================" << std::endl;
}

double OperatorAtractie::calculeazaSalariuTotal() const {
    return salariu + (experientaAni * 100);
}

// AgentPaza
AgentPaza::AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& zonaAsignata)
    : Angajat(nume, varsta, experientaAni, salariu), zonaAsignata(zonaAsignata) {}

AgentPaza::AgentPaza(const AgentPaza& other)
    : Angajat(other), zonaAsignata(other.zonaAsignata) {}

AgentPaza& AgentPaza::operator=(const AgentPaza& other) {
    if (this != &other) {
        Angajat::operator=(other);
        zonaAsignata = other.zonaAsignata;
    }
    return *this;
}

std::unique_ptr<Angajat> AgentPaza::clone() const {
    return std::make_unique<AgentPaza>(*this);
}

void AgentPaza::afiseaza(std::ostream& os) const {
    os << "=== AGENT PAZA ===" << std::endl;
    Angajat::afiseaza(os);
    os << "Zona asignata: " << zonaAsignata << std::endl;
    os << "Salariu total: " << calculeazaSalariuTotal() << " RON" << std::endl;
    os << "==================" << std::endl;
}

double AgentPaza::calculeazaSalariuTotal() const {
    return salariu + 200;
}

// Casier
Casier::Casier(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& interval)
    : Angajat(nume, varsta, experientaAni, salariu), interval(interval) {}

Casier::Casier(const Casier& other)
    : Angajat(other), interval(other.interval) {}

Casier& Casier::operator=(const Casier& other) {
    if (this != &other) {
        Angajat::operator=(other);
        interval = other.interval;
    }
    return *this;
}

std::unique_ptr<Angajat> Casier::clone() const {
    return std::make_unique<Casier>(*this);
}

void Casier::afiseaza(std::ostream& os) const {
    os << "=== CASIER ===" << std::endl;
    Angajat::afiseaza(os);
    os << "Interval: " << interval << std::endl;
    os << "==============" << std::endl;
}
