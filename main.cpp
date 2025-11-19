#include <iostream>
#include <limits>      // buat numeric_limits
#include "RekapNilai.h" // file header untuk struct dan deklarasi fungsi
using namespace std;

int main() {
    // disimpan di stack main, bukan variabel global yg di header
    Mahasiswa daftarMahasiswa[MAX_MAHASISWA];
    int jumlahMahasiswa = 0;
    int pilihanMenu;
    bool dataSudahDiinput = false; // apakah user sudah input data

    do {
        // menu utama
        cout << "\n--- MENU UTAMA ---\n";
        cout << "1. Input Data Mahasiswa\n";
        cout << "2. Tampilkan Daftar Nilai Lengkap\n";
        cout << "3. Tampilkan Peringkat\n";
        cout << "4. Cari Mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Pilihan Anda: ";
        
        // validasi input menu harus angka
        if (!(cin >> pilihanMenu)) {
            cout << "ERROR: Pilihan harus berupa angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean buffer
            continue; // loop kembali ke menu kalo bukan angka
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean buffer

        // cek apakah data sudah ada sebelum akses menu 2, 3, 4
        if (pilihanMenu > 1 && pilihanMenu < 5 && !dataSudahDiinput) {
            cout << "ERROR: Harap input data terlebih dahulu (Pilih menu 1).\n";
        } else {
            // percabangan menu
            switch (pilihanMenu) {
                case 1:
                    // memanggil InputData
                    InputData(daftarMahasiswa, jumlahMahasiswa);
                    
                    // if input berhasil (jumlah > 0), do perhitungan & sorting sekalian
                    if (jumlahMahasiswa > 0) {
                        HitungNilai(daftarMahasiswa, jumlahMahasiswa);
                        UrutkanData(daftarMahasiswa, jumlahMahasiswa);
                        dataSudahDiinput = true; // tandai data sudah siap
                        cout << "\n[INFO] Data berhasil diinput, dihitung, dan diurutkan.\n";
                    }
                    break;
                case 2: // menampilkan data lengkap
                    TampilDataLengkap(daftarMahasiswa, jumlahMahasiswa);
                    break;
                case 3: // menampilkan ranking
                    TampilRanking(daftarMahasiswa, jumlahMahasiswa);
                    break;
                case 4: // mencari mahasiswa berdasarkan NIM atau nama 
                    CariMahasiswa(daftarMahasiswa, jumlahMahasiswa);
                    break;
                case 5:
                    cout << "Terima kasih. Program selesai.\n";
                    break;
                default: // pilihan diluar 1-5
                    cout << "ERROR: Pilihan tidak valid (1-5).\n";
            }
        }
    } while (pilihanMenu != 5); // loop terus sampai user pilih 5
    return 0;
}