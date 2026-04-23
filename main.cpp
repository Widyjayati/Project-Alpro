// sistem manajemen laundry
#include <iostream>
#include <iomanip>
using namespace std;

struct pesanan {
    int id;
    string namaPelanggan;
    int jenisLayanan;   
    float beratKg;
    string pengiriman;
    string alamat;
    float harga;
    string status;
    string tanggal;
    pesanan* next;
};

struct Node{
    pesanan data;
    Node* next;
};

Node* head = NULL;
int idCounter = 1;


void tambahPesanan(){
    pesanan* baru = new pesanan();

    baru->id = idCounter++;

    cout << "Nama: ";
    cin.ignore();
    getline(cin, baru->namaPelanggan);

    cout << "Berat (kg): ";
    cin >> baru->beratKg;

    tampilkanLayanan(); // dari teman kamu
    cout << "Pilih layanan (1-5): ";
    cin >> baru->jenisLayanan;

    // HITUNG HARGA
    baru->harga = baru->beratKg * tarif[baru->jenisLayanan];

    // PENGIRIMAN
    cout << "Pengiriman (1. Antar / 2. Ambil): ";
    int p;
    cin >> p;

    if(p == 1){
        baru->pengiriman = "Antar";
        cout << "Alamat: ";
        cin.ignore();
        getline(cin, baru->alamat);
        baru->harga += biaya_antar;
    } else {
        baru->pengiriman = "Ambil";
        baru->alamat = "-";
    }

    cout << "Tanggal: ";
    cin >> baru->tanggal;

    baru->status = "Antri";

    baru->next = nullptr;

    // INSERT KE LINKED LIST
    if(head == nullptr){
        head = baru;
    } else {
        pesanan* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = baru;
    }

    cout << "\nPesanan berhasil ditambahkan!\n";
    system("pause");
}


void tampilkanSemuaPesanan(){
    system("cls");

    if(head == nullptr){
        cout << "Data kosong!\n";
        system("pause");
        return;
    }

    // HEADER
    cout << left;
    cout << setw(5)  << "ID"
         << setw(20) << "Nama"
         << setw(20) << "Layanan"
         << setw(8)  << "Berat"
         << setw(12) << "Kirim"
         << setw(20) << "Alamat"
         << setw(12) << "Harga"
         << setw(12) << "Status"
         << setw(15) << "Tanggal" << endl;

    cout << string(124, '-') << endl;

    // ISI DATA
    pesanan* temp = head;

    while(temp != nullptr){
        cout << setw(5)  << temp->id
             << setw(20) << temp->namaPelanggan
             << setw(20) << layanan[temp->jenisLayanan] // 🔥 dari array teman kamu
             << setw(8)  << temp->beratKg
             << setw(12) << temp->pengiriman
             << setw(20) << temp->alamat
             << setw(12) << temp->harga
             << setw(12) << temp->status
             << setw(15) << temp->tanggal
             << endl;

        temp = temp->next;
    }

    cout << endl;
    system("pause");
}


void cariPesanan(){
    int id;
    cout << "Masukkan ID: ";
    cin >> id;

    pesanan* temp = head;
    while(temp != nullptr){
        if(temp->id == id){
            cout << "\nDitemukan!\n";
            cout << "Nama: " << temp->namaPelanggan << endl;
            cout << "Status: " << temp->status << endl;
            system("pause");
            return;
        }
        temp = temp->next;
    }

    cout << "Pesanan tidak ditemukan!\n";
    system("pause");
}


void hapusPesanan(){
    int id;
    cout << "Masukkan ID yang mau dihapus: ";
    cin >> id;

    pesanan* temp = head;
    pesanan* prev = nullptr;

    while(temp != nullptr){
        if(temp->id == id){
            if(prev == nullptr){
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;

            cout << "Data berhasil dihapus!\n";
            system("pause");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "ID tidak ditemukan!\n";
    system("pause");
}


void editPesanan(){
    int id;
    cout << "Masukkan ID: ";
    cin >> id;

    pesanan* temp = head;

    while(temp != nullptr){
        if(temp->id == id){
            cout << "Status baru: ";
            cin >> temp->status;

            cout << "Data berhasil diupdate!\n";
            system("pause");
            return;
        }
        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n";
    system("pause");
}


void tampilkanStruk(){
    int id;
    cout << "Masukkan ID: ";
    cin >> id;

    pesanan* temp = head;

    while(temp != nullptr){
        if(temp->id == id){
            cout << "\n===== STRUK =====\n";
            cout << "ID: " << temp->id << endl;
            cout << "Nama: " << temp->namaPelanggan << endl;
            cout << "Layanan: " << layanan[temp->jenisLayanan] << endl;
            cout << "Total: Rp " << temp->harga << endl;
            cout << "Status: " << temp->status << endl;
            cout << "=================\n";

            system("pause");
            return;
        }
        temp = temp->next;
    }

    cout << "Tidak ditemukan!\n";
    system("pause");
}


void menuAdmin(){
    int pilih;

    do{
        system("cls");
        cout << "\n==== MENU ADMIN ====\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Semua Pesanan\n";
        cout << "3. Edit Pesanan\n";
        cout << "4. Hapus Pesanan\n";
        cout << "5. Cari Pesanan\n";
        cout << "6. Urutkan Pesanan\n";
        cout << "7. Lihat Riwayat\n";
        cout << "8. Tampilkan Struk\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih){
            case 1: tambahPesanan(); break;
            case 2: tampilkanSemuaPesanan(); break;
            case 3: editPesanan(); break;
            case 4: hapusPesanan(); break;
            case 5: cariPesanan(); break;
            case 6: sortPesanan(); break;   // dari teman kamu
            case 7: tampilkanRiwayat(); break;
            case 8: tampilkanStruk(); break;
        }

    } while(pilih != 0);
}


void menuPelanggan(){
    int pilih;

    do{
        cout << "\n=== MENU USER ===\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Pesanan\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        if(pilih == 1){
            tambahPesanan(false);
        }
        else if(pilih == 2){
            tampilkanPesanan();
        }

    } while(pilih != 0);   
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