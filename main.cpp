// sistem manajemen laundry
#include <iostream>
#include <iomanip>
using namespace std;

struct pesanan {
    int id;                     // 1
    string namaPelanggan;       // "Widy Jayati"
    string noHp;                // "081269705018"
    float beratKg;              // 3.5
    string jenisLayanan;        // "cuci + setrika"
    float hargaPerKg;           //10000 > diisi admin
    float totalHarga;           //otomatis : beratKg x hargaPerKg
    string tanggalMasuk;        //"01=04-2026" > diisi admin
    string status;              //"menunggu/proses/selesai/diambil"
    string metodeBayar;         //"cash atau transfer dll"
};

struct Node{
    pesanan data;
    Node* next;
};

Node* head = NULL;
int idCounter = 1;