#pragma once
#include <iostream>
using namespace std;

template<class T> class Edge;
template<class T> class Node;

template<class T>
class Node {
public:
    T data;
    Node<T>* next;     
    Edge<T>* edges;    

    Node(T val) : data(val), next(nullptr), edges(nullptr) {}

    void addEdge(Node<T>* destination, int weight);
    void printEdges();
};


template<class T>
class Edge {
public:
    Node<T>* dest;     
    int weight;        
    Edge<T>* next;     

    Edge(Node<T>* d, int w) : dest(d), weight(w), next(nullptr) {}
};


template<class T>
void Node<T>::addEdge(Node<T>* destination, int weight) {
  
    Edge<T>* newEdge = new Edge<T>(destination, weight);
    newEdge->next = edges;
    edges = newEdge;
}

template<class T>
void Node<T>::printEdges() {
    Edge<T>* current = edges;
    while (current) {
        cout << "  -> " << current->dest->data << " (Peso: " << current->weight << ")" << endl;
        current = current->next;
    }
}


template<class T>
class Graph {
private:
    Node<T>* nodes; 
public:
    Graph() : nodes(nullptr) {}

    Node<T>* findNode(T val); 
    void addNode(T val);      
    void addEdge(T from, T to, int weight); 
    void printGraph();        
    void shortestPath(T start, T end);
};

template<class T>
Node<T>* Graph<T>::findNode(T val) {
    Node<T>* current = nodes;
    while (current) {
        if (current->data == val) return current;
        current = current->next;
    }
    return nullptr;
}

template<class T>
void Graph<T>::addNode(T val) {
    if (!findNode(val)) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = nodes;
        nodes = newNode;
    }
}

template<class T>
void Graph<T>::addEdge(T from, T to, int weight) {
    Node<T>* fromNode = findNode(from);
    Node<T>* toNode = findNode(to);
    if (fromNode && toNode) {
        fromNode->addEdge(toNode, weight);
        
    }
}

template<class T>
void Graph<T>::printGraph() {
    Node<T>* current = nodes;
    while (current) {
        cout << "Nodo: " << current->data << endl;
        current->printEdges();
        current = current->next;
    }
}

template<class T>
void Graph<T>::shortestPath(T start, T end) {
    // Paso 1: contar nodos para crear arreglos
    int n = 0;
    Node<T>* aux = nodes;
    while (aux) { n++; aux = aux->next; }

    // Paso 2: hacer arrays para distancias, visitados, padres y referencias nodos
    int* dist = new int[n];
    bool* visited = new bool[n];
    int* parent = new int[n];
    Node<T>** nodeRefs = new Node<T>*[n];

    // Paso 3: llenar referencias y asignar indices
    aux = nodes;
    int idx = 0;
    while (aux) {
        nodeRefs[idx] = aux;
        dist[idx] = INT_MAX;
        visited[idx] = false;
        parent[idx] = -1;
        aux = aux->next;
        idx++;
    }

    // Paso 4: buscar índice del nodo de inicio y fin
    int startIdx = -1, endIdx = -1;
    for (int i = 0; i < n; i++) {
        if (nodeRefs[i]->data == start) startIdx = i;
        if (nodeRefs[i]->data == end) endIdx = i;
    }
    if (startIdx == -1 || endIdx == -1) {
        cout << "Nodo no encontrado." << endl;
        delete[] dist; delete[] visited; delete[] parent; delete[] nodeRefs;
        return;
    }

    dist[startIdx] = 0;

    // Paso 5: Dijkstra
    for (int k = 0; k < n; k++) {
        // Buscar el nodo no visitado con menor distancia
        int u = -1;
        int minDist = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if (u == -1) break; // No quedan nodos alcanzables
        visited[u] = true;

        // Relajar aristas
        Edge<T>* edge = nodeRefs[u]->edges;
        while (edge) {
            // Buscar índice del nodo destino
            int v = -1;
            for (int i = 0; i < n; i++)
                if (nodeRefs[i] == edge->dest) v = i;
            if (v != -1 && !visited[v] && dist[u] + edge->weight < dist[v]) {
                dist[v] = dist[u] + edge->weight;
                parent[v] = u;
            }
            edge = edge->next;
        }
    }

    // Paso 6: reconstruir camino
    if (dist[endIdx] == INT_MAX) {
        cout << "No hay camino de " << start << " a " << end << "." << endl;
    } else {
        cout << "Distancia minima de " << start << " a " << end << " es " << dist[endIdx] << endl;
        cout << "Camino: ";
        // reconstruir camino
        int curr = endIdx;
        T path[100]; 
        int len = 0;
        while (curr != -1) {
            path[len++] = nodeRefs[curr]->data;
            curr = parent[curr];
        }
        for (int i = len - 1; i >= 0; i--) {
            cout << path[i];
            if (i) cout << " -> ";
        }
        cout << endl;
    }

    delete[] dist; delete[] visited; delete[] parent; delete[] nodeRefs;
}