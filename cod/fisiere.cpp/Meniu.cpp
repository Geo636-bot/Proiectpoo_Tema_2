#include "Meniu.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>

using namespace std;

Menu::Menu(ParcDistractii& parc) : parc(parc) {
    // Creez observeri și îi adaug la parc
    logObserver = std::make_shared<LogObserver>();
    statsObserver = std::make_shared<StatisticsObserver>();
    
    parc.adaugaObserver(logObserver);
    parc.adaugaObserver(statsObserver);
}

void Menu::clearInput() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Menu::getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << endl;
        clearInput();
    }
}

double Menu::getValidDouble(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << endl;
        clearInput();
    }
}

std::string Menu::getValidString(const std::string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "❌ Textul nu poate fi gol!" << endl;
    }
}

bool Menu::getYesNo(const std::string& prompt) {
    char response;
    while (true) {
        cout << prompt << " (y/n): ";
        cin >> response;
        clearInput();
        if (response == 'y' || response == 'Y') return true;
        if (response == 'n' || response == 'N') return false;
        cout << "❌ Raspunde cu 'y' sau 'n'!" << endl;
    }
}

void Menu::afiseazaMeniu() {
    cout << "\n🎪 ========== MENIU PARC DISTRACȚII ========== 🎪" << endl;
    cout << "1. 🎢 Adauga Atractie (manual)" << endl;
    cout << "2. 🏭 Adauga Atractie (Factory Pattern)" << endl;
    cout << "3. 👤 Adauga Angajat" << endl;
    cout << "4. 🎫 Adauga Vizitator" << endl;
    cout << "5. 📋 Afiseaza Atractii" << endl;
    cout << "6. 👥 Afiseaza Angajati" << endl;
    cout << "7. 🎫 Afiseaza Vizitatori" << endl;
    cout << "8. 📊 Afiseaza Statistici Generale" << endl;
    cout << "9. 🔢 Afiseaza Statistici Template" << endl;
    cout << "10. 🔍 Verifica Acces Atractie" << endl;
    cout << "11. 🔬 Demonstratie Dynamic Cast" << endl;
    cout << "0. 🚪 Iesire" << endl;
    cout << "=============================================" << endl;
    cout << "Alegerea ta: ";
}

void Menu::ruleazaMeniu() {
    int optiune;
    
    do {
        afiseazaMeniu();
        optiune = getValidInt("", 0, 11);
        
        try {
            switch (optiune) {
                case 1:
                    adaugaAtractieInteractiv();
                    break;
                case 2:
                    adaugaAtractieFactory();
                    break;
                case 3:
                    adaugaAngajatInteractiv();
                    break;
                case 4:
                    adaugaVizitatorInteractiv();
                    break;
                case 5:
                    parc.afiseazaAtractii();
                    break;
                case 6:
                    parc.afiseazaAngajati();
                    break;
                case 7:
                    parc.afiseazaVizitatori();
                    break;
                case 8:
                    parc.afiseazaStatistici();
                    break;
                case 9:
                    parc.afiseazaStatisticiTemplate();
                    break;
                case 10:
                    verificaAccesInteractiv();
                    break;
                case 11:
                    parc.demonstratieDynamicCast();
                    break;
                case 0:
                    cout << "\n🎪 Multumim ca ati vizitat parcul! La revedere! 🎪\n" << endl;
                    cout << "📊 Statistici finale observeri: " << statsObserver->getNumarEvenimente() 
                         << " evenimente procesate" << endl;
                    break;
                default:
                    cout << "❌ Optiune invalida!" << endl;
            }
        } catch (const ParcException& e) {
            cout << "❌ Eroare: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "❌ Eroare neasteptata: " << e.what() << endl;
        }
        
        if (optiune != 0) {
            cout << "\nApasa Enter pentru a continua...";
            cin.ignore();
            cin.get();
        }
        
    } while (optiune != 0);
}

void Menu::adaugaAtractieFactory() {
    cout << "\n🏭 === ADAUGARE ATRACTIE CU FACTORY PATTERN === 🏭\n" << endl;
    
    cout << "Tipuri disponibile:" << endl;
    cout << "1. montagne (Montagne Russe)" << endl;
    cout << "2. carusel (Carusel)" << endl;
    cout << "3. casa (Casa Groazei)" << endl;
    
    int tipOptiune = getValidInt("Alege tipul atractiei (1-3): ", 1, 3);
    
    string tipAtractie;
    string parametruNume;
    switch (tipOptiune) {
        case 1:
            tipAtractie = "montagne";
            parametruNume = "viteza maxima (km/h)";
            break;
        case 2:
            tipAtractie = "carusel";
            parametruNume = "numar cai";
            break;
        case 3:
            tipAtractie = "casa";
            parametruNume = "nivel frica (1-10)";
            break;
    }
    
    string nume = getValidString("Numele atractiei: ");
    int inaltimeMinima = getValidInt("Inaltimea minima (cm): ", 50, 200);
    int capacitate = getValidInt("Capacitatea: ", 1, 100);
    int parametruSpecific = getValidInt(parametruNume + ": ", 1, 300);
    
    auto atractie = parc.creeazaAtractieFactory(tipAtractie, nume, inaltimeMinima, capacitate, parametruSpecific);
    
    if (atractie) {
        parc.adaugaAtractie(std::move(atractie));
        cout << "✅ Atractie creata cu succes folosind Factory Pattern!" << endl;
    } else {
        cout << "❌ Eroare la crearea atractiei!" << endl;
    }
}

void Menu::adaugaAtractieInteractiv() {
    cout << "\n➕ ========== ADAUGARE ATRACTIE NOUA ========== ➕\n" << endl;
    try {
        auto atractie = creeazaAtractie();
        parc.adaugaAtractie(std::move(atractie));
    } catch (const ParcException& e) {
        cout << "❌ Eroare la adaugarea atractiei: " << e.what() << endl;
    }
}

void Menu::adaugaAngajatInteractiv() {
    cout << "\n➕ ========== ADAUGARE ANGAJAT NOU ========== ➕\n" << endl;
    try {
        auto angajat = creeazaAngajat();
        parc.adaugaAngajat(std::move(angajat));
    } catch (const ParcException& e) {
        cout << "❌ Eroare la adaugarea angajatului: " << e.what() << endl;
    }
}

void Menu::adaugaVizitatorInteractiv() {
    cout << "\n➕ ========== ADAUGARE VIZITATOR NOU ========== ➕\n" << endl;
    try {
        auto vizitator = creeazaVizitator();
        parc.adaugaVizitator(std::move(vizitator));
    } catch (const ParcException& e) {
        cout << "❌ Eroare la adaugarea vizitatorului: " << e.what() << endl;
    }
}

void Menu::verificaAccesInteractiv() {
    cout << "\n🔍 ========== VERIFICARE ACCES ATRACTIE ========== 🔍\n" << endl;
    
    string numeVizitator = getValidString("Nume vizitator: ");
    string numeAtractie = getValidString("Nume atractie: ");
    
    parc.verificaAccesAtractie(numeVizitator, numeAtractie);
}

std::unique_ptr<Atractie> Menu::creeazaAtractie() {
    cout << "\nTip atractie:" << endl;
    cout << "1. Montagne Russe" << endl;
    cout << "2. Carusel" << endl;
    cout << "3. Casa Groazei" << endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    string nume = getValidString("Nume atractie: ");
    int inaltime = getValidInt("Inaltime minima (cm): ", 50, 200);
    int capacitate = getValidInt("Capacitate (persoane): ", 1, 100);
    
    if (inaltime < 50) {
        throw InaltimeInsuficienta("Inaltimea minima nu poate fi sub 50 cm");
    }
    
    switch (tip) {
        case 1: {
            int viteza = getValidInt("Viteza maxima (km/h): ", 10, 200);
            return std::make_unique<MontagneRusse>(nume, inaltime, capacitate, viteza);
        }
        case 2: {
            int cai = getValidInt("Numar cai: ", 4, 50);
            return std::make_unique<Carusel>(nume, inaltime, capacitate, cai);
        }
        case 3: {
            int frica = getValidInt("Nivel frica (1-10): ", 1, 10);
            return std::make_unique<CasaGroazei>(nume, inaltime, capacitate, frica);
        }
        default:
            throw DateInvalide("Tip atractie invalid");
    }
}

std::unique_ptr<Angajat> Menu::creeazaAngajat() {
    cout << "\nTip angajat:" << endl;
    cout << "1. Operator Atractie" << endl;
    cout << "2. Agent Paza" << endl;
    cout << "3. Casier" << endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    string nume = getValidString("Nume angajat: ");
    int varsta = getValidInt("Varsta: ", 18, 70);
    int experienta = getValidInt("Experienta (ani): ", 0, 50);
    double salariu = getValidDouble("Salariu: ", 1000.0, 50000.0);
    
    if (varsta < 18) {
        throw VarstaNecorespunzatoare("Angajatul trebuie sa aiba minim 18 ani");
    }
    
    switch (tip) {
        case 1: {
            string atractie = getValidString("Atractie deservita: ");
            return std::make_unique<OperatorAtractie>(nume, varsta, experienta, salariu, atractie);
        }
        case 2: {
            string zona = getValidString("Zona asignata: ");
            return std::make_unique<AgentPaza>(nume, varsta, experienta, salariu, zona);
        }
        case 3: {
            string interval = getValidString("Interval (ex: 08:00-16:00): ");
            return std::make_unique<Casier>(nume, varsta, experienta, salariu, interval);
        }
        default:
            throw DateInvalide("Tip angajat invalid");
    }
}

std::unique_ptr<Vizitator> Menu::creeazaVizitator() {
    cout << "\nTip vizitator:" << endl;
    cout << "1. Copil" << endl;
    cout << "2. Adolescent" << endl;
    cout << "3. Adult" << endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    string nume = getValidString("Nume vizitator: ");
    int varsta = getValidInt("Varsta: ", 1, 120);
    int inaltime = getValidInt("Inaltime (cm): ", 50, 250);
    
    auto bilet = creeazaBilet();
    
    switch (tip) {
        case 1: {
            if (varsta > 17) {
                throw VarstaNecorespunzatoare("Copilul nu poate avea peste 17 ani");
            }
            bool insotit = getYesNo("Insotit de adult?");
            return std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), insotit);
        }
        case 2: {
            if (varsta < 13 || varsta > 19) {
                throw VarstaNecorespunzatoare("Adolescentul trebuie sa aiba intre 13-19 ani");
            }
            bool buletin = getYesNo("Are buletin?");
            return std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), buletin);
        }
        case 3: {
            if (varsta < 18) {
                throw VarstaNecorespunzatoare("Adultul trebuie sa aiba minim 18 ani");
            }
            string ocupatie = getValidString("Ocupatie: ");
            return std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie);
        }
        default:
            throw DateInvalide("Tip vizitator invalid");
    }
}

std::unique_ptr<Bilet> Menu::creeazaBilet() {
    cout << "\nTip bilet:" << endl;
    cout << "1. Bilet Copil" << endl;
    cout << "2. Bilet Adult" << endl;
    cout << "3. Bilet VIP" << endl;
    
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
