#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <cstdio>
using namespace std;

vector<vector<double> > dist;

double costoRuta(const vector<int>& ruta) {
    double c = 0;
    int n = ruta.size();
    for (int i = 0; i < n; i++) c += dist[ruta[i]][ruta[(i + 1) % n]];
    return c;
}

// Heuristica constructiva: Nearest Neighbor desde la ciudad 0
vector<int> vecinoMasCercano(int n) {
    vector<bool> visitado(n, false);
    vector<int> ruta;
    ruta.push_back(0);
    visitado[0] = true;
    for (int paso = 1; paso < n; paso++) {
        int actual = ruta.back(), mejor = -1;
        for (int c = 0; c < n; c++)
            if (!visitado[c] && (mejor == -1 || dist[actual][c] < dist[actual][mejor]))
                mejor = c;
        ruta.push_back(mejor);
        visitado[mejor] = true;
    }
    return ruta;
}

// Busqueda local: 2-opt hasta llegar a un optimo local
void dosOpt(vector<int>& ruta) {
    int n = ruta.size();
    bool mejora = true;
    while (mejora) {
        mejora = false;
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                vector<int> nueva = ruta;
                reverse(nueva.begin() + i, nueva.begin() + j + 1);
                if (costoRuta(nueva) < costoRuta(ruta) - 1e-9) {
                    ruta = nueva;
                    mejora = true;
                }
            }
        }
    }
}

// Perturbacion "double-bridge": parte la ruta en A B C D y la reordena como A C B D
vector<int> perturbar(const vector<int>& ruta, mt19937& rng) {
    int n = ruta.size();
    int p1 = 1 + rng() % (n - 3);
    int p2 = p1 + 1 + rng() % (n - p1 - 2);
    int p3 = p2 + 1 + rng() % (n - p2 - 1);
    vector<int> nueva(ruta.begin(), ruta.begin() + p1);                  // A
    nueva.insert(nueva.end(), ruta.begin() + p2, ruta.begin() + p3);     // C
    nueva.insert(nueva.end(), ruta.begin() + p1, ruta.begin() + p2);     // B
    nueva.insert(nueva.end(), ruta.begin() + p3, ruta.end());            // D
    return nueva;
}

// Insercion golosa: coloca la ciudad c en la posicion donde MENOS aumenta el costo
void insertarGoloso(vector<int>& ruta, int c) {
    int n = ruta.size();
    int mejorPos = 1;
    double mejorAumento = 1e18;
    for (int pos = 1; pos <= n; pos++) {
        int a = ruta[pos - 1];
        int b = ruta[pos % n];
        double aumento = dist[a][c] + dist[c][b] - dist[a][b];
        if (aumento < mejorAumento) {
            mejorAumento = aumento;
            mejorPos = pos;
        }
    }
    ruta.insert(ruta.begin() + mejorPos, c);
}

// ILS del ejercicio resuelto (CAMBIO: en una funcion, sin imprimir cada mejora)
double ils(int n, int iteraciones, mt19937& rng) {
    vector<int> actual = vecinoMasCercano(n);
    dosOpt(actual);
    double costoActual = costoRuta(actual);
    double costoMejor = costoActual;
    for (int it = 1; it <= iteraciones; it++) {
        vector<int> candidata = perturbar(actual, rng);
        dosOpt(candidata);
        double costoCand = costoRuta(candidata);
        if (costoCand < costoActual - 1e-9) {
            actual = candidata;
            costoActual = costoCand;
            if (costoActual < costoMejor) costoMejor = costoActual;
        }
    }
    return costoMejor;
}

// IG del ejercicio resuelto (CAMBIO: en una funcion, sin imprimir cada mejora)
double ig(int n, int iteraciones, int D, mt19937& rng) {
    vector<int> actual = vecinoMasCercano(n);
    double costoActual = costoRuta(actual);
    double costoMejor = costoActual;
    for (int it = 1; it <= iteraciones; it++) {
        vector<int> candidata = actual;
        vector<int> quitadas;
        for (int k = 0; k < D; k++) {
            int pos = 1 + rng() % (candidata.size() - 1);
            quitadas.push_back(candidata[pos]);
            candidata.erase(candidata.begin() + pos);
        }
        for (size_t k = 0; k < quitadas.size(); k++)
            insertarGoloso(candidata, quitadas[k]);
        double costoCand = costoRuta(candidata);
        if (costoCand < costoActual - 1e-9) {
            actual = candidata;
            costoActual = costoCand;
            if (costoActual < costoMejor) costoMejor = costoActual;
        }
    }
    return costoMejor;
}

int main() {
    // CAMBIO: 50 ciudades con coordenadas aleatorias entre 0 y 100 (semilla fija)
    int n = 50;
    mt19937 gen(2026);
    vector<pair<double, double> > ciudad(n);
    for (int i = 0; i < n; i++) ciudad[i] = { (double)(gen() % 101), (double)(gen() % 101) };
    dist.assign(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = hypot(ciudad[i].first - ciudad[j].first,
                            ciudad[i].second - ciudad[j].second);

    mt19937 rng(42);
    double costo[5], ms[5];
    string nombre[5] = { "Nearest Neighbor", "NN + 2-opt", "ILS (500 iter)", "IG d=3 (500 iter)",
                         "IG d=3 (300000 iter)" };   // extra: IG con un tiempo parecido al de ILS

    for (int m = 0; m < 5; m++) {
        auto t0 = chrono::high_resolution_clock::now();
        if (m == 0) costo[m] = costoRuta(vecinoMasCercano(n));
        if (m == 1) { vector<int> r = vecinoMasCercano(n); dosOpt(r); costo[m] = costoRuta(r); }
        if (m == 2) costo[m] = ils(n, 500, rng);
        if (m == 3) costo[m] = ig(n, 500, 3, rng);
        if (m == 4) costo[m] = ig(n, 300000, 3, rng);
        auto t1 = chrono::high_resolution_clock::now();
        ms[m] = chrono::duration<double, milli>(t1 - t0).count();
    }

    cout << "Metodo               Costo     Tiempo (ms)   Mejora vs NN+2-opt" << endl;
    for (int m = 0; m < 5; m++) {
        printf("%-21s %8.2f   %10.2f    %6.2f %%\n", nombre[m].c_str(), costo[m], ms[m],
               100.0 * (costo[1] - costo[m]) / costo[1]);
    }
    return 0;
}