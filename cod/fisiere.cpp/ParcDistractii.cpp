


#include "../Fisiere.h/ParcDistractii.h"
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

ParcDistractii::ParcDistractii(std::string nume)
    : zicurenta(0), nume(std::move(nume)) {
    ++numarParcuri;
}

void ParcDistractii::simuleazaZi() {
    zicurenta = (zicurenta + 1) % 7;
    std::cout << "📅 Zi simulata: " << getZiCurentaString() << std::endl;
}

int ParcDistractii::getZiCurenta() const {
    return zicurenta;
}

std::string ParcDistractii::getZiCurentaString() const {
    static const std::string zile[] = {
        "Luni", "Marti", "Miercuri", "Joi", "Vineri", "Sambata", "Duminica"
    };
    return zile[zicurenta];
}

ParcDistractii::ParcDistractii(const ParcDistractii& other) : nume(other.nume) {
    ++numarParcuri;
    copiazaAtractii(other.atractii);
    copiazaAngajati(other.angajati);
    copiazaVizitatori(other.vizitatori);
}

ParcDistractii& ParcDistractii::operator=(const ParcDistractii& other) {
    if (this != &other) {
        ParcDistractii temp(other);
        swap(temp);
    }
    return *this;
}

void ParcDistractii::swap(ParcDistractii& other) noexcept {
    std::swap(nume, other.nume);
    atractii.swap(other.atractii);
    angajati.swap(other.angajati);
    vizitatori.swap(other.vizitatori);
}

void ParcDistractii::copiazaAtractii(const std::vector<std::unique_ptr<Atractie>>& sursa) {
    for (const auto& atractie : sursa) {
        atractii.push_back(atractie->clone());
    }
}

void ParcDistractii::copiazaAngajati(const std::vector<std::unique_ptr<Angajat>>& sursa) {
    for (const auto& angajat : sursa) {
        angajati.push_back(angajat->clone());
    }
}

void ParcDistractii::copiazaVizitatori(const std::vector<std::unique_ptr<Vizitator>>& sursa) {
    for (const auto& vizitator : sursa) {
        vizitatori.push_back(vizitator->clone());
    }
}

bool ParcDistractii::atractieExista(const std::string &numeCautat) const {
    return ranges::any_of(atractii, [&](const std::unique_ptr<Atractie>& a) {
        return a->getNume() == numeCautat;
    });
}
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

void ParcDistractii::demonstratieDynamicCast() const {
    std::cout << "\n🔬 ========== DEMONSTRATIE DYNAMIC_CAST ========== 🔬\n" << std::endl;
    
    // Dynamic cast pentru atractii
    for (const auto& atractie : atractii) {
        std::cout << "Atractie: " << atractie->getNume() << " - ";
        
        if (auto montagne = dynamic_cast<const MontagneRusse*>(atractie.get())) {
            std::cout << "Este Montagne Russe cu viteza " << montagne->getVitezaMaxima() << " km/h" << std::endl;
        } else if (auto carusel = dynamic_cast<const Carusel*>(atractie.get())) {
            std::cout << "Este Carusel cu " << carusel->getNumarCai() << " cai" << std::endl;
        } else if (auto casa = dynamic_cast<const CasaGroazei*>(atractie.get())) {
            std::cout << "Este Casa Groazei cu nivel frica " << casa->getNivelFrica() << std::endl;
        }
    }
    
    // Dynamic cast pentru angajati
    for (const auto& angajat : angajati) {
        std::cout << "Angajat: " << angajat->getNume() << " - ";
        
        if (auto operator_atr = dynamic_cast<const OperatorAtractie*>(angajat.get())) {
            std::cout << "Operator pentru " << operator_atr->getAtractieDeservita() << std::endl;
        } else if (auto agent = dynamic_cast<const AgentPaza*>(angajat.get())) {
            std::cout << "Agent paza in zona " << agent->getZonaAsignata() << std::endl;
        } else if (auto casier = dynamic_cast<const Casier*>(angajat.get())) {
            std::cout << "Casier cu intervalul " << casier->getInterval() << std::endl;
        }
    }

    for (const auto& vizitator : vizitatori) {
        std::cout << "Viztator: " << vizitator->getNume() << " - ";
        if (auto copil = dynamic_cast<const Copil*>(vizitator.get())) {
            std::cout << "Este Copil, varsta: " << copil->getVarsta()
                      << ", insotit: " << (copil->getInsotitDeAdult() ? "da" : "nu") << std::endl;
        } else if (auto adolescent = dynamic_cast<const Adolescent*>(vizitator.get())) {
            std::cout << "Este Adolescent, varsta: " << adolescent->getVarsta()
                      << ", buletin: " << (adolescent->getAreBuletin() ? "da" : "nu") << std::endl;
        } else if (auto adult = dynamic_cast<const Adult*>(vizitator.get())) {
            std::cout << "Este Adult, varsta: " << adult->getVarsta()
                      << ", ocupatie: " << adult->getOcupatie() << std::endl;
        } else {
            std::cout << "Tip necunoscut de vizitator." << std::endl;
        }
    }

    std::cout << "==================================================\n" << std::endl;
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
    
    // Afisare statistici statice
    std::cout << "Numar total atractii create: " << Atractie::getNumarTotalAtractii() << std::endl;
    std::cout << "Salariu mediu angajati: " << Angajat::getSalariuMediu() << " RON" << std::endl;
    std::cout << "Numar parcuri create: " << getNumarParcuri() << std::endl;
    
    double profit = calculezaVenitTotal() - calculezaCosturiSalariale();
    std::cout << "Profit estimat: " << profit << " RON" << std::endl;
    std::cout << "========================================\n" << std::endl;
}

void ParcDistractii::verificaAccesAtractie(const std::string& numeVizitator, const std::string& numeAtractie) const {
    // Cauta vizitatorul
    auto vizitatorIt = ranges::find_if(vizitatori,
                                       [&numeVizitator](const std::unique_ptr<Vizitator>& v) {
                                           return v->getNume() == numeVizitator;
                                       });
    
    if (vizitatorIt == vizitatori.end()) {
        std::cout << "❌ Vizitatorul '" << numeVizitator << "' nu a fost gasit!" << std::endl;
        return;
    }
    
    // Cauta atractia
    auto atractieIt = ranges::find_if(atractii,
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

    if (vizitator->poateAccesaAtractia(atractie->getInaltimeMinima(),atractie->getVarstaNecesara())) {
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
        if (vizitator->getVarsta() < atractie->getVarstaNecesara()) {
            std::cout << "   - Varsta insuficienta (" << vizitator->getVarsta()
                      << " ani < " << atractie->getVarstaNecesara() << " ani)" << std::endl;
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
