#include "../Fisiere.h/Meniu.h"
#include "../FIsiere.h/Exceptions.h"
#include <iostream>
#include <limits>

Menu::Menu(ParcDistractii& parc) : parc(parc) {}

void Menu::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Menu::getValidInt(const std::string& prompt, int min, int max) {
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

double Menu::getValidDouble(const std::string& prompt, double min, double max) {
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

std::string Menu::getValidString(const std::string& prompt) {
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

bool Menu::getYesNo(const std::string& prompt) {
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
}

void Menu::ruleazaMeniu() {
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
            }
        } catch (const ParcException& e) {
            std::cout << "❌ Eroare: " << e.what() << std::endl;
        }
        
        if (optiune != 0) {
            std::cout << "\nApasa Enter pentru a continua...";
            std::cin.get();
        }
        
    } while (optiune != 0);
}

void Menu::adaugaAtractieInteractiv() {
    std::cout << "\n➕ ========== ADAUGARE ATRACTIE NOUA ========== ➕\n" << std::endl;
    try {
        auto atractie = creeazaAtractie();
        parc.adaugaAtractie(std::move(atractie));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea atractiei: " << e.what() << std::endl;
    }
}

void Menu::adaugaAngajatInteractiv() {
    std::cout << "\n➕ ========== ADAUGARE ANGAJAT NOU ========== ➕\n" << std::endl;
    try {
        auto angajat = creeazaAngajat();
        parc.adaugaAngajat(std::move(angajat));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea angajatului: " << e.what() << std::endl;
    }
}

void Menu::adaugaVizitatorInteractiv() {
    std::cout << "\n➕ ========== ADAUGARE VIZITATOR NOU ========== ➕\n" << std::endl;
    try {
        auto vizitator = creeazaVizitator();
        parc.adaugaVizitator(std::move(vizitator));
    } catch (const ParcException& e) {
        std::cout << "❌ Eroare la adaugarea vizitatorului: " << e.what() << std::endl;
    }
}

void Menu::verificaAccesInteractiv() {
    std::cout << "\n🔍 ========== VERIFICARE ACCES ATRACTIE ========== 🔍\n" << std::endl;
    
    std::string numeVizitator = getValidString("Nume vizitator: ");
    std::string numeAtractie = getValidString("Nume atractie: ");
    
    parc.verificaAccesAtractie(numeVizitator, numeAtractie);
}

std::unique_ptr<Atractie> Menu::creeazaAtractie() {
    std::cout << "\nTip atractie:" << std::endl;
    std::cout << "1. Montagne Russe" << std::endl;
    std::cout << "2. Carusel" << std::endl;
    std::cout << "3. Casa Groazei" << std::endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    std::string nume = getValidString("Nume atractie: ");
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
            std::string atractie = getValidString("Atractie deservita: ");
            return std::make_unique<OperatorAtractie>(nume, varsta, experienta, salariu, atractie);
        }
        case 2: {
            std::string zona = getValidString("Zona asignata: ");
            return std::make_unique<AgentPaza>(nume, varsta, experienta, salariu, zona);
        }
        case 3: {
            std::string interval = getValidString("Interval (ex: 08:00-16:00): ");
            return std::make_unique<Casier>(nume, varsta, experienta, salariu, interval);
        }
        default:
            throw DateInvalide("Tip angajat invalid");
    }
}

std::unique_ptr<Vizitator> Menu::creeazaVizitator() {
    std::cout << "\nTip vizitator:" << std::endl;
    std::cout << "1. Copil" << std::endl;
    std::cout << "2. Adolescent" << std::endl;
    std::cout << "3. Adult" << std::endl;
    
    int tip = getValidInt("Alege tipul: ", 1, 3);
    
    std::string nume = getValidString("Nume vizitator: ");
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
            std::string ocupatie = getValidString("Ocupatie: ");
            return std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie);
        }
        default:
            throw DateInvalide("Tip vizitator invalid");
    }
}

std::unique_ptr<Bilet> Menu::creeazaBilet() {
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
