#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    int n = 6;
    string lugar[] = {
        "Puerta principal",
        "Biblioteca",
        "Ingenieria",
        "Comedor",
        "Centro de Computo",
        "Estadio"
    };
    vector<vector<pair<int, int>>> grafo(n);

    auto conectar =
        [&](int a, int b, int distancia) {

        grafo[a].push_back({b, distancia});
        grafo[b].push_back({a, distancia});
    };
    // Distancias en metros
    conectar(0, 1, 180);
    conectar(0, 2, 250);
    conectar(1, 2, 100);
    conectar(1, 3, 220);
    conectar(2, 4, 160);
    conectar(3, 4, 140);
    conectar(3, 5, 200);
    conectar(4, 5, 120);

    cout << "Puntos de la universidad:\n";
    for (int i = 0; i < n; i++) {
        cout << i << ". " << lugar[i] << endl;
    }

    int origen, destino;
    cout << "\nOrigen: ";
    cin >> origen;
    cout << "Destino: ";
    cin >> destino;
    vector<int> distancia(
        n,
        INT_MAX
    );
    vector<int> predecesor(
        n,
        -1
    );
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;
    distancia[origen] = 0;
    pq.push({0,origen});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > distancia[u])
            continue;

        for (auto [v, peso] : grafo[u]) {
            if (distancia[u] + peso <
                distancia[v]) {

                distancia[v] = distancia[u] + peso;

                predecesor[v] = u;

                pq.push({distancia[v], v});
            }
        }
    }

    if (distancia[destino] == INT_MAX) {
        cout << "\nNo existe ruta." << endl;
        return 0;
    }

    vector<int> ruta;
    int actual = destino;

    while (actual != -1) {
        ruta.push_back(actual);
        actual = predecesor[actual];
    }

    reverse(ruta.begin(), ruta.end());

    cout << "\nDistancia minima: " << distancia[destino] << " metros\n";

    cout << "Ruta: ";

    for (int i = 0; i < ruta.size(); i++){
        cout << lugar[ruta[i]];
        if (i < ruta.size() - 1)
            cout << " -> ";
    }

    cout << endl;
    return 0;
}