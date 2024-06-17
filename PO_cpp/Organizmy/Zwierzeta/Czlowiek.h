//
// Created by olgar on 23.04.2024.
//

#ifndef UNTITLED1_CZLOWIEK_H
#define UNTITLED1_CZLOWIEK_H

#define SILA_CZLOWIEKA 5
#define INICJATYWA_CZLOWIEKA 4

#include "Zwierze.h"

class Czlowiek :
        public Zwierze{
private:
    int silaNormalna;
    int licznikTury;

public:
    Czlowiek(Swiat& swiat, int x, int y);

    ~Czlowiek() override;
    std::string GetNazwa() override;
    bool WybierzPola(int *px, int* py, char command);
    bool Unik(Organizm* atakujacy, Organizm* zaatakowany) override;
    void Akcja(char command) override;
    Organizm *dziecko(int x, int y) override;
    void Umrzyj(Organizm * zabijajacy);
    void supermoc();
    void SetSila(int dodajsile);

};



#endif //UNTITLED1_CZLOWIEK_H
