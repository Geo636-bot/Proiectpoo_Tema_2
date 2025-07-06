

#include "../Fisiere.h/ParcDistractii.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

// Inițializare atribut static
int ParcDistractii::numarParcuri = 0;

ParcDistractii::ParcDistractii(std::string  nume)
    : nume(std::move(nume)) {
    ++numarParcuri;
}

ParcDistractii::ParcDistractii(const ParcDistractii& other) 
    : nume(other.nume) {
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

bool ParcDistractii::existaAtractie(const std::string& numeAtractie) const {
    return ranges::find_if(atractii,
                           [&numeAtractie](const std::unique_ptr<Atractie>& a) {
                               return a->getNume() == numeAtractie;
                           }) != atractii.end();
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

// Metode pentru incarcarea datelor din CSV
void ParcDistractii::incarcaAtractiiDinCSV() {
    std::ifstream file("../../data/Atractii.csv");
    if (!file.is_open()) {
        std::cout << "❌ Nu s-a putut deschide fisierul data/atractii.csv" << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line); // Skip header
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nume, tip, param1, param2, param3, param4;
        
        std::getline(ss, nume, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, param1, ',');
        std::getline(ss, param2, ',');
        std::getline(ss, param3, ',');
        std::getline(ss, param4, ',');
        
        int inaltimeMin = std::stoi(param1);
        int capacitate = std::stoi(param2);
        int varstaNecesara = std::stoi(param3);
        int parametruSpecific = std::stoi(param4);
        
        if (tip == "montagne") {
            adaugaAtractie(std::make_unique<MontagneRusse>(nume, inaltimeMin, capacitate, varstaNecesara, parametruSpecific));
        } else if (tip == "carusel") {
            adaugaAtractie(std::make_unique<Carusel>(nume, inaltimeMin, capacitate, varstaNecesara, parametruSpecific));
        } else if (tip == "casa") {
            adaugaAtractie(std::make_unique<CasaGroazei>(nume, inaltimeMin, capacitate, varstaNecesara, parametruSpecific));
        }
    }
    
    std::cout << "✅ Atractii incarcate din CSV!" << std::endl;
}

void ParcDistractii::incarcaAngajatiDinCSV() {
    std::ifstream file("../../data/Angajati.csv");
    if (!file.is_open()) {
        std::cout << "❌ Nu s-a putut deschide fisierul data/angajati.csv" << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line); // Skip header
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nume, tip, param1, param2, param3, param4;
        
        std::getline(ss, nume, ',');
        std::getline(ss, param1, ',');
        std::getline(ss, param2, ',');
        std::getline(ss, param3, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, param4, ',');
        
        int varsta = std::stoi(param1);
        int experienta = std::stoi(param2);
        double salariu = std::stod(param3);
        
        if (tip == "operator") {
            adaugaAngajat(std::make_unique<OperatorAtractie>(nume, varsta, experienta, salariu, param4));
        } else if (tip == "paza") {
            adaugaAngajat(std::make_unique<AgentPaza>(nume, varsta, experienta, salariu, param4));
        } else if (tip == "casier") {
            adaugaAngajat(std::make_unique<Casier>(nume, varsta, experienta, salariu, param4));
        }
    }
    
    std::cout << "✅ Angajati incarcati din CSV!" << std::endl;
}

void ParcDistractii::incarcaVizitatoriDinCSV() {
    std::ifstream file("../../data/Vizitatori.csv");
    if (!file.is_open()) {
        std::cout << "❌ Nu s-a putut deschide fisierul data/vizitatori.csv" << std::endl;
        return;
    }
    
    std::string line;
    std::getline(file, line); // Skip header
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string nume, varsta_str, inaltime_str, tip_bilet, parametru_str;
        
        std::getline(ss, nume, ',');
        std::getline(ss, varsta_str, ',');
        std::getline(ss, inaltime_str, ',');
        std::getline(ss, tip_bilet, ',');
        std::getline(ss, parametru_str, ',');
        
        int varsta = std::stoi(varsta_str);
        int inaltime = std::stoi(inaltime_str);
        bool parametru = (parametru_str == "true");
        
        // Creez biletul bazat pe tip
        std::unique_ptr<Bilet> bilet;
        if (tip_bilet == "standard") {
            bilet = std::make_unique<BiletStandard>(1);
        } else if (tip_bilet == "adult") {
            bilet = std::make_unique<BiletAdult>(1, parametru);
        } else if (tip_bilet == "vip") {
            bilet = std::make_unique<BiletVIP>(1, parametru);
        }
        
        // Determin tipul de vizitator bazat pe varsta
        if (varsta < 13) {
            adaugaVizitator(std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), parametru));
        } else if (varsta < 18) {
            adaugaVizitator(std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), parametru));
        } else {
            adaugaVizitator(std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), "Necunoscut"));
        }
    }
    
    std::cout << "✅ Vizitatori incarcati din CSV!" << std::endl;
}

void ParcDistractii::incarcaToateDatale() {
    std::cout << "\n📁 ========== INCARCARE DATE CSV ========== 📁\n" << std::endl;
    incarcaAtractiiDinCSV();
    incarcaAngajatiDinCSV();
    incarcaVizitatoriDinCSV();
    std::cout << "==========================================\n" << std::endl;
}
