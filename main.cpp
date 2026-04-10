// sistem manajemen laundry
#include <iostream>
using namespace std;

struct pesanan {
    int id;                     // 1
    string namaPelanggan;       // "Widy Jayati"
    string noHp;                // "081269705018"
    float beratKg;              // 3.5
    string jenisLayanan;        // "cuci + setrika"
    float hargaPerKg;           //10000 > diisi admin
    float totalBiaya;           //otomatis : beratKg x hargaPerKg
    string tanggalMasuk;        //"01=04-2026" > diisi admin
    string status;              //"menunggu/proses/selesai/diambil"
};
