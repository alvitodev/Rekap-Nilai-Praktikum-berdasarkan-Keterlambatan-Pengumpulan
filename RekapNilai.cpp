#include "RekapNilai.h"
#include <iostream>
#include <iomanip> // setprecision (desimal)
#include <limits>  // buat numeric_limits (clean buffer)

using namespace std;

// HELPERRRR
// apakah string hanya berisi angka
bool isNumeric(const string& str) {
    if (str.empty()) return false;
    for (char c : str) { // ternary
        // jika ada satu saja karakter yang bukan digit, return false
        if (!isdigit(c)) return false;
    }
    return true;
}

// cek duplikasi NIM (Sequential Search sederhana)
// cek data dari index 0 sampai sebelum index saat ini (currentIndex)
bool CekDuplikasiNIM(const Mahasiswa mhs[], int currentIndex, const string& nimBaru) {
    for (int k = 0; k < currentIndex; k++) {
        if (mhs[k].nim == nimBaru) {
            return true; // duplicate ditemukan
        }
    }
    return false; // tidak ada duplicate
}

// 1. InputData
void InputData(Mahasiswa mhs[], int &jumlahMhs) {
    // validasi input jumlah mahasiswa
    do {
        cout << "Masukkan jumlah mahasiswa: ";
        if (!(cin >> jumlahMhs)) {
            cout << "ERROR: Input harus berupa angka.\n";
            cin.clear();                                          // reset status error cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear buffer
            jumlahMhs = -1;                                       // set invalid agar loop berulang
        } else if (jumlahMhs <= 0 || jumlahMhs > MAX_MAHASISWA) {
            cout << "ERROR: Jumlah harus > 0 dan <= " << MAX_MAHASISWA << ".\n";
        }
    } while (jumlahMhs <= 0 || jumlahMhs > MAX_MAHASISWA);
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');          // clear buffer

    // loop input data per-mahasiswa
    for (int i = 0; i < jumlahMhs; i++) {
        cout << "\n--- Data Mahasiswa ke-" << (i + 1) << " ---\n";
        
        string inputTemp;

        // A. Input NIM
        do {
            cout << "Masukkan NIM: ";
            getline(cin, inputTemp);
            // validasi NIM tidak boleh kosong & duplikasi
            if (inputTemp.empty()) {
                cout << "ERROR: NIM tidak boleh kosong.\n";
            } else if (CekDuplikasiNIM(mhs, i, inputTemp)) {
                cout << "ERROR: NIM sudah terdaftar. Masukkan NIM lain.\n";
            } else {
                mhs[i].nim = inputTemp;
                break; // Input valid, keluar loop
            }
        } while (true);

        // B. Input Nama 
        do {
            cout << "Masukkan Nama: ";
            getline(cin, inputTemp);
            // validasi nama tidak boleh kosong & bukan angka
            if (inputTemp.empty()) {
                cout << "ERROR: Nama tidak boleh kosong.\n";
            } else if (isNumeric(inputTemp)) {
                cout << "ERROR: Nama tidak boleh berupa angka.\n";
            } else {
                mhs[i].nama = inputTemp;
                break; // Input valid, keluar loop
            }
        } while (true);

        // C. jumlah hari terlambat 
        do {
            cout << "Masukkan Hari Terlambat: ";
            // validasi input harus angka & tidak negatif
            if (!(cin >> mhs[i].hariTerlambat)) {
                cout << "ERROR: Input harus berupa angka.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mhs[i].hariTerlambat = -1;
            } else if (mhs[i].hariTerlambat < 0) {
                cout << "ERROR: Hari tidak boleh negatif.\n";
            }
        } while (mhs[i].hariTerlambat < 0);
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
    }
}






