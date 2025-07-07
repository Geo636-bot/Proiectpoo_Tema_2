

#ifndef BILET_TEMPLATE_HPP
#define BILET_TEMPLATE_HPP

#include <algorithm>

// Inițializare atribute statice template
template<typename T>
T Bilet<T>::pretMediu = T(75.0);

template<typename T>
ZiSaptamana Bilet<T>::ziCurenta = ZiSaptamana::Luni;

// Implementarea constructorului template
template<typename T>
Bilet<T>::Bilet(T pretBaza, int valabilitateZile)
    : pretBaza(pretBaza), valabilitateZile(valabilitateZile) {
    // Setez strategia implicită
    if (esteWeekend(ziCurenta)) {
        strategieCalcul = std::make_unique<CalculPretWeekend<T>>();
    } else {
        strategieCalcul = std::make_unique<CalculPretStandard<T>>();
    }
}

template<typename T>
Bilet<T>::Bilet(const Bilet& other)
    : pretBaza(other.pretBaza), valabilitateZile(other.valabilitateZile) {
    if (other.strategieCalcul) {
        strategieCalcul = other.strategieCalcul->clone();
    }
}

template<typename T>
Bilet<T>& Bilet<T>::operator=(const Bilet& other) {
    if (this != &other) {
        pretBaza = other.pretBaza;
        valabilitateZile = other.valabilitateZile;
        if (other.strategieCalcul) {
            strategieCalcul = other.strategieCalcul->clone();
        }
    }
    return *this;
}

template<typename T>
void Bilet<T>::swap(Bilet& other) noexcept {
    std::swap(pretBaza, other.pretBaza);
    std::swap(valabilitateZile, other.valabilitateZile);
    std::swap(strategieCalcul, other.strategieCalcul);
    std::swap(observatori, other.observatori);
}

template<typename T>
void Bilet<T>::scadeValabilitate() {
    if (valabilitateZile > 0) {
        valabilitateZile--;
        if (valabilitateZile == 0) {
            // Notific observatorii că biletul a expirat
            for (auto* observer : observatori) {
                observer->notificareExpirare(getTip());
            }
        }
    }
}

template<typename T>
double Bilet<T>::calculeazaPretFinal() const {
    if (strategieCalcul) {
        return strategieCalcul->calculeazaPret(pretBaza, valabilitateZile);
    }
    return calculeazaPretCuWeekend();
}

template<typename T>
double Bilet<T>::calculeazaPretCuWeekend() const {
    double pretTotal = static_cast<double>(pretBaza) * valabilitateZile;
    if (esteWeekend(ziCurenta)) {
        pretTotal *= 1.25;
    }
    return pretTotal;
}

template<typename T>
void Bilet<T>::notificaObservatori(double pretNou) {
    for (auto* observer : observatori) {
        observer->notificareSchimbarePret(pretNou);
    }
}

template<typename T>
bool Bilet<T>::esteWeekend(ZiSaptamana zi) {
    return zi == ZiSaptamana::Sambata || zi == ZiSaptamana::Duminica;
}

template<typename T>
void Bilet<T>::trecutZi() {
    int ziInt = static_cast<int>(ziCurenta);
    ziInt++;
    if (ziInt > 7) {
        ziInt = 1;
    }
    ziCurenta = static_cast<ZiSaptamana>(ziInt);
}

template<typename T>
std::string Bilet<T>::getNumeZi(ZiSaptamana zi) {
    switch (zi) {
        case ZiSaptamana::Luni: return "Luni";
        case ZiSaptamana::Marti: return "Marti";
        case ZiSaptamana::Miercuri: return "Miercuri";
        case ZiSaptamana::Joi: return "Joi";
        case ZiSaptamana::Vineri: return "Vineri";
        case ZiSaptamana::Sambata: return "Sambata";
        case ZiSaptamana::Duminica: return "Duminica";
        default: return "Necunoscut";
    }
}

template<typename T>
void Bilet<T>::actualizarePretMediu(const T& nouPret) {
    pretMediu = (pretMediu + nouPret) / T(2.0);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Bilet<T>& bilet) {
    bilet.afiseaza(os);
    return os;
}

template<typename T>
void Bilet<T>::afiseaza(std::ostream& os) const {
    os << "🎫 " << getTip() << " - Pret: " << calculeazaPretFinal()
       << " RON (Valabil " << valabilitateZile << " zile)";
    if (valabilitateZile == 0) {
        os << " [EXPIRAT]";
    } else if (esteWeekend(ziCurenta)) {
        os << " [Weekend +25%]";
    }
}

// BiletStandard template implementation
template<typename T>
BiletStandard<T>::BiletStandard(int valabilitateZile)
    : Bilet<T>(T(50.0), valabilitateZile) {}

template<typename T>
BiletStandard<T>::BiletStandard(const BiletStandard& other)
    : Bilet<T>(other) {}

template<typename T>
BiletStandard<T>& BiletStandard<T>::operator=(const BiletStandard& other) {
    if (this != &other) {
        Bilet<T>::operator=(other);
    }
    return *this;
}

template<typename T>
std::unique_ptr<Bilet<T>> BiletStandard<T>::clone() const {
    return std::make_unique<BiletStandard<T>>(*this);
}

template<typename T>
void BiletStandard<T>::afiseaza(std::ostream& os) const {
    Bilet<T>::afiseaza(os);
}

// BiletPremium template implementation
template<typename T>
BiletPremium<T>::BiletPremium(int valabilitateZile, bool includeAccesBufet)
    : Bilet<T>(T(75.0), valabilitateZile), includeAccesBufet(includeAccesBufet) {}

template<typename T>
BiletPremium<T>::BiletPremium(const BiletPremium& other)
    : Bilet<T>(other), includeAccesBufet(other.includeAccesBufet) {}

template<typename T>
BiletPremium<T>& BiletPremium<T>::operator=(const BiletPremium& other) {
    if (this != &other) {
        Bilet<T>::operator=(other);
        includeAccesBufet = other.includeAccesBufet;
    }
    return *this;
}

template<typename T>
std::unique_ptr<Bilet<T>> BiletPremium<T>::clone() const {
    return std::make_unique<BiletPremium<T>>(*this);
}

template<typename T>
double BiletPremium<T>::calculeazaPretFinal() const {
    double pretTotal = static_cast<double>(this->pretBaza) * this->valabilitateZile;
    if (includeAccesBufet) {
        pretTotal += 30;
    }
    if (Bilet<T>::esteWeekend(Bilet<T>::ziCurenta)) {
        pretTotal *= 1.25;
    }
    return pretTotal;
}

template<typename T>
void BiletPremium<T>::afiseaza(std::ostream& os) const {
    Bilet<T>::afiseaza(os);
    if (includeAccesBufet) {
        os << " + Acces Bufet";
    }
}

// BiletVIP template implementation
template<typename T>
BiletVIP<T>::BiletVIP(int valabilitateZile, bool accesPiscina)
    : Bilet<T>(T(100.0), valabilitateZile), accesPiscina(accesPiscina) {}

template<typename T>
BiletVIP<T>::BiletVIP(const BiletVIP& other)
    : Bilet<T>(other), accesPiscina(other.accesPiscina) {}

template<typename T>
BiletVIP<T>& BiletVIP<T>::operator=(const BiletVIP& other) {
    if (this != &other) {
        Bilet<T>::operator=(other);
        accesPiscina = other.accesPiscina;
    }
    return *this;
}

template<typename T>
std::unique_ptr<Bilet<T>> BiletVIP<T>::clone() const {
    return std::make_unique<BiletVIP<T>>(*this);
}

template<typename T>
double BiletVIP<T>::calculeazaPretFinal() const {
    double pretTotal = static_cast<double>(this->pretBaza) * this->valabilitateZile;
    if (accesPiscina) {
        pretTotal += 50;
    }
    if (Bilet<T>::esteWeekend(Bilet<T>::ziCurenta)) {
        pretTotal *= 1.25;
    }
    return pretTotal;
}

template<typename T>
void BiletVIP<T>::afiseaza(std::ostream& os) const {
    Bilet<T>::afiseaza(os);
    if (accesPiscina) {
        os << " + Acces Piscina";
    }
}

// Factory template implementation
template<typename T>
std::map<std::string, std::function<std::unique_ptr<Bilet<T>>(int, bool)>> BiletFactory<T>::creatoriInregistrati;

template<typename T>
std::unique_ptr<Bilet<T>> BiletFactory<T>::creeazaBilet(const std::string& tip, int valabilitate, bool parametru) {
    if (tip == "standard") {
        return std::make_unique<BiletStandard<T>>(valabilitate);
    } else if (tip == "premium") {
        return std::make_unique<BiletPremium<T>>(valabilitate, parametru);
    } else if (tip == "vip") {
        return std::make_unique<BiletVIP<T>>(valabilitate, parametru);
    }
    return nullptr;
}

#endif
