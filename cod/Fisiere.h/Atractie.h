#ifndef ATRACTIE_H
#define ATRACTIE_H

#include <string>
#include <iostream>

class Atractie {
protected:
  std::string nume;
  int inaltimeMinima;
  int capacitate;

public:
  Atractie(const std::string& nume, int inaltimeMinima, int capacitate){}

  virtual ~Atractie() = default;

  virtual void print(std::ostream& out) const = 0;

  friend std::ostream& operator<<(std::ostream& out,const Atractie& atr){
    atr.print(out);
    return out;
  }

  virtual std::string getTip() const = 0;

  // Getters
  std::string getNume() const { return nume; }
  int getInaltimeMinima() const { return inaltimeMinima; }
  int getCapacitate() const { return capacitate; }
};

class RollerCoaster : public Atractie {
private:
  int vitezaMaxima;

public:
  RollerCoaster(const std::string& nume, int inaltimeMinima, int capacitate, int vitezaMaxima);
  void print(std::ostream& out) const override{
    out <<"Roller Coaster: " << nume <<std::endl
        <<"Inaltime minima obligatorie: " << inaltimeMinima<<std::endl
        <<"Capacitate: " << capacitate <<std::endl
        <<"Viteza maxima: " << vitezaMaxima <<std::endl;

  }
  std::string getTip() const override { return "Roller Coaster"; }
  int getVitezaMaxima() const { return vitezaMaxima; }
};

class Carusel : public Atractie {
private:
  int numarCai;

public:
  Carusel(const std::string& nume, int inaltimeMinima, int capacitate, int numarCai);
  void print(std::ostream& out) const override{
    out << "Carusel: " << nume <<std::endl<<"Inaltime minima obligatorie: " << inaltimeMinima
          <<std::endl<<"Capacitate: " << capacitate <<std::endl<<"Numarul de cai: "<<numarCai<<std::endl;

  }
  std::string getTip() const override { return "Carusel"; }
  int getNumarCai() const { return numarCai; }
};

class CasaGroazei : public Atractie {
private:
  int nivelFrica;

public:
  CasaGroazei(const std::string& nume, int inaltimeMinima, int capacitate, int nivelFrica);
  void print(std::ostream& out) const override{
    out << "Casa Groazei: " << nume <<std::endl
        <<"Inaltime minima obligatorie: " << inaltimeMinima<<std::endl
        <<"Capacitate: " << capacitate <<std::endl
        <<"Nivel de frica: "<<nivelFrica<<std::endl;
  }
  std::string getTip() const override { return "Casa Groazei"; }
  int getNivelFrica() const { return nivelFrica; }
};

#endif