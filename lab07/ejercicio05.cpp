#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Compra {
    string nombre;
    int costo;
    int beneficio;
};

int main() {
    int presupuesto = 3000;
    vector<Compra> lista = {
        {"Laptop",             1500, 90},
        {"Monitor",             600, 40},
        {"Silla ergonomica",    450, 35},
        {"Teclado mecanico",    200, 15},
        {"Disco SSD",           300, 30},
        {"Audifonos",           250, 12},
        {"Curso online",        400, 45},
        {"Impresora",           700, 25}
    };
    int n = lista.size();

    vector<vector<int>> dp(n + 1, vector<int>(presupuesto + 1, 0));
    for (int i = 1; i <= n; i++) {
        int c = lista[i - 1].costo, b = lista[i - 1].beneficio;
        for (int p = 0; p <= presupuesto; p++) {
            dp[i][p] = dp[i - 1][p];
            if (c <= p)
                dp[i][p] = max(dp[i][p], b + dp[i - 1][p - c]);
        }
    }

    vector<int> elegidos;
    int p = presupuesto;
    for (int i = n; i >= 1; i--) {
        if (dp[i][p] != dp[i - 1][p]) {
            elegidos.push_back(i - 1);
            p -= lista[i - 1].costo;
        }
    }
    reverse(elegidos.begin(), elegidos.end());

    int gasto = 0;
    cout << "Presupuesto: S/ " << presupuesto << "\n\nCompras recomendadas:\n";
    for (int i : elegidos) {
        cout << "  - " << lista[i].nombre << " (costo S/ " << lista[i].costo
            << ", beneficio " << lista[i].beneficio << ")\n";
        gasto += lista[i].costo;
    }
    cout << "\nBeneficio total: " << dp[n][presupuesto] << endl;
    cout << "Gasto total: S/ " << gasto << "  (sobra S/ " << presupuesto - gasto << ")" << endl;
    return 0;
}