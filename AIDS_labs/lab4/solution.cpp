#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (int t = 0; t < n; ++t) {
        int size;
        cin >> size;

        vector<vector<char>> matrix(size, vector<char>(size));

        // Wczytaj macierz sąsiedztwa
        getchar();
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = getchar();
            }
        }
        getchar();

        // Sprawdź czy istnieje cykl
        int count;
        bool cycle_exists = true;
        for (int i = 0; i < size; ++i) {
            count = 0;
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] == '1') {
                    count++;
                }
            }
            if (count != 2)
                cycle_exists = false;
        }

        if (cycle_exists) {
            int j = 0, i = 0, tmp;
            count = 0;
            while (matrix[i][j] != '1') {
                j++;
            }
            while (matrix[i][j] == '1') {
                matrix[i][j] = '0';
                count++;
                if (matrix[j][i] == '1') {
                    tmp = i;
                    i = j;
                    j = tmp;
                }
                else {
                    j = 0;
                    while (j < size && matrix[i][j] != '1') {
                        j++;
                    }
                }
                if (j == size){
                    j--;
                    break;
                }
            }
            if (count/2 != size)
                cycle_exists = false;
        }
        cout << (cycle_exists ? "1" : "0") << endl;
    }

    return 0;
}
