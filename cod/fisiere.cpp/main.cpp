

#include <iostream>
#include "../Fisiere.h/ParcDistractii.h"
#include "../Fisiere.h/Menu.h"

int main() {
    try {
        ParcDistractii parc("Wonderland Adventure Park");

        std::cout << "🎪 Bun venit la " << parc.getNume() << "! 🎪\n" << std::endl;
        std::cout << "Sistem de gestiune a parcului de distractii folosind POO\n" << std::endl;

        // Intreb utilizatorul daca vrea sa incarce date din CSV
        std::cout << "📁 Doriti sa incarcati date de exemplu din fisiere CSV? (y/n): ";
        char raspuns;
        std::cin >> raspuns;
        std::cin.ignore(); // Clear input buffer

        if (raspuns == 'y' || raspuns == 'Y') {
            parc.incarcaToateDatale();
            std::cout << "\n🎉 Date incarcate! Puteti vedea atractiile, angajatii si vizitatorii in meniu." << std::endl;
        }

        Menu menu(parc);
        menu.ruleazaMeniu();

    } catch (const std::exception& e) {
        std::cerr << "❌ Eroare neasteptata: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
