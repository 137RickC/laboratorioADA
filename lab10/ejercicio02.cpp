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

    int valoresD[] = { 1, 2, 3, 5, 8 };           // CAMBIO: D ya no es fijo
    for (int D : valoresD) {
        double suma = 0, suma20 = 0;              // CAMBIO: tambien se mide en la iteracion 20
        int llegaron = 0;
        for (int semilla = 1; semilla <= 10; semilla++) {   // CAMBIO: 10 semillas
            mt19937 rng(semilla);

            vector<int> actual = vecinoMasCercano(n);
            double costoActual = costoRuta(actual);
            vector<int> mejor = actual;
            double costoMejor = costoActual;

            for (int it = 1; it <= 200; it++) {
                // DESTRUCCION
                vector<int> candidata = actual;
                vector<int> quitadas;
                for (int k = 0; k < D; k++) {
                    int pos = 1 + rng() % (candidata.size() - 1);
                    quitadas.push_back(candidata[pos]);
                    candidata.erase(candidata.begin() + pos);
                }
                // CONSTRUCCION
                for (size_t k = 0; k < quitadas.size(); k++)
                    insertarGoloso(candidata, quitadas[k]);

                double costoCand = costoRuta(candidata);
                if (costoCand < costoActual - 1e-9) {
                    actual = candidata;
                    costoActual = costoCand;
                    if (costoActual < costoMejor) {
                        mejor = actual;
                        costoMejor = costoActual;
                    }
                }
                if (it == 20) suma20 += costoMejor;
            }
            suma += costoMejor;
            if (costoMejor < 72.21 + 0.01) llegaron++;
        }
        cout << "d = " << D << ": promedio a las 20 iter = " << suma20 / 10
            << ", promedio a las 200 iter = " << suma / 10
            << ", llegaron al optimo " << llegaron << " de 10" << endl;
    }
    return 0;
}