
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
    virtual std::unique_ptr<Atractie> clone() const = 0;
    
    virtual std::string getTip() const = 0;
    
    // Operatorul << virtual pentru polimorfism
    friend std::ostream& operator<<(std::ostream& os, const Atractie& atractie);
    
    // Funcție statică
    
    
    // Getters
    const std::string& getNume() const { return nume; }

protected:
    virtual void afiseaza(std::ostream& os) const;
    void swap(Atractie& other); // pentru copy-and-swap
};

class MontagneRusse : public Atractie {
private:
    int vitezaMaxima;

public:
    MontagneRusse(const std::string& nume, int inaltimeMinima, int capacitate, int vitezaMaxima);
    MontagneRusse(const MontagneRusse& other);
    MontagneRusse& operator=(const MontagneRusse& other);
    
    std::unique_ptr<Atractie> clone() const override;
   
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
    
    std::unique_ptr<Atractie> clone() const override;
    const std::string& getTip() const override { return "Carusel"; }
   

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
    
    std::unique_ptr<Atractie> clone() const override;
    std::string getTip() const override { return "Casa Groazei"; }
    
protected:
    void afiseaza(std::ostream& os) const override;
};

#endif
