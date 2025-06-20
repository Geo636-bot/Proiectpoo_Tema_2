

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class ParcException : public std::exception {
protected:
    std::string message;

public:
    ParcException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class InaltimeInsuficienta : public ParcException {
public:
    InaltimeInsuficienta(const std::string& msg) 
        : ParcException("Inaltime insuficienta: " + msg) {}
};

class VarstaNecorespunzatoare : public ParcException {
public:
    VarstaNecorespunzatoare(const std::string& msg) 
        : ParcException("Varsta necorespunzatoare: " + msg) {}
};

class CapacitateDepasita : public ParcException {
public:
    CapacitateDepasita(const std::string& msg) 
        : ParcException("Capacitate depasita: " + msg) {}
};

class DateInvalide : public ParcException {
public:
    DateInvalide(const std::string& msg) 
        : ParcException("Date invalide: " + msg) {}
};

#endif
