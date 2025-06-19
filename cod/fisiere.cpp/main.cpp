
#include <iostream>
#include <memory>
#include <limits>
#include "ParcDistractii.h"
#include "Atractie.h"
#include "Angajat.h"
#include "Bilet.h"
#include "Vizitator.h"

void afiseazaMeniu() {
    std::cout << "\n🎡 ========== SISTEM GESTIUNE PARC DE DISTRACTII ========== 🎡\n";
    std::cout << "1. Afiseaza toate atractiile" << std::endl;
    std::cout << "2. Afiseaza toti angajatii" << std::endl;
    std::cout << "3. Afiseaza toti vizitatorii" << std::endl;
    std::cout << "4. Afiseaza statistici parc" << std::endl;
    std::cout << "5. Verifica accesul la o atractie" << std::endl;
    std::cout << "6. Adauga vizitator nou" << std::endl;
    std::cout << "7. Demonstratie polimorfism" << std::endl;
    std::cout << "0. Iesire" << std::endl;
    std::cout << "===========================================================\n";
    std::cout << "Alege optiunea: ";
}

void initializeazaDatele(ParcDistractii& parc) {
    std::cout << "🎪 Initializare date pentru parcul de distractii...\n" << std::endl;

    // Adauga atractii
    parc.adaugaAtractie(std::make_unique<MontagneRusse>("Thunder Mountain", 140, 24, 80));
    parc.adaugaAtractie(std::make_unique<Carusel>("Caruselul Magic", 100, 16, 12));
    parc.adaugaAtractie(std::make_unique<CasaGroazei>("Casa Vampirilor", 120, 8, 9));
    parc.adaugaAtractie(std::make_unique<MontagneRusse>("Speed Demon", 160, 20, 120));

    // Adauga angajati
    parc.adaugaAngajat(std::make_unique<OperatorAtractie>("Mihai Popescu", 28, 3, 2500, "Thunder Mountain"));
    parc.adaugaAngajat(std::make_unique<AgentPaza>("Ana Ionescu", 35, 8, 2800, "Zona Principala"));
    parc.adaugaAngajat(std::make_unique<Casier>("Elena Dumitrescu", 24, 1, 2200, "08:00-16:00"));
    parc.adaugaAngajat(std::make_unique<OperatorAtractie>("George Marinescu", 32, 5, 2600, "Caruselul Magic"));

    // Adauga vizitatori
    parc.adaugaVizitator(std::make_unique<Copil>("Alex Marin", 8, 125, 
        std::make_unique<BiletCopil>(80, 1, 8), true));
    
    parc.adaugaVizitator(std::make_unique<Adult>("Maria Vasilescu", 29, 165, 
        std::make_unique<BiletAdult>(120, 1, true), "Inginer"));
    
    parc.adaugaVizitator(std::make_unique<Adolescent>("Radu Stefan", 16, 170, 
        std::make_unique<BiletAdult>(120, 1, false), true));
    
    parc.adaugaVizitator(std::make_unique<Adult>("Ion Gheorghe", 45, 180, 
        std::make_unique<BiletVIP>(120, 3, true), "Manager"));

    parc.adaugaVizitator(std::make_unique<Copil>("Sofia Dima", 4, 95, 
        std::make_unique<BiletCopil>(80, 1, 4), false));

    std::cout << "✅ Date initializate cu succes!\n" << std::endl;
}

void demonstratiePolimorfism(const ParcDistractii& parc) {
    std::cout << "\n🔬 ========== DEMONSTRATIE POLIMORFISM ========== 🔬\n" << std::endl;
    
    // Cream un vector de pointeri la clasa de baza
    std::vector<std::unique_ptr<Atractie>> atractiiDemo;
    atractiiDemo.push_back(std::make_unique<MontagneRusse>("Demo Roller", 150, 16, 100));
    atractiiDemo.push_back(std::make_unique<Carusel>("Demo Carusel", 80, 20, 8));
    atractiiDemo.push_back(std::make_unique<CasaGroazei>("Demo Casa", 110, 6, 7));

    std::cout << "Polimorfism cu operatorul << suprascris:\n" << std::endl;
    
    for (const auto& atractie : atractiiDemo) {
        // Demonstratie polimorfism cu operatorul <<
        std::cout << "Tip: " << atractie->getTip() << std::endl;
        std::cout << *atractie;
        std::cout << "-------------------" << std::endl;
    }

    // Demonstratie cu angajati
    std::vector<std::unique_ptr<Angajat>> angajatiDemo;
    angajatiDemo.push_back(std::make_unique<OperatorAtractie>("Demo Operator", 25, 2, 2400, "Demo Atractie"));
    angajatiDemo.push_back(std::make_unique<AgentPaza>("Demo Agent", 30, 4, 2600, "Demo Zona"));
    angajatiDemo.push_back(std::make_unique<Casier>("Demo Casier", 22, 1, 2100, "Demo Program"));

    std::cout << "\nCalcul salarii folosind polimorfism si operatorul <<:\n" << std::endl;
    
    for (const auto& angajat : angajatiDemo) {
        std::cout << angajat->getNume() << " (" << angajat->getTip() << ")" << std::endl;
        std::cout << "Salariu de baza: " << angajat->getSalariu() << " RON" << std::endl;
        std::cout << "Salariu total: " << angajat->calculeazaSalariuTotal() << " RON" << std::endl;
        std::cout << "-------------------" << std::endl;
    }

    std::cout << "===============================================\n" << std::endl;
}

void adaugaVizitatorNou(ParcDistractii& parc) {
    std::cout << "\n➕ ========== ADAUGARE VIZITATOR NOU ========== ➕\n" << std::endl;
    
    std::string nume;
    int varsta, inaltime, tipVizitator, tipBilet;
    
    std::cout << "Nume vizitator: ";
    std::cin.ignore();
    std::getline(std::cin, nume);
    
    std::cout << "Varsta: ";
    std::cin >> varsta;
    
    std::cout << "Inaltime (cm): ";
    std::cin >> inaltime;
    
    std::cout << "\nTip vizitator:" << std::endl;
    std::cout << "1. Copil" << std::endl;
    std::cout << "2. Adolescent" << std::endl;
    std::cout << "3. Adult" << std::endl;
    std::cout << "Alege: ";
    std::cin >> tipVizitator;
    
    std::cout << "\nTip bilet:" << std::endl;
    std::cout << "1. Bilet Copil" << std::endl;
    std::cout << "2. Bilet Adult" << std::endl;
    std::cout << "3. Bilet VIP" << std::endl;
    std::cout << "Alege: ";
    std::cin >> tipBilet;
    
    // Cream biletul
    std::unique_ptr<Bilet> bilet;
    switch (tipBilet) {
        case 1:
            bilet = std::make_unique<BiletCopil>(80, 1, varsta);
            break;
        case 2: {
            char fastPass;
            std::cout << "Include Fast Pass? (y/n): ";
            std::cin >> fastPass;
            bilet = std::make_unique<BiletAdult>(120, 1, fastPass == 'y' || fastPass == 'Y');
            break;
        }
        case 3: {
            char lounge;
            std::cout << "Include acces Lounge? (y/n): ";
            std::cin >> lounge;
            bilet = std::make_unique<BiletVIP>(120, 1, lounge == 'y' || lounge == 'Y');
            break;
        }
        default:
            bilet = std::make_unique<BiletAdult>(120, 1, false);
    }
    
    // Cream vizitatorul
    std::unique_ptr<Vizitator> vizitator;
    switch (tipVizitator) {
        case 1: {
            char insotit;
            std::cout << "Insotit de adult? (y/n): ";
            std::cin >> insotit;
            vizitator = std::make_unique<Copil>(nume, varsta, inaltime, std::move(bilet), 
                insotit == 'y' || insotit == 'Y');
            break;
        }
        case 2: {
            char buletin;
            std::cout << "Are buletin? (y/n): ";
            std::cin >> buletin;
            vizitator = std::make_unique<Adolescent>(nume, varsta, inaltime, std::move(bilet), 
                buletin == 'y' || buletin == 'Y');
            break;
        }
        case 3: {
            std::string ocupatie;
            std::cout << "Ocupatie: ";
            std::cin.ignore();
            std::getline(std::cin, ocupatie);
            vizitator = std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), ocupatie);
            break;
        }
        default:
            vizitator = std::make_unique<Adult>(nume, varsta, inaltime, std::move(bilet), "Nespecificat");
    }
    
    parc.adaugaVizitator(std::move(vizitator));
    std::cout << "\n✅ Vizitator adaugat cu succes!\n" << std::endl;
}

void verificaAcces(const ParcDistractii& parc) {
    std::string numeVizitator, numeAtractie;
    
    std::cout << "\n🔍 ========== VERIFICARE ACCES ATRACTIE ========== 🔍\n" << std::endl;
    std::cout << "Nume vizitator: ";
    std::cin.ignore();
    std::getline(std::cin, numeVizitator);
    
    std::cout << "Nume atractie: ";
    std::getline(std::cin, numeAtractie);
    
    parc.verificaAccesAtractie(numeVizitator, numeAtractie);
}

int main() {
    ParcDistractii parc("Wonderland Adventure Park");
    
    std::cout << "🎪 Bun venit la " << parc.getNume() << "! 🎪\n" << std::endl;
    
    initializeazaDatele(parc);
    
    int optiune;
    do {
        afiseazaMeniu();
        std::cin >> optiune;
        
        // Verificare input valid
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "❌ Optiune invalida! Te rog introdu un numar.\n" << std::endl;
            continue;
        }
        
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
                verificaAcces(parc);
                break;
            case 6:
                adaugaVizitatorNou(parc);
                break;
            case 7:
                demonstratiePolimorfism(parc);
                break;
            case 0:
                std::cout << "\n🎡 Multumim ca ai vizitat " << parc.getNume() << "! La revedere! 🎡\n" << std::endl;
                break;
            default:
                std::cout << "❌ Optiune invalida! Te rog alege o optiune valida (0-7).\n" << std::endl;
        }
        
        if (optiune != 0) {
            std::cout << "\nApasa Enter pentru a continua...";
            std::cin.ignore();
            std::cin.get();
        }
        
    } while (optiune != 0);
    
    return 0;
}
