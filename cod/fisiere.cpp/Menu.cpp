

#include "../Fisiere.h/Menu.h"
#include "../Fisiere.h/Bilet.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

Menu::Menu(ParcDistractii& parc) : parc(parc) {}

void Menu::afiseazaMeniu() {
    cout << "\n🎪 ========== MENIU PARC DISTRACȚII ========== 🎪" << endl;
    cout << "📅 Ziua curenta: " << Bilet::getNumeZi(Bilet::getZiCurenta());
    if (Bilet::esteWeekend(Bilet::getZiCurenta())) {
        cout << " (Weekend - preturi majorate cu 25%)";
    }
    cout << "\n" << endl;

    cout << "1. 🎢 Afiseaza toate atractiile" << endl;
    cout << "2. 👥 Afiseaza toti angajatii" << endl;
    cout << "3. 🎫 Afiseaza toti vizitatorii" << endl;
    cout << "4. 📊 Afiseaza statistici parc" << endl;
    cout << "5. 🎢 Adauga atractie noua" << endl;
    cout << "6. 👤 Adauga angajat nou" << endl;
    cout << "7. 🎫 Adauga vizitator nou" << endl;
    cout << "8. 🔍 Verifica accesul la o atractie" << endl;
    cout << "9. 🔬 Demonstratie dynamic_cast" << endl;
    cout << "10. 📁 Incarca Date din CSV" << endl;
    cout << "11. 📅 Simuleaza trecerea unei zile" << endl;
    cout << "0. 🚪 Iesire" << endl;
    cout << "=============================================" << endl;
    cout << "Alegerea ta: ";
}

void Menu::ruleazaMeniu() const {
    int optiune;

    do {
        afiseazaMeniu();
        optiune = getValidInt("", 0, 11);

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
                case 10:
                    parc.incarcaToateDatale();
                    break;
                case 11:
                    simuleazaTrecereaZilei();
                    break;
                case 0:
                    cout << "\n🎪 Multumim ca ati vizitat parcul! La revedere! 🎪\n" << endl;
                    break;
                default:
                    cout << "❌ Optiune invalida!" << endl;
            }
        } catch (const exception& e) {
            cout << "❌ Eroare neasteptata: " << e.what() << endl;
        }


    } while (optiune != 0);
}

void Menu::simuleazaTrecereaZilei() {
    cout << "\n📅 ========== SIMULARE TRECERE ZI ========== 📅\n" << endl;

    ZiSaptamana ziVeche = Bilet::getZiCurenta();
    cout << "Ziua curenta: " << Bilet::getNumeZi(ziVeche);
    if (Bilet::esteWeekend(ziVeche)) {
        cout << " (Weekend)";
    }
    cout << endl;

    Bilet::trecutZi();

    ZiSaptamana ziNoua = Bilet::getZiCurenta();
    cout << "Ziua noua: " << Bilet::getNumeZi(ziNoua);
    if (Bilet::esteWeekend(ziNoua)) {
        cout << " (Weekend - preturile vor fi majorate cu 25%)";
    }
    cout << endl;

    cout << "\n✅ A trecut o zi! Preturile biletelor se vor actualiza automat." << endl;
    cout << "==========================================\n" << endl;
}

void Menu::adaugaAtractieInteractiv() const {
    cout << "\n🎢 ========== ADAUGARE ATRACTIE ========== 🎢\n" << endl;

    string nume = getValidString("Introduceti numele atractiei: ");
    int inaltimeMinima = getValidInt("Introduceti inaltimea minima (cm): ", 80, 200);
    int capacitate = getValidInt("Introduceti capacitatea: ", 1, 100);
    int varstaNecesara = getValidInt("Introduceti varsta minima necesara: ", 0, 18);

    cout << "\nTipuri de atractii disponibile:" << endl;
    cout << "1. Montagne Russe" << endl;
    cout << "2. Carusel" << endl;
    cout << "3. Casa Groazei" << endl;

    switch (getValidInt("Alegeti tipul atractiei (1-3): ", 1, 3)) {
        case 1: {
            int vitezaMaxima = getValidInt("Introduceti viteza maxima (km/h): ", 30, 200);
            parc.adaugaAtractie(std::make_unique<MontagneRusse>(nume, inaltimeMinima, capacitate, varstaNecesara, vitezaMaxima));
            break;
        }
        case 2: {
            int numarCai = getValidInt("Introduceti numarul de cai: ", 4, 20);
            parc.adaugaAtractie(std::make_unique<Carusel>(nume, inaltimeMinima, capacitate, varstaNecesara, numarCai));
            break;
        }
        case 3: {
            int nivelFrica = getValidInt("Introduceti nivelul de frica (1-10): ", 1, 10);
            parc.adaugaAtractie(std::make_unique<CasaGroazei>(nume, inaltimeMinima, capacitate, varstaNecesara, nivelFrica));
            break;
        }
        default:
            break;
    }

    cout << "==========================================\n" << endl;
}

void Menu::adaugaAngajatInteractiv() const {
    cout << "\n👤 ========== ADAUGARE ANGAJAT ========== 👤\n" << endl;

    string nume = getValidString("Introduceti numele angajatului: ");
    int varsta = getValidInt("Introduceti varsta: ", 18, 70);
    int experientaAni = getValidInt("Introduceti experienta (ani): ", 0, 40);
    double salariu = getValidDouble("Introduceti salariul: ", 1500.0, 10000.0);

    cout << "\nTipuri de angajati disponibili:" << endl;
    cout << "1. Operator Atractie" << endl;
    cout << "2. Agent Paza" << endl;
    cout << "3. Casier" << endl;

    switch (getValidInt("Alegeti tipul angajatului (1-3): ", 1, 3)) {
        case 1: {
            string atractieDeservita = getValidString("Introduceti atractia deservita: ");
            parc.adaugaAngajat(std::make_unique<OperatorAtractie>(nume, varsta, experientaAni, salariu, atractieDeservita));
            break;
        }
        case 2: {
            string zonaAsignata = getValidString("Introduceti zona asignata: ");
            parc.adaugaAngajat(std::make_unique<AgentPaza>(nume, varsta, experientaAni, salariu, zonaAsignata));
            break;
        }
        case 3: {
            string interval = getValidString("Introduceti intervalul de lucru: ");
            parc.adaugaAngajat(std::make_unique<Casier>(nume, varsta, experientaAni, salariu, interval));
            break;
        }
        default: break;
    }

    cout << "==========================================\n" << endl;
}

void Menu::adaugaVizitatorInteractiv() const {
    cout << "\n🎫 ========== ADAUGARE VIZITATOR ========== 🎫\n" << endl;

    string nume = getValidString("Introduceti numele vizitatorului: ");
    int varsta = getValidInt("Introduceti varsta: ", 3, 100);
    int inaltime = getValidInt("Introduceti inaltimea (cm): ", 80, 220);

    // Creez biletul
    cout << "\nTipuri de bilete disponibile:" << endl;
    cout << "1. Bilet Standard (50 RON)" << endl;
    cout << "2. Bilet Premium (75 RON + optiuni)" << endl;
    cout << "3. Bilet VIP (100 RON + optiuni)" << endl;

    int tipBilet = getValidInt("Alegeti tipul biletului (1-3): ", 1, 3);
    int valabilitateZile = getValidInt("Introduceti valabilitatea (zile): ", 1, 30);

    std::unique_ptr<Bilet> bilet;

    switch (tipBilet) {
        case 1:
            bilet = std::make_unique<BiletStandard>(valabilitateZile);
            break;
        case 2: {
            bool accesBufet = getValidBool("Doriti acces la bufet? (y/n): ");
            bilet = std::make_unique<BiletAdult>(valabilitateZile, accesBufet);
            break;
        }
        case 3: {
            bool accesPiscina = getValidBool("Doriti acces la piscina? (y/n): ");
            bilet = std::make_unique<BiletVIP>(valabilitateZile, accesPiscina);
            break;
        }
        default: break;
    }

    // Determin tipul de vizitator
    if (varsta < 13) {
        bool insotitDeAdult = getValidBool("Este insotit de adult? (y/n): ");
        parc.adaugaVizitator(std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), insotitDeAdult));
    } else if (varsta < 18) {
        bool areBuletin = getValidBool("Are buletin? (y/n): ");
        parc.adaugaVizitator(std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), areBuletin));
    } else {
        string ocupatie = getValidString("Introduceti ocupatia: ");
        parc.adaugaVizitator(std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie));
    }

    cout << "==========================================\n" << endl;
}

void Menu::verificaAccesInteractiv() const {
    cout << "\n🔍 ========== VERIFICARE ACCES ========== 🔍\n" << endl;

    string numeVizitator = getValidString("Introduceti numele vizitatorului: ");
    string numeAtractie = getValidString("Introduceti numele atractiei: ");

    parc.verificaAccesAtractie(numeVizitator, numeAtractie);

    cout << "==========================================\n" << endl;
}

// Metode de validare
int Menu::getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        if (!prompt.empty()) {
            cout << prompt;
        }

        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "❌ Valoare invalida! Introduceti un numar intre " << min << " si " << max << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double Menu::getValidDouble(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << "❌ Valoare invalida! Introduceti un numar intre " << min << " si " << max << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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
        cout << "❌ Valoarea nu poate fi goala! ";
    }
}

bool Menu::getValidBool(const std::string& prompt) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 'y' || choice == 'Y') {
            return true;
        } else if (choice == 'n' || choice == 'N') {
            return false;
        } else {
            cout << "❌ Introduceti 'y' pentru da sau 'n' pentru nu: ";
        }
    }
}
