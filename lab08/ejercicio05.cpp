#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double log10RutasTSP(int n) {
    return (lgamma((double)n) - log(2.0)) / log(10.0);
}

int main() {
    int paradas[] = { 10, 15, 25, 50, 100, 120, 150 };
    double log10SegundosTierra = log10(4.5e9 * 365.25 * 24 * 3600);  // edad de la Tierra

    cout << "Paradas   Rutas distintas   Segundos de fuerza bruta (1e6 rutas/s)" << endl;
    for (int n : paradas) {
        double lr = log10RutasTSP(n + 1); 
        cout << setw(7) << n << "   ~10^" << setw(4) << left << (int)lr << right
            << "        ~10^" << (int)(lr - 6) << endl;
    }
    cout << "\nSegundos desde que existe la Tierra: ~10^" << (int)log10SegundosTierra << endl;
    cout << "Con 120 paradas hay ~10^" << (int)log10RutasTSP(121)
        << " rutas: por eso ORION usa heuristicas y no fuerza bruta." << endl;
    return 0;
}