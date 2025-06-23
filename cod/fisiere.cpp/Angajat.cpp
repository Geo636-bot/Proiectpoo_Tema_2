
#include "../Fisiere.h/Angajat.h"
#include <iostream>
#include <utility>

using namespace std;

// Inițializare atribut static
double Angajat::salariuMediu = 2500.0;

Angajat::Angajat(std::string  nume, int varsta, int experientaAni, double salariu)
    : nume(std::move(nume)), varsta(varsta), experientaAni(experientaAni), salariu(salariu) {
    actualizareSalariuMediu(salariu);
}

Angajat::Angajat(const Angajat& other)
    : nume(other.nume), varsta(other.varsta), experientaAni(other.experientaAni), salariu(other.salariu) {}

Angajat& Angajat::operator=(const Angajat& other) {
    if (this != &other) {
         nume = other.nume;
        varsta = other.varsta;
        experientaAni = other.experientaAni;
        salariu = other.salariu;
    }
    return *this;
}

std::unique_ptr<Angajat> Angajat::clone() const {
    return nullptr;
}

void Angajat::swap(Angajat& other) noexcept {
    std::swap(nume, other.nume);
    std::swap(varsta, other.varsta);
    std::swap(experientaAni, other.experientaAni);
    std::swap(salariu, other.salariu);
}

double Angajat::calculeazaSalariuTotal() const {
    return salariu + (experientaAni * 100); // bonus experienta
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
       << " ani, Salariu: " << salariu << " RON)";
}

// OperatorAtractie implementation
OperatorAtractie::OperatorAtractie(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  atractieDeservita)
    : Angajat(nume, varsta, experientaAni, salariu), atractieDeservita(std::move(atractieDeservita)) {}

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

double OperatorAtractie::calculeazaSalariuTotal() const {
    return Angajat::calculeazaSalariuTotal() + 500; // bonus responsabilitate
}

void OperatorAtractie::afiseaza(std::ostream& os) const {
    Angajat::afiseaza(os);
    os << " - Opereaza: " << atractieDeservita;
}

// AgentPaza implementation
AgentPaza::AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  zonaAsignata)
    : Angajat(nume, varsta, experientaAni, salariu), zonaAsignata(std::move(zonaAsignata)) {}

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

double AgentPaza::calculeazaSalariuTotal() const {
    return Angajat::calculeazaSalariuTotal() + 300; // bonus paza
}

void AgentPaza::afiseaza(std::ostream& os) const {
    Angajat::afiseaza(os);
    os << " - Zona: " << zonaAsignata;
}

// Casier implementation
Casier::Casier(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  interval)
    : Angajat(nume, varsta, experientaAni, salariu), interval(std::move(interval)) {}

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
    Angajat::afiseaza(os);
    os << " - Program: " << interval;
}