#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> peso = { 1, 2, 3, 2, 4 };
    vector<int> valor = { 2, 3, 4, 4, 5 };
    int n = peso.size();
    int W = 7;

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (peso[i - 1] <= w)
                dp[i][w] = max(dp[i][w], valor[i - 1] + dp[i - 1][w - peso[i - 1]]);
        }
    }

    cout << "Tabla dp (filas = objetos 0..i, columnas = capacidad w)\n\n";
    cout << setw(8) << "i \\ w";
    for (int w = 0; w <= W; w++) cout << setw(4) << w;
    cout << "\n";
    for (int i = 0; i <= n; i++) {
        cout << setw(8) << i;
        for (int w = 0; w <= W; w++) cout << setw(4) << dp[i][w];
        cout << "\n";
    }

    cout << "\nValor maximo: dp[" << n << "][" << W << "] = " << dp[n][W] << "\n\n";
    cout << "Reconstruccion:\n";
    int w = W;
    vector<int> elegidos;
    for (int i = n; i >= 1; i--) {
        cout << "  dp[" << i << "][" << w << "] = " << dp[i][w]
            << " vs dp[" << i - 1 << "][" << w << "] = " << dp[i - 1][w];
        if (dp[i][w] != dp[i - 1][w]) {
            cout << " -> distintos: se lleva objeto " << i
                << " (peso " << peso[i - 1] << "), w = " << w << " - " << peso[i - 1]
                << " = " << w - peso[i - 1] << "\n";
            elegidos.push_back(i);
            w -= peso[i - 1];
        } else {
            cout << " -> iguales: objeto " << i << " no se lleva\n";
        }
    }
    reverse(elegidos.begin(), elegidos.end());
    cout << "\nObjetos elegidos: ";
    for (int i : elegidos) cout << i << " ";
    cout << endl;
    return 0;
}