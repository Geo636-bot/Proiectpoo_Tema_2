# 🎢 Proiect POO – Sistem de Gestiune a unui Parc de Distracții

## 📋 Descriere generală

Acest proiect reprezintă o aplicație simplă care modelează un **parc de distracții** folosind principii de **Programare Orientată pe Obiecte (POO)**. Scopul este să gestioneze entități precum atracțiile, angajații, biletele și vizitatorii, folosind moștenirea, polimorfismul și încapsularea.

---

## 🧱 Structura proiectului

### ✅ Clase de bază și clase derivate

#### 1. `Atracție`
- Atribute comune: `nume`, `inaltimeMinima`, `capacitate`
- Derivate:
  - `MontagneRusse` → `vitezaMaxima`
  - `Carusel` → `numarCai`
  - `CasaGroazei` → `nivelFrica`

#### 2. `Angajat`
- Atribute comune: `nume`, `varsta`, `experientaAni`, `salariu`
- Derivate:
  - `OperatorAtracție` → `atractieDeservita`
  - `AgentPaza` → `zonaAsignata`
  - `Casier` → `Interval`

#### 3. `Bilet`
- Atribute comune: `pret`, `valabilitateZile`,`ziCurenta (scumpire la pret cu 25% daca este weekend,pretul se calculeaza pretul de baza * valabilitatezile)`
- Derivate:
  - `BiletStandard (pret= 50)`
  - `BiletAdult` → `includeAccesBufet (pret= 75 +30 daca are acces la bufet)`
  - `BiletVIP` → `accesPiscina (pret= 100 +50 daca are acces la piscina)`

#### 4. `Vizitator`
- Atribute comune: `nume`, `varsta`, `inaltime`, `bilet`
- Derivate:
  - `Copil` → `insotitDeAdult`
  - `Adolescent` → `areBuletin`
  - `Adult` → `ocupatie`

---

## 💡 Funcționalități

- Inițializarea și gestionarea listelor de atracții, angajați, bilete și vizitatori
- Verificarea eligibilității unui vizitator pentru o atracție (ex: înălțime, vârstă)
- Afișarea informațiilor detaliate despre fiecare entitate
- Exemplu de **moștenire multiplă** și **suprascriere a metodelor**

---

## 🚀 Tehnologii utilizate

- Limbaj: `C++` 
- Paradigme: Programare Orientată pe Obiecte
- Opțional: Interfață CLI (meniu în consolă)

---
## Meniu interactiv
 - 1. Afiseaza toate atractiile
 - 2. Afiseaza toti angajatii
 - 3. Afiseaza toti vizitatorii
 - 4. Afiseaza statistici parc
 - 5. Adauga atractie noua
 - 6. Adauga angajat nou
 - 7. Adauga vizitator nou
 - 8. Verifica accesul la o atractie
 - 9. Demonstratie dynamic_cast
 - 10.Incarca Date din CSV
 - 11. Simuleaza trecerea unei zile


## Structura Proiectului

```text
Proiectpoo_Tema_2/
├── cod/                  # Codul sursă al proiectului
│   ├── fisiere.cpp/      # Fișierele .cpp pentru fiecare clasă
│   │   ├── Angajat.cpp
│   │   ├── Atractie.cpp
│   │   ├── Bilet.cpp
│   │   ├── Meniu.cpp
│   │   ├── ParcDistractii.cpp
│   │   ├── Vizitator.cpp
│   │   └—— main.cpp      # Punctul de pornire al aplicației
│   └—— Fisiere.h/        # Fișierele header (.h)
│       ├—— Angajat.h
│       ├—— Atractie.h
│       ├—— Bilet.h
│       ├—— Exceptions.h
│       ├—— Meniu.h
│       ├—— ParcDistractii.h
│       └—— Vizitator.h
├── generated/            # Fișiere generate automat
│   └—— src/
│       └—— Helper.cpp
├── cmake/                # Configurări pentru CMake
│   ├—— CompilerFlags.cmake
│   ├—— CopyHelper.cmake
│   └—— Options.cmake
├── tastatura.txt         # Fișier de intrare de la tastatură
├── CMakeLists.txt        # Configurația proiectului pentru CMake
└—— README.md             # Acest fișier
```
