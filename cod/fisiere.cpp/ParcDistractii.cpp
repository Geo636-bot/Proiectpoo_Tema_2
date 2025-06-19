

#include "ParcDistractii.h"
#include <iostream>
#include <algorithm>

ParcDistractii::ParcDistractii(const std::string& nume) : nume(nume) {}

void ParcDistractii::adaugaAtractie(std::unique_ptr<Atractie> atractie) {
    atractii.push_back(std::move(atractie));
    std::cout << "✅ Atractie adaugata cu succes!" << std::endl;
}

void ParcDistractii::adaugaAngajat(std::unique_ptr<Angajat> angajat) {
    angajati.push_back(std::move(angajat));
    std::cout << "✅ Angajat adaugat cu succes!" << std::endl;
}

void ParcDistractii::adaugaVizitator(std::unique_ptr<Vizitator> vizitator) {
    vizitatori.push_back(std::move(vizitator));
    std::cout << "✅ Vizitator adaugat cu succes!" << std::endl;
}

void ParcDistractii::afiseazaAtractii() const {
    std::cout << "\n🎢 ========== ATRACTII DISPONIBILE ========== 🎢\n" << std::endl;
    if (atractii.empty()) {
        std::cout << "Nu exista atractii disponibile." << std::endl;
        return;
    }
    
    for (const auto& atractie : atractii) {
        std::cout << *atractie << std::endl;
    }
    std::cout << "============================================\n" << std::endl;
}

void ParcDistractii::afiseazaAngajati() const {
    std::cout << "\n👥 ========== ANGAJATI ========== 👥\n" << std::endl;
    if (angajati.empty()) {
        std::cout << "Nu exista angajati inregistrati." << std::endl;
        return;
    }
    
    for (const auto& angajat : angajati) {
        std::cout << *angajat << std::endl;
    }
    std::cout << "=================================\n" << std::endl;
}

void ParcDistractii::afiseazaVizitatori() const {
    std::cout << "\n🎫 ========== VIZITATORI ========== 🎫\n" << std::endl;
    if (vizitatori.empty()) {
        std::cout << "Nu exista vizitatori inregistrati." << std::endl;
        return;
    }
    
    for (const auto& vizitator : vizitatori) {
        std::cout << *vizitator << std::endl;
    }
    std::cout << "===================================\n" << std::endl;
}

void ParcDistractii::afiseazaStatistici() const {
    std::cout << "\n📊 ========== STATISTICI PARC ========== 📊\n" << std::endl;
    std::cout << "Nume parc: " << nume << std::endl;
    std::cout << "Numar total atractii: " << atractii.size() << std::endl;
    std::cout << "Numar total angajati: " << angajati.size() << std::endl;
    std::cout << "Numar total vizitatori: " << vizitatori.size() << std::endl;
    std::cout << "Venit total din bilete: " << calculezaVenitTotal() << " RON" << std::endl;
    std::cout << "Costuri salariale totale: " << calculezaCosturiSalariale() << " RON" << std::endl;
    
    double profit = calculezaVenitTotal() - calculezaCosturiSalariale();
    std::cout << "Profit estimat: " << profit << " RON" << std::endl;
    std::cout << "========================================\n" << std::endl;
}

void ParcDistractii::verificaAccesAtractie(const std::string& numeVizitator, const std::string& numeAtractie) const {
    // Cauta vizitatorul
    auto vizitatorIt = std::find_if(vizitatori.begin(), vizitatori.end(),
        [&numeVizitator](const std::unique_ptr<Vizitator>& v) {
            return v->getNume() == numeVizitator;
        });
    
    if (vizitatorIt == vizitatori.end()) {
        std::cout << "❌ Vizitatorul '" << numeVizitator << "' nu a fost gasit!" << std::endl;
        return;
    }
    
    // Cauta atractia
    auto atractieIt = std::find_if(atractii.begin(), atractii.end(),
        [&numeAtractie](const std::unique_ptr<Atractie>& a) {
            return a->getNume() == numeAtractie;
        });
    
    if (atractieIt == atractii.end()) {
        std::cout << "❌ Atractia '" << numeAtractie << "' nu a fost gasita!" << std::endl;
        return;
    }
    
    const auto& vizitator = *vizitatorIt;
    const auto& atractie = *atractieIt;
    
    std::cout << "\n🔍 Verificare acces pentru:" << std::endl;
    std::cout << "Vizitator: " << vizitator->getNume() << " (" << vizitator->getTip() << ")" << std::endl;
    std::cout << "Atractie: " << atractie->getNume() << " (" << atractie->getTip() << ")" << std::endl;
    
    bool poateAccesa = vizitator->poateAccesaAtractia(atractie->getInaltimeMinima());
    
    if (poateAccesa) {
        std::cout << "✅ ACCES PERMIS! Vizitatorul poate accesa atractia." << std::endl;
    } else {
        std::cout << "❌ ACCES INTERZIS! Motivele posibile:" << std::endl;
        if (vizitator->getInaltime() < atractie->getInaltimeMinima()) {
            std::cout << "   - Inaltimea insuficienta (" << vizitator->getInaltime() 
                      << " cm < " << atractie->getInaltimeMinima() << " cm)" << std::endl;
        }
        if (vizitator->getTip() == "Copil" && vizitator->getVarsta() < 8) {
            std::cout << "   - Copilul trebuie insotit de adult" << std::endl;
        }
    }
    std::cout << std::endl;
}

double ParcDistractii::calculezaVenitTotal() const {
    double total = 0.0;
    for (const auto& vizitator : vizitatori) {
        if (vizitator->getBilet()) {
            total += vizitator->getBilet()->calculeazaPretFinal();
        }
    }
    return total;
}

double ParcDistractii::calculezaCosturiSalariale() const {
    double total = 0.0;
    for (const auto& angajat : angajati) {
        total += angajat->calculeazaSalariuTotal();
    }
    return total;
}
