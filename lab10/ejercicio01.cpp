#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
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

// Perturbacion double-bridge: parte la ruta en A B C D y la reordena como A C B D
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

int main() {
    vector<pair<double, double> > ciudad = {
        {0, 0}, {3, 14}, {18, 5}, {8, 7}, {6, 2}, {10, 0},
        {4, 4}, {1, 13}, {19, 11}, {8, 14}, {2, 17}, {7, 18}
    };
    int n = ciudad.size();
    dist.assign(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = hypot(ciudad[i].first - ciudad[j].first,
                            ciudad[i].second - ciudad[j].second);

    int llegaron = 0;
    // CAMBIO: todo el ILS se repite con las semillas 1 a 10
    for (int semilla = 1; semilla <= 10; semilla++) {
        mt19937 rng(semilla);

        vector<int> actual = vecinoMasCercano(n);
        dosOpt(actual);
        double costoActual = costoRuta(actual);
        vector<int> mejor = actual;
        double costoMejor = costoActual;
        int iterMejor = 0;                        // CAMBIO: iteracion donde aparecio el mejor

        for (int it = 1; it <= 200; it++) {
            vector<int> candidata = perturbar(actual, rng);
            dosOpt(candidata);
            double costoCand = costoRuta(candidata);
            if (costoCand < costoActual - 1e-9) {
                actual = candidata;
                costoActual = costoCand;
                if (costoActual < costoMejor) {
                    mejor = actual;
                    costoMejor = costoActual;
                    iterMejor = it;
                }
            }
        }

        cout << "Semilla " << semilla << ": costo final = " << costoMejor
            << ", encontrado en la iteracion " << iterMejor << endl;
        if (costoMejor < 72.21 + 0.01) llegaron++;
    }
    cout << "\nSemillas que llegaron al optimo 72.21: " << llegaron << " de 10" << endl;
    return 0;
}