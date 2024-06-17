//
// Created by olgar on 20.04.2024.
//

#ifndef UNTITLED1_ORGANIZM_H
#define UNTITLED1_ORGANIZM_H
#include <string>
#include "../Swiat.h"
//
class Swiat;
class Organizm {

protected:
    int x, y; //zmienne położenia
    char symbol;
    bool zyje;
    int sila;
    int inicjatywa;
    Swiat &swiat;


public:

    //Konstruktor i destruktor
    Organizm(Swiat &swiat, int x, int y, const int inicjatywa, const int sila, const char symbol);
    virtual ~Organizm();

    // getery i setery
    int GetX() const;
    int GetY() const;
    void SetPozycja(int x, int y);
    int GetInicjatywa() const;
    char GetSymbol();
    int GetSila() const;
2
    virtual std::string GetNazwa() = 0;
    bool CzyZywy() const;    //zwraca czy organizm jest żywy


    //działanie klasy
    virtual void Akcja(char command) = 0; //różna w zależności od organizmu
    void Naysowanie();
    virtual void Umrzyj(Organizm * zabijajacy);
    virtual void RuszSie(int px, int py); //zmiana położenia
    virtual bool LosujPola(int *x, int* y);


    //funkcje kolizyjne i pokolizyjne
    virtual bool Kolizja(Organizm * zaatakowany) = 0; //zwaraca true jeżeli zaatakowany umarł
                                                    //zwrara false jeżeli this umarł albo zrobił dzieci albo zrobil unik
    virtual bool Unik(Organizm* atakujacy, Organizm* zaatakowany) = 0;
    virtual bool CzyTenSamGatunek(Organizm *drugi); //zwraca true jeżeli spotkały się 2 organizmy tego samego gatunku
    virtual void ZrobDzieci(const int &x, const int &y) = 0; //Zwraca organizm swojego typu np wilka czy mlecza
    virtual Organizm *dziecko(int x, int y) = 0;

};


#endif //UNTITLED1_ORGANIZM_H
