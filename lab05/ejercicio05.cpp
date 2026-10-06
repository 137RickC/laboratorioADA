#include <iostream>
#include <vector>
#include <algorithm>
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
    string localidades[] = {
        "Arequipa",
        "Cayma",
        "Yanahuara",
        "Sachaca",
        "Tiabaya",
        "Uchumayo"
    };
    vector<Arista> aristas = {
        {0, 1, 12},
        {0, 2, 8},
        {1, 2, 5},
        {1, 3, 15},
        {2, 3, 7},
        {2, 4, 18},
        {3, 4, 6},
        {3, 5, 14},
        {4, 5, 9}
    };

    sort(aristas.begin(), aristas.end(),
        [](Arista a, Arista b) {
            return a.peso < b.peso;
        });

    padre.resize(n);
    rango.assign(n, 0);

    for (int i = 0; i < n; i++)
        padre[i] = i;

    int pesoTotal = 0;

    cout << "Red minima de distribucion de agua:\n\n";

    for (auto& a : aristas) {
        if (unir(a.u, a.v)) {
            cout << localidades[a.u]
                << " - "
                << localidades[a.v];

            cout << " (costo S/ "
                << a.peso
                << " mil)"
                << endl;

            pesoTotal += a.peso;
        }
    }

    cout << "\nCosto total de la red: S/ "
        << pesoTotal
        << " mil"
        << endl;

    return 0;
}