#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

void mostrarRuta(int destino, const vector<int>& predecesor,
    string nombres[]) {

    vector<int> ruta;
    int actual = destino;

    while (actual != -1) {
        ruta.push_back(actual);
        actual = predecesor[actual];
    }

    reverse(ruta.begin(), ruta.end());
    for (int i = 0; i < ruta.size(); i++) {
        cout << nombres[ruta[i]];
        if (i < ruta.size() - 1)
            cout << " -> ";
    }
}

int main() {
    int n = 6;
    vector<vector<pair<int, int>>> grafo(n);

    auto agregarArista =
        [&](int u, int v, int peso) {

        grafo[u].push_back({v, peso});
        grafo[v].push_back({u, peso});
    };

    agregarArista(0, 1, 4);
    agregarArista(0, 2, 2);
    agregarArista(1, 2, 1);
    agregarArista(1, 3, 5);
    agregarArista(2, 3, 8);
    agregarArista(2, 4, 10);
    agregarArista(3, 4, 2);
    agregarArista(3, 5, 6);
    agregarArista(4, 5, 3);

    vector<int> dist(n, INT_MAX);
    vector<int> predecesor(n, -1);

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    int origen = 0;

    dist[origen] = 0;

    pq.push({0, origen});

    while (!pq.empty()) {

        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto [v, peso] : grafo[u]) {

            if (dist[u] + peso < dist[v]) {

                dist[v] = dist[u] + peso;

                predecesor[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

    string nombres[] = {
        "A", "B", "C", "D", "E", "F"
    };

    cout << "Caminos mas cortos desde A:\n\n";

    for (int i = 0; i < n; i++) {

        cout << "Destino: " << nombres[i] << endl;
        cout << "Distancia: "
             << dist[i] << endl;

        cout << "Ruta: ";
        mostrarRuta(i, predecesor, nombres);

        cout << "\n\n";
    }

    return 0;
}