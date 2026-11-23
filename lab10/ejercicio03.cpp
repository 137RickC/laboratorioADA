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

// CAMBIO: el ILS resuelto pasado a una funcion; probPeor = probabilidad de aceptar una peor
double ils(int n, int semilla, int iteraciones, double probPeor) {
    mt19937 rng(semilla);
    uniform_real_distribution<double> azar(0.0, 1.0);

    vector<int> actual = vecinoMasCercano(n);
    dosOpt(actual);
    double costoActual = costoRuta(actual);
    vector<int> mejor = actual;
    double costoMejor = costoActual;

    for (int it = 1; it <= iteraciones; it++) {
        vector<int> candidata = perturbar(actual, rng);
        dosOpt(candidata);
        double costoCand = costoRuta(candidata);
        // CAMBIO: se acepta si mejora O, con probabilidad probPeor, aunque sea peor
        if (costoCand < costoActual - 1e-9 || azar(rng) < probPeor) {
            actual = candidata;
            costoActual = costoCand;
        }
        if (costoActual < costoMejor) {           // la mejor se guarda siempre
            mejor = actual;
            costoMejor = costoActual;
        }
    }
    return costoMejor;
}

// Compara ambos criterios con varias semillas
void comparar(int n, int iteraciones, int semillas) {
    double sumaSolo = 0, sumaProb = 0;
    int ganaProb = 0, ganaSolo = 0;
    for (int semilla = 1; semilla <= semillas; semilla++) {
        double a = ils(n, semilla, iteraciones, 0.0);    // "solo si mejora"
        double b = ils(n, semilla, iteraciones, 0.05);   // acepta peores con 5 %
        sumaSolo += a; sumaProb += b;
        if (b < a - 1e-9) ganaProb++;
        if (a < b - 1e-9) ganaSolo++;
    }
    cout << "  Solo si mejora: promedio = " << sumaSolo / semillas << endl;
    cout << "  Peor con 5 %:   promedio = " << sumaProb / semillas << endl;
    cout << "  Gana 'peor con 5 %' en " << ganaProb << " semillas, 'solo si mejora' en "
        << ganaSolo << ", empatan en " << semillas - ganaProb - ganaSolo << endl;
}

int main() {
    // Caso 1: el TSP de 12 ciudades del ejercicio resuelto
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

    cout << "TSP de 12 ciudades, 20 iteraciones, 30 semillas:" << endl;
    comparar(n, 20, 30);

    // Caso 2: un TSP mas dificil de 50 ciudades al azar
    n = 50;
    mt19937 gen(2026);
    ciudad.assign(n, { 0, 0 });
    for (int i = 0; i < n; i++) ciudad[i] = { (double)(gen() % 101), (double)(gen() % 101) };
    dist.assign(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = hypot(ciudad[i].first - ciudad[j].first,
                            ciudad[i].second - ciudad[j].second);
    cout << "\nTSP de 50 ciudades, 30 iteraciones, 10 semillas:" << endl;
    comparar(n, 30, 10);
    return 0;
}