
#include "../Fisiere.h/Menu.h"
#include "../Fisiere.h/Bilet.h"
#include <iostream>
#include <limits>
#include <string>
#include <regex>

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
    cout << "12. 💰 Afiseaza profit saptamanal" << endl;
    cout << "0. 🚪 Iesire" << endl;
    cout << "=============================================" << endl;
    cout << "Alegerea ta: ";
}

void Menu::ruleazaMeniu() const {
    int optiune;

    do {
        afiseazaMeniu();
        optiune = getValidInt("", 0, 12);

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
                case 12:
                    afiseazaProfitSaptamanal();
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

void Menu::afiseazaProfitSaptamanal() const {
    cout << "\n💰 ========== PROFIT SAPTAMANAL ========== 💰\n" << endl;

    double venitTotal = parc.calculezaVenitTotal();
    double costuriSalariale = parc.calculezaCosturiSalariale();
    double profitSaptamanal = venitTotal - costuriSalariale;

    cout << "📈 Venituri totale (bilete): " << venitTotal << " RON" << endl;
    cout << "💸 Costuri salariale (saptamanal): " << costuriSalariale << " RON" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;

    if (profitSaptamanal > 0) {
        cout << "💚 PROFIT SAPTAMANAL: +" << profitSaptamanal << " RON" << endl;
        cout << "✅ Parcul genereaza profit!" << endl;
    } else if (profitSaptamanal == 0) {
        cout << "⚖️ ECHILIBRU: " << profitSaptamanal << " RON" << endl;
        cout << "🔄 Parcul acopera exact costurile!" << endl;
    } else {
        cout << "💔 PIERDERE SAPTAMANALA: " << profitSaptamanal << " RON" << endl;
        cout << "⚠️ Parcul pierde bani!" << endl;
    }

    cout << "\n📊 Analiza profitabilitatii:" << endl;
    if (costuriSalariale > 0) {
        double marjaProfit = (profitSaptamanal / venitTotal) * 100;
        cout << "📈 Marja de profit: " << marjaProfit << "%" << endl;
    }

    cout << "==========================================\n" << endl;
}

void Menu::simuleazaTrecereaZilei() const {
    cout << "\n📅 ========== SIMULARE TRECERE ZI ========== 📅\n" << endl;

    ZiSaptamana ziVeche = Bilet::getZiCurenta();
    cout << "Ziua curenta: " << Bilet::getNumeZi(ziVeche);
    if (Bilet::esteWeekend(ziVeche)) {
        cout << " (Weekend)";
    }
    cout << endl;

    Bilet::trecutZi();

    // Scade valabilitatea biletelor pentru toti vizitatorii
    parc.scadeValabilitateBilete();

    ZiSaptamana ziNoua = Bilet::getZiCurenta();
    cout << "Ziua noua: " << Bilet::getNumeZi(ziNoua);
    if (Bilet::esteWeekend(ziNoua)) {
        cout << " (Weekend - preturile vor fi majorate cu 25%)";
    }
    cout << endl;

    cout << "\n✅ A trecut o zi! Preturile biletelor si valabilitatea s-au actualizat automat." << endl;
    cout << "==========================================\n" << endl;
}

void Menu::adaugaAtractieInteractiv() const {
    cout << "\n🎢 ========== ADAUGARE ATRACTIE ========== 🎢\n" << endl;

    string nume = getValidString("Introduceti numele atractiei: ");
    int inaltimeMinima = getValidInt("Introduceti inaltimea minima (cm): ", 80, 200);
    int varstaNecesara = getValidInt("Introduceti varsta minima necesara: ", 0, 18);

    cout << "\nTipuri de atractii disponibile:" << endl;
    cout << "1. Montagne Russe" << endl;
    cout << "2. Carusel" << endl;
    cout << "3. Casa Groazei" << endl;

    switch (getValidInt("Alegeti tipul atractiei (1-3): ", 1, 3)) {
        case 1: {
            int vitezaMaxima = getValidInt("Introduceti viteza maxima (km/h): ", 30, 200);
            parc.adaugaAtractie(std::make_unique<MontagneRusse>(nume, inaltimeMinima, varstaNecesara, vitezaMaxima));
            break;
        }
        case 2: {
            int numarCai = getValidInt("Introduceti numarul de cai: ", 4, 20);
            parc.adaugaAtractie(std::make_unique<Carusel>(nume, inaltimeMinima, varstaNecesara, numarCai));
            break;
        }
        case 3: {
            int nivelFrica = getValidInt("Introduceti nivelul de frica (1-10): ", 1, 10);
            parc.adaugaAtractie(std::make_unique<CasaGroazei>(nume, inaltimeMinima, varstaNecesara, nivelFrica));
            break;
        }
        default: break;
    }

    cout << "==========================================\n" << endl;
}

void Menu::adaugaAngajatInteractiv() const {
    cout << "\n👤 ========== ADAUGARE ANGAJAT ========== 👤\n" << endl;

    string nume = getValidString("Introduceti numele angajatului: ");
    int varsta = getValidInt("Introduceti varsta: ", 18, 70);
    int experientaAni = getValidInt("Introduceti experienta (ani): ", 0, 40);

    cout << "\nTipuri de angajati disponibili:" << endl;
    cout << "1. Operator Atractie (Salariu de baza: 600 RON/saptamana + experienta)" << endl;
    cout << "2. Agent Paza (Salariu de baza: 550 RON/saptamana + experienta)" << endl;
    cout << "3. Casier (Salariu de baza: 500 RON/saptamana + experienta)" << endl;

    int tipAngajat = getValidInt("Alegeti tipul angujatului (1-3): ", 1, 3);

    double salariu;

    switch (tipAngajat) {
        case 1: {
            salariu = calculezaSalariuCuExperienta(600.0, experientaAni);
            cout << "Salariul calculat: " << salariu << " RON/saptamana" << endl;

            // Verific daca exista atractii fara operator
            string atractieDisponibila = gasesteAtractieFaraOperator();
            if (atractieDisponibila.empty()) {
                cout << "❌ Nu exista atractii disponibile fara operator!" << endl;
                return;
            }

            cout << "Atractii disponibile fara operator:" << endl;
            cout << "- " << atractieDisponibila << endl;
            string atractieDeservita = getValidString("Introduceti atractia deservita: ");

            // Verific daca atractia introdusa exista si nu are operator
            if (!verificaAtractieDisponibila(atractieDeservita)) {
                cout << "❌ Atractia nu exista sau are deja operator!" << endl;
                return;
            }

            parc.adaugaAngajat(std::make_unique<OperatorAtractie>(nume, varsta, experientaAni, salariu, atractieDeservita));
            break;
        }
        case 2: {
            salariu = calculezaSalariuCuExperienta(550.0, experientaAni);
            cout << "Salariul calculat: " << salariu << " RON/saptamana" << endl;

            // Verific numarul de paznici existenti
            if (parc.getNumarPaznici() >= 4) {
                cout << "❌ Nu puteti avea mai mult de 4 paznici!" << endl;
                return;
            }

            string zonaAsignata = getValidZona("Introduceti zona asignata (N/S/E/W): ");

            // Verific daca zona este deja ocupata
            if (parc.verificaZonaOcupata(zonaAsignata)) {
                cout << "❌ Zona " << zonaAsignata << " este deja ocupata!" << endl;
                return;
            }

            parc.adaugaAngajat(std::make_unique<AgentPaza>(nume, varsta, experientaAni, salariu, zonaAsignata));
            break;
        }
        case 3: {
            salariu = calculezaSalariuCuExperienta(500.0, experientaAni);
            cout << "Salariul calculat: " << salariu << " RON/saptamana" << endl;

            string interval = getValidInterval("Introduceti intervalul orar (ex: 08:00-16:00): ");
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
    cout << "2. Bilet Adult (75 RON + optiuni)" << endl;
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

        // Permit trecerea copilului doar daca este insotit de adult
        if (!insotitDeAdult) {
            cout << "❌ Copiii sub 13 ani trebuie sa fie insotiti de un adult pentru a intra in parc!" << endl;
            cout << "==========================================\n" << endl;
            return;
        }

        parc.adaugaVizitator(std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), insotitDeAdult));
    } else if (varsta < 18) {
        // Pentru adolescenți, nu mai cerem areBuletin - folosim valoarea default
        parc.adaugaVizitator(std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), true));
    } else {
        // Pentru adulți, nu mai cerem ocupația - folosim o valoare default
        parc.adaugaVizitator(std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), "Necunoscuta"));
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

double Menu::calculezaSalariuCuExperienta(double salariuBaza, int experientaAni) {
    // Adaug 50 RON pentru fiecare an de experienta
    return salariuBaza + (experientaAni * 50.0);
}

string Menu::gasesteAtractieFaraOperator() {
    // Implementez logica pentru a gasi o atractie fara operator
    // Pentru simplitate, returnez prima atractie gasita
    // In implementarea reala, ar trebui sa verific in parc
    return "Montagne Russe 1"; // placeholder - ar trebui implementat corect
}

bool Menu::verificaAtractieDisponibila(const string& numeAtractie) const {
    // Verific daca atractia exista si nu are operator
    return parc.existaAtractie(numeAtractie);
}

int Menu::getNumarPaznici() {
    // Numar paznicii existenti - ar trebui implementat in ParcDistractii
    return 0; // placeholder
}

bool Menu::verificaZonaOcupata(const string& zona) {
    // Verific daca zona este deja ocupata de alt paznic
    return false; // placeholder
}

string Menu::getValidZona(const string& prompt) {
    string zona;
    while (true) {
        cout << prompt;
        getline(cin, zona);

        if (zona == "N" || zona == "S" || zona == "E" || zona == "W" ||
            zona == "n" || zona == "s" || zona == "e" || zona == "w") {
            // Convertesc la majuscule
            if (zona.length() == 1) {
                zona[0] = toupper(zona[0]);
            }
            return zona;
        }
        cout << "❌ Zona invalida! Introduceti N, S, E sau W: ";
    }
}

string Menu::getValidInterval(const string& prompt) {
    string interval;
    regex intervalRegex(R"(\d{2}:\d{2}-\d{2}:\d{2})");

    while (true) {
        cout << prompt;
        getline(cin, interval);

        if (regex_match(interval, intervalRegex)) {
            // Verific daca orele sunt valide (00-23)
            string ora1 = interval.substr(0, 2);
            string ora2 = interval.substr(6, 2);
            string min1 = interval.substr(3, 2);
            string min2 = interval.substr(9, 2);

            int h1 = stoi(ora1), h2 = stoi(ora2);
            int m1 = stoi(min1), m2 = stoi(min2);

            if (h1 >= 0 && h1 <= 23 && h2 >= 0 && h2 <= 23 &&
                m1 >= 0 && m1 <= 59 && m2 >= 0 && m2 <= 59) {
                return interval;
            }
        }
        cout << "❌ Format invalid! Introduceti intervalul in format HH:MM-HH:MM: ";
    }
}

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
