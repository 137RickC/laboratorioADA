#include <iostream>
#include <vector>
#include <climits>
using namespace std;

string nombres[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
vector<vector<int>> siguientes; // todos los vecinos que logran f(u)

// Recorre todas las decisiones optimas e imprime cada camino completo
void imprimirCaminos(int u, vector<int>& camino) {
    camino.push_back(u);
    if (siguientes[u].empty()) {
        for (size_t i = 0; i < camino.size(); i++) {
            cout << nombres[camino[i]];
            if (i + 1 < camino.size()) cout << " -> ";
        }
        cout << endl;
    } else {
        for (int v : siguientes[u])
            imprimirCaminos(v, camino);
    }
    camino.pop_back();
}

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

    vector<int> f(n, INT_MAX);
    siguientes.assign(n, vector<int>());
    f[7] = 0;

    for (int u = 6; u >= 0; u--) {
        for (size_t k = 0; k < grafo[u].size(); k++) {
            int v = grafo[u][k].first, costo = grafo[u][k].second;
            if (f[v] == INT_MAX) continue;
            if (costo + f[v] < f[u]) {
                // nuevo minimo: se descartan las decisiones anteriores
                f[u] = costo + f[v];
                siguientes[u] = { v };
            } else if (costo + f[v] == f[u]) {
                // empate: se guarda tambien esta decision
                siguientes[u].push_back(v);
            }
        }
    }

    cout << "Costo minimo desde A hasta H: " << f[0] << endl;
    cout << "Caminos optimos:" << endl;
    vector<int> camino;
    imprimirCaminos(0, camino);

    return 0;
}
