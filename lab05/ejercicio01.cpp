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
    int n, m;

    cout << "Numero de edificios: ";
    cin >> n;

    cout << "Numero de conexiones: ";
    cin >> m;

    vector<Arista> aristas;

    for (int i = 0; i < m; i++) {
        Arista a;
        cout << "\nConexion " << i + 1 << endl;
        cout << "Edificio origen: ";
        cin >> a.u;

        cout << "Edificio destino: ";
        cin >> a.v;

        cout << "Costo: ";
        cin >> a.peso;

        aristas.push_back(a);
    }

    sort(aristas.begin(), aristas.end(),
        [](Arista a, Arista b) {
            return a.peso < b.peso;
        });

    padre.resize(n);
    rango.assign(n, 0);

    for (int i = 0; i < n; i++)
        padre[i] = i;

    int pesoTotal = 0;
    int cantidad = 0;

    cout << "\nAristas seleccionadas:\n";

    for (auto& a : aristas) {
        if (unir(a.u, a.v)) {
            cout << a.u << " - " << a.v;
            cout << " (costo " << a.peso << ")" << endl;

            pesoTotal += a.peso;
            cantidad++;

            if (cantidad == n - 1)
                break;
        }
    }

    cout << "\nCosto total de la red: "
        << pesoTotal << endl;

    return 0;
}