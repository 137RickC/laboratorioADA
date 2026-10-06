#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Arista {
    int u, v, peso;
};
vector<int> padre, rango;

int encontrar(int x) {
    if (padre[x] != x)
        padre[x] = encontrar(padre[x]);

    return padre[x];
}

bool unir(int x, int y) {
    int rx = encontrar(x);
    int ry = encontrar(y);

    if (rx == ry)
        return false;

    if (rango[rx] < rango[ry])
        swap(rx, ry);

    padre[ry] = rx;

    if (rango[rx] == rango[ry])
        rango[rx]++;

    return true;
}

int main() {
    int n = 6;
    vector<Arista> aristas = {
        {0, 1, 4},
        {0, 2, 2},
        {1, 2, 1},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 3}
    };

    string nombres[] = {
        "A", "B", "C", "D", "E", "F"
    };

    // KRUSKAL
    sort(aristas.begin(), aristas.end(),
        [](Arista a, Arista b) {
            return a.peso < b.peso;
        });

    padre.resize(n);
    rango.assign(n, 0);

    for (int i = 0; i < n; i++)
        padre[i] = i;

    int pesoKruskal = 0;

    cout << "KRUSKAL" << endl;

    for (auto& a : aristas) {
        if (unir(a.u, a.v)) {
            cout << nombres[a.u] << " - ";
            cout << nombres[a.v];
            cout << " (peso " << a.peso << ")" << endl;

            pesoKruskal += a.peso;
        }
    }

    cout << "Peso total: " << pesoKruskal << endl;

    // PRIM
    vector<vector<pair<int, int>>> grafo(n);

    for (auto& a : aristas) {
        grafo[a.u].push_back({a.v, a.peso});
        grafo[a.v].push_back({a.u, a.peso});
    }

    vector<bool> enArbol(n, false);

    // peso, {vertice, padre}
    priority_queue<
        pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>,
        greater<pair<int, pair<int, int>>>
    > pq;

    pq.push({0, {0, -1}});

    int pesoPrim = 0;

    cout << "\nPRIM " << endl;

    while (!pq.empty()) {
        int peso = pq.top().first;
        int u = pq.top().second.first;
        int anterior = pq.top().second.second;

        pq.pop();

        if (enArbol[u])
            continue;

        enArbol[u] = true;
        pesoPrim += peso;

        if (anterior != -1) {
            cout << nombres[anterior]
                << " - "
                << nombres[u]
                << " (peso "
                << peso
                << ")"
                << endl;
        }

        for (auto [v, p] : grafo[u]) {
            if (!enArbol[v])
                pq.push({p, {v, u}});
        }
    }

    cout << "Peso total: " << pesoPrim << endl;

    cout << "\nCOMPARACION" << endl;

    if (pesoKruskal == pesoPrim)
        cout << "Ambos algoritmos obtienen el mismo peso minimo." << endl;
    else
        cout << "Los resultados son diferentes." << endl;

    return 0;
}