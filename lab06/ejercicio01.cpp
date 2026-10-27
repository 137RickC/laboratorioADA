#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    // Nodos: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, 7=H, 8=I, 9=J, 10=K
    int n = 11;
    vector<vector<pair<int, int>>> grafo(n); // (destino, costo)

    grafo[0] = { {1, 3}, {2, 5}, {3, 2} };  // A -> B, C, D
    grafo[1] = { {4, 4}, {5, 6}, {6, 5} };  // B -> E, F, G
    grafo[2] = { {4, 2}, {5, 3}, {6, 7} };  // C -> E, F, G
    grafo[3] = { {4, 6}, {5, 4}, {6, 3} };  // D -> E, F, G
    grafo[4] = { {7, 5}, {8, 3}, {9, 6} };  // E -> H, I, J
    grafo[5] = { {7, 2}, {8, 4}, {9, 3} };  // F -> H, I, J
    grafo[6] = { {7, 4}, {8, 6}, {9, 2} };  // G -> H, I, J
    grafo[7] = { {10, 4} };                 // H -> K
    grafo[8] = { {10, 5} };                 // I -> K
    grafo[9] = { {10, 3} };                 // J -> K

    vector<int> f(n, INT_MAX);
    vector<int> siguiente(n, -1);
    f[10] = 0; // B: caso base

    // T: orden topologico inverso: J, I, H, G, F, E, D, C, B, A
    for (int u = 9; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, costo = grafo[u][k].second;
            // R: relacion de recurrencia
            if (f[v] != INT_MAX && costo + f[v] < f[u]) {
                f[u] = costo + f[v];
                siguiente[u] = v;
            }
        }
    }

    string nombres[] = { 
        "A", "B", "C", 
        "D", "E", "F", 
        "G", "H", "I",
        "J", "K" 
    };

    cout << "Tabla f(nodo):" << endl;
    for (int u = n - 1; u >= 0; u--)
        cout << "  f(" << nombres[u] << ") = " << f[u] << endl;

    cout << "Costo minimo desde A hasta K: " << f[0] << endl;

    cout << "Ruta optima: ";
    int actual = 0; // O: problema original f[0]
    while (actual != -1) {
        cout << nombres[actual];
        actual = siguiente[actual];
        if (actual != -1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
