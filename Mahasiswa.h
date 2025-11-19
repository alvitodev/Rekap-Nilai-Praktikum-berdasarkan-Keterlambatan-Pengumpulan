#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <string>
#include <iostream>
using namespace std;

const int MAX_MAHASISWA = 100; // ukuran array
const double NILAI_AWAL_DEFAULT = 100.0;

struct Mahasiswa {
    string nim;
    string nama;
    int hariTerlambat;
    double nilaiAkhir;
    string statusKeterlambatan;
    int ranking;
};
// untuk cek string angka dan duplikasi NIM
bool isNumeric(const string& str);
bool CekDuplikasiNIM(const Mahasiswa mhs[], int currentIndex, const string& nimBaru);

// InputData menerima reference& untuk jumlahMhs karena nilainya akan diubah di dalam fungsi
void InputData(Mahasiswa mhs[], int &jumlahMhs);

// menerima array dan jumlah data untuk diproses
void HitungNilai(Mahasiswa mhs[], int jumlahMhs);
void UrutkanData(Mahasiswa mhs[], int jumlahMhs);

// fungsi menampilkan data, parameter menggunakan const karena hanya membaca data
void TampilDataLengkap(const Mahasiswa mhs[], int jumlahMhs);
void TampilRanking(const Mahasiswa mhs[], int jumlahMhs);
void CariMahasiswa(const Mahasiswa mhs[], int jumlahMhs);

#endif