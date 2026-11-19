#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
using namespace std;

int N;                                   
vector<vector<int>> dist;

int costoRuta(const vector<int>& ruta) {
    int c = 0;
    for (int i = 0; i + 1 < N; i++) c += dist[ruta[i]][ruta[i + 1]];
    c += dist[ruta[N - 1]][ruta[0]];
    return c;
}

int main() {
    int tamanos[] = { 20, 50, 100 };

    for (int n : tamanos) {
        N = n;
        dist.assign(N, vector<int>(N, 0));
        mt19937 rng(42);
        uniform_int_distribution<int> d(10, 100);
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                dist[i][j] = dist[j][i] = d(rng);

        auto t0 = chrono::high_resolution_clock::now();   
        int inicio = 0;
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

        auto t1 = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(t1 - t0).count();

        double rutas = 1;
        for (int k = 2; k <= N - 1; k++) rutas *= k;
        rutas /= 2;
        double anios = rutas / 1e6 / (365.25 * 24 * 3600);

        cout << "n = " << N << ":  costo = " << costoRuta(ruta)
            << ",  NN + 2-opt = " << ms << " ms,  fuerza bruta = " << rutas
            << " rutas (~" << anios << " anios)" << endl;
    }
    return 0;
}