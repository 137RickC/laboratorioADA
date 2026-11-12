#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
using namespace std;

// Costo de la ruta 
int costoRuta(const vector<vector<int>>& dist, const vector<int>& ciudades) {
    int costo = dist[0][ciudades[0]];
    for (int i = 0; i < (int)ciudades.size() - 1; i++)
        costo += dist[ciudades[i]][ciudades[i + 1]];
    costo += dist[ciudades.back()][0];
    return costo;
}

// Fuerza bruta 
int fuerzaBruta(const vector<vector<int>>& dist, vector<int> ciudades) {
    int mejorCosto = INT_MAX;
    sort(ciudades.begin(), ciudades.end());
    do {
        mejorCosto = min(mejorCosto, costoRuta(dist, ciudades));
    } while (next_permutation(ciudades.begin(), ciudades.end()));
    return mejorCosto;
}

// Monte Carlo
int monteCarlo(const vector<vector<int>>& dist, vector<int> ciudades,
            int iteraciones, mt19937& rng, vector<int>& mejorRuta) {
    int mejorCosto = INT_MAX;
    for (int it = 0; it < iteraciones; it++) {
        shuffle(ciudades.begin(), ciudades.end(), rng);
        int costo = costoRuta(dist, ciudades);
        if (costo < mejorCosto) {
            mejorCosto = costo;
            mejorRuta = ciudades;
        }
    }
    return mejorCosto;
}

int main() {
    int n = 10;

    mt19937 gen(42);
    uniform_int_distribution<int> d(10, 100);
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            dist[i][j] = dist[j][i] = d(gen);

    vector<int> ciudades;
    for (int i = 1; i < n; i++) ciudades.push_back(i);

    int optimo = fuerzaBruta(dist, ciudades);
    cout << "Optimo real (fuerza bruta): " << optimo << endl << endl;

    mt19937 rng(random_device{}());
    vector<int> pruebas = { 100, 1000, 10000 };
    int corridas = 30;  

    for (int iter : pruebas) {
        vector<int> mejorRuta;
        int costo = monteCarlo(dist, ciudades, iter, rng, mejorRuta);
        double brecha = 100.0 * (costo - optimo) / optimo;

        cout << "Monte Carlo con " << iter << " iteraciones " << endl;
        cout << "Mejor ruta: 0 -> ";
        for (int c : mejorRuta) cout << c << " -> ";
        cout << "0" << endl;
        cout << "Costo: " << costo << "  (" << brecha << " % sobre el optimo)" << endl;

        // Promedio de varias corridas y cuantas veces llego al optimo
        double suma = 0; int aciertos = 0;
        for (int r = 0; r < corridas; r++) {
            vector<int> tmp;
            int c = monteCarlo(dist, ciudades, iter, rng, tmp);
            suma += c;
            if (c == optimo) aciertos++;
        }
        double prom = suma / corridas;
        cout << "Promedio en " << corridas << " corridas: " << prom
            << "  (" << 100.0 * (prom - optimo) / optimo << " % sobre el optimo)"
            << ", llego al optimo " << aciertos << "/" << corridas << " veces" << endl << endl;
    }
    return 0;
}