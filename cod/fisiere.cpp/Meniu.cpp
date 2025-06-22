#include <iostream>
#include <limits>

Menu::Menu(ParcDistractii& parc) : parc(parc) {}
using namespace std;

Menu::Menu(ParcDistractii& parc) : parc(parc) {
    // Creez observeri și îi adaug la parc
    logObserver = std::make_shared<LogObserver>();
    statsObserver = std::make_shared<StatisticsObserver>();
    
    parc.adaugaObserver(logObserver);
    parc.adaugaObserver(statsObserver);
}

void Menu::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Menu::getValidInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        std::cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << std::endl;
        cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << endl;
        clearInput();
    }
}

double Menu::getValidDouble(const std::string& prompt, double min, double max) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            clearInput();
            return value;
        }
        std::cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << std::endl;
        cout << "❌ Valoare invalida! Introdu un numar intre " << min << " si " << max << endl;
        clearInput();
    }
}

std::string Menu::getValidString(const std::string& prompt) {
    std::string value;
    string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "❌ Textul nu poate fi gol!" << std::endl;
        cout << "❌ Textul nu poate fi gol!" << endl;
    }
}

bool Menu::getYesNo(const std::string& prompt) {
    char response;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::cin >> response;
        cout << prompt << " (y/n): ";
        cin >> response;
        clearInput();
        if (response == 'y' || response == 'Y') return true;
        if (response == 'n' || response == 'N') return false;
        std::cout << "❌ Raspunde cu 'y' sau 'n'!" << std::endl;
        cout << "❌ Raspunde cu 'y' sau 'n'!" << endl;
    }
}

void Menu::afiseazaMeniu() {
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
        optiune = getValidInt("", 0, 9);
        optiune = getValidInt("", 0, 11);

        try {
            switch (optiune) {
                case 1:
                    parc.afiseazaAtractii();
                    adaugaAtractieInteractiv();
                    break;
                case 2:
                    parc.afiseazaAngajati();
                    adaugaAtractieFactory();
                    break;
                case 3:
                    parc.afiseazaVizitatori();
                    adaugaAngajatInteractiv();
                    break;
                case 4:
                    parc.afiseazaStatistici();
                    adaugaVizitatorInteractiv();
                    break;
                case 5:
                    adaugaAtractieInteractiv();
                    parc.afiseazaAtractii();
                    break;
                case 6:
                    adaugaAngajatInteractiv();
                    parc.afiseazaAngajati();
                    break;
                case 7:
                    adaugaVizitatorInteractiv();
                    parc.afiseazaVizitatori();
                    break;
                case 8:
                    verificaAccesInteractiv();
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
                    std::cout << "\n🎡 Multumim ca ai vizitat " << parc.getNume() << "! La revedere! 🎡\n" << std::endl;
                    cout << "\n🎪 Multumim ca ati vizitat parcul! La revedere! 🎪\n" << endl;
                    cout << "📊 Statistici finale observeri: " << statsObserver->getNumarEvenimente() 
                         << " evenimente procesate" << endl;
                    break;
                default:
                    cout << "❌ Optiune invalida!" << endl;
            }
        } catch (const ParcException& e) {
            std::cout << "❌ Eroare: " << e.what() << std::endl;
            cout << "❌ Eroare: " << e.what() << endl;
        } catch (const exception& e) {
            cout << "❌ Eroare neasteptata: " << e.what() << endl;
        }

        if (optiune != 0) {
            std::cout << "\nApasa Enter pentru a continua...";
            std::cin.get();
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
    std::cout << "\n➕ ========== ADAUGARE ATRACTIE NOUA ========== ➕\n" << std::endl;
    cout << "\n➕ ========== ADAUGARE ATRACTIE NOUA ========== ➕\n" << endl;
    try {
        auto atractie = creeazaAtractie();
        parc.adaugaAtractie(std::move(atractie));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea atractiei: " << e.what() << std::endl;
        cout << "❌ Eroare la adaugarea atractiei: " << e.what() << endl;
    }
}

void Menu::adaugaAngajatInteractiv() {
    std::cout << "\n➕ ========== ADAUGARE ANGAJAT NOU ========== ➕\n" << std::endl;
    cout << "\n➕ ========== ADAUGARE ANGAJAT NOU ========== ➕\n" << endl;
    try {
        auto angajat = creeazaAngajat();
        parc.adaugaAngajat(std::move(angajat));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea angajatului: " << e.what() << std::endl;
        cout << "❌ Eroare la adaugarea angajatului: " << e.what() << endl;
    }
}

void Menu::adaugaVizitatorInteractiv() {
    std::cout << "\n➕ ========== ADAUGARE VIZITATOR NOU ========== ➕\n" << std::endl;
    cout << "\n➕ ========== ADAUGARE VIZITATOR NOU ========== ➕\n" << endl;
    try {
        auto vizitator = creeazaVizitator();
        parc.adaugaVizitator(std::move(vizitator));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea vizitatorului: " << e.what() << std::endl;
        cout << "❌ Eroare la adaugarea vizitatorului: " << e.what() << endl;
    }
}

void Menu::verificaAccesInteractiv() {
    std::cout << "\n🔍 ========== VERIFICARE ACCES ATRACTIE ========== 🔍\n" << std::endl;
    cout << "\n🔍 ========== VERIFICARE ACCES ATRACTIE ========== 🔍\n" << endl;

    std::string numeVizitator = getValidString("Nume vizitator: ");
    std::string numeAtractie = getValidString("Nume atractie: ");
    string numeVizitator = getValidString("Nume vizitator: ");
    string numeAtractie = getValidString("Nume atractie: ");

    parc.verificaAccesAtractie(numeVizitator, numeAtractie);
}

std::unique_ptr<Atractie> Menu::creeazaAtractie() {
    std::cout << "\nTip atractie:" << std::endl;
    std::cout << "1. Montagne Russe" << std::endl;
    std::cout << "2. Carusel" << std::endl;
    std::cout << "3. Casa Groazei" << std::endl;
    cout << "\nTip atractie:" << endl;
    cout << "1. Montagne Russe" << endl;
    cout << "2. Carusel" << endl;
    cout << "3. Casa Groazei" << endl;

    int tip = getValidInt("Alege tipul: ", 1, 3);

    std::string nume = getValidString("Nume atractie: ");
    string nume = getValidString("Nume atractie: ");
    int inaltime = getValidInt("Inaltime minima (cm): ", 50, 200);
    int capacitate = getValidInt("Capacitate (persoane): ", 1, 100);

@@ -201,14 +268,14 @@ std::unique_ptr<Atractie> Menu::creeazaAtractie() {
}

std::unique_ptr<Angajat> Menu::creeazaAngajat() {
    std::cout << "\nTip angajat:" << std::endl;
    std::cout << "1. Operator Atractie" << std::endl;
    std::cout << "2. Agent Paza" << std::endl;
    std::cout << "3. Casier" << std::endl;
    cout << "\nTip angajat:" << endl;
    cout << "1. Operator Atractie" << endl;
    cout << "2. Agent Paza" << endl;
    cout << "3. Casier" << endl;

    int tip = getValidInt("Alege tipul: ", 1, 3);

    std::string nume = getValidString("Nume angajat: ");
    string nume = getValidString("Nume angajat: ");
    int varsta = getValidInt("Varsta: ", 18, 70);
    int experienta = getValidInt("Experienta (ani): ", 0, 50);
    double salariu = getValidDouble("Salariu: ", 1000.0, 50000.0);
@@ -219,15 +286,15 @@ std::unique_ptr<Angajat> Menu::creeazaAngajat() {

    switch (tip) {
        case 1: {
            std::string atractie = getValidString("Atractie deservita: ");
            string atractie = getValidString("Atractie deservita: ");
            return std::make_unique<OperatorAtractie>(nume, varsta, experienta, salariu, atractie);
        }
        case 2: {
            std::string zona = getValidString("Zona asignata: ");
            string zona = getValidString("Zona asignata: ");
            return std::make_unique<AgentPaza>(nume, varsta, experienta, salariu, zona);
        }
        case 3: {
            std::string interval = getValidString("Interval (ex: 08:00-16:00): ");
            string interval = getValidString("Interval (ex: 08:00-16:00): ");
            return std::make_unique<Casier>(nume, varsta, experienta, salariu, interval);
        }
        default:
@@ -236,14 +303,14 @@ std::unique_ptr<Angajat> Menu::creeazaAngajat() {
}

std::unique_ptr<Vizitator> Menu::creeazaVizitator() {
    std::cout << "\nTip vizitator:" << std::endl;
    std::cout << "1. Copil" << std::endl;
    std::cout << "2. Adolescent" << std::endl;
    std::cout << "3. Adult" << std::endl;
    cout << "\nTip vizitator:" << endl;
    cout << "1. Copil" << endl;
    cout << "2. Adolescent" << endl;
    cout << "3. Adult" << endl;

    int tip = getValidInt("Alege tipul: ", 1, 3);

    std::string nume = getValidString("Nume vizitator: ");
    string nume = getValidString("Nume vizitator: ");
    int varsta = getValidInt("Varsta: ", 1, 120);
    int inaltime = getValidInt("Inaltime (cm): ", 50, 250);

@@ -268,7 +335,7 @@ std::unique_ptr<Vizitator> Menu::creeazaVizitator() {
            if (varsta < 18) {
                throw VarstaNecorespunzatoare("Adultul trebuie sa aiba minim 18 ani");
            }
            std::string ocupatie = getValidString("Ocupatie: ");
            string ocupatie = getValidString("Ocupatie: ");
            return std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie);
        }
        default:
@@ -277,10 +344,10 @@ std::unique_ptr<Vizitator> Menu::creeazaVizitator() {
}

std::unique_ptr<Bilet> Menu::creeazaBilet() {
    std::cout << "\nTip bilet:" << std::endl;
    std::cout << "1. Bilet Copil" << std::endl;
    std::cout << "2. Bilet Adult" << std::endl;
    std::cout << "3. Bilet VIP" << std::endl;
    cout << "\nTip bilet:" << endl;
    cout << "1. Bilet Copil" << endl;
    cout << "2. Bilet Adult" << endl;
    cout << "3. Bilet VIP" << endl;

    int tip = getValidInt("Alege tipul: ", 1, 3);
