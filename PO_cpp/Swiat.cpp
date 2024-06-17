//
// Created by olgar on 20.04.2024.
//
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Swiat.h"
#include "Organizmy/Zwierzeta/Owca.h"

Swiat::Swiat(int wysokosc, int szerokosc)
        : wysokosc(wysokosc), szerokosc(szerokosc) {
    this->uzupelnijPlansze();
    this->zywyCzlowiek = true;
    this->tura = 0;
}

void Swiat::uzupelnijPlansze() {
    for(int y = 0; y < wysokosc; y++) {
        for(int x = 0; x < szerokosc; x++) {
            pola[y][x] = ' ';
        }
    }
}

void Swiat::wykonajTure(char *command) {
    system("CLS");
    this->tura +=1;
    std::cout << "OLGA RODZIEWICZ s198421 aktualna tura: " << tura << std::endl
    << "WYKONAJ RUCH (q-zakoncz, n-specjalna umiejetnosc, z-zapisz do pliku)" << std::endl;
    for(int j = 7; j >= 0; j--) {
        for(int i = 0; i < this->iloscOrganizmow(); i++) {
            if(organizmy[i]->GetInicjatywa() == j && organizmy[i]->CzyZywy()) {
                organizmy[i]->Akcja(*command);
            }
        }
    }
    this->rysujSwiat();
    if(!zywyCzlowiek){
        *command='q';
    }
}

void Swiat::rysujSwiat() {
    for(int x = 0; x < szerokosc+1; x++) {
        std::cout << "---";
    }
    std::cout << std::endl;
    for(int y = 0; y < wysokosc; y++) {
        std::cout << "||";
        for(int x = 0; x < szerokosc; x++) {
            std::cout << ' ' << pola[y][x] << ' ';
        }
        std::cout << "||" << std::endl;
    }
    for(int x = 0; x < szerokosc+1; x++) {
        std::cout << "---";
    }
    std::cout << std::endl;
}
int Swiat::getTura() {
    return tura;
}
int Swiat::iloscOrganizmow() {
    return organizmy.size();
}

bool Swiat::CzyPoleJestPuste(int x, int y) {
    if(pola[y][x] == ' ')
        return true;
    return false;
}

bool Swiat::CzyPoleJestPrawidlowe(int x, int y) {
    return (x >= 0 && y >= 0 && x < szerokosc && y < wysokosc);
}

Organizm* Swiat::dajOrganizmZPola(int x, int y) {
    for(int i = 0; i < this->iloscOrganizmow(); i++) {
        if(organizmy[i]->GetX() == x && organizmy[i]->GetY() == y) {
            return organizmy[i];
        }
    }
    return nullptr;
}

int Swiat::dajSileZOrganizmu(int x, int y) {
    return dajOrganizmZPola(x, y)->GetSila();
}

int Swiat::dajInicjatyweZOrganizmu(int x, int y) {
    return dajOrganizmZPola(x, y)->GetInicjatywa();
}

void Swiat::dodajOrganizm(Organizm* organizm) {
    int x, y;
    while(true) {
        x = organizm->GetX();
        y = organizm->GetY();
        if(this->CzyPoleJestPrawidlowe(x, y) && this->CzyPoleJestPuste(x, y)) {
            this->dodajNaUstalonePole(x, y, organizm);
            break;
        } else {
            organizm->SetPozycja(rand() % szerokosc, rand() % wysokosc);
        }
    }
}

void Swiat::dodajNaUstalonePole(int x, int y, Organizm* organizm) {
    try {
        organizmy.push_back(organizm);
        pola[y][x] = organizm->GetSymbol();
    } catch(const std::exception& e) {

    }
}

void Swiat::ZmienPozycje(int x, int y, int px, int py) {
    char tmp = pola[y][x];
    pola[y][x] = ' ';
    pola[y + py][x + px] = tmp;
}

void Swiat::WyczyscPole(int x, int y) {
    Organizm *zgon = this->dajOrganizmZPola(x, y); // Pobierz organizm z danego pola
    if (zgon != nullptr) {
        // Szukaj organizmu w wektorze organizmów
        for (auto it = organizmy.begin(); it != organizmy.end();) {
            if (*it == zgon) {
                delete *it;
                it = organizmy.erase(it);
                break;
            } else {
                ++it; // Przejdź do następnego elementu
            }
        }
        // Ustaw pole jako puste
        pola[y][x] = ' ';
    }
}
void Swiat::wyczyscPamiec() {
    for (auto& organizm : organizmy) {
        delete organizm; // Zwolnij pamięć po obiekcie
    }
    // Usuń wszystkie elementy z wektora
    organizmy.clear();
}

void Swiat::zabijczlowieka() {
    this->zywyCzlowiek = false;
}
void Swiat::zapiszDoPliku() {
    FILE * slot;
    slot= fopen("../slot1.txt", "w");
    if (slot == nullptr) {
        std::cerr << "Błąd otwierania pliku." << std::endl;
        return;
    }
    fprintf(slot, "%d %d\n", szerokosc, wysokosc);
    fprintf(slot, "%d \n", static_cast<int>(organizmy.size()));
    for (auto& organizm : organizmy) {
        fprintf(slot, "%s %d %d %d\n", organizm->GetNazwa().c_str(), organizm->GetX(), organizm->GetX(), organizm->GetSila());
    }
    fclose(slot);
}