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
- Atribute comune: `pret`, `tip`, `valabilitateZile`
- Derivate:
  - `BiletCopil` → `reducereProcent`
  - `BiletAdult` → `includeFastPass`
  - `BiletVIP` → `accesLounge`

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
## Structura proiectului

Proiectpoo_Tema_2/
├── cod/               # Codul sursă al proiectului
│   ├── fisiere.cpp/   # Fișierele .cpp pentru fiecare clasă
│   │   ├── Angajat.cpp
│   │   ├── Atractie.cpp
│   │   ├── Bilet.cpp
│   │   ├── Meniu.cpp
│   │   ├── ParcDistractii.cpp
│   │   ├── Vizitator.cpp
│   │   ├── main.cpp   # Punctul de pornire al aplicației
│   ├── Fisiere.h/     # Fișierele header (.h)
│       ├── Angajat.h
│       ├── Atractie.h
│       ├── Bilet.h
│       ├── Exceptions.h
│       ├── Meniu.h
│       ├── ParcDistractii.h
│       ├── Vizitator.h
├── generated/         # Fișiere generate automat
│   └── src/
│       └── Helper.cpp
├── cmake/             # Configurări pentru CMake
│   ├── CompilerFlags.cmake
│   ├── CopyHelper.cmake
│   └── Options.cmake
├── tastatura.txt      # Fișier de intrare de la tastatură
├── CMakeLists.txt     # Configurația proiectului pentru CMake
└── README.md          # Acest fișier



