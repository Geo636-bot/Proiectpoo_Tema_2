


#include "../Fisiere.h/Bilet.h"
#include <iostream>

using namespace std;

// Instanțieri explicite pentru tipurile folosite
template class Bilet<double>;
template class BiletStandard<double>;
template class BiletPremium<double>;
template class BiletVIP<double>;
template class BiletFactory<double>;

// Instanțieri pentru funcția template liberă
template bool compararePret<BiletStandard<double>, BiletPremium<double>>(const BiletStandard<double>&, const BiletPremium<double>&);
template bool compararePret<BiletPremium<double>, BiletVIP<double>>(const BiletPremium<double>&, const BiletVIP<double>&);

// Pentru compatibilitate cu restul codului, creez typedef-uri
using BiletStandardDouble = BiletStandard<double>;
using BiletPremiumDouble = BiletPremium<double>;
using BiletVIPDouble = BiletVIP<double>;

// Observer simplu pentru demonstrație
class ParcBiletObserver : public BiletObserver {
public:
    void notificareSchimbarePret(double pretNou) override {
        std::cout << "📢 Observator: Pretul biletului s-a schimbat la " << pretNou << " RON" << std::endl;
    }

    void notificareExpirare(const std::string& tipBilet) override {
        std::cout << "⏰ Observator: " << tipBilet << " a expirat!" << std::endl;
    }
};

// Funcție pentru demonstrarea template-urilor și design patterns
void demonstreazaTemplatesSiPatterns() {
    std::cout << "\n🔧 ========== DEMONSTRATIE TEMPLATES SI DESIGN PATTERNS ========== 🔧\n" << std::endl;

    // Creez bilete cu Factory Pattern
    auto biletStandard = BiletFactory<double>::creeazaBilet("standard", 3, false);
    auto biletPremium = BiletFactory<double>::creeazaBilet("premium", 5, true);
    auto biletVIP = BiletFactory<double>::creeazaBilet("vip", 7, true);

    std::cout << "🏭 Factory Pattern - Bilete create:" << std::endl;
    if (biletStandard) std::cout << "  " << *biletStandard << std::endl;
    if (biletPremium) std::cout << "  " << *biletPremium << std::endl;
    if (biletVIP) std::cout << "  " << *biletVIP << std::endl;

    // Observer Pattern
    std::cout << "\n👁️ Observer Pattern - Adaug observator:" << std::endl;
    ParcBiletObserver observer;
    if (biletPremium) {
        biletPremium->adaugaObserver(&observer);
        biletPremium->actualizeazaPretBaza(80.0);
    }

    // Strategy Pattern
    std::cout << "\n📊 Strategy Pattern - Schimb strategia de calcul:" << std::endl;
    if (biletStandard) {
        auto strategieWeekend = std::make_unique<CalculPretWeekend<double>>();
        biletStandard->setStrategieCalcul(std::move(strategieWeekend));
        std::cout << "  Pret cu strategie weekend: " << biletStandard->calculeazaPretFinal() << " RON" << std::endl;
    }

    // Template function - comparare preturi
    std::cout << "\n🔢 Functie Template - Comparare preturi:" << std::endl;
    if (biletStandard && biletPremium) {
        bool standardMaiIeftin = compararePret(*biletStandard, *biletPremium);
        std::cout << "  Biletul standard este mai ieftin: " << (standardMaiIeftin ? "DA" : "NU") << std::endl;
    }

    // Template member function
    std::cout << "\n💱 Functie Template Membru - Conversie pret:" << std::endl;
    if (biletVIP) {
        auto pretEUR = biletVIP-> convertestePreț<double>(20.0, 0.2); // 20 EUR la 0.2 rata
        std::cout << "  Pret convertit din EUR: " << pretEUR << " RON" << std::endl;
    }

    std::cout << "================================================================\n" << std::endl;
}
