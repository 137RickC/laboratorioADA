#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>
using namespace std;

int calcularMakespan(const vector<int>& duracion, const vector<int>& asignacion, int lineas) {
    vector<int> carga(lineas, 0);
    for (int t = 0; t < (int)duracion.size(); t++)
        carga[asignacion[t]] += duracion[t];
    return *max_element(carga.begin(), carga.end());
}

int main() {
    vector<int> duracion = { 4, 3, 2, 5, 6, 1 };   
    int tareas = duracion.size();
    int lineas = 2;

    vector<int> asignacion(tareas);
    mt19937 rng(random_device{}());
    uniform_int_distribution<int> elegirLinea(0, lineas - 1);

    int mejorMakespan = INT_MAX;
    vector<int> mejorAsignacion;
    int iteraciones = 200;

    for (int it = 0; it < iteraciones; it++) {
        for (int t = 0; t < tareas; t++)
            asignacion[t] = elegirLinea(rng);

        int ms = calcularMakespan(duracion, asignacion, lineas);

        if (ms < mejorMakespan) {
            mejorMakespan = ms;
            mejorAsignacion = asignacion;
            cout << "Iteracion " << it + 1 << ": nuevo mejor makespan = " << ms << endl;
        }
    }

    cout << "\nMejor asignacion encontrada (Monte Carlo, " << iteraciones << " iter):" << endl;
    for (int l = 0; l < lineas; l++) {
        int carga = 0;
        cout << "Linea " << l + 1 << ": ";
        for (int t = 0; t < tareas; t++)
            if (mejorAsignacion[t] == l) {
                cout << "T" << t + 1 << "(" << duracion[t] << "h) ";
                carga += duracion[t];
            }
        cout << "-> " << carga << " h" << endl;
    }
    cout << "Makespan: " << mejorMakespan << " h" << endl;

    // Verificacion por fuerza bruta
    int optimo = INT_MAX;
    for (int mask = 0; mask < (1 << tareas); mask++) {
        for (int t = 0; t < tareas; t++) asignacion[t] = (mask >> t) & 1;
        optimo = min(optimo, calcularMakespan(duracion, asignacion, lineas));
    }
    cout << "Optimo real (fuerza bruta, " << (1 << tareas) << " asignaciones): "
        << optimo << " h" << endl;
    return 0;
}