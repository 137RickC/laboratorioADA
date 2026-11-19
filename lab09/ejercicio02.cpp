#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

const int N = 15;
int dist[N][N];

int costoRuta(const vector<int>& ruta) {
    int c = 0;
    for (int i = 0; i + 1 < N; i++) c += dist[ruta[i]][ruta[i + 1]];
    c += dist[ruta[N - 1]][ruta[0]];
    return c;
}

int main() {
    mt19937 rng(42);
    uniform_int_distribution<int> d(10, 100);
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            dist[i][j] = dist[j][i] = d(rng);

    for (int inicio = 0; inicio < N; inicio++) {
        vector<bool> visitado(N, false);
        vector<int> ruta = { inicio };
        visitado[inicio] = true;

        for (int paso = 1; paso < N; paso++) {
            int actual = ruta.back();
            int masCercano = -1;
            int mejorDist = 1000000;
            for (int c = 0; c < N; c++) {
                if (!visitado[c] && dist[actual][c] < mejorDist) {
                    mejorDist = dist[actual][c];
                    masCercano = c;
                }
            }
            ruta.push_back(masCercano);
            visitado[masCercano] = true;
        }
        int costoNN = costoRuta(ruta);

        bool mejora = true;
        while (mejora) {
            mejora = false;
            for (int i = 1; i < N - 1; i++) {
                for (int j = i + 1; j < N; j++) {
                    vector<int> nueva = ruta;
                    reverse(nueva.begin() + i, nueva.begin() + j + 1);
                    if (costoRuta(nueva) < costoRuta(ruta)) {
                        ruta = nueva;
                        mejora = true;
                    }
                }
            }
        }

        cout << "Inicio " << inicio << ":  NN = " << costoNN
            << "   NN + 2-opt = " << costoRuta(ruta) << endl;
    }
    return 0;
}