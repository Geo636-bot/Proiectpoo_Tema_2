

#ifndef VIZITATOR_H
#define VIZITATOR_H

#include <string>
#include <memory>
#include "Bilet.h"

class Vizitator {
protected:
    std::string nume;
    int varsta;
    int inaltime;
    std::unique_ptr<Bilet> bilet;
    static int numarTotalVizitatori; // atribut static

public:
    Vizitator(std::string  nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet);
    Vizitator(const Vizitator& other);
    Vizitator& operator=(const Vizitator& other);
    virtual ~Vizitator() = default;

    // Constructor virtual (clone pattern)
    [[nodiscard]] virtual std::unique_ptr<Vizitator> clone() const = 0;

    [[nodiscard]] virtual std::string getTip() const = 0;
    [[nodiscard]] virtual bool poateAccesaAtractia(int inaltimeMinima, int varstaNecesara ) const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Vizitator& vizitator);

    // Funcții statice
    //static int getNumarTotalVizitatori() { return numarTotalVizitatori; }
    //static void resetContorVizitatori() { numarTotalVizitatori = 0; }

    // Getters
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] int getVarsta() const { return varsta; }
    [[nodiscard]] int getInaltime() const { return inaltime; }
    [[nodiscard]] const Bilet* getBilet() const { return bilet.get(); }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Vizitator& other) noexcept;
};

class Copil : public Vizitator {
private:
    bool insotitDeAdult;

public:
    Copil(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool insotitDeAdult);
    Copil(const Copil& other);
    Copil& operator=(const Copil& other);

    [[nodiscard]] std::unique_ptr<Vizitator> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Copil"; }
    [[nodiscard]] bool poateAccesaAtractia(int inaltimeMinima, int varstaNecesara ) const override;
    [[nodiscard]] bool getInsotitDeAdult() const { return insotitDeAdult; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Adolescent : public Vizitator {
private:
    bool areBuletin;

public:
    Adolescent(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, bool areBuletin);
    Adolescent(const Adolescent& other);
    Adolescent& operator=(const Adolescent& other);

    [[nodiscard]] std::unique_ptr<Vizitator> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Adolescent"; }
    [[nodiscard]] bool getAreBuletin() const { return areBuletin; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Adult : public Vizitator {
private:
    std::string ocupatie;

public:
    Adult(const std::string& nume, int varsta, int inaltime, std::unique_ptr<Bilet> bilet, std::string  ocupatie);
    Adult(const Adult& other);
    Adult& operator=(const Adult& other);

    [[nodiscard]] std::unique_ptr<Vizitator> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Adult"; }
    [[nodiscard]] const std::string& getOcupatie() const { return ocupatie; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
