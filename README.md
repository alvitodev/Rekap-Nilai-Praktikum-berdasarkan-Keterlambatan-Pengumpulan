# Rekap Nilai Praktikum berdasarkan Keterlambatan Pengumpulan

Program bertujuan untuk membantu dosen atau pembimbing menghitung nilai berdasarkan keterlambatan mahasiswa saat mengumpulkan tugas. Program akan menghitung nilai berdasarkan berapa hari keterlambatan tugas yang dikumpulkan, serta program bisa menampilkan hasil yang telah diurutkan dan dapat dicari.

## Pseudocode

### Struktur data & Variabel Global

```py
// Tipe data terstruktur untuk menampung data mahasiswa
TYPE Mahasiswa RECORD
    NIM : STRING
    Nama : STRING
    HariTerlambat : INTEGER
    NilaiAkhir : REAL
    Status : STRING
    Ranking : INTEGER
END RECORD

// Deklarasi Variabel Global
VAR DaftarMahasiswa : ARRAY OF Mahasiswa
VAR JumlahMahasiswa : INTEGER
VAR DataSudahDiinput : BOOLEAN
VAR PilihanMenu : INTEGER
```

### RekapNilai() (main program)

```py
PROGRAM RekapNilai
BEGIN
    DataSudahDiinput <- False

    REPEAT
        DISPLAY "--- MENU UTAMA ---"
        DISPLAY "1. Input Data Mahasiswa"
        DISPLAY "2. Tampilkan Daftar Nilai Lengkap"
        DISPLAY "3. Tampilkan Peringkat"
        DISPLAY "4. Cari Mahasiswa"
        DISPLAY "5. Keluar"
        DISPLAY "Pilihan Anda: "
        READ PilihanMenu

        // Validasi jika data belum diinput
        IF (PilihanMenu > 1 AND PilihanMenu < 5) AND (DataSudahDiinput = False) THEN
            DISPLAY "ERROR: Harap input data terlebih dahulu (Pilihan 1)."
        ELSE
            // Struktur CASE untuk navigasi menu
            CASE PilihanMenu OF
                1:
                    CALL InputData
                    CALL HitungNilai
                    CALL UrutkanData
                    DataSudahDiinput <- True
                2:
                    CALL TampilDataLengkap
                3:
                    CALL TampilRanking
                4:
                    CALL CariMahasiswa
                5:
                    DISPLAY "Terima kasih. Program selesai."
                DEFAULT:
                    DISPLAY "ERROR: Pilihan tidak valid."
            END CASE
        END IF
    UNTIL PilihanMenu = 5
END PROGRAM
```

### InputData()

```py
PROCEDURE InputData
BEGIN
    REPEAT
        DISPLAY "Masukkan jumlah mahasiswa: "
        READ JumlahMahasiswa
        IF (ISNUMERIC(JumlahMahasiswa) = FALSE) OR (JumlahMahasiswa <= 0) THEN
            DISPLAY "ERROR: Jumlah mahasiswa harus berupa angka dan lebih dari 0."
        END IF
    UNTIL (ISNUMERIC(JumlahMahasiswa) = TRUE) AND (JumlahMahasiswa > 0)

    // Alokasikan memori untuk array berdasarkan JumlahMahasiswa

    FOR i <- 1 TO JumlahMahasiswa DO
        DISPLAY "--- Data Mahasiswa ke-", i, " ---"
        DISPLAY "Masukkan NIM: "
        READ DaftarMahasiswa[i].NIM
        DISPLAY "Masukkan Nama: "
        READ DaftarMahasiswa[i].Nama

// Validasi duplikasi NIM
REPEAT
    DISPLAY "Masukkan NIM: "
    READ NIMBaru
    IF (CekDuplikasiNIM(DaftarMahasiswa, i-1, NIMBaru) = TRUE) THEN
        DISPLAY "ERROR: NIM sudah terdaftar. Masukkan NIM lain."
        END IF
 UNTIL CekDuplikasiNIM(DaftarMahasiswa, i-1, NIMBaru) = FALSE
 DaftarMahasiswa[i].NIM <- NIMBaru

        // Validasi nama tidak numerik
        REPEAT
            DISPLAY "Masukkan Nama: "
            READ NamaBaru
            IF ISNUMERIC(NamaBaru) = TRUE THEN
                DISPLAY "ERROR: Nama tidak boleh berupa angka."
            END IF
        UNTIL ISNUMERIC(NamaBaru) = FALSE
        DaftarMahasiswa[i].Nama <- NamaBaru


        // Loop validasi input HariTerlambat
        REPEAT
            DISPLAY "Masukkan Hari Terlambat: "
            READ DaftarMahasiswa[i].HariTerlambat
            IF DaftarMahasiswa[i].HariTerlambat < 0 THEN
                DISPLAY "ERROR: Hari tidak boleh negatif."
            END IF
        UNTIL DaftarMahasiswa[i].HariTerlambat >= 0
    END FOR
END PROCEDURE
```

### HitungNilai()

```py
PROCEDURE HitungNilai
BEGIN
    VAR NilaiAwal : CONSTANT INTEGER = 100
    VAR Potongan : REAL
    
    FOR i <- 1 TO JumlahMahasiswa DO
        VAR Hari : INTEGER
        Hari <- DaftarMahasiswa[i].HariTerlambat

        IF Hari = 0 THEN
            Potongan <- 0
            DaftarMahasiswa[i].Status <- "Tepat Waktu"
        ELSE IF Hari = 1 OR Hari = 2 THEN
            Potongan <- 0.10 * NilaiAwal
            DaftarMahasiswa[i].Status <- "Terlambat (1-2 hr)"
        ELSE IF Hari >= 3 AND Hari <= 5 THEN
            Potongan <- 0.25 * NilaiAwal
            DaftarMahasiswa[i].Status <- "Terlambat (3-5 hr)"
        ELSE // Hari > 5
            Potongan <- 0.50 * NilaiAwal
            DaftarMahasiswa[i].Status <- "Terlambat (>5 hr)"
        END IF

        DaftarMahasiswa[i].NilaiAkhir <- NilaiAwal - Potongan
    END FOR
END PROCEDURE
```

### UrutkanData()

```py
PROCEDURE UrutkanData
BEGIN
    VAR Temp : Mahasiswa // Variabel sementara untuk SWAP

    // Algoritma Bubble Sort (Descending berdasarkan NilaiAkhir)
    FOR i <- 1 TO (JumlahMahasiswa - 1) DO
        FOR j <- 1 TO (JumlahMahasiswa - i) DO
            IF DaftarMahasiswa[j].NilaiAkhir < DaftarMahasiswa[j+1].NilaiAkhir THEN
                // Lakukan SWAP
                Temp <- DaftarMahasiswa[j]
                DaftarMahasiswa[j] <- DaftarMahasiswa[j+1]
                DaftarMahasiswa[j+1] <- Temp
            END IF
        END FOR
    END FOR

    IF Tukar = FALSE THEN
            EXIT FOR // Early exit optimization
        END IF
    END FOR

    // Tetapkan Ranking setelah data diurutkan
    FOR i <- 1 TO JumlahMahasiswa DO
        DaftarMahasiswa[i].Ranking <- i
    END FOR
END PROCEDURE
```

### TampilDataLengkap()

```py
PROCEDURE TampilDataLengkap
BEGIN
    DISPLAY "--- Daftar Nilai Lengkap Mahasiswa ---"
    DISPLAY "Rank | NIM | Nama | Status | Nilai"
    DISPLAY "---------------------------------------------------"
    
    FOR i <- 1 TO JumlahMahasiswa DO
        DISPLAY DaftarMahasiswa[i].Ranking, " | ", 
                DaftarMahasiswa[i].NIM, " | ", 
                DaftarMahasiswa[i].Nama, " | ", 
                DaftarMahasiswa[i].Status, " | ", 
                DaftarMahasiswa[i].NilaiAkhir
    END FOR
END PROCEDURE
```

### TampilRanking()

```py
PROCEDURE TampilRanking
BEGIN
    DISPLAY "--- Peringkat Mahasiswa ---"
    DISPLAY "Rank | Nama | Nilai"
    DISPLAY "------------------------------"
    
    FOR i <- 1 TO JumlahMahasiswa DO
        DISPLAY DaftarMahasiswa[i].Ranking, " | ", 
                DaftarMahasiswa[i].Nama, " | ", 
                DaftarMahasiswa[i].NilaiAkhir
    END FOR
END PROCEDURE
```

### CariMahasiswa()

```py
PROCEDURE CariMahasiswa
BEGIN
    VAR KataKunci : STRING
    VAR Ditemukan : BOOLEAN
    VAR i : INTEGER

    DISPLAY "Masukkan NIM atau Nama yang dicari: "
    READ KataKunci
    
    Ditemukan <- False
    i <- 1

    // Algoritma Sequential Search
    WHILE i <= JumlahMahasiswa AND Ditemukan = False DO
        IF DaftarMahasiswa[i].NIM = KataKunci OR DaftarMahasiswa[i].Nama = KataKunci THEN
            Ditemukan <- True
        ELSE
            i <- i + 1
        END IF
    END WHILE

    // Tampilkan hasil
    IF Ditemukan = True THEN
        DISPLAY "Data Ditemukan:"
        DISPLAY "Ranking : ", DaftarMahasiswa[i].Ranking
        DISPLAY "NIM     : ", DaftarMahasiswa[i].NIM
        DISPLAY "Nama    : ", DaftarMahasiswa[i].Nama
        DISPLAY "Status  : ", DaftarMahasiswa[i].Status
        DISPLAY "Nilai   : ", DaftarMahasiswa[i].NilaiAkhir
    ELSE
        DISPLAY "Data dengan kata kunci '", KataKunci, "' tidak ditemukan."
    END IF
END PROCEDURE
```
