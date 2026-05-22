//riwayat
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

//nampilin smua riwayat dlm bntuk tabel
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


//tampilin pesenan
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

//nampilin pesenan user yang lg login aja
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


//struk
void tampilkanStruk() {
    int id;
    cout << "\n  Masukkan ID pesanan: "; cin >> id;

    pesanan* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            //user cm bisa cetak struk punya snsdiri
            if (sesiRole == "user" && temp->namaPelanggan != sesiNama) {
                cout << "\n  Akses ditolak. Bukan pesanan Anda.\n\n";
                system("pause");
                return;
            }
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
            garisBintang();
            cout << endl;
            system("pause");
            return;
        }
        temp = temp->next;
    }

    cout << "\n  Pesanan dengan ID " << id << " tidak ditemukan.\n\n";
    system("pause");
}




//edit pesenan
void editPesanan() {
    system("cls");
    tampilkanHeader();
    cout << "========== EDIT PESANAN ==========" << endl;

    int id;
    cout << "\n  Masukkan ID pesanan yang ingin diedit: "; cin >> id;

    pesanan* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            //user cm bisa edit punya sendiri
            if (sesiRole == "user" && temp->namaPelanggan != sesiNama) {
                cout << "\n  Akses ditolak. Bukan pesanan Anda.\n\n";
                system("pause");
                return;
            }

            cout << "\n  Status saat ini  : " << temp->status << endl;
            cout << "  Status baru (Antri / Proses / Selesai): ";
            cin >> temp->status;

            //catet prubahan ke riwayat
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


//hapus pesenan
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
            //catet riwayat sblm dihapus
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


//cari pesenan
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
        //cari sesuai id
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
                break; //krn id = unik, jadi lgnsn berenti
            }
            temp = temp->next;
        }

    } else {
        //cari sesuai nama
        string nama;
        cout << "  Masukkan nama: ";
        cin.ignore();
        getline(cin, nama);

        pesanan* temp = head;
        while (temp != nullptr) {
            if (temp->namaPelanggan == nama) {
                // User tidak boleh lihat data orang lain
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
            //ngga break, karena nama bisa ada banyak pesanan
        }
    }

    if (!ketemu)
        cout << "\n  Data tidak ditemukan.\n";

    cout << endl;
    system("pause");
}


//login

//login admin (cek usn & pw)
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

//login user (masukkin nama aja)
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


//menu admin
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
        cout << "  [7] Tampilkan Struk" << endl;
        cout << "  [8] Simpan ke File" << endl;
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
            case 7: tampilkanStruk();        break;
            case 8: simpanKeFile();          break;            
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


//menu pelanggan
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
            case 1: tambahPesanan();   break;
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


//halaman utama
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


//main
int main() {
    loadDariFile();   
    halamanUtama();
    return 0;
}