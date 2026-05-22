#include <iostream>
#include <iomanip>
using namespace std;

const string adminUser  = "admin";
const string adminPass  = "12345";
const float biaya_antar = 5000;
const float tarif[6]    = {
    0,
    7000,
    5000,
    4000,
    12000,
    15000
};
const string layanan[6] = {
    "",
    "Cuci + Setrika",
    "Cuci Saja",
    "Setrika Saja",
    "Express (Cuci + Setrika)",
    "Dry Clean"
};

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
pesanan* head = nullptr;

struct riwayat{
    int idPesanan;
    string namaPelanggan;
    string keterangan;
    string tanggal;
    riwayat* next;
    riwayat* prev;
};

riwayat* rHead  = nullptr;
riwayat* rTail  = nullptr;
int idCounter   = 1;
string sesiRole = "";
string sesiNama = "";

void tampilkanSemuaPesanan();
void tambahRiwayat(int idPesanan, string nama, string keterangan, string tanggal);

void garis(){
    cout << setfill('-') << setw(42) << "" << setfill(' ') << endl;
}
void garisBintang(){
    cout << setfill('*') << setw(42) << "" << setfill(' ') << endl;
}
void tampilkanHeader(){
    cout << setfill('=') << setw(42) << "" << setfill(' ') << endl;
    cout << "         SISTEM MANAJEMEN LAUNDRY" << endl;
    cout << setfill('=') << setw(42) << "" << setfill(' ') << endl;
}
void tampilkanLayanan(){
    cout << "Jenis Layanan:" << endl;
    garis();
    for(int i=1; i<=5; i++){
        cout << " [" << i << "] " << left << setw(26) << layanan[i]
        << "Rp " << right << setw(5) << tarif[i] << "/kg" << endl;
    }
    garis();
}

void simpanKeFile(){
    FILE* fptr = fopen("Pesanan.txt", "w");
    if(fptr == NULL){
        cout << "Gagal membuka file" << endl << endl;
        system("pause");
        return;
    }
    pesanan* temp = head;
    while(temp != nullptr){
        fprintf(fptr, "%d|%s|%d|%.2f|%s|%s|%.2f|%s|%s\n",
            temp->id,
            temp->namaPelanggan.c_str(),
            temp->jenisLayanan,
            temp->beratKg,
            temp->pengiriman.c_str(),
            temp->alamat.c_str(),
            temp->harga,
            temp->status.c_str(),
            temp->tanggal.c_str()
        );
        temp = temp->next;
    }
    fclose(fptr);
    cout << "\n  Data berhasil disimpan ke 'Pesanan.txt'!" << endl << endl;
    system("pause");
}

void loadDariFile(){
    FILE* fptr = fopen("Pesanan.txt", "r");
    if(fptr == NULL) return;

    char namaBuf[100], pengBuf[10], alamatBuf[200];
    char statusBuf[20], tglBuf[20];
    int idBuf, layanBuf;
    float beratBuf, hargaBuf;
    int maxId = 0;

    while(fscanf(fptr, "%d|%99[^|]|%d|%f|%9[^|]|%199[^|]|%f|%19[^|]|%19[^\n]\n",
            &idBuf, namaBuf, &layanBuf, &beratBuf,
            pengBuf, alamatBuf, &hargaBuf,
            statusBuf, tglBuf) == 9)
    {
        pesanan* baru       = new pesanan();
        baru->id            = idBuf;
        baru->namaPelanggan = string(namaBuf);
        baru->jenisLayanan  = layanBuf;
        baru->beratKg       = beratBuf;
        baru->pengiriman    = string(pengBuf);
        baru->alamat        = string(alamatBuf);
        baru->harga         = hargaBuf;
        baru->status        = string(statusBuf);
        baru->tanggal       = string(tglBuf);
        baru->next          = nullptr;

        if(head == nullptr) {
            head = baru;
        } else {
            pesanan* temp = head;
            while(temp->next != nullptr) temp = temp->next;
            temp->next = baru;
        }
        if(baru->id > maxId) maxId = baru->id;
    }
    idCounter = maxId + 1;
    fclose(fptr);
    cout << "  Data berhasil dimuat dari file." << endl;
    system("pause");
}

void sortPesanan(){
    system("cls");
    tampilkanHeader();
    cout << "============ URUTKAN PESANAN ============" << endl;

    if(head == nullptr || head->next == nullptr){
        cout << "\n  Data tidak cukup untuk diurutkan." << endl << endl;
        system("pause");
        return;
    }
    garis();
    cout << "  [1] Harga Terendah ke Tertinggi" << endl;
    cout << "  [2] Harga Tertinggi ke Terendah" << endl;
    garis();
    int pil;
    do {
        cout << "  Pilihan (1-2): "; cin >> pil;
        if (pil < 1 || pil > 2)
            cout << "  Pilihan tidak valid, coba lagi.\n";
    } while (pil < 1 || pil > 2);

    bool swapped;
    do{
        swapped      = false;
        pesanan* cur = head;

        while(cur->next != nullptr){
            bool perluTukar = (pil == 1 && cur->harga > cur->next->harga) ||
                              (pil == 2 && cur->harga < cur->next->harga);

            if(perluTukar){
                swap(cur->id, cur->next->id);
                swap(cur->namaPelanggan, cur->next->namaPelanggan);
                swap(cur->jenisLayanan, cur->next->jenisLayanan);
                swap(cur->beratKg, cur->next->beratKg);
                swap(cur->pengiriman, cur->next->pengiriman);
                swap(cur->alamat, cur->next->alamat);
                swap(cur->harga, cur->next->harga);
                swap(cur->status, cur->next->status);
                swap(cur->tanggal, cur->next->tanggal);
                swapped = true;
            }
            cur = cur->next;
        }
    } while(swapped);
    cout << "\n  Pesanan berhasil diurutkan!" << endl << endl;
    system("pause");
    tampilkanSemuaPesanan();
}

void tambahPesanan(){
    system("cls");
    tampilkanHeader();
    cout << "============ TAMBAH PESANAN ============" << endl;
    pesanan* baru = new pesanan();
    baru->id = idCounter++;
    baru->namaPelanggan = sesiNama;
    cout << "  Nama Pelanggan         : " << sesiNama << endl;
    cout << "  Berat (kg)             : "; cin >> baru->beratKg;
    cout << endl;
    tampilkanLayanan();
    int pilihan;
    do {
        cout << "  Pilih jenis layanan (1-5): "; cin >> pilihan;
    } while(pilihan < 1 || pilihan > 5);
    baru->jenisLayanan = pilihan;

    baru->harga = baru->beratKg * tarif[baru->jenisLayanan];

    int p;
    cout << "\n  Pengiriman:" << endl;
    cout << "  [1] Ambil di Tempat" << endl;
    cout << "  [2] Antar ke Alamat (+Rp " << biaya_antar << ")" << endl;
    cout << "  Pilih: "; cin >> p;

    if(p == 1){
        baru->pengiriman = "Ambil";
        baru->alamat = "-";
    } else {
        baru->pengiriman = "Antar";
        cout << "  Alamat Pengantaran   : ";
        cin.ignore();
        getline(cin, baru->alamat);
        baru->harga += biaya_antar;
    }

    cout << "  Tanggal (dd/mm/yyyy): ";
    cin >> baru->tanggal;

    baru->status = "Antri";
    baru->next   = nullptr;

    if (head == nullptr) {
        head = baru;
    } else {
        pesanan* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = baru;
    }

    tambahRiwayat(baru->id, baru->namaPelanggan, "Tambah", baru->tanggal);

    cout << "\n  Pesanan berhasil ditambahkan!" << endl;
    cout << "  Total harga: Rp " << baru->harga << endl << endl;
    system("pause");

    garisBintang();
    cout << "           STRUK LAUNDRY" << endl;
    garisBintang();
    cout << "  ID Pesanan  : " << baru->id << endl;
    cout << "  Nama        : " << baru->namaPelanggan << endl;
    cout << "  Layanan     : " << layanan[baru->jenisLayanan] << endl;
    cout << "  Berat       : " << baru->beratKg << " kg" << endl;
    cout << "  Pengiriman  : " << baru->pengiriman << endl;
    if (baru->pengiriman == "Antar")
        cout << "  Alamat      : " << baru->alamat << endl;
    cout << "  Total Harga : Rp " << baru->harga << endl;
    cout << "  Status      : " << baru->status << endl;
    cout << "  Tanggal     : " << baru->tanggal << endl;
    garisBintang();
    cout << endl;
    system("pause");
}

void tambahRiwayat(int idPesanan, string nama, string keterangan, string tanggal) {
    riwayat* baru       = new riwayat();
    baru->idPesanan     = idPesanan;
    baru->namaPelanggan = nama;
    baru->keterangan    = keterangan;
    baru->tanggal       = tanggal;
    baru->next          = nullptr;
    baru->prev          = nullptr;

    if (rHead == nullptr) {
        rHead = baru;
        rTail = baru;
    } else {
        baru->prev  = rTail;
        rTail->next = baru;
        rTail       = baru;
    }
}

void tampilkanRiwayat() {
    system("cls");
    tampilkanHeader();
    cout << "========== RIWAYAT AKTIVITAS ==========" << endl;
    garis();

    if (rHead == nullptr) {
        cout << "\n  Belum ada riwayat aktivitas.\n\n";
        system("pause");
        return;
    }

    cout << left
         << setw(4)  << "No"
         << setw(6)  << "ID"
         << setw(22) << "Nama Pelanggan"
         << setw(12) << "Aktivitas"
         << setw(14) << "Tanggal" << endl;
    garis();

    riwayat* temp = rHead;
    int no = 1;
    while (temp != nullptr) {
        cout << left
             << setw(4)  << no++
             << setw(6)  << temp->idPesanan
             << setw(22) << temp->namaPelanggan
             << setw(12) << temp->keterangan
             << setw(14) << temp->tanggal << endl;
        temp = temp->next;
    }

    garis();
    cout << endl;
    system("pause");
}

void tampilkanSemuaPesanan() {
    system("cls");
    tampilkanHeader();
    cout << "========== DAFTAR SEMUA PESANAN ==========" << endl;
    garis();

    if (head == nullptr) {
        cout << "\n  Data pesanan masih kosong.\n\n";
        system("pause");
        return;
    }

    cout << left
         << setw(5)  << "ID"
         << setw(18) << "Nama"
         << setw(22) << "Layanan"
         << setw(7)  << "Berat"
         << setw(8)  << "Kirim"
         << setw(20) << "Alamat"
         << setw(12) << "Harga"
         << setw(10) << "Status"
         << setw(12) << "Tanggal" << endl;
    garis();

    pesanan* temp = head;
    while (temp != nullptr) {
        cout << left
             << setw(5)  << temp->id
             << setw(18) << temp->namaPelanggan
             << setw(22) << layanan[temp->jenisLayanan]
             << setw(7)  << temp->beratKg
             << setw(8)  << temp->pengiriman
             << setw(20) << temp->alamat
             << setw(12) << temp->harga
             << setw(10) << temp->status
             << setw(12) << temp->tanggal << endl;
        temp = temp->next;
    }

    garis();
    cout << endl;
    system("pause");
}

void tampilkanPesananUser() {
    system("cls");
    tampilkanHeader();
    cout << "  Pesanan atas nama: " << sesiNama << endl;
    garis();

    bool ada = false;
    pesanan* temp = head;
    while (temp != nullptr) {
        if (temp->namaPelanggan == sesiNama) {
            ada = true;
            cout << "  ID        : " << temp->id << endl;
            cout << "  Layanan   : " << layanan[temp->jenisLayanan] << endl;
            cout << "  Berat     : " << temp->beratKg << " kg" << endl;
            cout << "  Pengiriman: " << temp->pengiriman << endl;
            if (temp->pengiriman == "Antar")
                cout << "  Alamat    : " << temp->alamat << endl;
            cout << "  Harga     : Rp " << temp->harga << endl;
            cout << "  Status    : " << temp->status << endl;
            cout << "  Tanggal   : " << temp->tanggal << endl;
            garis();
        }
        temp = temp->next;
    }

    if (!ada)
        cout << "\n  Anda belum memiliki pesanan.\n";

    cout << endl;
    system("pause");
}

void tampilkanStruk() {
    system("cls");
    tampilkanHeader();
    cout << "========== STRUK PESANAN SAYA ==========" << endl;

    bool ada = false;
    pesanan* temp = head;

    while (temp != nullptr) {
        if (temp->namaPelanggan == sesiNama) {
            ada = true;
            garisBintang();
            cout << "           STRUK LAUNDRY" << endl;
            garisBintang();
            cout << "  ID Pesanan  : " << temp->id << endl;
            cout << "  Nama        : " << temp->namaPelanggan << endl;
            cout << "  Layanan     : " << layanan[temp->jenisLayanan] << endl;
            cout << "  Berat       : " << temp->beratKg << " kg" << endl;
            cout << "  Pengiriman  : " << temp->pengiriman << endl;
            if (temp->pengiriman == "Antar")
                cout << "  Alamat      : " << temp->alamat << endl;
            cout << "  Total Harga : Rp " << temp->harga << endl;
            cout << "  Status      : " << temp->status << endl;
            cout << "  Tanggal     : " << temp->tanggal << endl;
            cout << endl;
        }
        temp = temp->next;
    }

    if (!ada)
        cout << "\n  Anda belum memiliki pesanan.\n";

    cout << endl;
    system("pause");
}

void editPesanan() {
    system("cls");
    tampilkanHeader();
    cout << "========== EDIT PESANAN ==========" << endl;

    int id;
    cout << "\n  Masukkan ID pesanan yang ingin diedit: "; cin >> id;

    pesanan* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            if (sesiRole == "user" && temp->namaPelanggan != sesiNama) {
                cout << "\n  Akses ditolak. Bukan pesanan Anda.\n\n";
                system("pause");
                return;
            }
            cout << "\n  Status saat ini  : " << temp->status << endl;
            cout << "  Status baru (Antri / Proses / Selesai): ";
            cin >> temp->status;
            tambahRiwayat(temp->id, temp->namaPelanggan, "Edit", temp->tanggal);
            cout << "\n  Data berhasil diperbarui!\n\n";
            system("pause");
            return;
        }
        temp = temp->next;
    }

    cout << "\n  ID tidak ditemukan.\n\n";
    system("pause");
}

void hapusPesanan() {
    system("cls");
    tampilkanHeader();
    cout << "========== HAPUS PESANAN ==========" << endl;

    int id;
    cout << "\n  Masukkan ID yang ingin dihapus: "; cin >> id;

    pesanan* temp = head;
    pesanan* prev = nullptr;

    while (temp != nullptr) {
        if (temp->id == id) {
            tambahRiwayat(temp->id, temp->namaPelanggan, "Hapus", temp->tanggal);
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "\n  Pesanan berhasil dihapus!\n\n";
            system("pause");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "\n  ID tidak ditemukan.\n\n";
    system("pause");
}

void cariPesanan() {
    system("cls");
    tampilkanHeader();
    cout << "========== CARI PESANAN ==========" << endl;

    int pil;
    cout << "\n  Cari berdasarkan:" << endl;
    cout << "  [1] ID Pesanan" << endl;
    cout << "  [2] Nama Pelanggan" << endl;
    cout << "  Pilih: "; cin >> pil;

    bool ketemu = false;

    if (pil == 1) {
        int id;
        cout << "  Masukkan ID: "; cin >> id;

        pesanan* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                if (sesiRole == "user" && temp->namaPelanggan != sesiNama) {
                    break;
                }
                ketemu = true;
                garis();
                cout << "  ID        : " << temp->id << endl;
                cout << "  Nama      : " << temp->namaPelanggan << endl;
                cout << "  Layanan   : " << layanan[temp->jenisLayanan] << endl;
                cout << "  Berat     : " << temp->beratKg << " kg" << endl;
                cout << "  Harga     : Rp " << temp->harga << endl;
                cout << "  Status    : " << temp->status << endl;
                cout << "  Tanggal   : " << temp->tanggal << endl;
                garis();
                break;
            }
            temp = temp->next;
        }
    } else {
        string nama;
        cout << "  Masukkan nama: ";
        cin.ignore();
        getline(cin, nama);

        pesanan* temp = head;
        while (temp != nullptr) {
            if (temp->namaPelanggan == nama) {
                if (sesiRole == "user" && temp->namaPelanggan != sesiNama) {
                    temp = temp->next;
                    continue;
                }
                ketemu = true;
                garis();
                cout << "  ID        : " << temp->id << endl;
                cout << "  Layanan   : " << layanan[temp->jenisLayanan] << endl;
                cout << "  Berat     : " << temp->beratKg << " kg" << endl;
                cout << "  Harga     : Rp " << temp->harga << endl;
                cout << "  Status    : " << temp->status << endl;
                cout << "  Tanggal   : " << temp->tanggal << endl;
            }
            temp = temp->next;
        }
    }

    if (!ketemu)
        cout << "\n  Data tidak ditemukan.\n";

    cout << endl;
    system("pause");
}

bool loginAdmin() {
    string user, pass;
    cout << "\n  Username : "; cin >> user;
    cout << "  Password : "; cin >> pass;

    if (user == "admin" && pass == "12345") {
        sesiRole = "admin";
        sesiNama = "Admin";
        cout << "\n  Login berhasil! Selamat datang, Admin.\n\n";
        system("pause");
        return true;
    }

    cout << "\n  Username atau password salah!\n\n";
    system("pause");
    return false;
}

bool loginUser() {
    string nama;
    cout << "\n  Masukkan nama Anda: ";
    cin.ignore();
    getline(cin, nama);

    if (nama.empty()) {
        cout << "\n  Nama tidak boleh kosong!\n\n";
        system("pause");
        return false;
    }

    sesiRole = "user";
    sesiNama = nama;
    cout << "\n  Selamat datang, " << nama << "!\n\n";
    system("pause");
    return true;
}

void menuAdmin() {
    int pilih;
    do {
        system("cls");
        tampilkanHeader();
        cout << "  Halo, Admin!" << endl;
        garis();
        cout << "  [1] Lihat Semua Pesanan" << endl;
        cout << "  [2] Edit Pesanan" << endl;
        cout << "  [3] Hapus Pesanan" << endl;
        cout << "  [4] Cari Pesanan" << endl;
        cout << "  [5] Urutkan Pesanan" << endl;
        cout << "  [6] Lihat Riwayat Aktivitas" << endl;
        cout << "  [7] Simpan ke File" << endl;
        cout << "  [0] Logout" << endl;
        garis();
        cout << "  Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: tampilkanSemuaPesanan(); break;
            case 2: editPesanan();           break;
            case 3: hapusPesanan();          break;
            case 4: cariPesanan();           break;
            case 5: sortPesanan();           break;
            case 6: tampilkanRiwayat();      break;
            case 7: simpanKeFile();          break;
            case 0:
                sesiRole = "";
                sesiNama = "";
                cout << "\n  Logout berhasil.\n\n";
                system("pause");
                break;
            default:
                cout << "\n  Pilihan tidak valid.\n\n";
                system("pause");
        }
    } while (pilih != 0);
}

void menuPelanggan() {
    int pilih;
    do {
        system("cls");
        tampilkanHeader();
        cout << "  Halo, " << sesiNama << "!" << endl;
        garis();
        cout << "  [1] Tambah Pesanan" << endl;
        cout << "  [2] Lihat Pesanan Saya" << endl;
        cout << "  [3] Tampilkan Struk" << endl;
        cout << "  [4] Cari Pesanan" << endl;
        cout << "  [0] Logout" << endl;
        garis();
        cout << "  Pilih: "; cin >> pilih;

        switch (pilih) {
            case 1: tambahPesanan();        break;
            case 2: tampilkanPesananUser(); break;
            case 3: tampilkanStruk();       break;
            case 4: cariPesanan();          break;
            case 0:
                sesiRole = "";
                sesiNama = "";
                cout << "\n  Logout berhasil.\n\n";
                system("pause");
                break;
            default:
                cout << "\n  Pilihan tidak valid.\n\n";
                system("pause");
        }
    } while (pilih != 0);
}

void halamanUtama() {
    int pilihRole;
    do {
        system("cls");
        tampilkanHeader();
        cout << "  Silakan pilih role:" << endl;
        garis();
        cout << "  [1] Admin" << endl;
        cout << "  [2] Pelanggan" << endl;
        cout << "  [3] Keluar" << endl;
        garis();
        cout << "  Pilih (1-3): "; cin >> pilihRole;

        if (pilihRole == 1) {
            if (loginAdmin()) menuAdmin();
        } else if (pilihRole == 2) {
            if (loginUser()) menuPelanggan();
        } else if (pilihRole == 3) {
            cout << "\n  Terima kasih! Sampai jumpa.\n\n";
        } else {
            cout << "\n  Pilihan tidak valid.\n\n";
            system("pause");
        }

    } while (pilihRole != 3);
}

void bersihkanPesanan() {
    pesanan* temp = head;
    while (temp != nullptr) {
        pesanan* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
    head = nullptr;
}

void bersihkanRiwayat() {
    riwayat* temp = rHead;
    while (temp != nullptr) {
        riwayat* hapus = temp;
        temp = temp->next;
        delete hapus;
    }
    rHead = nullptr;
    rTail = nullptr;
}

int main() {
    loadDariFile();
    halamanUtama();

    bersihkanPesanan();
    bersihkanRiwayat();
    return 0;
}
