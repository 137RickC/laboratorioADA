#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mochila2D(const vector<int>& peso, const vector<int>& valor, int W, size_t& bytes) {
    int n = peso.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (peso[i - 1] <= w)
                dp[i][w] = max(dp[i][w], valor[i - 1] + dp[i - 1][w - peso[i - 1]]);
        }
    bytes = (n + 1) * (W + 1) * sizeof(int);
    return dp[n][W];
}

int mochila1D(const vector<int>& peso, const vector<int>& valor, int W, size_t& bytes, bool derechaIzquierda) {
    int n = peso.size();
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; i++) {
        if (derechaIzquierda) {
            for (int w = W; w >= peso[i]; w--)
                dp[w] = max(dp[w], valor[i] + dp[w - peso[i]]);
        } else {
            for (int w = peso[i]; w <= W; w++)
                dp[w] = max(dp[w], valor[i] + dp[w - peso[i]]);
        }
    }
    bytes = (W + 1) * sizeof(int);
    return dp[W];
}

int main() {
    vector<int> peso = { 1, 2, 3 };
    vector<int> valor = { 2, 3, 4 };
    int W = 4;
    size_t b2, b1, bMal;

    int r2 = mochila2D(peso, valor, W, b2);
    int r1 = mochila1D(peso, valor, W, b1, true);
    int rMal = mochila1D(peso, valor, W, bMal, false);

    cout << "Ejemplo de la guia (n = 3, W = 4)\n";
    cout << "  2D dp[n+1][W+1]           -> valor " << r2 << ", memoria " << b2 << " bytes\n";
    cout << "  1D derecha a izquierda    -> valor " << r1 << ", memoria " << b1 << " bytes\n";
    cout << "  1D izquierda a derecha    -> valor " << rMal << " (incorrecto: repite objetos)\n\n";

    int n = 100, Wg = 10000;
    vector<int> p(n), v(n);
    for (int i = 0; i < n; i++) { p[i] = 1 + (i * 37) % 97; v[i] = 1 + (i * 53) % 89; }
    r2 = mochila2D(p, v, Wg, b2);
    r1 = mochila1D(p, v, Wg, b1, true);
    cout << "Caso grande (n = " << n << ", W = " << Wg << ")\n";
    cout << "  2D -> valor " << r2 << ", memoria " << b2 / 1024.0 << " KB\n";
    cout << "  1D -> valor " << r1 << ", memoria " << b1 / 1024.0 << " KB\n";
    cout << "  Ahorro: " << (double)b2 / b1 << " veces menos memoria\n";
    return 0;
}