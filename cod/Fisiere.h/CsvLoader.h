
#ifndef CSVLOADER_H
#define CSVLOADER_H

#include "ParcDistractii.h"
#include <string>
#include <vector>

class CSVLoader {
public:
    static bool incarcaDate(ParcDistractii& parc);
    static bool incarcaAtractii(ParcDistractii& parc, const std::string& fisier);
    static bool incarcaAngajati(ParcDistractii& parc, const std::string& fisier);
    static bool incarcaVizitatori(ParcDistractii& parc, const std::string& fisier);

private:
    static std::vector<std::string> parseazaLinie(const std::string& linie);
    static std::string trim(const std::string& str);
};

#endif
