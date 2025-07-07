
#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <iostream>
#include <memory>

class Angajat {
protected:
    std::string nume;
    int varsta;
    int experientaAni;
    double salariu;
    static double salariuMediu; // atribut static

public:
    Angajat(std::string  nume, int varsta, int experientaAni, double salariu);
    Angajat(const Angajat& other);
    Angajat& operator=(const Angajat& other);
    virtual ~Angajat() = default;

    // Constructor virtual (clone pattern)
    [[nodiscard]] virtual std::unique_ptr<Angajat> clone() const = 0;

    [[nodiscard]] virtual std::string getTip() const = 0;
    [[nodiscard]] virtual double calculeazaSalariuTotal() const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);

    // Funcții statice
    static double getSalariuMediu() { return salariuMediu; }
    static void actualizareSalariuMediu(double nouSalariu);

    // Getters - return const references for strings
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] int getVarsta() const { return varsta; }
    [[nodiscard]] int getExperientaAni() const { return experientaAni; }
    [[nodiscard]] double getSalariu() const { return salariu; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Angajat& other) noexcept;
};

class OperatorAtractie : public Angajat {
private:
    std::string atractieDeservita;

public:
    OperatorAtractie(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  atractieDeservita);
    OperatorAtractie(const OperatorAtractie& other);
    OperatorAtractie& operator=(const OperatorAtractie& other);

    [[nodiscard]] std::unique_ptr<Angajat> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Operator Atractie"; }
    [[nodiscard]] double calculeazaSalariuTotal() const override;
    [[nodiscard]] const std::string& getAtractieDeservita() const { return atractieDeservita; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class AgentPaza : public Angajat {
private:
    std::string zonaAsignata;

public:
    AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  zonaAsignata);
    AgentPaza(const AgentPaza& other);
    AgentPaza& operator=(const AgentPaza& other);

    [[nodiscard]] std::unique_ptr<Angajat> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Agent Paza"; }
    [[nodiscard]] double calculeazaSalariuTotal() const override;
    [[nodiscard]] const std::string& getZonaAsignata() const { return zonaAsignata; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Casier : public Angajat {
private:
    std::string interval;

public:
    Casier(const std::string& nume, int varsta, int experientaAni, double salariu, std::string  interval);
    Casier(const Casier& other);
    Casier& operator=(const Casier& other);

    [[nodiscard]] std::unique_ptr<Angajat> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Casier"; }
    [[nodiscard]] const std::string& getInterval() const { return interval; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif