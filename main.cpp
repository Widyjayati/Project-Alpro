#include <iostream>
#include <iomanip>
using namespace std;

//KONSTANTA
const string adminUser  = "admin";
const string adminPass  = "12345";
const float biaya_antar = 5000;
const float tarif[6]    = {
    0,                  //[0] tidak dipakai
    7000,               //[1] cuci + setrika
    5000,               //[2] cuci saja
    4000,               //[3] setrika saja
    12000,              //[4] express
    15000               //[5] dry clean
};
const string layanan[6] = {
    "",
    "Cuci + Setrika",
    "Cuci Saja",
    "Setrika Saja",
    "Express (Cuci + Setrika)",
    "Dry Clean"
};

//STRUCT PESANAN - ll tunggal
struct pesanan {
    int id;
    string namaPelanggan;
    string jenisLayanan;        // kode 1-5
    float beratKg;
    string pengiriman;          //Ambil | Antar
    string alamat;              // diisi jika pengiriman = "antar"
    float harga;
    string status;              //Antri | Proses | Selesai
    string tanggal;             //input manual dd/mm/yyyy
    pesanan* next;              //POINTER ke pesanan berikutnya
};

//STRUCT RIWAYAT - ll Ganda menyimpan log setiap aktivitas CRUD
struct riwayat{
    int idPesanan;
    string namaPelanggan;
    string keterangan;
    string tanggal;
    riwayat* next;              //POINTER ke riwayat berikutnya
    riwayat* prev;              //POINTER ke riwayat sebelumnya
};

//VARIABEL GLOBAL
pesanan* head   = nullptr;
riwayat* rHead  = nullptr;
riwayat* rTail  = nullptr;
int idCounter   = 1;            //counter id pesanan otomatis
//data sesi login
string sesiRole = "";           //"admin" atau "user"
string sesiNama = "";           //nama pelanggan (untuk User)

//UTILITAS : Garis Pembatas
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

//OPERASI FILE - Simpan Pesanan ke File
void simpanKeFile(){
    FILE* fptr = fopen("Pesanan.txt", "w");
    if(fptr == NULL){
        cout << "Gagal membuka file" << endl << endl;
        system("pause");
        return;
    }
    pesanan* temp = head;
    while(temp != nullptr){
        //tulis 1 baris per pesanan, field dipisah '|'
        //.c_str() = konversi string ke char* untuk fprintf
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

//OPERASI FILE - Load Pesanan dari File
//fopen mode "r" = read (baca file yang sudah ada)
void loadDariFile(){
    FILE* fptr = fopen("Pesanan.txt", "r");

    if(fptr == NULL) return;

    char namaBuf[100], pengBuf[10], alamatBuf[100];
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

        //insert ke akhir ll
        if(head == nullptr) {
            head = baru;
        } else {
            pesanan* temp = head;
            while(temp->next != nullptr) temp = temp->next;
            temp->next = baru;
        }
        if(baru->id > maxId) maxId = baru->id;
    }
    idCounter = maxId + 1;          //lanjutkan ID dari data terakhir
    fclose(fptr);
    cout << "  Data berhasil dimuat dari file." << endl;
    system("pause");
}

void tampilkanSemuaPesanan(){}

//SORTING - Bubble Sort by Harga (Admin)
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
    cout << "  Pilihan: "; int pil; cin >> pil;

    //bubble sort: tukar isi node
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
    cout << "\n  Pesanan berhasil diurutkan! " << endl << endl;
    system("pause");
    tampilkanSemuaPesanan();
}