#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

vector<vector<double> > dist;

double costoRuta(const vector<int>& ruta) {
    double c = 0;
    int n = ruta.size();
    for (int i = 0; i < n; i++) c += dist[ruta[i]][ruta[(i + 1) % n]];
    return c;
}

// Heuristica constructiva: Nearest Neighbor desde la ciudad 0
vector<int> vecinoMasCercano(int n) {
    vector<bool> visitado(n, false);
    vector<int> ruta;
    ruta.push_back(0);
    visitado[0] = true;
    for (int paso = 1; paso < n; paso++) {
        int actual = ruta.back(), mejor = -1;
        for (int c = 0; c < n; c++)
            if (!visitado[c] && (mejor == -1 || dist[actual][c] < dist[actual][mejor]))
                mejor = c;
        ruta.push_back(mejor);
        visitado[mejor] = true;
    }
    return ruta;
}

// Busqueda local: 2-opt hasta llegar a un optimo local
void dosOpt(vector<int>& ruta) {
    int n = ruta.size();
    bool mejora = true;
    while (mejora) {
        mejora = false;
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                vector<int> nueva = ruta;
                reverse(nueva.begin() + i, nueva.begin() + j + 1);
                if (costoRuta(nueva) < costoRuta(ruta) - 1e-9) {
                    ruta = nueva;
                    mejora = true;
                }
            }
        }
    }
}

// Perturbacion "double-bridge": parte la ruta en A B C D y la reordena como A C B D
vector<int> perturbar(const vector<int>& ruta, mt19937& rng) {
    int n = ruta.size();
    int p1 = 1 + rng() % (n - 3);
    int p2 = p1 + 1 + rng() % (n - p1 - 2);
    int p3 = p2 + 1 + rng() % (n - p2 - 1);
    vector<int> nueva(ruta.begin(), ruta.begin() + p1);                  // A
    nueva.insert(nueva.end(), ruta.begin() + p2, ruta.begin() + p3);     // C
    nueva.insert(nueva.end(), ruta.begin() + p1, ruta.begin() + p2);     // B
    nueva.insert(nueva.end(), ruta.begin() + p3, ruta.end());            // D
    return nueva;
}

// CAMBIO: distancia real en km entre dos coordenadas (latitud, longitud) con Haversine
double haversine(pair<double, double> a, pair<double, double> b) {
    double r = M_PI / 180;
    double h = pow(sin((b.first - a.first) * r / 2), 2) +
               cos(a.first * r) * cos(b.first * r) * pow(sin((b.second - a.second) * r / 2), 2);
    return 2 * 6371 * asin(sqrt(h));
}

int main() {
    // CAMBIO: 20 capitales del Peru con coordenadas aproximadas (latitud, longitud)
    vector<string> nombre = {
        "Lima", "Ica", "Ayacucho", "Huancavelica", "Huancayo",
        "Cerro de Pasco", "Huanuco", "Huaraz", "Trujillo", "Chiclayo",
        "Piura", "Tumbes", "Cajamarca", "Chachapoyas", "Moyobamba",
        "Pucallpa", "Cusco", "Puno", "Arequipa", "Tacna"
    };
    vector<pair<double, double> > ciudad = {
        {-12.046, -77.043}, {-14.068, -75.729}, {-13.163, -74.224}, {-12.787, -74.976},
        {-12.065, -75.204}, {-10.683, -76.256}, { -9.930, -76.242}, { -9.528, -77.528},
        { -8.112, -79.029}, { -6.771, -79.841}, { -5.194, -80.632}, { -3.567, -80.451},
        { -7.164, -78.500}, { -6.231, -77.869}, { -6.034, -76.972}, { -8.379, -74.554},
        {-13.532, -71.967}, {-15.840, -70.022}, {-16.409, -71.537}, {-18.006, -70.246}
    };
    int n = ciudad.size();
    dist.assign(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = haversine(ciudad[i], ciudad[j]);

    // Solo Nearest Neighbor (para comparar)
    vector<int> rutaNN = vecinoMasCercano(n);
    cout << "Solo Nearest Neighbor: " << costoRuta(rutaNN) << " km" << endl;
    for (size_t i = 0; i < rutaNN.size(); i++) cout << nombre[rutaNN[i]] << " -> ";
    cout << nombre[rutaNN[0]] << endl << endl;

    // ILS igual que el resuelto 
    mt19937 rng(42);
    vector<int> actual = vecinoMasCercano(n);
    dosOpt(actual);
    double costoActual = costoRuta(actual);
    vector<int> mejor = actual;
    double costoMejor = costoActual;
    cout << "Optimo local inicial (NN + 2-opt): " << costoActual << " km" << endl;

    for (int it = 1; it <= 500; it++) {
        vector<int> candidata = perturbar(actual, rng);
        dosOpt(candidata);
        double costoCand = costoRuta(candidata);
        if (costoCand < costoActual - 1e-9) {
            actual = candidata;
            costoActual = costoCand;
            if (costoActual < costoMejor) {
                mejor = actual;
                costoMejor = costoActual;
                cout << "Iteracion " << it << ": nuevo mejor costo = " << costoMejor << " km" << endl;
            }
        }
    }

    cout << "\nRuta final (ILS): " << costoMejor << " km" << endl;
    for (size_t i = 0; i < mejor.size(); i++) cout << nombre[mejor[i]] << " -> ";
    cout << nombre[mejor[0]] << endl;
    cout << "Ahorro frente a solo NN: " << costoRuta(rutaNN) - costoMejor << " km ("
         << 100 * (costoRuta(rutaNN) - costoMejor) / costoRuta(rutaNN) << " %)" << endl;
    return 0;
}