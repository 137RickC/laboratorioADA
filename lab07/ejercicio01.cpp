#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, W;
    cout << "Cantidad de objetos (minimo 8): ";
    cin >> n;
    while (n < 8) {
        cout << "Debe ingresar al menos 8 objetos: ";
        cin >> n;
    }
    vector<int> peso(n), valor(n);
    for (int i = 0; i < n; i++) {
        cout << "Objeto " << i + 1 << " (peso valor): ";
        cin >> peso[i] >> valor[i];
    }
    cout << "Capacidad de la mochila: ";
    cin >> W;

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (peso[i - 1] <= w)
                dp[i][w] = max(dp[i][w], valor[i - 1] + dp[i - 1][w - peso[i - 1]]);
        }
    }

    vector<int> elegidos;
    int w = W;
    for (int i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            elegidos.push_back(i);
            w -= peso[i - 1];
        }
    }
    reverse(elegidos.begin(), elegidos.end());
    cout << "\nValor maximo: " << dp[n][W] << endl;
    cout << "Objetos elegidos:" << endl;
    int pesoTotal = 0;
    for (int i : elegidos) {
        cout << "  Objeto " << i << " (peso " << peso[i - 1] << ", valor " << valor[i - 1] << ")" << endl;
        pesoTotal += peso[i - 1];
    }
    cout << "Peso total usado: " << pesoTotal << " / " << W << endl;
    return 0;
}