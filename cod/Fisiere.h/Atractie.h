
#ifndef ATRACTIE_H
#define ATRACTIE_H

#include <string>
#include <iostream>
#include <memory>

class Atractie {
protected:
    std::string nume;
    int inaltimeMinima;
    int capacitate;
    static int numarTotalAtractii; // atribut static

public:
    Atractie(const std::string& nume, int inaltimeMinima, int capacitate);
    Atractie(const Atractie& other); // copy constructor
    Atractie& operator=(const Atractie& other); // assignment operator
    virtual ~Atractie() = default;
    
    // Constructor virtual (clone pattern)
    [[nodiscard]] virtual std::unique_ptr<Atractie> clone() const = 0;
    
    [[nodiscard]] virtual std::string getTip() const = 0;
    
    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Atractie& atractie);
    
    // Funcție statică
    static int getNumarTotalAtractii() { return numarTotalAtractii; }
    static void resetContorAtractii() { numarTotalAtractii = 0; }
    
    // Getters
    [[nodiscard]] const std::string& getNume() const { return nume; }
    [[nodiscard]] int getInaltimeMinima() const { return inaltimeMinima; }
    [[nodiscard]] int getCapacitate() const { return capacitate; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Atractie& other) noexcept; // pentru copy-and-swap
};

class MontagneRusse : public Atractie {
private:
    int vitezaMaxima;

public:
    MontagneRusse(const std::string& nume, int inaltimeMinima, int capacitate, int vitezaMaxima);
    MontagneRusse(const MontagneRusse& other);
    MontagneRusse& operator=(const MontagneRusse& other);
    
    [[nodiscard]] std::unique_ptr<Atractie> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Montagne Russe"; }
    [[nodiscard]] int getVitezaMaxima() const { return vitezaMaxima; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class Carusel : public Atractie {
private:
    int numarCai;

public:
    Carusel(const std::string& nume, int inaltimeMinima, int capacitate, int numarCai);
    Carusel(const Carusel& other);
    Carusel& operator=(const Carusel& other);
    
    [[nodiscard]] std::unique_ptr<Atractie> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Carusel"; }
    [[nodiscard]] int getNumarCai() const { return numarCai; }

protected:
    void afiseaza(std::ostream& os) const override;
};

class CasaGroazei : public Atractie {
private:
    int nivelFrica;

public:
    CasaGroazei(const std::string& nume, int inaltimeMinima, int capacitate, int nivelFrica);
    CasaGroazei(const CasaGroazei& other);
    CasaGroazei& operator=(const CasaGroazei& other);
    

    [[nodiscard]] std::unique_ptr<Atractie> clone() const override;
    [[nodiscard]] std::string getTip() const override { return "Casa Groazei"; }
    [[nodiscard]] int getNivelFrica() const { return nivelFrica; }

protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
