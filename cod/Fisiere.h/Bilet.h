

#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <map>

enum class ZiSaptamana {
    Luni = 1, Marti, Miercuri, Joi, Vineri, Sambata, Duminica
};

// Functie template libera pentru compararea preturilor
template<typename T, typename U>
bool compararePret(const T& bilet1, const U& bilet2) {
    return bilet1.calculeazaPretFinal() < bilet2.calculeazaPretFinal();
}

// Design Pattern: Observer pentru notificari
class BiletObserver {
public:
    virtual ~BiletObserver() = default;
    virtual void notificareSchimbarePret(double pretNou) = 0;
    virtual void notificareExpirare(const std::string& tipBilet) = 0;
};

// Design Pattern: Strategy pentru calculul preturilor
template<typename T>
class CalculPretStrategy {
public:
    virtual ~CalculPretStrategy() = default;
    virtual double calculeazaPret(const T& pretBaza, int valabilitate) const = 0;
    virtual std::unique_ptr<CalculPretStrategy<T>> clone() const = 0;
};

template<typename T>
class CalculPretStandard : public CalculPretStrategy<T> {
public:
    double calculeazaPret(const T& pretBaza, int valabilitate) const override {
        return static_cast<double>(pretBaza) * valabilitate;
    }

    std::unique_ptr<CalculPretStrategy<T>> clone() const override {
        return std::make_unique<CalculPretStandard<T>>();
    }
};

template<typename T>
class CalculPretWeekend : public CalculPretStrategy<T> {
public:
    double calculeazaPret(const T& pretBaza, int valabilitate) const override {
        return static_cast<double>(pretBaza) * valabilitate * 1.25;
    }

    std::unique_ptr<CalculPretStrategy<T>> clone() const override {
        return std::make_unique<CalculPretWeekend<T>>();
    }
};

// Clasa template Bilet
template<typename T = double>
class Bilet {
protected:
    T pretBaza; // atribut de tip T
    int valabilitateZile;
    static ZiSaptamana ziCurenta;
    static T pretMediu; // atribut static de tip T
    std::unique_ptr<CalculPretStrategy<T>> strategieCalcul; // Strategy pattern
    std::vector<BiletObserver*> observatori; // Observer pattern

public:
    Bilet(T pretBaza, int valabilitateZile);
    Bilet(const Bilet& other);
    Bilet& operator=(const Bilet& other);
    virtual ~Bilet() = default;

    // Constructor virtual (clone pattern)
    virtual std::unique_ptr<Bilet<T>> clone() const = 0;

    virtual std::string getTip() const = 0;
    virtual double calculeazaPretFinal() const;

    // Functie template membru care depinde de T
    template<typename U>
    T convertestePret(const U& pretStrain, double rataSchimb) const {
        return static_cast<T>(pretStrain * rataSchimb);
    }

    // Functie membru care lucreaza cu tip T
    void actualizeazaPretBaza(const T& pretNou) {
        pretBaza = pretNou;
        notificaObservatori(static_cast<double>(pretNou));
    }

    // Observer pattern methods
    void adaugaObserver(BiletObserver* observer) {
        observatori.push_back(observer);
    }

    void eliminaObserver(BiletObserver* observer) {
        observatori.erase(
            std::remove(observatori.begin(), observatori.end(), observer),
            observatori.end()
        );
    }

    // Strategy pattern methods
    void setStrategieCalcul(std::unique_ptr<CalculPretStrategy<T>> strategie) {
        strategieCalcul = std::move(strategie);
    }

    // Operatorul << virtual pentru polimorfism
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Bilet<U>& bilet);

    // Functii statice pentru gestionarea zilei
    static ZiSaptamana getZiCurenta() { return ziCurenta; }
    static void trecutZi();
    static std::string getNumeZi(ZiSaptamana zi);
    static bool esteWeekend(ZiSaptamana zi);

    // Functii statice pentru tipul T
    static void actualizarePretMediu(const T& nouPret);
    static T getPretMediu() { return pretMediu; }

    // Getters
    T getPretBaza() const { return pretBaza; }
    int getValabilitateZile() const { return valabilitateZile; }

    // Metoda pentru scaderea valabilitatii
    void scadeValabilitate();
    bool esteValid() const { return valabilitateZile > 0; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Bilet& other) noexcept;
    double calculeazaPretCuWeekend() const;
    void notificaObservatori(double pretNou);
};

// Design Pattern: Factory pentru crearea biletelor
template<typename T = double>
class BiletFactory {
public:
    static std::unique_ptr<Bilet<T>> creeazaBilet(const std::string& tip, int valabilitate, bool parametru = false);

private:
    static std::map<std::string, std::function<std::unique_ptr<Bilet<T>>(int, bool)>> creatoriInregistrati;
};

// Clasele derivate ca template
template<typename T = double>
class BiletStandard : public Bilet<T> {
public:
    explicit BiletStandard(int valabilitateZile);
    BiletStandard(const BiletStandard& other);
    BiletStandard& operator=(const BiletStandard& other);

    std::unique_ptr<Bilet<T>> clone() const override;
    std::string getTip() const override { return "Bilet Standard"; }

protected:
    void afiseaza(std::ostream& os) const override;
};

template<typename T = double>
class BiletPremium : public Bilet<T> {
private:
    bool includeAccesBufet;

public:
    BiletPremium(int valabilitateZile, bool includeAccesBufet);
    BiletPremium(const BiletPremium& other);
    BiletPremium& operator=(const BiletPremium& other);

    std::unique_ptr<Bilet<T>> clone() const override;
    std::string getTip() const override { return "Bilet Premium"; }
    double calculeazaPretFinal() const override;
    bool getIncludeAccesBufet() const { return includeAccesBufet; }

protected:
    void afiseaza(std::ostream& os) const override;
};

template<typename T = double>
class BiletVIP : public Bilet<T> {
private:
    bool accesPiscina;

public:
    BiletVIP(int valabilitateZile, bool accesPiscina);
    BiletVIP(const BiletVIP& other);
    BiletVIP& operator=(const BiletVIP& other);

    std::unique_ptr<Bilet<T>> clone() const override;
    std::string getTip() const override { return "Bilet VIP"; }
    double calculeazaPretFinal() const override;
    bool getAccesPiscina() const { return accesPiscina; }

protected:
    void afiseaza(std::ostream& os) const override;
};

// Implementarea template-urilor (trebuie în header pentru linkage)
#include "BiletTemplate.hpp"

#endif
