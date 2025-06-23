

#include <iostream>
#include "../Fisiere.h/ParcDistractii.h"
#include "../Fisiere.h/Menu.h"
#include "../Fisiere.h/Exceptions.h"
#include "../Fisiere.h/StatisticsManager.h"

int main() {
    try {
        ParcDistractii parc("Wonderland Adventure Park - Advanced Edition");

        std::cout << "🎪 Bun venit la " << parc.getNume() << "! 🎪\n" << std::endl;
        std::cout << "Versiunea avansata cu Template-uri si Design Patterns!\n" << std::endl;
        std::cout << "✨ Functionalitati noi:" << std::endl;
        std::cout << "  - Clasa template StatisticsManager<T>" << std::endl;
        std::cout << "  - Observer Pattern pentru notificari" << std::endl;
        std::cout << "  - Factory Method Pattern pentru atractii" << std::endl;
        std::cout << "  - Functii template generice" << std::endl;
        std::cout << "\nToate datele vor fi introduse interactiv de la tastatura.\n" << std::endl;

        // Demonstratie rapida a template-urilor
        std::cout << "🔢 Demonstratie rapida template:" << std::endl;
        StatisticsManager<double> demoStats("Demo");
        demoStats.adaugaDate(10.5);
        demoStats.adaugaDate(20.3);
        demoStats.adaugaDate(15.7);
        demoStats.afiseazaStatistici();

        Menu menu(parc);
        menu.ruleazaMeniu();

    } catch (const ParcException& e) {
        std::cerr << "❌ Eroare critica: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "❌ Eroare neasteptata: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
