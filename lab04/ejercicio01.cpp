#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

class GrafoCiudades {
private:
    int numCiudades;
    vector<string> nombresCiudades;
    map<string, int> ciudadIndice;
    vector<vector<int>> matrizAdyacencia;
public:
    GrafoCiudades(const vector<string>& ciudades) {
        numCiudades = ciudades.size();
        nombresCiudades = ciudades;
        matrizAdyacencia.resize(numCiudades, vector<int>(numCiudades, INT_MAX));
        for (int i = 0; i < numCiudades; ++i) {
            ciudadIndice[ciudades[i]] = i;
            matrizAdyacencia[i][i] = 0; // Distancia a sí misma es 0
        }

    }
    void agregarCarretera(const string& origen, const string& destino, int distancia){
        if(ciudadIndice.find(origen) == ciudadIndice.end() || ciudadIndice.find(destino) == ciudadIndice.end()){
            cout << "Una de las ciudades no existe en el grafo.\n";
            return;
        }
        int u = ciudadIndice[origen];
        int v = ciudadIndice[destino];
        matrizAdyacencia[u][v] = distancia;
        matrizAdyacencia[v][u] = distancia; // Grafo no dirigido
    }
    void dijkstra(const string& origenStr, const string& destinoStr){
        if(ciudadIndice.find(origenStr) == ciudadIndice.end() || ciudadIndice.find(destinoStr) == ciudadIndice.end()){
            cout << "Una de las ciudades no existe en el grafo.\n";
            return;
        }  
        int origen = ciudadIndice[origenStr];
        int destino = ciudadIndice[destinoStr];
        
        vector<int> dist(numCiudades, INT_MAX);
        vector<bool> visitado(numCiudades, false);
        vector<int> padre(numCiudades, -1); 

        dist[origen] = 0;
        //MATRIZ DE ADYACENCIA CON DIJKSTRA
        for(int i=0 ; i<numCiudades-1; i++){
            int u = -1;
            int minDist = INT_MAX;   
            for(int j=0; j<numCiudades; j++){
                if(!visitado[j] && dist[j] < minDist){
                    minDist = dist[j];
                    u = j;
                }
            }
            if(u == -1) break; // No hay más nodos alcanzables
            visitado[u] = true;
            for(int v=0; v<numCiudades; v++){
                if(!visitado[v] && matrizAdyacencia[u][v] != INT_MAX ){
                    if(dist[u] + matrizAdyacencia[u][v] < dist[v]){
                        dist[v] = dist[u] + matrizAdyacencia[u][v];
                        padre[v] = u;
                    }
                }
            }
        }
        if(dist[destino] == INT_MAX){
            cout << "No hay camino desde " << origenStr << " hasta " << destinoStr << ".\n";
            return;
        }
        cout << "Distancia minima desde " << origenStr << " hasta " << destinoStr << ": " << dist[destino] << endl;
        vector<int> camino;//guarda los indices
        for(int v = destino; v != -1; v = padre[v]){
            camino.push_back(v);
        }
        reverse(camino.begin(), camino.end());
        cout << "Caminoa seguir: ";
        for(int i = 0; i < camino.size(); i++){
            cout << nombresCiudades[camino[i]];
            if(i < camino.size() - 1){
                cout << " -> ";
            }
        }
        cout << endl;
    } 
};
int main(){
    vector<string> ciudades = {"A", "B", "C", "D", "E"};
    GrafoCiudades mapa(ciudades);

    mapa.agregarCarretera("A", "B", 4);
    mapa.agregarCarretera("A", "C", 2);
    mapa.agregarCarretera("B", "C", 5);
    mapa.agregarCarretera("B", "D", 10);
    mapa.agregarCarretera("C", "D", 3);
    mapa.agregarCarretera("D", "E", 1);
     
    string origen, destino;
    cout << "Ingrese la ciudad de origen: ";
    cin >> origen;
    cout << "Ingrese la ciudad de destino: ";
    cin >> destino;

    mapa.dijkstra(origen, destino);
    return 0;
};
