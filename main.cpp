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

void Halaman_utama(){
    int pilihRole;

    do{
        cout << setw(30) << setfill('=') << "" << endl;
        cout << "Silakan Memilih Role: " << endl;
        cout << setw(30) << setfill('=') << "" << endl << endl;
        cout << "1. Admin" << endl;
        cout << "2. Pelanggan" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih role (1-3): "; cin >> pilihRole;

        system("pause");
        system("cls");

        if (pilihRole == 1){

        } elseif (pilihRole == 2){

        } elseif (pilihRole == 3){
            cout << ""
            return;
        } else{
            cout << "Menu tidak terdaftar!" << endl;
        }
    } while (pilihRole != 3);

}