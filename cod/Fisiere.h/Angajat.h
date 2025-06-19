#ifndef ANGAJAT_H
#define ANGAJAT_H

#include <string>
#include <iostream>

class Angajat {
protected:
    std::string nume;
    int varsta;
    int experientaAni;
    double salariu;

public:
    Angajat(const std::string& nume, int varsta, int experientaAni, double salariu){};
    virtual ~Angajat() = default;
    
    virtual void print(std::ostream& out) const = 0;

    friend std::ostream& operator<<(std::ostream& out,const Angajat& ang){
        ang.print(out);
        return out;
    }
    virtual std::string getTip() const = 0;

    
    // Getters
    std::string getNume() const { return nume; }
    int getVarsta() const { return varsta; }
    int getExperientaAni() const { return experientaAni; }
    double getSalariu() const { return salariu; }
};

class OperatorAtractie : public Angajat {
private:
    std::string atractieDeservita;

public:
    OperatorAtractie(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& atractieDeservita);
    void print(std::ostream& out) const override {
        out << "Operator Atractie: " << nume <<std::endl<<"Varsta: " << varsta<<std::endl
          <<"Experienta: " << experientaAni << " ani"<<std::endl
          <<"Salariu: " << salariu<<std::endl
          <<"Atractie: " << atractieDeservita<<std::endl;
    }
    std::string getTip() const override { return "Operator Atractie"; }

    std::string getAtractieDeservita() const { return atractieDeservita; }
};

class AgentPaza : public Angajat {
private:
    std::string zonaAsignata;

public:
    AgentPaza(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& zonaAsignata);
    void print(std::ostream& out) const override{
        out << "Agent Paza: " << nume <<std::endl
          <<"Varsta: " << varsta<<std::endl
          <<"Experienta: " << experientaAni << " ani"<<std::endl
          <<"Salariu: " << salariu<<std::endl
          <<"Zona in care este asignat: "<<zonaAsignata<<std::endl;

    }
    std::string getTip() const override { return "Agent Paza"; }

    std::string getZonaAsignata() const { return zonaAsignata; }
};

class Casier : public Angajat {
private:
    std::string interval;

public:
    Casier(const std::string& nume, int varsta, int experientaAni, double salariu, const std::string& interval);
    void print(std::ostream& out)const override{
        out << "Casier: " << nume <<std::endl
          <<"Varsta: " << varsta<<std::endl
          <<"Experienta: " << experientaAni << " ani"<<std::endl
          <<"Salariu: " << salariu<<std::endl
          <<"Interval tura: "<<interval<<std::endl;
    }
    std::string getTip() const override { return "Casier"; }
    std::string getInterval() const { return interval; }
};

#endif
