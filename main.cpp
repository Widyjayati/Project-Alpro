// sistem manajemen laundry
#include <iostream>
#include <iomanip>
using namespace std;

// struct, node, pointer, linkedlist tunggal, crud pelanggan, bubble sort, operasi file
struct pesanan {
    int id;                     // 1
    string namaPelanggan;       // "Widy Jayati"
    string noHp;                // "081269705018"
    float beratKg;              // 3.5
    string jenisLayanan;        // "cuci + setrika", "cuci kering"
    float hargaPerKg;           //10000 > diisi admin
    float totalHarga;           //otomatis : beratKg * hargaPerKg
    string tanggalMasuk;        
    string status;              //"menunggu/proses/selesai/diambil"
    string metodeBayar;         //"cash atau transfer dll"
};

//ll tunggal > membungkus struct pesanan + pointer next
struct NodePesanan{
    pesanan data;   //isi datanya (struct di atas)
    NodePesanan* next;     // pointer ke data selanjutnya
};

//Node untuk ll ganda (riwayat pesanan selesai/diambil)
struct NodeRiwayat{
    pesanan data;           //data pesanan yang sudah selesai/diambil
    NodeRiwayat* next;      //pointer ke data selanjutnya
    NodeRiwayat* prev;      //pointer ke data sebelumnya
};

//variabel global penanda posisi dalam linked list
NodePesanan* headPesanan = nullptr;       //kepala ll tunggal > menunjuk ke data pertama
NodeRiwayat* headRiwayat = nullptr;         //kepala ll ganda > menunjuk ke data pertama    
NodeRiwayat* tailRiwayat = nullptr;         //ekor ll ganda > menunjuk ke data terakhir

//counter ID pesanan (selalu bertambah setiap pesanan baru)
int idPesananAuto = 1;
int idTransaksiAuto = 1;    //untuk riwayat

// =====FUNGSI BANTU========
//cetak tanggal hari ini
string getTanggal(){
    
}

void menuAdmin(){

}


void menuPelanggan(){
    
}


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

        } else if (pilihRole == 2){

        } else if (pilihRole == 3){
            cout << "Terima Kasih!" << endl;
            break;
        } else{
            cout << "Menu tidak terdaftar!" << endl;
        }
    } while (pilihRole != 3);

}