


#ifndef BILET_H
#define BILET_H

#include <string>
#include <iostream>
#include <memory>

class Bilet {
protected:
    double pret;
    int valabilitateZile;
    static double pretMediu; // atribut static

public:
    Bilet(double pret, int valabilitateZile);
    Bilet(const Bilet& other);
    Bilet& operator=(const Bilet& other);
    virtual ~Bilet() = default;

    // Constructor virtual (clone pattern)
    [[nodiscard]] virtual std::unique_ptr<Bilet> clone() const = 0;

    [[nodiscard]] virtual std::string getTip() const = 0;
    [[nodiscard]] virtual double calculeazaPretFinal() const;

    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Bilet& bilet);

    // Funcții statice
    //static double getPretMediu() { return pretMediu; }


    // Getters
    [[nodiscard]] double getPret() const { return pret; }
    [[nodiscard]] int getValabilitateZile() const { return valabilitateZile; }

    void scadeValabilitate() {
        if (valabilitateZile > 0)
            --valabilitateZile;
    }

    [[nodiscard]] bool esteExpirat() const {
        return valabilitateZile <= 0;
    }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Bilet& other) noexcept;
};

class BiletStandard : public Bilet {

public:
    BiletStandard(double pret, int valabilitateZile,int zi);
    BiletStandard(const BiletStandard& other);
    BiletStandard& operator=(const BiletStandard& other);

    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] double calculeazaPretFinal() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet Standard"; }


protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletPremium : public Bilet {
private:
    bool includeAccesBufet{};

public:
    BiletPremium(double pret, int valabilitateZile, bool includeAccesBufet);
    BiletPremium(const BiletPremium& other);
    BiletPremium& operator=(const BiletPremium& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet Premium"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
    //[[nodiscard]] bool getIncludeFastPass() const { return includeFastPass; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class BiletVIP : public Bilet {
private:
    bool accesLounge;

public:
    BiletVIP(double pret, int valabilitateZile, bool accesLounge);
    BiletVIP(const BiletVIP& other);
    BiletVIP& operator=(const BiletVIP& other);
    
    [[nodiscard]] std::unique_ptr<Bilet> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Bilet VIP"; }
    [[nodiscard]] double calculeazaPretFinal() const override;
    //[[nodiscard]] bool getAccesLounge() const { return accesLounge; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
