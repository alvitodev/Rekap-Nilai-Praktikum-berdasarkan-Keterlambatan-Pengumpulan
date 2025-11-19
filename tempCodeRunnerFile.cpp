    // --- Variabel Lokal ---
    // Array disimpan di stack main, bukan variabel global
    Mahasiswa daftarMahasiswa[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    int pilihanMenu;
    bool dataSudahDiinput = false; // Penanda apakah user sudah input data

    do {
        // --- Tampilan Menu ---
        cout << "\n--- MENU UTAMA ---\n";
        cout << "1. Input Data Mahasiswa\n";
        cout << "2. Tampilkan Daftar Nilai Lengkap\n";
        cout << "3. Tampilkan Peringkat\n";
        cout << "4. Cari Mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        
        // Validasi Input Menu (Harus Angka)
        if (!(cin >> pilihanMenu)) {
            cout << "ERROR: Pilihan harus berupa angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Ulangi loop
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer

        // Validasi Logika: Cek apakah data sudah ada sebelum akses menu 2, 3, 4
        if (pilihanMenu > 1 && pilihanMenu < 5 && !dataSudahDiinput) {
            cout << "ERROR: Harap input data terlebih dahulu (Pilih menu 1).\n";
        } else {
            // Percabangan Menu
            switch (pilihanMenu) {
                case 1:
                    // Memanggil InputData
                    InputData(daftarMahasiswa, jumlahMahasiswa);
                    
                    // Jika input berhasil (jumlah > 0), lakukan perhitungan & sorting otomatis
                    if (jumlahMahasiswa > 0) {
                        HitungNilai(daftarMahasiswa, jumlahMahasiswa);
                        UrutkanData(daftarMahasiswa, jumlahMahasiswa);
                        dataSudahDiinput = true; // Tandai data sudah siap
                        cout << "\n[INFO] Data berhasil diinput, dihitung, dan diurutkan.\n";
                    }
                    break;
                case 2:
                    TampilDataLengkap(daftarMahasiswa, jumlahMahasiswa);
                    break;
                case 3:
                    TampilRanking(daftarMahasiswa, jumlahMahasiswa);
                    break;
                case 4:
                    CariMahasiswa(daftarMahasiswa, jumlahMahasiswa);
                    break;
                case 5:
                    cout << "Terima kasih. Program selesai.\n";
                    break;
                default:
                    cout << "ERROR: Pilihan tidak valid (1-5).\n";
            }
        }
    } while 