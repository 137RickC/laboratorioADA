#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    vector<int> demanda = { 2, 3, 2, 4 };
    int T = demanda.size();
    int MAX_PROD = 5, MAX_INV = 4;
    int costoFijo = 3, costoUnidad = 1, costoInv = 1;

    vector<vector<int>> f(T + 1, vector<int>(MAX_INV + 1, INT_MAX));
    vector<vector<int>> decision(T, vector<int>(MAX_INV + 1, -1));

    for (int s = 0; s <= MAX_INV; s++) f[T][s] = 0; // B: caso base

    for (int t = T - 1; t >= 0; t--) {
        for (int s = 0; s <= MAX_INV; s++) {
            for (int x = 0; x <= MAX_PROD; x++) {
                int resto = s + x - demanda[t];
                if (resto < 0 || resto > MAX_INV || f[t + 1][resto] == INT_MAX) continue;
                // R: costo de producir x + guardar el sobrante + resto del plan
                int costo = (x > 0 ? costoFijo + costoUnidad * x : 0) + costoInv * resto + f[t + 1][resto];
                if (costo < f[t][s]) {
                    f[t][s] = costo;
                    decision[t][s] = x;
                }
            }
        }
    }

    cout << "Costo minimo total: " << f[0][0] << endl;

    int s = 0; // O: se parte del mes 1 con almacen vacio
    for (int t = 0; t < T; t++) {
        int x = decision[t][s];
        int resto = s + x - demanda[t];
        cout << "Mes " << t + 1 << ": inventario inicial " << s << ", producir " << x
            << ", demanda " << demanda[t] << ", inventario final " << resto << endl;
        s = resto;
    }

    return 0;
}
