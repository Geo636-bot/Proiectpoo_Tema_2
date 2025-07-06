

#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>
#include <memory>

enum class ZiSaptamana {
    Luni = 1, Marti, Miercuri, Joi, Vineri, Sambata, Duminica
};

class Bilet {
protected:
    double pretBaza;
    int valabilitateZile;
    static ZiSaptamana ziCurenta; // atribut static pentru zi curenta
    static double pretMediu; // atribut static

public:
    Bilet(double pretBaza, int valabilitateZile);
    Bilet(const Bilet& other);
    Bilet& operator=(const Bilet& other);
    virtual ~Bilet() = default;
    
    // Constructor virtual (clone pattern)
    [[nodiscard]] virtual std::unique_ptr<Bilet> clone() const = 0;
    
    [[nodiscard]] virtual std::string getTip() const = 0;
    [[nodiscard]] virtual double calculeazaPretFinal() const;
    
    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Bilet& bilet);
    
    // Funcții statice pentru gestionarea zilei
    static ZiSaptamana getZiCurenta() { return ziCurenta; }
    static void setZiCurenta(ZiSaptamana zi) { ziCurenta = zi; }
    static void trecutZi();
    static std::string getNumeZi(ZiSaptamana zi);
    static bool esteWeekend(ZiSaptamana zi);
    
    // Funcții statice
    static double getPretMediu() { return pretMediu; }
    static void actualizarePretMediu(double nouPret);
    
    // Getters
    [[nodiscard]] double getPretBaza() const { return pretBaza; }
    [[nodiscard]] int getValabilitateZile() const { return valabilitateZile; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Bilet& other) noexcept;
    [[nodiscard]] double calculeazaPretCuWeekend() const;
};

class BiletStandard : public Bilet {
public:
    explicit BiletStandard(int valabilitateZile);
    BiletStandard(const BiletStandard& other);
    BiletStandard& operator=(const BiletStandard& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet Standard"; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletAdult : public Bilet {
private:
    bool includeAccesBufet;

public:
    BiletAdult(int valabilitateZile, bool includeAccesBufet);
    BiletAdult(const BiletAdult& other);
    BiletAdult& operator=(const BiletAdult& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet Adult"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
    [[nodiscard]] bool getIncludeAccesBufet() const { return includeAccesBufet; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletVIP : public Bilet {
private:
    bool accesPiscina;

public:
    BiletVIP(int valabilitateZile, bool accesPiscina);
    BiletVIP(const BiletVIP& other);
    BiletVIP& operator=(const BiletVIP& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet VIP"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
    [[nodiscard]] bool getAccesPiscina() const { return accesPiscina; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
