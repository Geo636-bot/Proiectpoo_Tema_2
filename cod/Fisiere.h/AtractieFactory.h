
#ifndef ATRACTIEFACTORY_H
#define ATRACTIEFACTORY_H

#include "Atractie.h"
#include <memory>
#include <string>
#include <map>
#include <functional>

// Abstract Factory pentru crearea atractiilor
class AtractieFactory {
public:
    virtual ~AtractieFactory() = default;
    [[nodiscard]] virtual std::unique_ptr<Atractie> creeazaAtractie(
        const std::string& nume,
        int inaltimeMinima,
        int capacitate,
        int varstaNecesara,
        int parametruSpecific) const = 0;
    [[nodiscard]] virtual std::string getTipAtractie() const = 0;
};

// Concrete Factories
class MontagneRusseFactory : public AtractieFactory {
public:
    [[nodiscard]] std::unique_ptr<Atractie> creeazaAtractie(
        const std::string& nume,
        int inaltimeMinima,
        int capacitate,
        int varstaNecesara,
        int vitezaMaxima) const override {
        return std::make_unique<MontagneRusse>(nume, inaltimeMinima, capacitate, varstaNecesara, vitezaMaxima);
    }

    [[nodiscard]] std::string getTipAtractie() const override { return "Montagne Russe"; }
};

class CaruselFactory : public AtractieFactory {
public:
    [[nodiscard]] std::unique_ptr<Atractie> creeazaAtractie(
        const std::string& nume,
        int inaltimeMinima,
        int capacitate,
        int varstaNecesara,
        int numarCai) const override {
        return std::make_unique<Carusel>(nume, inaltimeMinima, capacitate, varstaNecesara, numarCai);
    }

    [[nodiscard]] std::string getTipAtractie() const override { return "Carusel"; }
};

class CasaGroazeiFactory : public AtractieFactory {
public:
    [[nodiscard]] std::unique_ptr<Atractie> creeazaAtractie(
        const std::string& nume,
        int inaltimeMinima,
        int capacitate,
        int varstaNecesara,
        int nivelFrica) const override {
        return std::make_unique<CasaGroazei>(nume, inaltimeMinima, capacitate, varstaNecesara, nivelFrica);
    }

    [[nodiscard]] std::string getTipAtractie() const override { return "Casa Groazei"; }
};

// Factory Manager pentru registrul de factories
class AtractieFactoryManager {
private:
    std::map<std::string, std::unique_ptr<AtractieFactory>> factories;

public:
    AtractieFactoryManager() {
        factories["montagne"] = std::make_unique<MontagneRusseFactory>();
        factories["carusel"] = std::make_unique<CaruselFactory>();
        factories["casa"] = std::make_unique<CasaGroazeiFactory>();
    }

    [[nodiscard]] std::unique_ptr<Atractie> creeazaAtractie(
        const std::string& tip,
        const std::string& nume,
        int inaltimeMinima,
        int capacitate,
        int varstaNecesara,
        int parametruSpecific) const {

        auto it = factories.find(tip);
        if (it != factories.end()) {
            return it->second->creeazaAtractie(nume, inaltimeMinima, capacitate, varstaNecesara, parametruSpecific);
        }
        return nullptr;
    }

    // [[nodiscard]] std::vector<std::string> getTipuriDisponibile() const {
    //     std::vector<std::string> tipuri;
    //     for (const auto& pair : factories) {
    //         tipuri.push_back(pair.first + " (" + pair.second->getTipAtractie() + ")");
    //     }
    //     return tipuri;
    // }
};

#endif