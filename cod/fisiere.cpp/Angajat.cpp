
#include "../Fisiere.h/Angajat.h"
#include <iostream>
#include <utility>

using namespace std;

// Inițializare atribut static
double Angajat::salariuMediu = 600.0; // salariu mediu saptamanal

Angajat::Angajat(std::string  nume, int varsta, int experientaAni, double salariu)
    : nume(std::move(nume)), varsta(varsta), experientaAni(experientaAni), salariu(salariu) {
    actualizareSalariuMediu(salariu);
}

Angajat::Angajat(const Angajat& other)
    = default;

Angajat& Angajat::operator=(const Angajat& other) {
    if (this != &other) {
        nume = other.nume;
        varsta = other.varsta;
        experientaAni = other.experientaAni;
        salariu = other.salariu;
    }
    return *this;
}

void Angajat::swap(Angajat& other) noexcept {
    std::swap(nume, other.nume);
    std::swap(varsta, other.varsta);
    std::swap(experientaAni, other.experientaAni);
    std::swap(salariu, other.salariu);
}

double Angajat::calculeazaSalariuTotal() const {
    // Salariul este deja calculat pe saptamana + bonus experienta (20 RON/an experienta)
    return salariu + (experientaAni * 20);
}

void Angajat::actualizareSalariuMediu(double nouSalariu) {
    salariuMediu = (salariuMediu + nouSalariu) / 2.0;
}

std::ostream& operator<<(std::ostream& os, const Angajat& angajat) {
    angajat.afiseaza(os);
    return os;
}

void Angajat::afiseaza(std::ostream& os) const {
    os << "👤 " << getTip() << ": " << nume
       << " (Varsta: " << varsta << ", Experienta: " << experientaAni
       << " ani, Salariu saptamanal: " << salariu << " RON)";
}

// OperatorAtractie implementation
OperatorAtractie::OperatorAtractie(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  atractieDeservita)
    : Angajat(nume, varsta, experientaAni, salariu), atractieDeservita(std::move(atractieDeservita)) {}

OperatorAtractie::OperatorAtractie(const OperatorAtractie& other)
     = default;

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

double OperatorAtractie::calculeazaSalariuTotal() const {
    return Angajat::calculeazaSalariuTotal() + 100; // bonus responsabilitate saptamanal
}

void OperatorAtractie::afiseaza(std::ostream& os) const {
    Angajat::afiseaza(os);
    os << " - Opereaza: " << atractieDeservita;
}

// AgentPaza implementation
AgentPaza::AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  zonaAsignata)
    : Angajat(nume, varsta, experientaAni, salariu), zonaAsignata(std::move(zonaAsignata)) {}

AgentPaza::AgentPaza(const AgentPaza& other)
    = default;

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

double AgentPaza::calculeazaSalariuTotal() const {
    return Angajat::calculeazaSalariuTotal() + 75; // bonus paza saptamanal
}

void AgentPaza::afiseaza(std::ostream& os) const {
    Angajat::afiseaza(os);
    os << " - Zona: " << zonaAsignata;
}

// Casier implementation
Casier::Casier(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  interval)
    : Angajat(nume, varsta, experientaAni, salariu), interval(std::move(interval)) {}

Casier::Casier(const Casier& other)
     = default;

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
    Angajat::afiseaza(os);
    os << " - Program: " << interval;
}