

#ifndef VIZITATOR_H
#define VIZITATOR_H

#include <string>
#include <iostream>
#include <memory>
#include "Bilet.h"

class Vizitator {
protected:
    std::string nume;
    int varsta;
    int inaltime;
    std::unique_ptr<Bilet<double>> bilet; // Actualizat pentru template
    static int numarTotalVizitatori; // atribut static

public:
    Vizitator(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet<double>> bilet);
    Vizitator(const Vizitator& other);
    Vizitator& operator=(const Vizitator& other);
    virtual ~Vizitator() = default;

    // Constructor virtual (clone pattern)
    virtual std::unique_ptr<Vizitator> clone() const = 0;

    virtual std::string getTip() const = 0;
    virtual bool poateAccesaAtractia(int inaltimeMinima, int varstaNecesara = 0) const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Vizitator& vizitator);

    // Functii statice
    static int getNumarTotalVizitatori() { return numarTotalVizitatori; }

    // Getters - return const reference for strings
    const std::string& getNume() const { return nume; }
    int getVarsta() const { return varsta; }
    int getInaltime() const { return inaltime; }
    const Bilet<double>* getBilet() const { return bilet.get(); } // Actualizat pentru template
    Bilet<double>* getBilet() { return bilet.get(); } // Actualizat pentru template

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Vizitator& other);
};

class Copil : public Vizitator {
private:
    bool insotitDeAdult;

public:
    Copil(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet<double>> bilet, bool insotitDeAdult);
    Copil(const Copil& other);
    Copil& operator=(const Copil& other);

    std::unique_ptr<Vizitator> clone() const override;
    std::string getTip() const override { return "Copil"; }
    bool poateAccesaAtractia(int inaltimeMinima, int varstaNecesara = 0) const override;
    bool getInsotitDeAdult() const { return insotitDeAdult; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Adolescent : public Vizitator {
public:
    Adolescent(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet<double>> bilet);
    Adolescent(const Adolescent& other);
    Adolescent& operator=(const Adolescent& other);

    std::unique_ptr<Vizitator> clone() const override;
    std::string getTip() const override { return "Adolescent"; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Adult : public Vizitator {
public:
    Adult(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet<double>> bilet);
    Adult(const Adult& other);
    Adult& operator=(const Adult& other);

    std::unique_ptr<Vizitator> clone() const override;
    std::string getTip() const override { return "Adult"; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
