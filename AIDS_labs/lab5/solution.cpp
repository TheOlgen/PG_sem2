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
        bool cycle_exists = true;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = j + 1; k < size; k++) {
                    for (int l = k + 1; l < size; l++) {
                        if (matrix[i][j]=='1') {
                            if (matrix[i][k] == '1') {
                                if (matrix[i][l] == '1') {
                                    if (matrix[j][l] == '0') {
                                        if (matrix[j][k] == '0') {
                                            if (matrix[k][l] == '0') {
                                                cycle_exists = false;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << (cycle_exists ? "1" : "0") << endl;
    }

    return 0;
}
