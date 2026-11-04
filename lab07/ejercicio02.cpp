#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n, M;
    cout << "Cantidad de denominaciones: ";
    cin >> n;
    vector<int> moneda(n);
    cout << "Denominaciones: ";
    for (int i = 0; i < n; i++) cin >> moneda[i];
    cout << "Monto objetivo: ";
    cin >> M;

    const int INF = INT_MAX;
    vector<int> dp(M + 1, INF), usada(M + 1, -1);
    dp[0] = 0;

    for (int m = 1; m <= M; m++) {
        for (int i = 0; i < n; i++) {
            if (moneda[i] <= m && dp[m - moneda[i]] != INF && dp[m - moneda[i]] + 1 < dp[m]) {
                dp[m] = dp[m - moneda[i]] + 1;
                usada[m] = i;
            }
        }
    }

    if (dp[M] == INF) {
        cout << "No es posible formar el monto " << M << endl;
        return 0;
    }

    vector<int> cantidad(n, 0);
    for (int m = M; m > 0; m -= moneda[usada[m]])
        cantidad[usada[m]]++;

    cout << "\nMinimo de monedas: " << dp[M] << endl;
    cout << "Combinacion:" << endl;
    for (int i = 0; i < n; i++)
        if (cantidad[i] > 0)
            cout << "  " << cantidad[i] << " x " << moneda[i] << endl;
    return 0;
}