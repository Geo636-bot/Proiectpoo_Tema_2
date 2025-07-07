
#include "../Fisiere.h/ParcDistractii.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// Inițializare atribut static
int ParcDistractii::numarParcuri = 0;

ParcDistractii::ParcDistractii(const std::string& nume)
    : nume(nume), profitSaptamanal(0.0) {
    ++numarParcuri;
}

ParcDistractii::ParcDistractii(const ParcDistractii& other)
    : nume(other.nume), profitSaptamanal(other.profitSaptamanal) {
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

void ParcDistractii::swap(ParcDistractii& other) {
    std::swap(nume, other.nume);
    std::swap(profitSaptamanal, other.profitSaptamanal);
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
    return std::find_if(atractii.begin(), atractii.end(),
        [&numeAtractie](const std::unique_ptr<Atractie>& a) {
            return a->getNume() == numeAtractie;
        }) != atractii.end();
}

void ParcDistractii::scadeValabilitateBilete() {
    // Vector pentru a stoca vizitatorii care raman valizi
    std::vector<std::unique_ptr<Vizitator>> vizitatoriValizi;
    bool vizitatorEliminat = false;

    for (auto& vizitator : vizitatori) {
        if (vizitator->getBilet()) {
            vizitator->getBilet()->scadeValabilitate();

            // Verific daca biletul este inca valid dupa scaderea valabilitatii
            if (vizitator->getBilet()->esteValid()) {
                vizitatoriValizi.push_back(std::move(vizitator));
            } else {
                std::cout << "🗑️ Vizitatorul " << vizitator->getNume()
                         << " a fost eliminat din parc - bilet expirat!" << std::endl;
                vizitatorEliminat = true;
            }
        } else {
            // Daca nu are bilet, il elimin oricum
            std::cout << "🗑️ Vizitatorul " << vizitator->getNume()
                     << " a fost eliminat din parc - nu are bilet!" << std::endl;
            vizitatorEliminat = true;
        }
    }

    // Inlocuiesc vectorul de vizitatori cu cei valizi
    vizitatori = std::move(vizitatoriValizi);

    // NU mai resetez profitul - acesta se va actualiza doar Lunea
    if (vizitatorEliminat) {
        std::cout << "💰 Profitul săptămânal va fi actualizat în următoarea zi de Luni!" << std::endl;
    }
}

void ParcDistractii::actualizeazaProfitSaptamanal() {
    // Actualizez profitul doar in zilele de Luni
    if (Bilet::getZiCurenta() == ZiSaptamana::Luni) {
        double venitTotal = calculezaVenitTotal();
        double costuriSalariale = calculezaCosturiSalariale();
        profitSaptamanal = venitTotal - costuriSalariale;
        std::cout << "📊 Profitul săptămânal a fost actualizat (Luni): " << profitSaptamanal << " RON" << std::endl;
    }
}

// Metode noi pentru validari angajati
std::string ParcDistractii::gasesteAtractieFaraOperator() const {
    // Gasesc toate atractiile care nu au operator
    for (const auto& atractie : atractii) {
        bool areOperator = false;

        // Verific daca exista un operator pentru aceasta atractie
        for (const auto& angajat : angajati) {
            if (auto operator_atr = dynamic_cast<const OperatorAtractie*>(angajat.get())) {
                if (operator_atr->getAtractieDeservita() == atractie->getNume()) {
                    areOperator = true;
                    break;
                }
            }
        }

        if (!areOperator) {
            return atractie->getNume();
        }
    }

    return ""; // Nu exista atractii fara operator
}

bool ParcDistractii::atractieAreOperator(const std::string& numeAtractie) const {
    // Verific daca atractia are deja un operator asignat
    for (const auto& angajat : angajati) {
        if (auto operator_atr = dynamic_cast<const OperatorAtractie*>(angajat.get())) {
            if (operator_atr->getAtractieDeservita() == numeAtractie) {
                return true;
            }
        }
    }
    return false;
}

int ParcDistractii::getNumarPaznici() const {
    int numarPaznici = 0;
    for (const auto& angajat : angajati) {
        if (dynamic_cast<const AgentPaza*>(angajat.get())) {
            numarPaznici++;
        }
    }
    return numarPaznici;
}

bool ParcDistractii::verificaZonaOcupata(const std::string& zona) const {
    // Verific daca zona este deja ocupata de alt paznic
    for (const auto& angajat : angajati) {
        if (auto agent = dynamic_cast<const AgentPaza*>(angajat.get())) {
            if (agent->getZonaAsignata() == zona) {
                return true;
            }
        }
    }
    return false;
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
    std::cout << "Costuri salariale saptamanale: " << calculezaCosturiSalariale() << " RON" << std::endl;

    // Afisare statistici statice
    std::cout << "Numar total atractii create: " << Atractie::getNumarTotalAtractii() << std::endl;
    std::cout << "Salariu mediu angajati (saptamanal): " << Angajat::getSalariuMediu() << " RON" << std::endl;
    std::cout << "Numar parcuri create: " << getNumarParcuri() << std::endl;

    std::cout << "Profit saptamanal (actualizat Lunea): " << profitSaptamanal << " RON" << std::endl;
    if (Bilet::getZiCurenta() != ZiSaptamana::Luni) {
        std::cout << "⚠️ Profitul se va actualiza în următoarea zi de Luni" << std::endl;
    }
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

    bool poateAccesa = vizitator->poateAccesaAtractia(atractie->getInaltimeMinima(),atractie->getVarstaNecesara());

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

void ParcDistractii::incarcaAtractiiDinCSV() {
    std::ifstream file("data/atractii.csv");
    if (!file.is_open()) {
        std::cout << "❌ Nu s-a putut deschide fisierul data/atractii.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string numeAtractie, tip, param1, param2, param3;

        std::getline(ss, numeAtractie, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, param1, ',');
        std::getline(ss, param2, ',');
        std::getline(ss, param3, ',');

        int inaltimeMin = std::stoi(param1);
        int varstaNecesara = std::stoi(param2);
        int parametruSpecific = std::stoi(param3);

        if (tip == "montagne") {
            adaugaAtractie(std::make_unique<MontagneRusse>(numeAtractie, inaltimeMin, varstaNecesara, parametruSpecific));
        } else if (tip == "carusel") {
            adaugaAtractie(std::make_unique<Carusel>(numeAtractie, inaltimeMin, varstaNecesara, parametruSpecific));
        } else if (tip == "casa") {
            adaugaAtractie(std::make_unique<CasaGroazei>(numeAtractie, inaltimeMin, varstaNecesara, parametruSpecific));
        }
    }

    std::cout << "✅ Atractii incarcate din CSV!" << std::endl;
}

void ParcDistractii::incarcaAngajatiDinCSV() {
    std::ifstream file("data/angajati.csv");
    if (!file.is_open()) {
        std::cout << "❌ Nu s-a putut deschide fisierul data/angajati.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string numeAngajat, param1, param2, param3, tip, param4;

        std::getline(ss, numeAngajat, ',');
        std::getline(ss, param1, ',');
        std::getline(ss, param2, ',');
        std::getline(ss, param3, ',');
        std::getline(ss, tip, ',');
        std::getline(ss, param4, ',');

        int varsta = std::stoi(param1);
        int experienta = std::stoi(param2);
        double salariu = std::stod(param3); // acum este salariu saptamanal

        if (tip == "operator") {
            adaugaAngajat(std::make_unique<OperatorAtractie>(numeAngajat, varsta, experienta, salariu, param4));
        } else if (tip == "paza") {
            adaugaAngajat(std::make_unique<AgentPaza>(numeAngajat, varsta, experienta, salariu, param4));
        } else if (tip == "casier") {
            adaugaAngajat(std::make_unique<Casier>(numeAngajat, varsta, experienta, salariu, param4));
        }
    }

    std::cout << "✅ Angajati incarcati din CSV!" << std::endl;
}

void ParcDistractii::incarcaVizitatoriDinCSV() {
    std::ifstream file("data/vizitatori.csv");
    if (!file.is_open()) {
        std::cout << "❌ Nu s-a putut deschide fisierul data/vizitatori.csv" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string numeVizitator, varsta_str, inaltime_str, tip_bilet, parametru_str;

        std::getline(ss, numeVizitator, ',');
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
            bilet = std::make_unique<BiletPremium>(1, parametru);
        } else if (tip_bilet == "vip") {
            bilet = std::make_unique<BiletVIP>(1, parametru);
        }

        // Determin tipul de vizitator bazat pe varsta
        if (varsta < 13) {
            adaugaVizitator(std::make_unique<Copil>(numeVizitator, varsta, inaltime, std::move(bilet), parametru));
        } else if (varsta < 18) {
            adaugaVizitator(std::make_unique<Adolescent>(numeVizitator, varsta, inaltime, std::move(bilet)));
        } else {
            adaugaVizitator(std::make_unique<Adult>(numeVizitator, varsta, inaltime, std::move(bilet)));
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
