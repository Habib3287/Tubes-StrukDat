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
