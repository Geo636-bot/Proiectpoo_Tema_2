
#include "../Fisiere.h/Meniu.h"
#include "../Fisiere.h/Exceptions.h"
#include <iostream>
#include <limits>
#include <regex>

Meniu::Meniu(ParcDistractii& parc) : parc(parc) {}

void Meniu::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Meniu::getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        std::cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << std::endl;
        clearInput();
    }
}

double Meniu::getValidDouble(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        std::cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << std::endl;
        clearInput();
    }
}

std::string Meniu::getValidString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "❌ Textul nu poate fi gol!" << std::endl;
    }
}

bool Meniu::getYesNo(const std::string& prompt) {
    char response;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::cin >> response;
        clearInput();
        if (response == 'y' || response == 'Y') return true;
        if (response == 'n' || response == 'N') return false;
        std::cout << "❌ Raspunde cu 'y' sau 'n'!" << std::endl;
    }
}

void Meniu::afiseazaMeniu() {
    std::cout << "\n🎡 ========== SISTEM GESTIUNE PARC DE DISTRACTII ========== 🎡\n";
    std::cout << "1. Afiseaza toate atractiile" << std::endl;
    std::cout << "2. Afiseaza toti angajatii" << std::endl;
    std::cout << "3. Afiseaza toti vizitatorii" << std::endl;
    std::cout << "4. Afiseaza statistici parc" << std::endl;
    std::cout << "5. Adauga atractie noua" << std::endl;
    std::cout << "6. Adauga angajat nou" << std::endl;
    std::cout << "7. Adauga vizitator nou" << std::endl;
    std::cout << "8. Verifica accesul la o atractie" << std::endl;
    std::cout << "9. Demonstratie dynamic_cast" << std::endl;
    std::cout << "0. Iesire" << std::endl;
    std::cout << "===========================================================\n";
    std::cout << "Alege optiunea: ";
}

void Meniu::ruleazaMeniu() const {
    int optiune;
    do {
        afiseazaMeniu();
        optiune = getValidInt("", 0, 9);
        
        try {
            switch (optiune) {
                case 1:
                    parc.afiseazaAtractii();
                    break;
                case 2:
                    parc.afiseazaAngajati();
                    break;
                case 3:
                    parc.afiseazaVizitatori();
                    break;
                case 4:
                    parc.afiseazaStatistici();
                    break;
                case 5:
                    adaugaAtractieInteractiv();
                    break;
                case 6:
                    adaugaAngajatInteractiv();
                    break;
                case 7:
                    adaugaVizitatorInteractiv();
                    break;
                case 8:
                    verificaAccesInteractiv();
                    break;
                case 9:
                    parc.demonstratieDynamicCast();
                    break;
                case 0:
                    std::cout << "\n🎡 Multumim ca ai vizitat " << parc.getNume() << "! La revedere! 🎡\n" << std::endl;
                    break;
                default: ;
            }
        } catch (const ParcException& e) {
            std::cout << "❌ Eroare: " << e.what();
        }
        
    } while (optiune != 0);
}

void Meniu::adaugaAtractieInteractiv() const {
    std::cout << "\n➕ ========== ADAUGARE ATRACTIE NOUA ========== ➕\n" << std::endl;
    try {
        auto atractie = creeazaAtractie();
        parc.adaugaAtractie(std::move(atractie));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea atractiei: " << e.what();
    }
}

void Meniu::adaugaAngajatInteractiv() const {
    std::cout << "\n➕ ========== ADAUGARE ANGAJAT NOU ========== ➕\n" << std::endl;
    try {
        auto angajat = creeazaAngajat() ;
        parc.adaugaAngajat(std::move(angajat));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea angajatului: " << e.what();
    }
}

void Meniu::adaugaVizitatorInteractiv() const {

    try {
        auto vizitator = creeazaVizitator();
        parc.adaugaVizitator(std::move(vizitator));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea vizitatorului: " << e.what();
    }
}

void Meniu::verificaAccesInteractiv() const {
    std::cout << "\n🔍 ========== VERIFICARE ACCES ATRACTIE ========== 🔍\n" << std::endl;
    if (parc.getNumarAtractii()==0 || parc.getNumarVizitatori()==0) {
        throw DateInvalide("Trebuie sa ai minim un vizitator si minim o atractie pentru a verifica accesul");
    }
    std::string numeVizitator = getValidString("Nume vizitator: ");
    std::string numeAtractie = getValidString("Nume atractie: ");
    parc.verificaAccesAtractie(numeVizitator, numeAtractie);
}

std::unique_ptr<Atractie> Meniu::creeazaAtractie() {
    std::cout << "\nTip atractie:" << std::endl;
    std::cout << "1. Montagne Russe" << std::endl;
    std::cout << "2. Carusel" << std::endl;
    std::cout << "3. Casa Groazei" << std::endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    std::string nume = getValidString("Nume atractie: ");
    int inaltime = getValidInt("Inaltime minima (cm): ", 50, 200);
    int capacitate = getValidInt("Capacitate (persoane): ", 1, 100);
    int varsta=getValidInt("Varsta necesara: ", 1, 100);
    
    if (inaltime < 50) {
        throw InaltimeInsuficienta("Inaltimea minima nu poate fi sub 50 cm");
    }
    if (varsta<1){
        throw VarstaNecorespunzatoare("Varsta nu poate fi mai mica de un an");
    }
    
    switch (tip) {
        case 1: {
            int viteza = getValidInt("Viteza maxima (km/h): ", 10, 200);
            return std::make_unique<MontagneRusse>(nume, inaltime, capacitate,varsta, viteza);
        }
        case 2: {
            int cai = getValidInt("Numar cai: ", 4, 50);
            return std::make_unique<Carusel>(nume, inaltime, capacitate,varsta, cai);
        }
        case 3: {
            int frica = getValidInt("Nivel frica (1-10): ", 1, 10);
            return std::make_unique<CasaGroazei>(nume, inaltime, capacitate,varsta, frica);
        }
        default:
            throw DateInvalide("Tip atractie invalid");
    }
}

std::unique_ptr<Angajat> Meniu::creeazaAngajat() const {
    std::cout << "\nTip angajat:" << std::endl;
    std::cout << "1. Operator Atractie" << std::endl;
    std::cout << "2. Agent Paza" << std::endl;
    std::cout << "3. Casier" << std::endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    std::string nume = getValidString("Nume angajat: ");
    int varsta = getValidInt("Varsta: ", 18, 70);
    int experienta = getValidInt("Experienta (ani): ", 0, 50);
    double salariu = getValidDouble("Salariu: ", 1000.0, 50000.0);
    
    if (varsta < 18) {
        throw VarstaNecorespunzatoare("Angajatul trebuie sa aiba minim 18 ani");
    }
    
    switch (tip) {
        case 1: {
            std::string atractie;
            do {
                atractie = getValidString("Atractie deservita: ");
                if (!parc.atractieExista(atractie)) {
                    throw DateInvalide("Atractia nu exista! Introdu alta.");
                }
            } while (!parc.atractieExista(atractie));

            return std::make_unique<OperatorAtractie>(nume, varsta, experienta, salariu, atractie);
        }
        case 2: {
            std::string zona = getValidString("Zona asignata(N,S,E,W): ");
            if (zona !="N" && zona !="W" && zona !="E" && zona !="S") {
                throw zonaInvalida("Zona asignata poate fi doar N,S,E,W");
            }
            return std::make_unique<AgentPaza>(nume, varsta, experienta, salariu, zona);
        }
        case 3: {
            std::string interval = getValidString("Interval (ex: 08:00-16:00): ");
                std::regex format("^([01][0-9]|2[0-3]):[0-5][0-9]-([01][0-9]|2[0-3]):[0-5][0-9]$");
            if (!std::regex_match(interval, format)) {
                throw DateInvalide("Formatul intervalului este invalid. Exemplu valid: 08:00-16:00");
            }
            return std::make_unique<Casier>(nume, varsta, experienta, salariu, interval);
        }
        default:
            throw DateInvalide("Tip angajat invalid");
    }
}

std::unique_ptr<Vizitator> Meniu::creeazaVizitator() {
    std::cout << "\n➕ ========== CREARE VIZITATOR NOU ========== ➕\n" << std::endl;

    // Obțin datele de bază ale vizitatorului
    std::string nume =getValidString("Nume vizitator: ");
    int varsta = getValidInt("Varsta: ", 1, 120);
    int inaltime = getValidInt("Inaltime (cm): ", 50, 250);

    // Determin tipul de vizitator pe baza vârstei
    std::string tipVizitator;
    if (varsta <= 12) {
        tipVizitator = "Copil";
    } else if (varsta >= 13 && varsta <= 17) {
        tipVizitator = "Adolescent";
    } else {
        tipVizitator = "Adult";
    }

    std::cout << "📋 Tip vizitator detectat automat: " << tipVizitator << std::endl;

    // Creez biletul automat în funcție de vârstă
    std::unique_ptr<Bilet> bilet = creeazaBilet();

    // Creez vizitatorul în funcție de tip
    if (tipVizitator == "Copil") {
        bool insotit = getYesNo("Este insotit de adult? ");
        return std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), insotit);
    }
    else if (tipVizitator == "Adolescent") {
        bool buletin = getYesNo("Are buletin? ");
        return std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), buletin);
    }
    else { // Adult
        std::string ocupatie = getValidString("Ocupatie: ");
        return std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie);
    }
}

std::unique_ptr<Bilet> Meniu::creeazaBilet() {
    std::cout << "\nTip bilet:" << std::endl;
    std::cout << "1. Bilet Copil" << std::endl;
    std::cout << "2. Bilet Adult" << std::endl;
    std::cout << "3. Bilet VIP" << std::endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    double pret = getValidDouble("Pret de baza: ", 10.0, 1000.0);
    int valabilitate = getValidInt("Valabilitate (zile): ", 1, 365);
    
    switch (tip) {
        case 1: {
            int varsta = getValidInt("Varsta copilului: ", 1, 17);
            return std::make_unique<BiletCopil>(pret, valabilitate, varsta);
        }
        case 2: {
            bool fastPass = getYesNo("Include Fast Pass?");
            return std::make_unique<BiletAdult>(pret, valabilitate, fastPass);
        }
        case 3: {
            bool lounge = getYesNo("Include acces Lounge?");
            return std::make_unique<BiletVIP>(pret, valabilitate, lounge);
        }
        default:
            throw DateInvalide("Tip bilet invalid");
    }
}
