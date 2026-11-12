#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
#include <chrono>
using namespace std;

int main() {
    int n = 10;

    // Generar la matriz de distancias aleatoria 
    mt19937 rng(42);
    uniform_int_distribution<int> d(10, 100);
    vector<vector<int>> dist(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            dist[i][j] = dist[j][i] = d(rng);

    cout << "Matriz de distancias:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << dist[i][j] << "\t";
        cout << endl;
    }

    vector<int> ciudades;
    for (int i = 1; i < n; i++) ciudades.push_back(i);

    int mejorCosto = INT_MAX;
    vector<int> mejorRuta;
    long long rutasRevisadas = 0;

    auto inicio = chrono::high_resolution_clock::now();

    sort(ciudades.begin(), ciudades.end());
    do {
        int costo = dist[0][ciudades[0]];
        for (int i = 0; i < (int)ciudades.size() - 1; i++)
            costo += dist[ciudades[i]][ciudades[i + 1]];
        costo += dist[ciudades.back()][0];
        rutasRevisadas++;

        if (costo < mejorCosto) {
            mejorCosto = costo;
            mejorRuta = ciudades;
        }
    } while (next_permutation(ciudades.begin(), ciudades.end()));

    auto fin = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(fin - inicio).count();

    cout << "\nRuta optima (fuerza bruta): 0 -> ";
    for (int c : mejorRuta) cout << c << " -> ";
    cout << "0" << endl;
    cout << "Costo optimo: " << mejorCosto << endl;
    cout << "Permutaciones revisadas: " << rutasRevisadas << endl;
    cout << "Tiempo: " << ms << " ms" << endl;
    return 0;
}