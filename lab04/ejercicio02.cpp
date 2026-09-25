#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

const int INF = 1e9;//valor mas grande representando infinito

class GrafoFWarshall {
private:
    int V;
    vector<string> nombresVertices;
    vector<vector<int>> dist;
    vector<vector<int>> pred;
public:
    GrafoFWarshall(const vector<string>& vertices){
        nombresVertices = vertices;
        V = vertices.size();

        dist = vector<vector<int>>(V, vector<int>(V, INF));
        pred = vector<vector<int>>(V, vector<int>(V, -1));
        
        for(int i=0 ; i<V ; i++){
            dist[i][i] = 0;
            pred[i][i] = i;
        }
    }
    void agregarArista(int u, int v, int peso){
        dist[u][v] = peso;
        pred[u][v] = u;

    }
};  