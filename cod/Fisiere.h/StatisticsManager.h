

#ifndef STATISTICSMANAGER_H
#define STATISTICSMANAGER_H

#include <utility>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

template<typename T>
class StatisticsManager {
private:
    std::vector<T> data;
    std::string tip;

public:
    explicit StatisticsManager(std::string  tip) : tip(std::move(tip)) {}

    void adaugaDate(const T& valoare) {
        data.push_back(valoare);
    }

    void afiseazaStatistici() const {
        if (data.empty()) {
            std::cout << "Nu exista date pentru " << tip << std::endl;
            return;
        }

        std::cout << "\n📊 Statistici pentru " << tip << ":\n";
        std::cout << "Numar total elemente: " << data.size() << std::endl;

        if constexpr (std::is_arithmetic_v<T>) {
            T suma = calculeazaSuma();
            T media = suma / static_cast<T>(data.size());
            T minim = *std::min_element(data.begin(), data.end());
            T maxim = *std::max_element(data.begin(), data.end());

            std::cout << "Suma: " << suma << std::endl;
            std::cout << "Media: " << media << std::endl;
            std::cout << "Minim: " << minim << std::endl;
            std::cout << "Maxim: " << maxim << std::endl;
        }
        std::cout << std::endl;
    }

    T calculeazaSuma() const {
        static_assert(std::is_arithmetic_v<T>, "Suma poate fi calculata doar pentru tipuri numerice");
        return std::accumulate(data.begin(), data.end(), T{});
    }

    [[nodiscard]] size_t getNumarElemente() const { return data.size(); }
    const std::vector<T>& getData() const { return data; }

    template<typename U>
    friend void afiseazaComparatie(const StatisticsManager<U>& sm1, const StatisticsManager<U>& sm2);
};

// Funcție template liberă friend
template<typename T>
void afiseazaComparatie(const StatisticsManager<T>& sm1, const StatisticsManager<T>& sm2) {
    std::cout << "\n🔄 Comparatie statistici:\n";
    std::cout << sm1.tip << " vs " << sm2.tip << std::endl;
    std::cout << "Elemente: " << sm1.data.size() << " vs " << sm2.data.size() << std::endl;

    if constexpr (std::is_arithmetic_v<T>) {
        if (!sm1.data.empty() && !sm2.data.empty()) {
            T suma1 = sm1.calculeazaSuma();
            T suma2 = sm2.calculeazaSuma();
            std::cout << "Sume: " << suma1 << " vs " << suma2 << std::endl;
        }
    }
    std::cout << std::endl;
}

// Funcție template liberă generică
template<typename Container, typename Predicate>
size_t numara_daca(const Container& container, Predicate pred) {
    return std::count_if(container.begin(), container.end(), pred);
}

#endif
