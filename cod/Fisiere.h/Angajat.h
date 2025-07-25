

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
    Angajat(const std::string& nume, int varsta, int experientaAni, double salariu);
    Angajat(const Angajat& other);
    Angajat& operator=(const Angajat& other);
    virtual ~Angajat() = default;

    // Constructor virtual (clone pattern)
    virtual std::unique_ptr<Angajat> clone() const = 0;

    virtual std::string getTip() const = 0;
    virtual double calculeazaSalariuTotal() const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Angajat& angajat);

    // Functii statice
    static double getSalariuMediu() { return salariuMediu; }
    static void actualizareSalariuMediu(double nouSalariu);

    // Getters - return const references for strings
    const std::string& getNume() const { return nume; }
    int getVarsta() const { return varsta; }
    //int getExperientaAni() const { return experientaAni; }
    //double getSalariu() const { return salariu; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Angajat& other);
};

class OperatorAtractie : public Angajat {
private:
    std::string atractieDeservita;

public:
    OperatorAtractie(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& atractieDeservita);
    OperatorAtractie(const OperatorAtractie& other);
    OperatorAtractie& operator=(const OperatorAtractie& other);

    std::unique_ptr<Angajat> clone() const override;
    std::string getTip() const override { return "Operator Atractie"; }
    double calculeazaSalariuTotal() const override;
    const std::string& getAtractieDeservita() const { return atractieDeservita; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class AgentPaza : public Angajat {
private:
    std::string zonaAsignata;

public:
    AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& zonaAsignata);
    AgentPaza(const AgentPaza& other);
    AgentPaza& operator=(const AgentPaza& other);

    std::unique_ptr<Angajat> clone() const override;
    std::string getTip() const override { return "Agent Paza"; }
    double calculeazaSalariuTotal() const override;
    const std::string& getZonaAsignata() const { return zonaAsignata; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Casier : public Angajat {
private:
    std::string interval;

public:
    Casier(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& interval);
    Casier(const Casier& other);
    Casier& operator=(const Casier& other);

    std::unique_ptr<Angajat> clone() const override;
    std::string getTip() const override { return "Casier"; }
    const std::string& getInterval() const { return interval; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
