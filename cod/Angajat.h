#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <iostream>
#include <string>

using namespace std;

class Angajat{
protected:
std::string nume;
int varsta;
int experienta;//(in ani)
double salariu;// RON per luna


public:
Angajat(string nume,int varsta,int experienta,double salariu):
                 nume(nume), varsta(varsta),experienta(experienta),salariu(salariu){};

    virtual void print(ostream& out) const = 0;

    friend ostream& operator<<(ostream& out, const Angajat& ang) {
        ang.print(out);
        return out;
    }

    virtual ~Angajat() =default;
};

class Operator:public Angajat{
  private:
      string atractie;//Atractie de care se ocupa

  public:
    Operator(string nume,int varsta,int experienta,double salariu,string atractie):
    Angajat(nume,varsta,experienta,salariu),atractie(atractie){}

    void print(ostream& out) const override {
        out << "Operator Atractie: " << nume <<endl<<"Varsta: " << varsta
            <<endl<<"Experienta: " << experienta << " ani"<<endl<<"Salariu: " << salariu
            <<endl<<"Atractie: " << atractie<<endl;
    }
};

class AgentPaza:public Angajat{
  private:
    string zona; //In ce parte a parcului a fost asignat (N,V etc.)

  public:
  AgentPaza(string nume,int varsta,int experienta,double salariu,string zona):
  Angajat(nume,varsta,experienta,salariu),zona(zona){}


  void print(ostream& out) const override{
      out << "Agent Paza: " << nume <<endl<<"Varsta: " << varsta
              <<endl<<"Experienta: " << experienta << " ani"<<endl<<"Salariu: " << salariu
              <<endl<<"Zona in care este asignat: "<<zona<<endl;

  }
};

class Casier:public Angajat{
    private:
        string interval;//10:00-15:00


    public:
       Casier(string nume,int varsta,int experienta,double salariu,string interval):
      Angajat(nume,varsta,experienta,salariu),interval(interval){}
       void print(ostream& out)const override{
           out << "Casier: " << nume <<endl<<"Varsta: " << varsta
                <<endl<<"Experienta: " << experienta << " ani"<<endl<<"Salariu: " << salariu
                <<endl<<"Interval tura: "<<interval<<endl;
       }
};



#endif