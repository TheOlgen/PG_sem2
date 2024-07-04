#include <iostream>
using namespace std;

struct Punkt {
        int x;
        int y;
};

int main() {

        int linie;
        cin >> linie;
        

        for (int i = 0; i < linie; i++)
        {
                int n, Pole = 0;
                cin >> n;
                struct Punkt* tab = new Punkt[n/2];
                for (int j = 0; j < n / 2; j++)
                {
                        cin >> tab[j].x >> tab[j].y;
                }

                for (int j = 0; j < n / 2 - 1; j++)
                {
                        Pole += tab[j].x * tab[j + 1].y - tab[j + 1].x * tab[j].y;
                        //cout << Pole <<" "<< tab[j].x << " " << tab[j].y << endl;
                }
                Pole += -tab[0].x * tab[n/2 -1].y + tab[n/2-1].x * tab[0].y;
                //Pole += p[n / 2 - 1].x * p[0].y - p[0].x * p[n / 2 - 1].y;
                //cout << Pole << endl;
                Pole /= 2;
                if (Pole < 0)
                {
                        Pole *= -1;
                }
                cout << Pole << endl;
                delete[] tab;
        }

        return 0;

}
