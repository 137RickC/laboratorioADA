#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    ofstream csv("crecimiento.csv");            
    csv << "n,asignacion_n!,tsp_(n-1)!/2" << endl;

    cout << setw(4) << "n" << setw(18) << "Asignacion n!"
        << setw(18) << "TSP (n-1)!/2" << setw(10) << "Razon" << endl;

    long double fact = 1;                       
    for (int n = 1; n <= 25; n++) {
        long double factAnterior = fact;        
        fact *= n;                              
        long double asignacion = fact;
        long double tsp = factAnterior / 2;
        if (n < 3) continue;                    

        cout << setw(4) << n << scientific << setprecision(3)
            << setw(18) << (double)asignacion << setw(18) << (double)tsp
            << fixed << setprecision(0) << setw(10) << (double)(asignacion / tsp) << endl;
        csv << n << "," << scientific << setprecision(6)
            << (double)asignacion << "," << (double)tsp << endl;
    }
    csv.close();

    cout << "\nGrafica (escala log10)   A = asignacion n!   T = TSP (n-1)!/2" << endl;
    long double f = 1;
    for (int n = 1; n <= 25; n++) {
        long double fAnt = f; f *= n;
        if (n < 3) continue;
        int la = (int)log10((double)f);
        int lt = (int)log10((double)(fAnt / 2));
        cout << setw(3) << n << " A |" << string(la, '#') << " 10^" << la << endl;
        cout << "    T |" << string(lt, '=') << " 10^" << lt << endl;
    }
    cout << "\nDatos guardados en crecimiento.csv" << endl;
    return 0;
}