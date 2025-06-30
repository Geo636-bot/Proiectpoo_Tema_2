#ifndef TEMPLATEUTILS_H
#define TEMPLATEUTILS_H

#include <iostream>

// Funcție liberă template care poate afișa orice obiect care are metoda `afiseaza()`
template<typename T>
void afiseazaGeneric(const T& obj) {
    obj.afiseaza();
}

#endif

