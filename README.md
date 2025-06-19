# 🎢 Proiect POO – Sistem de Gestiune a unui Parc de Distracții

## 📋 Descriere generală

Acest proiect reprezintă o aplicație simplă care modelează un **parc de distracții** folosind principii de **Programare Orientată pe Obiecte (POO)**. Scopul este să gestioneze entități precum atracțiile, angajații, biletele și vizitatorii, folosind moștenirea, polimorfismul și încapsularea.

---

## 🧱 Structura proiectului

### ✅ Clase de bază și clase derivate

#### 1. `Atracție`
- Atribute comune: `nume`, `inaltimeMinima`, `capacitate`, `durata`
- Derivate:
  - `MontagneRusse` → `vitezaMaxima`
  - `Carusel` → `numarCai`
  - `CasaGroazei` → `nivelFrica`

#### 2. `Angajat`
- Atribute comune: `nume`, `varsta`, `experientaAni`, `salariu`
- Derivate:
  - `OperatorAtracție` → `atractieDeservita`
  - `AgentPaza` → `nivelAlerta`
  - `Casier` → `casierieID`

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
- Demonstratii de **polimorfism** cu metode virtuale
- Exemplu de **moștenire multiplă** și **suprascriere a metodelor**

---

## 🚀 Tehnologii utilizate

- Limbaj: `C++` / `Java` / `Python` *(alege în funcție de implementare)*
- Paradigme: Programare Orientată pe Obiecte
- Opțional: Interfață CLI (meniu în consolă)

---

## 📦 Structura fișierelor

```bash
📁 ParcDistractii/
├── src/
│   ├── Atractie.h / .cpp
│   ├── Angajat.h / .cpp
│   ├── Bilet.h / .cpp
│   ├── Vizitator.h / .cpp
│   └── main.cpp
├── README.md
└── Makefile / CMakeLists.txt 
