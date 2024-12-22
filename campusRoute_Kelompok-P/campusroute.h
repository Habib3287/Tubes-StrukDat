#ifndef CAMPUSROUTE_H
#define CAMPUSROUTE_H
#define MAX_DIST 100000
#include <iostream>
using namespace std;

struct Edge {
    char dest[30];
    int weight;
    Edge* next;
};

struct Vertex {
    char name[30];
    Edge* firstEdge;
    Vertex* next;
    bool visited;
    int distance;
    char parent[30];
};

struct Graph {
    Vertex* first;
};

void strCopy(char* dest, const char* src);
bool strCompare(const char* str1, const char* str2);
void createGraph(Graph &G);
void addVertex(Graph &G, const char* name);
Vertex* findVertex(Graph G, const char* name);
void addEdge(Graph &G, const char* src, const char* dest, int weight);
void findShortestPath(Graph &G, const char* src, const char* dest);
int countDirectRoutes(Graph G, const char* building);
void findMostConnectedBuilding(Graph G, char* result);
void displayAllRoutes(Graph G);

#endif
