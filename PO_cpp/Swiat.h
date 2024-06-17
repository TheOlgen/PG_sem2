//
// Created by olgar on 20.04.2024.
//

#ifndef SWIAT_H
#define SWIAT_H
#define MAX_CAPACITY 100
#include <vector>
#include "Organizmy/Organizm.h"
class Organizm;
class Swiat {
private:
    int wysokosc, szerokosc;
    std::vector<Organizm*> organizmy;
    char pola[MAX_CAPACITY][MAX_CAPACITY];
    bool zywyCzlowiek;
    void rysujSwiat();
    void uzupelnijPlansze();
    int tura;

public:
    Swiat(int wysokosc, int szerokosc);
    void wykonajTure(char *command);

    void dodajOrganizm(Organizm* organizm);
    void dodajNaUstalonePole(int x, int y, Organizm* organizm);

    int getTura();
    int iloscOrganizmow();
    void zabijczlowieka();

    bool CzyPoleJestPuste(int x, int y);
    bool CzyPoleJestPrawidlowe(int x, int y);
    Organizm* dajOrganizmZPola(int x, int y);
    int dajSileZOrganizmu(int x, int y);
    int dajInicjatyweZOrganizmu(int x, int y);
    void ZmienPozycje(int x, int y, int px, int py);
    void WyczyscPole(int x, int y);
    void zapiszDoPliku();
    void wyczyscPamiec();
};

#endif //SWIAT_H
