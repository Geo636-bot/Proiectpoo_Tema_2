

#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>
#include <memory>

enum class ZiSaptamana {
    Luni = 1, Marti, Miercuri, Joi, Vineri, Sambata, Duminica
};

class Bilet {
protected:
    double pretBaza;
    int valabilitateZile;
    static ZiSaptamana ziCurenta; // atribut static pentru zi curenta
    static double pretMediu; // atribut static

public:
    Bilet(double pretBaza, int valabilitateZile);
    Bilet(const Bilet& other);
    Bilet& operator=(const Bilet& other);
    virtual ~Bilet() = default;
    
    // Constructor virtual (clone pattern)
    virtual std::unique_ptr<Bilet> clone() const = 0;

    virtual std::string getTip() const = 0;
    virtual double calculeazaPretFinal() const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Bilet& bilet);

    // Funcții statice pentru gestionarea zilei
    static ZiSaptamana getZiCurenta() { return ziCurenta; }
    static void trecutZi();
    static std::string getNumeZi(ZiSaptamana zi);
    static bool esteWeekend(ZiSaptamana zi);

    // Funcții statice
    static void actualizarePretMediu(double nouPret);

    // Getters
   // double getPretBaza() const { return pretBaza; }
    //int getValabilitateZile() const { return valabilitateZile; }

    // Metoda pentru scaderea valabilitatii
    void scadeValabilitate();
    bool esteValid() const { return valabilitateZile > 0; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Bilet& other) noexcept;
    double calculeazaPretCuWeekend() const;
};

class BiletStandard : public Bilet {
public:
    explicit BiletStandard(int valabilitateZile);
    BiletStandard(const BiletStandard& other);
    BiletStandard& operator=(const BiletStandard& other);

    std::unique_ptr<Bilet> clone() const override;
    std::string getTip() const override { return "Bilet Standard"; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletPremium : public Bilet {
private:
    bool includeAccesBufet;

public:
    BiletPremium(int valabilitateZile, bool includeAccesBufet);
    BiletPremium(const BiletPremium& other);
    BiletPremium& operator=(const BiletPremium& other);

    std::unique_ptr<Bilet> clone() const override;
    std::string getTip() const override { return "Bilet Premium"; }
    double calculeazaPretFinal() const override;
    //bool getIncludeAccesBufet() const { return includeAccesBufet; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletVIP : public Bilet {
private:
    bool accesPiscina;

public:
    BiletVIP(int valabilitateZile, bool accesPiscina);
    BiletVIP(const BiletVIP& other);
    BiletVIP& operator=(const BiletVIP& other);

    std::unique_ptr<Bilet> clone() const override;
    std::string getTip() const override { return "Bilet VIP"; }
    double calculeazaPretFinal() const override;
    //bool getAccesPiscina() const { return accesPiscina; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
