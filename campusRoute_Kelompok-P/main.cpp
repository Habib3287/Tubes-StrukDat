#include "campusroute.h"

void showMenu() {
    cout << "=== MENU SISTEM REKOMENDASI RUTE KAMPUS ===" << endl;
    cout << "1. Tampilkan semua rute" << endl;
    cout << "2. Cari rute terpendek" << endl;
    cout << "3. Lihat gedung dengan konektivitas tertinggi" << endl;
    cout << "4. Tambah gedung baru" << endl;
    cout << "5. Tambah rute baru" << endl;
    cout << "0. Keluar" << endl;
    cout << "============================================" << endl;
    cout << "Pilihan: ";
}

void handleShortestPath(Graph &G) {
    char src[30], dest[30];
    cout << "Masukkan gedung asal: ";
    cin >> src;
    cout << "Masukkan gedung tujuan: ";
    cin >> dest;
    findShortestPath(G, src, dest);
}

void handleAddBuilding(Graph &G) {
    char name[30];
    cout << "Masukkan nama gedung baru: ";
    cin >> name;
    addVertex(G, name);
    cout << "Gedung " << name << " berhasil ditambahkan!" << endl;
}

void handleAddRoute(Graph &G) {
    char src[30], dest[30];
    int weight;
    cout << "Masukkan gedung asal: ";
    cin >> src;
    cout << "Masukkan gedung tujuan: ";
    cin >> dest;
    cout << "Masukkan jarak (meter): ";
    cin >> weight;
    addEdge(G, src, dest, weight);
    cout << "Rute berhasil ditambahkan!" << endl;
}

int main() {
    Graph G;
    createGraph(G);

    addVertex(G, "TULT");
    addVertex(G, "GKU");
    addVertex(G, "CACUK");
    addVertex(G, "PERPUS");
    addVertex(G, "GSG");

    addEdge(G, "TULT", "GKU", 150);
    addEdge(G, "TULT", "CACUK", 100);
    addEdge(G, "GKU", "PERPUS", 200);
    addEdge(G, "CACUK", "GSG", 300);
    addEdge(G, "PERPUS", "GSG", 250);
    addEdge(G, "GKU", "GSG", 400);

    int choice;
    do {
        showMenu();
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Daftar seluruh rute yang tersedia:" << endl;
                displayAllRoutes(G);
                cout << "============================================" << endl;
                break;
            case 2:
                handleShortestPath(G);
                cout << "============================================" << endl;
                break;
            case 3: {
                char mostConnected[30];
                findMostConnectedBuilding(G, mostConnected);
                cout << "Gedung dengan konektivitas tertinggi: " << mostConnected << endl;
                cout << "Jumlah rute langsung: " << countDirectRoutes(G, mostConnected) << endl;
                cout << "============================================" << endl;
                break;
            }
            case 4:
                handleAddBuilding(G);
                cout << "============================================" << endl;
                break;
            case 5:
                handleAddRoute(G);
                cout << "============================================" << endl;
                break;
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                cout << "============================================" << endl;
        }
    } while(choice != 0);

    return 0;
}
