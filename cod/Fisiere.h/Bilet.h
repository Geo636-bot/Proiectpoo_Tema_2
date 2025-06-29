

#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>
#include <memory>

class Bilet {
protected:
    double pret;
    int valabilitateZile;
    static double pretMediu; // atribut static

public:
    Bilet(double pret, int valabilitateZile);
    Bilet(const Bilet& other);
    Bilet& operator=(const Bilet& other);
    virtual ~Bilet() = default;

    // Constructor virtual (clone pattern)
    [[nodiscard]] virtual std::unique_ptr<Bilet> clone() const = 0;

    [[nodiscard]] virtual std::string getTip() const = 0;
    [[nodiscard]] virtual double calculeazaPretFinal() const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Bilet& bilet);

    // Funcții statice
    //static double getPretMediu() { return pretMediu; }
    static void actualizarePretMediu(double nouPret);

    // Getters
   // [[nodiscard]] double getPret() const { return pret; }
    //[[nodiscard]] int getValabilitateZile() const { return valabilitateZile; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Bilet& other) noexcept;
};

class BiletCopil : public Bilet {
private:
    int varstaCopil;

public:
    BiletCopil(double pret, int valabilitateZile, int varstaCopil);
    BiletCopil(const BiletCopil& other);
    BiletCopil& operator=(const BiletCopil& other);

    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "BiLet Copil"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
   // [[nodiscard]] int getVarstaCopil() const { return varstaCopil; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletAdult : public Bilet {
private:
    bool includeFastPass;

public:
    BiletAdult(double pret, int valabilitateZile, bool includeFastPass);
    BiletAdult(const BiletAdult& other);
    BiletAdult& operator=(const BiletAdult& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet Adult"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
    //[[nodiscard]] bool getIncludeFastPass() const { return includeFastPass; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletVIP : public Bilet {
private:
    bool accesLounge;

public:
    BiletVIP(double pret, int valabilitateZile, bool accesLounge);
    BiletVIP(const BiletVIP& other);
    BiletVIP& operator=(const BiletVIP& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet VIP"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
    //[[nodiscard]] bool getAccesLounge() const { return accesLounge; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
