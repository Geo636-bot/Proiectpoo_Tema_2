

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>

class ParcException : public std::exception {
protected:
    std::string message;

public:
    explicit ParcException(std::string  msg) : message(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};

class InaltimeInsuficienta : public ParcException {
public:
    explicit InaltimeInsuficienta(const std::string& msg) 
        : ParcException("Inaltime insuficienta: " + msg) {}
};

class VarstaNecorespunzatoare : public ParcException {
public:
    explicit VarstaNecorespunzatoare(const std::string& msg) 
        : ParcException("Varsta necorespunzatoare: " + msg) {}
};

class CapacitateDepasita : public ParcException {
public:
    explicit CapacitateDepasita(const std::string& msg) 
        : ParcException("Capacitate depasita: " + msg) {}
};

class DateInvalide : public ParcException {
public:
    explicit DateInvalide(const std::string& msg) 
        : ParcException("Date invalide: " + msg) {}
};

#endif
