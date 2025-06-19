#ifndef ATRACTIE_H
#define ATRACTIE_H

#include <iostream>
#include <string>

using namespace std;


class Atractie{
  protected:
    string nume;
    double inaltimemin;
    int capacitate;

  public:
    Atractie(string nume,double inaltimemin,int capacitate):
     nume(nume),inaltimemin(inaltimemin),capacitate(capacitate){}


    virtual void print(ostream& out) const = 0;

    friend ostream& operator<<(ostream& out,const Atractie& atr){
         atr.print(out);
         return out;
    }

    virtual ~Atractie() = default;


};

class RollerCoaster:public Atractie{
  private:
    double vitezaMax;


  public:
  RollerCoaster(string nume,double inaltimemin,int capacitate,double vitezaMax):
    Atractie(nume,inaltimemin,capacitate),vitezaMax(vitezaMax){}

  void print(ostream& out) const override{
    out << "Roller Coaster: " << nume <<endl<<"Inaltime minima obligatorie: " << inaltimemin
            <<endl<<"Capacitate: " << capacitate <<endl<<"Viteza maxima: " << vitezaMax <<endl;

  }
};
class Carusel:public Atractie{
  private:
    int nrcai;
  public:
    Carusel(string nume,double inaltimemin,int capacitate,int nrcai):
    Atractie(nume,inaltimemin,capacitate),nrcai(nrcai){}

    void print(ostream& out) const override{
      out << "Carusel: " << nume <<endl<<"Inaltime minima obligatorie: " << inaltimemin
            <<endl<<"Capacitate: " << capacitate <<endl<<"Numarul de cai: "<<nrcai<<endl;

    }
};

class CasaGroazei:public Atractie{
  private:
    int nivelFrica;//1-10

    public:
  CasaGroazei(string nume,double inaltimemin,int capacitate,int nivelFrica):
  Atractie(nume,inaltimemin,capacitate),nivelFrica(nivelFrica){}

  void print(ostream& out) const override{
    out << "Casa Groazei: " << nume <<endl<<"Inaltime minima obligatorie: " << inaltimemin
           <<endl<<"Capacitate: " << capacitate <<endl<<"Nivel de frica: "<<nivelFrica<<endl;
  }
};


#endif