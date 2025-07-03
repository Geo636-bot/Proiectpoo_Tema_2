

#include <iostream>
#include "../Fisiere.h/ParcDistractii.h"
#include "../Fisiere.h/Meniu.h"
#include "../Fisiere.h/Exceptions.h"


int main() {
    try {
        ParcDistractii parc("Wonderland Adventure Park");

        std::cout << "🎪 Bun venit la " << parc.getNume() << "! 🎪\n" << std::endl;
        std::cout << "Toate datele vor fi introduse interactiv de la tastatura.\n" << std::endl;

        const Meniu menu(parc);
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
