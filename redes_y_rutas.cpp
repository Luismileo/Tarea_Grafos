#include "Grafos.h"
using namespace std;

int main() {

    Graph<string> mapa;
    
    mapa.addNode("A");
    mapa.addNode("B");
    mapa.addNode("C");
    mapa.addNode("D");
    mapa.addNode("E");
    mapa.addNode("F");
    mapa.addNode("G");
    mapa.addNode("H");
    mapa.addNode("I");
    mapa.addNode("J");

    mapa.addEdge("A", "B", 4);
    mapa.addEdge("A", "C", 2);
    mapa.addEdge("B", "C", 1);
    mapa.addEdge("B", "D", 5);
    mapa.addEdge("C", "D", 8);
    mapa.addEdge("C", "E", 10);
    mapa.addEdge("D", "E", 2);
    mapa.addEdge("D", "F", 6);
    mapa.addEdge("E", "F", 3);
    mapa.addEdge("E", "G", 1);
    mapa.addEdge("F", "G", 1);
    mapa.addEdge("F", "H", 7);
    mapa.addEdge("G", "H", 2);
    mapa.addEdge("G", "I", 6);
    mapa.addEdge("H", "I", 3);
    mapa.addEdge("H", "J", 4);
    mapa.addEdge("I", "J", 2);

    mapa.printGraph();

    mapa.shortestPath("A", "J");

    mapa.shortestPath("A", "F");

    mapa.shortestPath("B", "I");

    return 0;
}