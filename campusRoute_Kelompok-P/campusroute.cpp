#include "campusroute.h"

void strCopy(char* dest, const char* src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

bool strCompare(const char* str1, const char* str2) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) return false;
        i++;
    }
    return str1[i] == str2[i];
}

void createGraph(Graph &G) {
    G.first = NULL;
}

void addVertex(Graph &G, const char* name) {
    Vertex* newVertex = new Vertex;
    strCopy(newVertex->name, name);
    newVertex->firstEdge = NULL;
    newVertex->next = NULL;
    newVertex->visited = false;
    newVertex->distance = MAX_DIST;
    newVertex->parent[0] = '\0'; //null

    if (!G.first) {
        G.first = newVertex;
    } else {
        Vertex* current = G.first;
        while (current->next) {
            current = current->next;
        }
        current->next = newVertex;
    }
}

Vertex* findVertex(Graph G, const char* name) {
    Vertex* current = G.first;
    while (current) {
        if (strCompare(current->name, name)) return current;
        current = current->next;
    }
    return NULL;
}

void addEdge(Graph &G, const char* src, const char* dest, int weight) {
    Vertex* srcVertex = findVertex(G, src);
    Vertex* destVertex = findVertex(G, dest);

    if (!srcVertex || !destVertex) return;

    Edge* newEdge = new Edge;
    strCopy(newEdge->dest, dest);
    newEdge->weight = weight;
    newEdge->next = srcVertex->firstEdge;
    srcVertex->firstEdge = newEdge;

    newEdge = new Edge;
    strCopy(newEdge->dest, src);
    newEdge->weight = weight;
    newEdge->next = destVertex->firstEdge;
    destVertex->firstEdge = newEdge;
}

void findShortestPath(Graph &G, const char* src, const char* dest) {
    Vertex* srcVertex = findVertex(G, src);
    if (!srcVertex) return;
    Vertex* current = G.first;
    while (current) {
        current->visited = false;
        current->distance = MAX_DIST;
        current->parent[0] = '\0'; //null
        current = current->next;
    }

    srcVertex->distance = 0;

    while(true) {
        Vertex* minVertex = NULL;
        int minDist = MAX_DIST;

        current = G.first;
        while(current) {
            if (!current->visited && current->distance < minDist) {
                minDist = current->distance;
                minVertex = current;
            }
            current = current->next;
        }

        if (!minVertex) break;

        minVertex->visited = true;
        Edge* edge = minVertex->firstEdge;
        while(edge) {
            Vertex* neighbor = findVertex(G, edge->dest);
            if (!neighbor->visited) {
                int newDist = minVertex->distance + edge->weight;
                if (newDist < neighbor->distance) {
                    neighbor->distance = newDist;
                    strCopy(neighbor->parent, minVertex->name);
                }
            }
            edge = edge->next;
        }
    }
    Vertex* destVertex = findVertex(G, dest);
    if (destVertex->distance == MAX_DIST) {
        cout << "Tidak ada rute yang tersedia dari " << src << " ke " << dest << endl;
        return;
    }
    char path[100][30];
    int pathSize = 0;

    char currentName[30];
    strCopy(currentName, dest);
    while(currentName[0] != '\0') {
        strCopy(path[pathSize++], currentName);
        strCopy(currentName, findVertex(G, currentName)->parent);
    }
    cout << "Rute terpendek dari " << src << " ke " << dest << ":" << endl;
    cout << "Total jarak: " << destVertex->distance << " meter" << endl;
    cout << "Rute: ";
    for (int i = pathSize-1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;
}

int countDirectRoutes(Graph G, const char* building) {
    Vertex* vertex = findVertex(G, building);
    if (!vertex) return 0;

    int count = 0;
    Edge* edge = vertex->firstEdge;
    while (edge) {
        count++;
        edge = edge->next;
    }
    return count;
}

void findMostConnectedBuilding(Graph G, char* result) {
    int maxConnections = 0;
    result[0] = '\0'; //null

    Vertex* current = G.first;
    while (current) {
        int connections = countDirectRoutes(G, current->name);
        if (connections > maxConnections) {
            maxConnections = connections;
            strCopy(result, current->name);
        }
        current = current->next;
    }
}

void displayAllRoutes(Graph G) {
    Vertex* current = G.first;
    while (current) {
        Edge* edge = current->firstEdge;
        while (edge) {
            cout << current->name << " <-> " << edge->dest
                 << " (" << edge->weight << " meter)" << endl;
            edge = edge->next;
        }
        current = current->next;
    }
}
