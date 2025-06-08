#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <map>
#include <random>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <ranges>

class Produs {
protected:
    std::string nume;
    int gramaj;
public:
    Produs(std::string  nume, int gramaj) : nume(std::move(nume)), gramaj(gramaj) {}
    virtual ~Produs() = default;

    virtual void afiseazaDetalii() const = 0;
    [[nodiscard]] [[maybe_unused]] virtual double calculeazaEnergie() const = 0;
};
// Clasa pentru bauturi
class Bautura : public Produs {
    bool laSticla;
public:
    Bautura(const std::string& nume, int gramaj, bool laSticla)
        : Produs(nume, gramaj), laSticla(laSticla) {}

    void afiseazaDetalii() const override {
        std::cout << "Bautura: " << nume << " (" << gramaj << "ml) - "
                  << (laSticla ? "PET" : "Nonpet")
                  << " - Energie necesara: " << std::fixed << std::setprecision(2)
                  << calculeazaEnergie() << " unitati" << std::endl;
    }

    [[nodiscard]] double calculeazaEnergie() const override {
        return laSticla ? 25 : 0.25 * gramaj;
    }
};

// Clasa pentru deserturi
class Desert : public Produs {
    std::string formatServire; // felie, cupa, portie
public:
    Desert(const std::string& nume, int gramaj, std::string  formatServire)
        : Produs(nume, gramaj), formatServire(std::move(formatServire)) {}

    void afiseazaDetalii() const override {
        std::cout << "Desert: " << nume << " (" << gramaj << "g) - "
                  << "servit ca: " << formatServire
                  << " - Energie necesara: " << std::fixed << std::setprecision(2)
                  << calculeazaEnergie() << " unitati" << std::endl;
    }

    [[nodiscard]] double calculeazaEnergie() const override {
        if (formatServire == "felie") return 25;
        else if (formatServire == "portie") return 0.5 * gramaj;
        else if (formatServire == "cup") return 2 * gramaj;
        return 0;
    }
};

// Clasa pentru burgeri
class Burger : public Produs {
    std::vector<std::string> ingrediente;
public:
    Burger(const std::string& nume, int gramaj, const std::vector<std::string>& ingrediente)
        : Produs(nume, gramaj), ingrediente(ingrediente) {}

    void afiseazaDetalii() const override {
        std::cout << "Burger: " << nume << " (" << gramaj << "g) - Ingrediente: ";
        for (const auto& ing : ingrediente) {
            std::cout << ing << " ";
        }
        std::cout << " - Energie necesara: " << std::fixed << std::setprecision(2)
                  << calculeazaEnergie() << " unitati" << std::endl;
    }

    [[nodiscard]] double calculeazaEnergie() const override {
        return gramaj * 0.25 * ingrediente.size();
    }
};

class Comanda {
    static int nextId;
    int id;
    std::vector<std::shared_ptr<Produs>> produse;
    bool preluata = false;
    bool preparata = false;
    bool livrata = false;
    bool prioritara = false;
public:
    Comanda() : id(++nextId) {}

    void adaugaProdus(const std::shared_ptr<Produs>& produs) {
        produse.push_back(produs);
    }

    void afiseazaComanda() const {
        std::cout << "Comanda #" << id << " [" << (prioritara ? "PRIORITARA" : "normal") << "] - Status: ";
        if (livrata) std::cout << "LIVRATA";
        else if (preparata) std::cout << "PREPARATA";
        else if (preluata) std::cout << "PRELUATA";
        else std::cout << "NEPRELUATA";

        std::cout << "\nProduse:\n";
        for (const auto& produs : produse) {
            produs->afiseazaDetalii();
        }
        std::cout << "Energie totala necesara preparare: " << std::fixed << std::setprecision(2)
                  << calculeazaEnergieTotala() << " unitati\n";
    }

    void marcheazaPrioritara() { prioritara = true; }
    [[nodiscard]] bool estePrioritara() const { return prioritara; }
    void marcheazaPreluata() { preluata = true; }
    void marcheazaPreparata() { preparata = true; }
    void marcheazaLivrata() { livrata = true; }

    [[nodiscard]] bool estePreluata() const { return preluata; }
    [[nodiscard]] bool estePreparata() const { return preparata; }
    [[nodiscard]] bool esteLivrata() const { return livrata; }
    [[nodiscard]] bool esteTerminata() const { return livrata; }

    [[nodiscard]] int getId() const { return id; }

    [[nodiscard]] double calculeazaEnergieTotala() const {
        double total = 0;
        for (const auto& produs : produse) {
            total += produs->calculeazaEnergie();
        }
        return total;
    }
};

int Comanda::nextId = 0;


enum class TipAngajat { CASIER, BUCATAR, LIVRATOR };

class Angajat {
protected:
    std::string nume;
    int energie = 100;
    Comanda* comandaAsignata = nullptr;
    TipAngajat tip;

public:
    Angajat(std::string  nume, TipAngajat tip) : nume(std::move(nume)), tip(tip) {}
    virtual ~Angajat() = default;

    [[nodiscard]] TipAngajat getTip() const { return tip; }
    [[nodiscard]] std::string getNumeTip() const {
        switch(tip) {
            case TipAngajat::CASIER: return "Casier";
            case TipAngajat::BUCATAR: return "Bucatar";
            case TipAngajat::LIVRATOR: return "Livrator";
            default: return "Necunoscut";
        }
    }

    [[nodiscard]] virtual bool poatePreluaComanda() const {
        return energie >= 100 && comandaAsignata == nullptr;
    }

    virtual bool preiaComanda(Comanda& comanda) {
        if (!poatePreluaComanda()) return false;

        comandaAsignata = &comanda;
        energie -= 100;
        comanda.marcheazaPreluata();
        std::cout << nume << " (" << getNumeTip() << ") a preluat comanda #" << comanda.getId() << "\n";
        return true;
    }

    [[nodiscard]] virtual bool poatePrepara() const {
        return comandaAsignata != nullptr && !comandaAsignata->estePreparata();
    }

    virtual void preparaComanda() {
        if (!poatePrepara()) return;

        int energieNecesara = comandaAsignata->calculeazaEnergieTotala();
        if (energie >= energieNecesara) {
            energie -= energieNecesara;
            comandaAsignata->marcheazaPreparata();
            std::cout << nume << " (" << getNumeTip() << ") a preparat comanda #" << comandaAsignata->getId() << "\n";
        }
    }

    [[nodiscard]] virtual bool poateLivra() const {
        return comandaAsignata != nullptr &&
               comandaAsignata->estePreparata() &&
               !comandaAsignata->esteLivrata() &&
               energie >= 100;
    }

    virtual bool livreazaComanda() {
        if (!poateLivra()) return false;

        energie -= 100;
        comandaAsignata->marcheazaLivrata();
        std::cout << nume << " (" << getNumeTip() << ") a livrat comanda #" << comandaAsignata->getId() << "\n";
        comandaAsignata = nullptr;
        return true;
    }

    virtual void reseteazaEnergie() {
        energie = 100;
        if (comandaAsignata != nullptr && !comandaAsignata->esteTerminata()) {
            comandaAsignata = nullptr;
        }
    }

    [[nodiscard]] bool esteLiber() const {
        return comandaAsignata == nullptr;
    }

    void afiseazaStatus() const {
        std::cout << "Angajat " << nume << " (" << getNumeTip() << ") - Energie: " << energie;
        if (comandaAsignata != nullptr) {
            std::cout << " - Lucreaza la comanda #" << comandaAsignata->getId();
        }
        std::cout << "\n";
    }
};

class Casier : public Angajat {
public:
    explicit Casier(const std::string& nume) : Angajat(nume, TipAngajat::CASIER) {}

    [[nodiscard]] bool poatePreluaComanda() const override {
        return energie >= 25 && comandaAsignata == nullptr;
    }

    bool preiaComanda(Comanda& comanda) override {
        if (!poatePreluaComanda()) return false;

        comandaAsignata = &comanda;
        energie -= 25;
        comanda.marcheazaPreluata();
        std::cout << nume << " (Casier) a preluat comanda #" << comanda.getId() << " (cost redus: 25 energie)\n";
        return true;
    }
};

class Bucatar : public Angajat {
public:
    explicit Bucatar(const std::string& nume) : Angajat(nume, TipAngajat::BUCATAR) {}

    void preparaComanda() override {
        if (!poatePrepara()) return;

        int energieNecesara = comandaAsignata->calculeazaEnergieTotala() / 2.0;
        if (energie >= energieNecesara) {
            energie -= energieNecesara;
            comandaAsignata->marcheazaPreparata();
            std::cout << nume << " (Bucatar) a preparat comanda #" << comandaAsignata->getId()
                      << " (eficienta dubla, cost: " << energieNecesara << " energie)\n";
        }
    }

    void reseteazaEnergie() override {
        energie += 100;
        if (energie > 100) {
            std::cout << nume << " (Bucatar) a primit bonus energie: " << energie << "/100\n";
        }
        if (comandaAsignata != nullptr && !comandaAsignata->esteTerminata()) {
            comandaAsignata = nullptr;
        }
    }
};

class Livrator : public Angajat {
public:
    explicit Livrator(const std::string& nume) : Angajat(nume, TipAngajat::LIVRATOR) {}

    [[nodiscard]] bool poateLivra() const override {
        return comandaAsignata != nullptr &&
               comandaAsignata->estePreparata() &&
               !comandaAsignata->esteLivrata() &&
               energie >= 25;
    }

    bool livreazaComanda() override {
        if (!poateLivra()) return false;

        energie -= 25;
        comandaAsignata->marcheazaLivrata();
        std::cout << nume << " (Livrator) a livrat comanda #" << comandaAsignata->getId()
                  << " (cost redus: 25 energie)\n";
        comandaAsignata = nullptr;
        return true;
    }
};

class Meniu {
    std::map<std::string, std::shared_ptr<Produs>> produse;
public:
    Meniu() {
        // Adaugam cateva produse predefinite in meniu
        produse["cola"] = std::make_shared<Bautura>("Cola", 330, true);
        produse["apa"] = std::make_shared<Bautura>("Apa minerala", 500, true);
        produse["suc"] = std::make_shared<Bautura>("Suc de portocale", 250, false);

        produse["tiramisu"] = std::make_shared<Desert>("Tiramisu", 150, "portie");
        produse["cheesecake"] = std::make_shared<Desert>("Cheesecake", 120, "felie");
        produse["inghetata"] = std::make_shared<Desert>("Inghetata", 100, "cup");

        produse["hamburger"] = std::make_shared<Burger>("Hamburger", 200,
            std::vector<std::string>{"carne", "salata", "rosii", "ceapa"});
        produse["cheeseburger"] = std::make_shared<Burger>("Cheeseburger", 220,
            std::vector<std::string>{"carne", "branza", "salata", "rosii"});
    }

    void afiseazaMeniu() const {
        std::cout << "==== MENIU ====" << std::endl;
        for (const auto &val: produse | std::views::values) {
            val->afiseazaDetalii();
        }
        std::cout << "===============" << std::endl;
    }

    [[nodiscard]] std::shared_ptr<Produs> getProdus(const std::string& nume) const {
        auto it = produse.find(nume);
        if (it != produse.end()) {
            return it->second;
        }
        return nullptr;
    }
};

enum class StrategiePreparare { PRIORITATE_PRIMUL, CELE_MAI_USOARE, CELE_MAI_GRELE };

class Simulator {
private:
    Meniu meniu;
    std::vector<std::unique_ptr<Angajat>> angajati;
    std::vector<Comanda> comenzi;
    StrategiePreparare strategie = StrategiePreparare::PRIORITATE_PRIMUL;

public:
    void adaugaComenziAutomat() {
        std::srand(std::time(nullptr));
        int numarComenzi = 2 + (std::rand() % 4); // 2-5 comenzi

        for (int i = 0; i < numarComenzi; ++i) {
            Comanda comanda;
            int numarProduse = 1 + (std::rand() % 3); // 1-3 produse

            std::vector<std::string> produseDisponibile = {
                "cola", "apa", "suc", "tiramisu", "cheesecake", "inghetata", "hamburger", "cheeseburger"
            };

            for (int j = 0; j < numarProduse; ++j) {
                int indexProdus = std::rand() % produseDisponibile.size();
                if (auto produs = meniu.getProdus(produseDisponibile[indexProdus])) {
                    comanda.adaugaProdus(produs);
                }
            }

            comenzi.push_back(comanda);
            std::cout << "A fost adaugata comanda #" << comanda.getId() << " cu "
                      << numarProduse << " produse\n";
        }
    }

    void afiseazaStatisticiAngajati() const {
        std::map<TipAngajat, int> count;
        for (const auto& angajat : angajati) {
            count[angajat->getTip()]++;
        }

        std::cout << "\n=== STATISTICI ANGAJATI ===\n";
        std::cout << "Casieri: " << count[TipAngajat::CASIER] << "\n";
        std::cout << "Bucatari: " << count[TipAngajat::BUCATAR] << "\n";
        std::cout << "Livratori: " << count[TipAngajat::LIVRATOR] << "\n";
    }

    void seteazaPrioritati() {
        std::cout << "\nSelectati comenzile prioritare (introduceti ID-uri separate prin spatiu, 0 pentru a termina):\n";
        for (const auto& comanda : comenzi) {
            if (!comanda.esteTerminata()) {
                comanda.afiseazaComanda();
            }
        }

        std::cout << "Introduceti ID-uri: ";

        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        int id;
        while (iss >> id) {
            if (id == 0) break;
            auto it = std::ranges::find_if(comenzi,
                                           [id](const Comanda& c) { return c.getId() == id; });
            if (it != comenzi.end()) {
                it->marcheazaPrioritara();
                std::cout << "Comanda #" << id << " marcata ca prioritara\n";
            }
        }
    }

    void selecteazaStrategie() {
        std::cout << "\nSelectati strategia de preparare:\n";
        std::cout << "1. Prioritare comenzile prioritare\n";
        std::cout << "2. Prioritare cele mai usoare comenzi\n";
        std::cout << "3. Prioritare cele mai grele comenzi\n";
        std::cout << "Alegere: ";

        int optiune;
        std::cin >> optiune;

        switch(optiune) {
            case 1: strategie = StrategiePreparare::PRIORITATE_PRIMUL; break;
            case 2: strategie = StrategiePreparare::CELE_MAI_USOARE; break;
            case 3: strategie = StrategiePreparare::CELE_MAI_GRELE; break;
            default: std::cout << "Optiune invalida, pastram strategia curenta\n";
        }
    }

    void preluareComenzi() {
        std::cout << "\n=== ETAPA DE PRELUARE COMENZI ===\n";

        // Sortam comenzi dupa prioritatea casierilor
        std::vector<Comanda*> comenziNepreluate;
        for (auto& comanda : comenzi) {
            if (!comanda.estePreluata()) {
                comenziNepreluate.push_back(&comanda);
            }
        }

        // Sortam dupa prioritate
        std::ranges::sort(comenziNepreluate,
                          [](const Comanda* a, const Comanda* b) {
                              if (a->estePrioritara() != b->estePrioritara()) {
                                  return a->estePrioritara();
                              }
                              return a->getId() < b->getId();
                          });

        // Prima incercare sa asignam casierii
        for (auto& comanda : comenziNepreluate) {
            for (auto& angajat : angajati) {
                if (angajat->getTip() == TipAngajat::CASIER && angajat->poatePreluaComanda()) {
                    angajat->preiaComanda(*comanda);
                    break;
                }
            }
        }

        // Asignam altii daca e nevoie
        for (auto& comanda : comenziNepreluate) {
            if (!comanda->estePreluata()) {
                for (auto& angajat : angajati) {
                    if (angajat->poatePreluaComanda()) {
                        angajat->preiaComanda(*comanda);
                        break;
                    }
                }
            }
        }
    }

    void preparareComenzi() {
        std::cout << "\n=== ETAPA DE PREPARARE COMENZI ===\n";

        // Sortam bucatarii dupa eficienta
        std::vector<Angajat*> bucatari;
        for (auto& angajat : angajati) {
            if (angajat->getTip() == TipAngajat::BUCATAR && angajat->poatePrepara()) {
                bucatari.push_back(angajat.get());
            }
        }

        std::vector<Comanda*> comenziDePreparat;
        for (auto& comanda : comenzi) {
            if (comanda.estePreluata() && !comanda.estePreparata()) {
                comenziDePreparat.push_back(&comanda);
            }
        }

        switch(strategie) {
            case StrategiePreparare::PRIORITATE_PRIMUL:
                std::ranges::sort(comenziDePreparat,
                                  [](const Comanda* a, const Comanda* b) {
                                      if (a->estePrioritara() != b->estePrioritara()) {
                                          return a->estePrioritara();
                                      }
                                      return a->calculeazaEnergieTotala() < b->calculeazaEnergieTotala();
                                  });
                break;
            case StrategiePreparare::CELE_MAI_USOARE:
                std::ranges::sort(comenziDePreparat,
                                  [](const Comanda* a, const Comanda* b) {
                                      return a->calculeazaEnergieTotala() < b->calculeazaEnergieTotala();
                                  });
                break;
            case StrategiePreparare::CELE_MAI_GRELE:
                std::ranges::sort(comenziDePreparat,
                                  [](const Comanda* a, const Comanda* b) {
                                      return a->calculeazaEnergieTotala() > b->calculeazaEnergieTotala();
                                  });
                break;
        }

        // Bucatarii
        for ([[maybe_unused]] const auto* comanda : comenziDePreparat) {
            for (auto& bucatar : bucatari) {
                if (bucatar->poatePrepara() && bucatar->esteLiber()) {
                    bucatar->preparaComanda();
                    break;
                }
            }
        }

        // Alti pot prepara daca nu este optim
        for (const auto* comanda : comenziDePreparat) {
            if (!comanda->estePreparata()) {
                for (auto& angajat : angajati) {
                    if (angajat->poatePrepara()) {
                        angajat->preparaComanda();
                        break;
                    }
                }
            }
        }
    }

    void livrareComenzi() const {
        std::cout << "\n=== ETAPA DE LIVRARE COMENZI ===\n";

        for (const auto& comanda : comenzi) {
            if (comanda.estePreparata() && !comanda.esteLivrata()) {
                for (auto& angajat : angajati) {
                    if (angajat->getTip() == TipAngajat::LIVRATOR && angajat->poateLivra()) {
                        if (angajat->livreazaComanda()) {
                            break;
                        }
                    }
                }
            }
        }

        // Asignam ati daca e nevoie
        for (const auto& comanda : comenzi) {
            if (comanda.estePreparata() && !comanda.esteLivrata()) {
                for (auto& angajat : angajati) {
                    if (angajat->poateLivra()) {
                        angajat->livreazaComanda();
                        break;
                    }
                }
            }
        }
    }

    void reseteazaEnergieAngajati() const {
        for (auto& angajat : angajati) {
            angajat->reseteazaEnergie();
        }
    }

    [[nodiscard]] bool toateComenziFinalizate() const {
        return std::ranges::all_of(comenzi, [](const Comanda& c) {
            return c.esteTerminata();
        });
    }

    Simulator() {
        // Initializare angajati
        angajati.push_back(std::make_unique<Casier>("Ion"));
        angajati.push_back(std::make_unique<Bucatar>("Maria"));
        angajati.push_back(std::make_unique<Livrator>("Alex"));
        angajati.push_back(std::make_unique<Casier>("Ana"));
        angajati.push_back(std::make_unique<Bucatar>("George"));


        meniu.afiseazaMeniu();
    }

    void ruleazaCiclu() {
        std::cout << "\n=== INCEPUT CICLU NOU ===\n";

        adaugaComenziAutomat();

        // Optiuni inter cicluri
        if (!comenzi.empty()) {
            seteazaPrioritati();
            selecteazaStrategie();
        }

        //Afiseaza statistici
        afiseazaStatisticiAngajati();

        // Stagi proces
        preluareComenzi();
        preparareComenzi();
        livrareComenzi();

        // Reseteaza energia
        reseteazaEnergieAngajati();

        //Afiseaza statusul final
        afiseazaStatusCiclu();

        //Sterge comenzi completate
        std::erase_if(comenzi,
                      [](const Comanda& c) { return c.esteTerminata(); });
    }

    void afiseazaStatusCiclu() const {
        std::cout << "\n=== STATUS FINAL CICLU ===\n";
        std::cout << "Comenzi:\n";
        for (const auto& comanda : comenzi) {
            comanda.afiseazaComanda();
        }

        std::cout << "\nAngajati:\n";
        for (const auto& angajat : angajati) {
            angajat->afiseazaStatus();
        }
    }

    void ruleazaSimulare(int numarCicluri) {
        for (int i = 0; i < numarCicluri; ++i) {
            ruleazaCiclu();

            if (toateComenziFinalizate() && i < numarCicluri - 1) {
                std::cout << "\nToate comenzile au fost finalizate. Continuam simularea...\n";
            }
        }
    }
};

int main() {
    Simulator simulator;
    simulator.ruleazaSimulare(3);
    return 0;
}
