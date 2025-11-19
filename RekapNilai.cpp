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






