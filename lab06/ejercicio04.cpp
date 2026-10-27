#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    // Nodos: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H
    int n = 8;
    vector<vector<pair<int, int>>> grafo(n); // (destino, costo)

    grafo[0] = { {1, 2}, {2, 4}, {3, 3} };  // A -> B, C, D
    grafo[1] = { {4, 7}, {5, 4}, {6, 6} };  // B -> E, F, G
    grafo[2] = { {4, 3}, {5, 2}, {6, 4} };  // C -> E, F, G
    grafo[3] = { {4, 4}, {5, 1}, {6, 5} };  // D -> E, F, G
    grafo[4] = { {7, 3} };                  // E -> H
    grafo[5] = { {7, 6} };                  // F -> H
    grafo[6] = { {7, 3} };                  // G -> H

    vector<int> g(n, INT_MIN); // INT_MIN: aun no se conoce camino
    vector<int> siguiente(n, -1);
    g[7] = 0; // B: caso base

    for (int u = 6; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, costo = grafo[u][k].second;
            // R: ahora se conserva el MAYOR valor
            if (g[v] != INT_MIN && costo + g[v] > g[u]) {
                g[u] = costo + g[v];
                siguiente[u] = v;
            }
        }
    }

    string nombres[] = { "A", "B", "C", "D", "E", "F", "G", "H" };

    cout << "Tabla g(nodo):" << endl;
    for (int u = n - 1; u >= 0; u--)
        cout << "  g(" << nombres[u] << ") = " << g[u] << endl;

    cout << "Costo maximo desde A hasta H: " << g[0] << endl;

    cout << "Ruta de costo maximo: ";
    int actual = 0;
    while (actual != -1) {
        cout << nombres[actual];
        actual = siguiente[actual];
        if (actual != -1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
