
#include "../Fisiere.h/CsvLoader.h"
#include "../Fisiere.h/Exceptions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

bool CSVLoader::incarcaDate(ParcDistractii& parc) {
    cout << "\n📁 ========== INCARCARE DATE DIN CSV ========== 📁\n" << endl;
    
    bool succes = true;
    
    cout << "🎢 Incarcam atractii..." << endl;
    if (!incarcaAtractii(parc, "data/atractii.csv")) {
        cout << "❌ Eroare la incarcarea atractiilor" << endl;
        succes = false;
    } else {
        cout << "✅ Atractii incarcate cu succes!" << endl;
    }
    
    cout << "\n👥 Incarcam angajati..." << endl;
    if (!incarcaAngajati(parc, "data/angajati.csv")) {
        cout << "❌ Eroare la incarcarea angajatilor" << endl;
        succes = false;
    } else {
        cout << "✅ Angajati incarcati cu succes!" << endl;
    }
    
    cout << "\n🎫 Incarcam vizitatori..." << endl;
    if (!incarcaVizitatori(parc, "data/vizitatori.csv")) {
        cout << "❌ Eroare la incarcarea vizitatorilor" << endl;
        succes = false;
    } else {
        cout << "✅ Vizitatori incarcati cu succes!" << endl;
    }
    
    cout << "\n=============================================" << endl;
    return succes;
}

bool CSVLoader::incarcaAtractii(ParcDistractii& parc, const std::string& fisier) {
    ifstream file(fisier);
    if (!file.is_open()) {
        return false;
    }
    
    string linie;
    bool primaLinie = true;
    
    while (getline(file, linie)) {
        if (primaLinie) {
            primaLinie = false;
            continue; // sare header-ul
        }
        
        if (linie.empty()) continue;
        
        try {
            auto campuri = parseazaLinie(linie);
            if (campuri.size() != 6) continue;
            
            string nume = trim(campuri[0]);
            string tip = trim(campuri[1]);
            int inaltimeMinima = stoi(trim(campuri[2]));
            int capacitate = stoi(trim(campuri[3]));
            int varstaNecesara = stoi(trim(campuri[4]));
            int parametruSpecific = stoi(trim(campuri[5]));
            
            auto atractie = parc.adaugaAtractie(tip, nume, inaltimeMinima, capacitate, parametruSpecific);
            if (atractie) {
                parc.adaugaAtractie(std::move(atractie));
            }
            
        } catch (const exception& e) {
            cout << "⚠️  Eroare la procesarea liniei: " << linie << endl;
            continue;
        }
    }
    
    return true;
}

bool CSVLoader::incarcaAngajati(ParcDistractii& parc, const std::string& fisier) {
    ifstream file(fisier);
    if (!file.is_open()) {
        return false;
    }
    
    string linie;
    bool primaLinie = true;
    
    while (getline(file, linie)) {
        if (primaLinie) {
            primaLinie = false;
            continue;
        }
        
        if (linie.empty()) continue;
        
        try {
            auto campuri = parseazaLinie(linie);
            if (campuri.size() != 6) continue;
            
            string nume = trim(campuri[0]);
            string tip = trim(campuri[1]);
            int varsta = stoi(trim(campuri[2]));
            int experienta = stoi(trim(campuri[3]));
            double salariu = stod(trim(campuri[4]));
            string parametruSpecific = trim(campuri[5]);
            
            std::unique_ptr<Angajat> angajat;
            
            if (tip == "operator") {
                angajat = std::make_unique<OperatorAtractie>(nume, varsta, experienta, salariu, parametruSpecific);
            } else if (tip == "paza") {
                angajat = std::make_unique<AgentPaza>(nume, varsta, experienta, salariu, parametruSpecific);
            } else if (tip == "casier") {
                angajat = std::make_unique<Casier>(nume, varsta, experienta, salariu, parametruSpecific);
            }
            
            if (angajat) {
                parc.adaugaAngajat(std::move(angajat));
            }
            
        } catch (const exception& e) {
            cout << "⚠️  Eroare la procesarea liniei: " << linie << endl;
            continue;
        }
    }
    
    return true;
}

bool CSVLoader::incarcaVizitatori(ParcDistractii& parc, const std::string& fisier) {
    ifstream file(fisier);
    if (!file.is_open()) {
        return false;
    }
    
    string linie;
    bool primaLinie = true;
    
    while (getline(file, linie)) {
        if (primaLinie) {
            primaLinie = false;
            continue;
        }
        
        if (linie.empty()) continue;
        
        try {
            auto campuri = parseazaLinie(linie);
            if (campuri.size() != 5) continue;
            
            string nume = trim(campuri[0]);
            int varsta = stoi(trim(campuri[1]));
            int inaltime = stoi(trim(campuri[2]));
            string tipBilet = trim(campuri[3]);
            bool parametruBilet = (trim(campuri[4]) == "true");
            
            // Creez biletul
            std::unique_ptr<Bilet> bilet;
            if (tipBilet == "copil") {
                bilet = std::make_unique<BiletCopil>(50.0, 1, varsta);
            } else if (tipBilet == "adult") {
                bilet = std::make_unique<BiletAdult>(80.0, 1, parametruBilet);
            } else if (tipBilet == "vip") {
                bilet = std::make_unique<BiletVIP>(120.0, 1, parametruBilet);
            }
            
            // Creez vizitatorul
            std::unique_ptr<Vizitator> vizitator;
            if (varsta <= 12) {
                vizitator = std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), parametruBilet);
            } else if (varsta <= 17) {
                vizitator = std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), parametruBilet);
            } else {
                string ocupatie = "Necunoscuta";
                vizitator = std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie);
            }
            
            if (vizitator) {
                parc.adaugaVizitator(std::move(vizitator));
            }
            
        } catch (const exception& e) {
            cout << "⚠️  Eroare la procesarea liniei: " << linie << endl;
            continue;
        }
    }
    
    return true;
}

std::vector<std::string> CSVLoader::parseazaLinie(const std::string& linie) {
    vector<string> campuri;
    stringstream ss(linie);
    string camp;
    
    while (getline(ss, camp, ',')) {
        campuri.push_back(camp);
    }
    
    return campuri;
}

std::string CSVLoader::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
