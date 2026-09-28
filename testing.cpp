
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ============================================================================
// STRUKTUR DATA
// ============================================================================
struct KaryaSeni {
    string judul;      // Judul tampilan karya seni (misal: "Kucing Lucu")
    string namaFile;   // Nama file tanpa ekstensi .txt (misal: "kucing")
    string kategori;   // Nama kategori/folder (misal: "Hewan")
    string deskripsi;  // Keterangan singkat mengenai karya
};

struct Kategori {
    string nama;                  // Nama kategori (misal: "Hewan")
    string keterangan;            // Keterangan kategori
    vector<KaryaSeni> daftarKarya; // Daftar karya seni di dalamnya
};

// ============================================================================
// FUNGSI BANTUAN TAMPILAN & KONSOL
// ============================================================================
void aktifkanModeKonsol() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

void batas(int panjang = 80, char simbol = '=') {
    for (int i = 0; i < panjang; i++) {
        cout << simbol;
    }
    cout << "\n";
}

void tekanEnter(const string& pesan = "  Tekan [ENTER] untuk melanjutkan...") {
    cout << pesan;
    string temp;
    getline(cin, temp);
}

void headerAplikasi() {
    cout << "\n";
    batas(80, '=');
    cout << "          * * *  GALERI KARYA SENI ASCII (ASCII ART GALLERY)  * * *          \n";
    cout << "             Dasar Pemrograman - UIN Sunan Gunung Djati Bandung              \n";
    batas(80, '=');
}

void headerHalaman(const string& breadcrumb) {
    cout << "  LOKASI: [ " << breadcrumb << " ]\n";
    batas(80, '-');
    cout << "\n";
}

// ============================================================================
// FUNGSI MANIPULASI STRING
// ============================================================================
string pangkasSpasi(const string& str) {
    size_t awal = str.find_first_not_of(" \t\r\n");
    if (awal == string::npos) return "";
    size_t akhir = str.find_last_not_of(" \t\r\n");
    return str.substr(awal, (akhir - awal + 1));
}

string keHurufKecil(string s) {
    for (char &c : s) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return s;
}

string kapitalPerKata(string s) {
    bool baru = true;
    for (char &c : s) {
        if (isspace(static_cast<unsigned char>(c)) || c == '-' || c == '_') {
            baru = true;
        } else if (baru) {
            c = toupper(static_cast<unsigned char>(c));
            baru = false;
        } else {
            c = tolower(static_cast<unsigned char>(c));
        }
    }
    return s;
}

// ============================================================================
// FUNGSI INPUT AMAN & RAMAH PENGGUNA (ANTI-CRASH)
// ============================================================================
string inputBaris(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int inputAngka(int min, int max, const string& prompt = "  Pilihan Anda: ") {
    while (true) {
        cout << prompt;
        string baris;
        getline(cin, baris);
        baris = pangkasSpasi(baris);

        if (baris.empty()) {
            cout << "  [!] Input tidak boleh kosong. Silakan masukkan angka [" << min << " - " << max << "].\n";
            continue;
        }

        try {
            size_t pos = 0;
            int nilai = stoi(baris, &pos);
            if (pos == baris.length() && nilai >= min && nilai <= max) {
                return nilai;
            }
        } catch (...) {
            // Tangkap jika bukan angka
        }

        cout << "  [!] Pilihan tidak valid. Silakan ketik angka antara " << min << " sampai " << max << ".\n";
    }
}

bool inputKonfirmasi(const string& prompt, bool defaultYa = true) {
    while (true) {
        cout << prompt;
        string baris;
        getline(cin, baris);
        baris = pangkasSpasi(baris);

        if (baris.empty()) {
            return defaultYa;
        }

        string bLower = keHurufKecil(baris);
        if (bLower == "y" || bLower == "ya" || bLower == "yes" || bLower == "1") {
            return true;
        }
        if (bLower == "n" || bLower == "tidak" || bLower == "no" || bLower == "t" || bLower == "0") {
            return false;
        }

        cout << "  [!] Ketik 'Y' untuk Ya, atau 'N' untuk Tidak.\n";
    }
}

// ============================================================================
// FUNGSI TAMPILKAN GAMBAR DARI FILE
// ============================================================================
bool tampilkanIsiFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        return false;
    }
    string baris;
    while (getline(file, baris)) {
        cout << baris << "\n";
    }
    file.close();
    return true;
}

void tampilkanKarya(const KaryaSeni& karya) {
    bersihkanLayar();
    headerAplikasi();
    cout << "\n";
    batas(80, '=');
    cout << "   KARYA SENI : " << karya.judul << "\n";
    cout << "   Kategori   : " << karya.kategori;
    if (!karya.deskripsi.empty()) {
        cout << " (" << karya.deskripsi << ")";
    }
    cout << "\n";
    batas(80, '-');
    cout << "\n";

    string path = karya.kategori + "/" + karya.namaFile + ".txt";
    bool sukses = tampilkanIsiFile(path);

    if (!sukses) {
        // Coba cari di folder root
        sukses = tampilkanIsiFile(karya.namaFile + ".txt");
    }

    if (!sukses) {
        cout << "  [!] Mohon maaf, berkas karya seni '" << karya.namaFile << ".txt' tidak dapat dibuka.\n";
        cout << "      Berkas mungkin belum dibuat atau lokasi file berbeda.\n\n";
    }

    cout << "\n";
    batas(80, '=');
    cout << "\n";
}

// ============================================================================
// INISIALISASI DATA KOLEKSI KARYA SENI
// ============================================================================
vector<Kategori> inisialisasiKoleksi() {
    vector<Kategori> list;

    // 1. Hewan
    Kategori hewan;
    hewan.nama = "Hewan";
    hewan.keterangan = "Berbagai ilustrasi hewan darat, air, dan udara.";
    hewan.daftarKarya = {
        {"Anjing Setia", "anjing", "Hewan", "Ilustrasi sahabat setia berkaki empat"},
        {"Burung Elang / Merpati", "burung", "Hewan", "Siluet burung yang terbang bebas"},
        {"Gajah Perkasa", "gajah", "Hewan", "Raksasa rimba yang anggun dan kuat"},
        {"Ikan Akuarium Samudera", "ikan", "Hewan", "Kehidupan bawah laut yang memesona"},
        {"Kelinci Lucu", "kelinci", "Hewan", "Kelinci mungil bertelinga panjang"},
        {"Tiga Kucing Menggemaskan", "kucing", "Hewan", "Trio kucing mengintip di atas pagar"},
        {"Kura-kura Bijak", "kura kura", "Hewan", "Kura-kura tenang penjelajah waktu"}
    };
    list.push_back(hewan);

    // 2. Bangun Datar
    Kategori bangunDatar;
    bangunDatar.nama = "Bangun Datar";
    bangunDatar.keterangan = "Bentuk-bentuk geometris simetris berpresisi tinggi.";
    bangunDatar.daftarKarya = {
        {"Belah Ketupat", "belah ketupat", "Bangun Datar", "Bentuk intan geometris simetris"},
        {"Bintang Kejora", "bintang", "Bangun Datar", "Bintang lima sudut yang bercahaya"},
        {"Lingkaran Sempurna", "lingkaran", "Bangun Datar", "Kurva tertutup tanpa sudut"},
        {"Persegi Simetris", "persegi", "Bangun Datar", "Segi empat teratur sama sisi"},
        {"Segi Delapan (Oktagon)", "segi delapan", "Bangun Datar", "Bentuk segi delapan beraturan"},
        {"Segi Enam (Heksagon)", "segi enam", "Bangun Datar", "Pola heksagon sarang lebah"},
        {"Segi Lima (Pentagon)", "segi lima", "Bangun Datar", "Segi lima geometris teratur"},
        {"Segitiga Piramida", "segitiga", "Bangun Datar", "Bentuk tiga sudut kokoh"}
    };
    list.push_back(bangunDatar);

    // 3. Manusia & Tokoh
    Kategori manusia;
    manusia.nama = "Manusia";
    manusia.keterangan = "Siluet sosok manusia dan figur tokoh inspiratif.";
    manusia.daftarKarya = {
        {"Elon Musk", "elon musk", "Manusia", "Tokoh teknologi dan visioner antariksa"},
        {"Ferry Irwandi", "ferry irwandi", "Manusia", "Content creator dan narator edukasi"},
        {"Joko Widodo (Jokowi)", "jokowi", "Manusia", "Presiden Republik Indonesia ke-7"},
        {"Sosok Manusia", "manusia", "Manusia", "Siluet figur wajah manusia"},
        {"Thomas Slebew", "thomas slebew", "Manusia", "Karakter ikonik humor populer"}
    };
    list.push_back(manusia);

    // 4. Pemandangan
    Kategori pemandangan;
    pemandangan.nama = "Pemandangan";
    pemandangan.keterangan = "Pemandangan alam pegunungan, pantai, dan kepulauan.";
    pemandangan.daftarKarya = {
        {"Peta Kepulauan Indonesia", "indonesia", "Pemandangan", "Zamrud Khatulistiwa dari Sabang sampai Merauke"},
        {"Panorama Alam Panorama", "pemandangan", "Pemandangan", "Gunung megah, pesisir pantai, dan cakrawala"}
    };
    list.push_back(pemandangan);

    // 5. Rumah & Arsitektur
    Kategori rumah;
    rumah.nama = "Rumah";
    rumah.keterangan = "Desain hunian dari sederhana hingga arsitektur tradisional.";
    rumah.daftarKarya = {
        {"Rumah Idaman Sederhana", "rumah sederhana", "Rumah", "Hunian hangat yang asri dan nyaman"},
        {"Vila / Rumah Mewah Dua Lantai", "rumah mewah", "Rumah", "Desain tempat tinggal megah dan elegan"},
        {"Rumah Adat Nusantara", "rumah adat", "Rumah", "Warisan arsitektur tradisional Indonesia"}
    };
    list.push_back(rumah);

    // 6. Tumbuhan & Alam
    Kategori tumbuhan;
    tumbuhan.nama = "Tumbuhan";
    tumbuhan.keterangan = "Keindahan flora, bunga merekah, dan pepohonan.";
    tumbuhan.daftarKarya = {
        {"Bunga Mekar Semerbak", "bunga", "Tumbuhan", "Kuntum bunga yang mekar di musim semi"},
        {"Pohon Rindang Teduh", "pohon", "Tumbuhan", "Pohon besar berdaun lebat penyejuk alam"}
    };
    list.push_back(tumbuhan);

    // 7. Koleksi Pribadi
    Kategori pribadi;
    pribadi.nama = "Koleksi Pribadi";
    pribadi.keterangan = "Karya seni orisinal yang Anda buat sendiri di studio.";
    pribadi.daftarKarya = {};
    list.push_back(pribadi);

    return list;
}

// ============================================================================
// MODE PAMERAN (SLIDESHOW DENGAN KONTROL PENGGUNA)
// ============================================================================
void modePameranKategori(const vector<KaryaSeni>& daftar, int mulaiDari, const string& namaKategori) {
    bersihkanLayar();
    headerAplikasi();
    headerHalaman("PAMERAN KARYA : " + namaKategori);

    cout << "  Selamat datang di Mode Pameran Karya Seni [" << namaKategori << "]!\n";
    cout << "  Setiap karya akan ditampilkan satu per satu secara berurutan.\n";
    cout << "  Anda dapat menikmati setiap karya tanpa terburu-buru.\n\n";
    tekanEnter("  Tekan [ENTER] untuk memulai pameran...");

    for (size_t i = mulaiDari; i < daftar.size(); ++i) {
        tampilkanKarya(daftar[i]);
        cout << "  Informasi: Menampilkan karya [" << (i + 1) << " dari " << daftar.size() << "] - " << daftar[i].judul << "\n";
        batas(80, '-');

        if (i + 1 < daftar.size()) {
            cout << "  Tekan [ENTER] untuk melanjutkan ke: " << daftar[i + 1].judul << "\n";
            cout << "  (Atau ketik '0' lalu tekan ENTER jika ingin menghentikan pameran): ";
            string input;
            getline(cin, input);
            input = pangkasSpasi(input);
            if (input == "0" || keHurufKecil(input) == "batal" || keHurufKecil(input) == "q") {
                cout << "\n  Pameran dihentikan oleh pengunjung.\n";
                tekanEnter();
                return;
            }
        } else {
            cout << "  Selamat! Anda telah selesai menikmati seluruh karya dalam kategori ini!\n";
            tekanEnter("  Tekan [ENTER] untuk kembali ke menu...");
        }
    }
}

// ============================================================================
// NAVIGASI INTERAKTIF PENAMPIL KARYA (NEXT / PREV / BACK)
// ============================================================================
void lihatKaryaDenganNavigasi(vector<KaryaSeni>& daftar, int indexAwal, const string& namaKategori) {
    if (daftar.empty()) {
        cout << "\n  [!] Belum ada karya seni yang tersedia dalam kategori ini.\n";
        tekanEnter();
        return;
    }

    int index = indexAwal;
    while (true) {
        if (index < 0) index = (int)daftar.size() - 1;
        if (index >= (int)daftar.size()) index = 0;

        tampilkanKarya(daftar[index]);

        cout << "  Status: Karya [" << (index + 1) << " dari " << daftar.size() << "] dalam Kategori " << namaKategori << "\n";
        batas(80, '-');
        cout << "  PILIHAN NAVIGASI:\n";
        cout << "    [1] >> Karya Selanjutnya : " << daftar[(index + 1) % daftar.size()].judul << "\n";
        cout << "    [2] << Karya Sebelumnya  : " << daftar[(index - 1 + daftar.size()) % daftar.size()].judul << "\n";
        cout << "    [3] || Mulai Pameran Slideshow dari Karya Ini\n";
        cout << "    [4] -- Kembali ke Daftar Karya Kategori " << namaKategori << "\n";
        cout << "    [0] == Kembali ke Menu Utama\n";
        batas(80, '-');

        int nav = inputAngka(0, 4, "  Masukkan pilihan navigasi Anda [0-4]: ");
        if (nav == 1) {
            index = (index + 1) % daftar.size();
        } else if (nav == 2) {
            index = (index - 1 + daftar.size()) % daftar.size();
        } else if (nav == 3) {
            modePameranKategori(daftar, index, namaKategori);
            break;
        } else if (nav == 4) {
            break;
        } else if (nav == 0) {
            break;
        }
    }
}

// ============================================================================
// MENU 1: JELAJAHI GALERI BERDASARKAN KATEGORI
// ============================================================================
void menuJelajahiKategori(vector<Kategori>& semuaKategori) {
    while (true) {
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("JELAJAHI GALERI > PILIH KATEGORI");

        cout << "  Silakan pilih kategori karya seni yang ingin Anda jelajahi:\n\n";
        for (size_t i = 0; i < semuaKategori.size(); ++i) {
            cout << "    [" << (i + 1) << "] " << left << setw(18) << semuaKategori[i].nama
                 << " : " << semuaKategori[i].keterangan 
                 << " (" << semuaKategori[i].daftarKarya.size() << " karya)\n";
        }
        cout << "\n    [0] Kembali ke Menu Utama\n";
        batas(80, '-');

        int pilihanKat = inputAngka(0, (int)semuaKategori.size(), "  Pilih nomor kategori [0-" + to_string(semuaKategori.size()) + "]: ");
        if (pilihanKat == 0) {
            break;
        }

        Kategori& katDipilih = semuaKategori[pilihanKat - 1];

        // Sub-menu karya di kategori ini
        while (true) {
            bersihkanLayar();
            headerAplikasi();
            headerHalaman("JELAJAHI GALERI > " + katDipilih.nama);

            cout << "  Daftar karya seni dalam kategori [" << katDipilih.nama << "]:\n\n";
            if (katDipilih.daftarKarya.empty()) {
                cout << "    (Saat ini belum ada karya seni yang tersimpan di kategori ini.)\n";
                cout << "    Anda dapat menambahkan karya baru melalui menu 'Studio Pembuat Gambar'!\n\n";
                cout << "    [0] Kembali ke Pilihan Kategori\n";
                batas(80, '-');
                inputAngka(0, 0, "  Ketik 0 untuk kembali: ");
                break;
            }

            for (size_t i = 0; i < katDipilih.daftarKarya.size(); ++i) {
                cout << "    [" << (i + 1) << "] " << left << setw(32) << katDipilih.daftarKarya[i].judul;
                if (!katDipilih.daftarKarya[i].deskripsi.empty()) {
                    cout << " - " << katDipilih.daftarKarya[i].deskripsi;
                }
                cout << "\n";
            }

            cout << "\n";
            cout << "    [P] Tampilkan Semua Karya (Mode Pameran / Slideshow)\n";
            cout << "    [0] Kembali ke Pilihan Kategori\n";
            batas(80, '-');

            cout << "  Pilih nomor karya seni yang ingin dilihat [1-" << katDipilih.daftarKarya.size() << "] atau 'P' / '0': ";
            string inputPilih;
            getline(cin, inputPilih);
            inputPilih = pangkasSpasi(inputPilih);
            string inputLower = keHurufKecil(inputPilih);

            if (inputLower == "0" || inputLower == "kembali" || inputLower == "batal") {
                break;
            } else if (inputLower == "p" || inputLower == "semua" || inputLower == "slideshow") {
                modePameranKategori(katDipilih.daftarKarya, 0, katDipilih.nama);
            } else {
                try {
                    int noKarya = stoi(inputPilih);
                    if (noKarya >= 1 && noKarya <= (int)katDipilih.daftarKarya.size()) {
                        lihatKaryaDenganNavigasi(katDipilih.daftarKarya, noKarya - 1, katDipilih.nama);
                    } else {
                        cout << "\n  [!] Pilihan tidak tersedia. Silakan pilih nomor antara 1 sampai " << katDipilih.daftarKarya.size() << ".\n";
                        tekanEnter();
                    }
                } catch (...) {
                    cout << "\n  [!] Input tidak valid. Masukkan nomor karya seni, 'P' untuk pameran, atau '0' untuk kembali.\n";
                    tekanEnter();
                }
            }
        }
    }
}

// ============================================================================
// MENU 2: PENCARIAN CERDAS (SMART SEARCH)
// ============================================================================
void menuPencarian(vector<Kategori>& semuaKategori) {
    while (true) {
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("PENCARIAN KARYA SENI CERDAS");

        cout << "  Fitur Pencarian Galeri Seni ASCII\n";
        cout << "  Temukan karya seni berdasarkan nama gambar, nama tokoh, atau bentuk yang Anda cari.\n\n";
        cout << "  Tips Pencarian:\n";
        cout << "  - Pencarian fleksibel & bebas huruf besar/kecil (contoh: 'kucing', 'jokowi', 'segi').\n";
        cout << "  - Mendukung kata kunci berspasi (contoh: 'kura kura', 'elon musk', 'rumah mewah').\n";
        cout << "  - Ketik 'DAFTAR' untuk melihat katalog semua karya yang ada di galeri.\n";
        cout << "  - Ketik '0' untuk kembali ke Menu Utama.\n";
        batas(80, '-');

        string kataKunci = inputBaris("  Masukkan nama karya yang ingin Anda cari: ");
        kataKunci = pangkasSpasi(kataKunci);

        if (kataKunci == "0" || keHurufKecil(kataKunci) == "kembali" || keHurufKecil(kataKunci) == "batal") {
            break;
        }

        if (kataKunci.empty()) {
            cout << "\n  [!] Kata kunci pencarian tidak boleh kosong.\n";
            tekanEnter();
            continue;
        }

        if (keHurufKecil(kataKunci) == "daftar" || keHurufKecil(kataKunci) == "help" || keHurufKecil(kataKunci) == "list") {
            bersihkanLayar();
            headerAplikasi();
            headerHalaman("KATALOG SELURUH KOLEKSI KARYA SENI");
            cout << "  Berikut adalah seluruh koleksi karya seni yang tersimpan di galeri:\n\n";
            for (const auto& kat : semuaKategori) {
                cout << "  * KATEGORI " << kat.nama << " (" << kat.daftarKarya.size() << " karya):\n";
                for (const auto& item : kat.daftarKarya) {
                    cout << "    - " << left << setw(30) << item.judul 
                         << " [Kata kunci: " << item.namaFile << "]\n";
                }
                cout << "\n";
            }
            batas(80, '=');
            tekanEnter();
            continue;
        }

        string queryLower = keHurufKecil(kataKunci);

        // Pencarian dengan peringkat kecocokan
        struct HasilCari {
            KaryaSeni karya;
            int prioritas; // 2 = match tepat, 1 = partial match
        };
        vector<HasilCari> hasil;

        for (const auto& kat : semuaKategori) {
            for (const auto& item : kat.daftarKarya) {
                string fileLower = keHurufKecil(item.namaFile);
                string judulLower = keHurufKecil(item.judul);

                if (fileLower == queryLower || judulLower == queryLower) {
                    hasil.push_back({item, 2});
                } else if (fileLower.find(queryLower) != string::npos || judulLower.find(queryLower) != string::npos) {
                    hasil.push_back({item, 1});
                }
            }
        }

        if (hasil.empty()) {
            cout << "\n  Mohon maaf, karya seni dengan kata kunci \"" << kataKunci << "\" belum ditemukan di galeri.\n\n";
            cout << "  Opsi yang dapat Anda pilih:\n";
            cout << "    [1] Coba cari lagi dengan kata kunci lain\n";
            cout << "    [2] Buka katalog lengkap semua karya seni yang tersedia\n";
            cout << "    [0] Kembali ke Menu Utama\n";
            batas(80, '-');

            int ops = inputAngka(0, 2, "  Pilihan Anda [0-2]: ");
            if (ops == 1) {
                continue;
            } else if (ops == 2) {
                bersihkanLayar();
                headerAplikasi();
                headerHalaman("KATALOG SELURUH KOLEKSI KARYA SENI");
                for (const auto& kat : semuaKategori) {
                    cout << "  * KATEGORI " << kat.nama << ":\n";
                    for (const auto& item : kat.daftarKarya) {
                        cout << "    - " << item.judul << " (keyword: " << item.namaFile << ")\n";
                    }
                    cout << "\n";
                }
                tekanEnter();
            } else {
                break;
            }
        } else if (hasil.size() == 1) {
            cout << "\n  [DITEMUKAN] Karya seni cocok ditemukan!\n";
            cout << "  Judul    : " << hasil[0].karya.judul << "\n";
            cout << "  Kategori : " << hasil[0].karya.kategori << "\n\n";
            tekanEnter("  Tekan [ENTER] untuk menampilkan karya seni...");

            tampilkanKarya(hasil[0].karya);

            bool cariLagi = inputKonfirmasi("  Ingin mencari karya seni lainnya? (Y/N): ", true);
            if (!cariLagi) break;
        } else {
            while (true) {
                bersihkanLayar();
                headerAplikasi();
                headerHalaman("HASIL PENCARIAN : \"" + kataKunci + "\"");
                cout << "  Ditemukan " << hasil.size() << " karya seni yang cocok dengan pencarian Anda:\n\n";
                for (size_t i = 0; i < hasil.size(); ++i) {
                    cout << "    [" << (i + 1) << "] " << left << setw(30) << hasil[i].karya.judul 
                         << " (Kategori: " << hasil[i].karya.kategori << ")\n";
                }
                cout << "\n    [0] Kembali ke Pencarian\n";
                batas(80, '-');

                int noPilih = inputAngka(0, (int)hasil.size(), "  Pilih nomor karya seni yang ingin ditampilkan [0-" + to_string(hasil.size()) + "]: ");
                if (noPilih == 0) {
                    break;
                }

                tampilkanKarya(hasil[noPilih - 1].karya);
                tekanEnter();
            }

            bool cariLagi = inputKonfirmasi("  Ingin melakukan pencarian karya seni lain? (Y/N): ", true);
            if (!cariLagi) break;
        }
    }
}

// ============================================================================
// MENU 3: STUDIO PEMBUAT GAMBAR ASCII (BUAT KARYA SENDIRI)
// ============================================================================
void menuBuatGambar(vector<Kategori>& semuaKategori) {
    while (true) {
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("STUDIO PEMBUAT SENI ASCII");

        cout << "  Selamat datang di Studio Kreativitas Seni ASCII!\n";
        cout << "  Di sini Anda dapat menciptakan karya seni visual sendiri menggunakan teks.\n\n";
        cout << "  Tahapan Pembuatan:\n";
        cout << "   1. Masukkan judul karya seni Anda.\n";
        cout << "   2. Tentukan kategori penyimpanan yang sesuai.\n";
        cout << "   3. Gambar baris demi baris menggunakan karakter keyboard.\n";
        cout << "   4. Periksa pratinjau (preview) hasil kreasi Anda.\n";
        cout << "   5. Konfirmasi untuk menyimpan karya ke dalam galeri.\n\n";
        cout << "  *Ketik '0' atau 'BATAL' pada nama judul jika ingin membatalkan.\n";
        batas(80, '-');

        string namaJudul = inputBaris("  Masukkan Judul / Nama Karya Seni Anda: ");
        namaJudul = pangkasSpasi(namaJudul);

        if (namaJudul == "0" || keHurufKecil(namaJudul) == "batal" || keHurufKecil(namaJudul) == "b") {
            cout << "\n  Pembuatan karya dibatalkan. Kembali ke menu utama...\n";
            tekanEnter();
            break;
        }

        if (namaJudul.empty()) {
            cout << "\n  [!] Judul karya tidak boleh kosong!\n";
            tekanEnter();
            continue;
        }

        // Buat nama file aman untuk sistem berkas
        string namaFileBersih = "";
        for (char c : namaJudul) {
            if (c == '/' || c == '\\' || c == ':' || c == '*' || c == '?' || c == '"' || c == '<' || c == '>' || c == '|') {
                namaFileBersih += '_';
            } else {
                namaFileBersih += c;
            }
        }
        string namaFileLower = keHurufKecil(namaFileBersih);

        // Pilih Kategori Penyimpanan
        cout << "\n  Pilih kategori tempat Anda ingin menyimpan karya ini:\n";
        for (size_t i = 0; i < semuaKategori.size(); ++i) {
            cout << "    [" << (i + 1) << "] " << semuaKategori[i].nama;
            if (semuaKategori[i].nama == "Koleksi Pribadi") {
                cout << " (Disarankan untuk karya orisinal Anda)";
            }
            cout << "\n";
        }
        cout << "    [0] Batalkan Pembuatan\n";
        batas(80, '-');

        int pilihanKat = inputAngka(0, (int)semuaKategori.size(), "  Pilih nomor kategori [0-" + to_string(semuaKategori.size()) + "]: ");
        if (pilihanKat == 0) {
            cout << "\n  Pembuatan karya seni dibatalkan.\n";
            tekanEnter();
            break;
        }

        Kategori& katTerpilih = semuaKategori[pilihanKat - 1];

        // Layar Studio Menggambar
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("STUDIO MENGGAMBAR : \"" + namaJudul + "\"");

        cout << "  Karya akan disimpan di : " << katTerpilih.nama << "/" << namaFileLower << ".txt\n";
        batas(80, '=');
        cout << "  PETUNJUK MENGGAMBAR:\n";
        cout << "  - Gambarlah baris demi baris menggunakan karakter pada keyboard Anda.\n";
        cout << "    Simbol rekomendasi: #  *  @  $  %  &  +  -  =  _  |  /  \\  (  )  ^  ~\n";
        cout << "  - Jika sudah selesai, ketik 'END' pada baris baru lalu tekan Enter.\n";
        cout << "  - Jika ingin membatalkan tanpa menyimpan, ketik 'BATAL' pada baris baru.\n";
        batas(80, '=');
        cout << "  Silakan mulai menggambar di bawah ini:\n\n";

        string isiGambar = "";
        string baris;
        bool dibatalkan = false;

        while (true) {
            getline(cin, baris);
            string barisTrim = pangkasSpasi(baris);
            if (barisTrim == "BATAL" || barisTrim == "batal") {
                dibatalkan = true;
                break;
            }
            if (barisTrim == "END" || barisTrim == "end") {
                break;
            }
            isiGambar += baris + "\n";
        }

        if (dibatalkan) {
            cout << "\n  Pembuatan gambar dibatalkan. Tidak ada berkas yang disimpan.\n";
            tekanEnter();
            bool cobaLagi = inputKonfirmasi("  Apakah Anda ingin mencoba membuat gambar lagi? (Y/N): ", true);
            if (cobaLagi) continue;
            else break;
        }

        if (pangkasSpasi(isiGambar).empty()) {
            cout << "\n  [!] Gambar masih kosong! Tidak ada karya yang dapat disimpan.\n";
            tekanEnter();
            bool cobaLagi = inputKonfirmasi("  Apakah Anda ingin mencoba lagi? (Y/N): ", true);
            if (cobaLagi) continue;
            else break;
        }

        // Tampilkan Pratinjau (Preview)
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("PRATINJAU HASIL KARYA ANDA");

        cout << "\n";
        batas(80, '=');
        cout << "   JUDUL KARYA : " << namaJudul << "\n";
        cout << "   Kategori    : " << katTerpilih.nama << "\n";
        batas(80, '-');
        cout << isiGambar;
        batas(80, '=');
        cout << "\n";

        bool simpan = inputKonfirmasi("  Apakah Anda puas dengan hasilnya dan ingin menyimpan karya ini? (Y/N): ", true);
        if (simpan) {
            // Pastikan folder ada jika koleksi pribadi
#ifdef _WIN32
            CreateDirectoryA(katTerpilih.nama.c_str(), NULL);
#endif
            string pathTujuan = katTerpilih.nama + "/" + namaFileLower + ".txt";
            ofstream fileOut(pathTujuan);
            bool berhasil = false;

            if (fileOut.is_open()) {
                fileOut << isiGambar;
                fileOut.close();
                berhasil = true;
            } else {
                // Alternatif simpan langsung di folder kerja jika sub-folder gagal
                string altPath = namaFileLower + ".txt";
                ofstream fileAlt(altPath);
                if (fileAlt.is_open()) {
                    fileAlt << isiGambar;
                    fileAlt.close();
                    pathTujuan = altPath;
                    berhasil = true;
                }
            }

            if (berhasil) {
                // Daftarkan langsung ke sistem agar dapat dilihat dan dicari seketika
                KaryaSeni karyaBaru;
                karyaBaru.judul = namaJudul;
                karyaBaru.namaFile = namaFileLower;
                karyaBaru.kategori = katTerpilih.nama;
                karyaBaru.deskripsi = "Karya seni orisinal buatan pengguna";
                katTerpilih.daftarKarya.push_back(karyaBaru);

                cout << "\n  [SELAMAT!] Karya seni Anda berhasil disimpan!\n";
                cout << "  Lokasi Berkas: " << pathTujuan << "\n\n";
                cout << "  Karya ini kini telah terdaftar di galeri dan dapat langsung Anda nikmati\n";
                cout << "  melalui menu 'Jelajahi Galeri' maupun menu 'Pencarian'!\n";
            } else {
                cout << "\n  [!] Mohon maaf, terjadi kendala saat menyimpan berkas ke penyimpanan.\n";
            }
        } else {
            cout << "\n  Karya seni tidak disimpan ke galeri.\n";
        }

        tekanEnter();
        bool buatLagi = inputKonfirmasi("  Apakah Anda ingin membuat karya seni lainnya? (Y/N): ", false);
        if (!buatLagi) break;
    }
}

// ============================================================================
// MENU 4: SOROTAN KARYA SENI ACAK (RANDOM ART SPOTLIGHT)
// ============================================================================
void menuKaryaAcak(vector<Kategori>& semuaKategori) {
    vector<KaryaSeni> semuaKarya;
    for (const auto& kat : semuaKategori) {
        for (const auto& item : kat.daftarKarya) {
            semuaKarya.push_back(item);
        }
    }

    if (semuaKarya.empty()) {
        cout << "\n  Belum ada koleksi karya seni yang tersedia.\n";
        tekanEnter();
        return;
    }

    while (true) {
        int idx = rand() % semuaKarya.size();
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("SOROTAN KARYA ACAK (SPOTLIGHT)");

        cout << "  Memilih karya seni secara acak dari seluruh koleksi galeri...\n";
        tekanEnter("  Tekan [ENTER] untuk menampilkan karya terpilih...");

        tampilkanKarya(semuaKarya[idx]);

        cout << "  Sorotan: " << semuaKarya[idx].judul << " (Kategori: " << semuaKarya[idx].kategori << ")\n";
        batas(80, '-');
        cout << "  [1] Acak dan tampilkan karya seni lainnya\n";
        cout << "  [0] Kembali ke Menu Utama\n";
        batas(80, '-');

        int opt = inputAngka(0, 1, "  Pilihan Anda [0/1]: ");
        if (opt == 0) break;
    }
}

// ============================================================================
// MENU 5: PANDUAN PENGGUNAAN & TENTANG GALERI
// ============================================================================
void menuBantuan() {
    bersihkanLayar();
    headerAplikasi();
    headerHalaman("PANDUAN PENGGUNAAN & TENTANG APLIKASI");

    cout << "  TENTANG GALERI SENI ASCII:\n";
    cout << "  Seni ASCII (ASCII Art) adalah bentuk seni visual digital yang diciptakan\n";
    cout << "  menggunakan kombinasi karakter teks, angka, dan simbol tipografi standar.\n";
    cout << "  Aplikasi ini dibuat sebagai galeri interaktif yang memungkinkan siapa saja\n";
    cout << "  untuk menikmati keindahan seni berbasis teks secara terstruktur dan nyaman.\n\n";

    batas(80, '-');
    cout << "  FITUR DAN CARA PENGGUNAAN:\n";
    cout << "  1. Jelajahi Galeri Berdasarkan Kategori\n";
    cout << "     - Pilih kategori favorit (Hewan, Bangun Datar, Tokoh Manusia, dll).\n";
    cout << "     - Pilih karya tertentu, atau nikmati Mode Slideshow/Pameran berurutan.\n";
    cout << "     - Gunakan tombol navigasi [1] Next dan [2] Prev untuk berpindah karya!\n\n";

    cout << "  2. Pencarian Cerdas Berdasarkan Nama / Kata Kunci\n";
    cout << "     - Ketik nama apa pun (misal: 'kucing', 'jokowi', 'segi', 'kura kura').\n";
    cout << "     - Sistem mengenali kata kunci secara fleksibel tanpa membedakan huruf besar/kecil.\n";
    cout << "     - Ketik 'DAFTAR' untuk melihat seluruh koleksi karya seni yang tersedia.\n\n";

    cout << "  3. Studio Pembuat Gambar ASCII\n";
    cout << "     - Tuangkan imajinasi Anda dengan mengetikkan karakter pada keyboard.\n";
    cout << "     - Dilengkapi fitur Pratinjau (Preview) sebelum disimpan.\n";
    cout << "     - Karya buatan Anda langsung dapat dinikmati di galeri seketika itu juga!\n\n";

    cout << "  4. Sorotan Karya Seni Acak (Spotlight)\n";
    cout << "     - Menyajikan karya seni secara acak untuk memberikan inspirasi seketika.\n\n";

    batas(80, '-');
    cout << "  INFORMASI PENGEMBANGAN:\n";
    cout << "  - Mata Kuliah : Dasar Pemrograman (Project UAS Semester 1)\n";
    cout << "  - Institusi   : UIN Sunan Gunung Djati Bandung\n";
    cout << "  - Bahasa      : C++ Modern (ISO C++)\n";
    cout << "  - Status      : Ramah Pengguna & Lengkap dengan Koleksi Seni Nusantara\n";
    batas(80, '=');

    tekanEnter();
}

// ============================================================================
// BANNER SAMBUTAN PEMBUKA
// ============================================================================
void tampilkanBannerPembuka() {
    bersihkanLayar();
    cout << "\n";
    // Ornamen pohon dekoratif dari karya asli
    for (int i = 1; i <= 5; i++) {
        for (int ulang = 0; ulang < 11; ulang++) {
            for (int s1 = 1; s1 <= 5 - i; s1++) cout << " ";
            for (int b = 1; b <= (2 * i - 1); b++) cout << "*";
            for (int s2 = 1; s2 <= 5 - i + 2; s2++) cout << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    batas(80, '=');
    cout << "     SELAMAT DATANG DI GALERI KARYA SENI ASCII (ASCII ART GALLERY)\n";
    cout << "             Dasar Pemrograman - UIN Sunan Gunung Djati Bandung\n";
    batas(80, '=');
    cout << "\n  Selamat datang! Nikmati pengalaman menjelajahi keajaiban seni visual\n";
    cout << "  berbasis karakter teks, cari karya favorit, atau buat karya Anda sendiri!\n\n";
    tekanEnter("  Tekan [ENTER] untuk masuk ke Menu Utama...");
}

// ============================================================================
// KONFIRMASI KELUAR
// ============================================================================
bool konfirmasiKeluar() {
    bersihkanLayar();
    headerAplikasi();
    cout << "\n";
    batas(80, '=');
    cout << "                        KONFIRMASI KELUAR APLIKASI\n";
    batas(80, '=');
    cout << "\n  Apakah Anda yakin ingin mengakhiri kunjungan di Galeri Seni ASCII?\n";
    bool yakin = inputKonfirmasi("  Ketik [Y] untuk Keluar, atau [N] untuk Tetap di Galeri: ", false);

    if (yakin) {
        bersihkanLayar();
        cout << "\n\n";
        batas(80, '=');
        cout << "         TERIMA KASIH TELAH BERKUNJUNG KE GALERI KARYA SENI ASCII!\n";
        cout << "       \"Kreativitas tidak dibatasi oleh media, bahkan sekadar teks\n";
        cout << "           dapat melahirkan karya seni visual yang mengagumkan.\"\n";
        cout << "\n";
        cout << "                    Semoga hari Anda menyenangkan!\n";
        cout << "               UIN Sunan Gunung Djati Bandung - 2026\n";
        batas(80, '=');
        cout << "\n\n";
        return true;
    }
    return false;
}

// ============================================================================
// PROGRAM UTAMA (MAIN)
// ============================================================================
int main() {
    aktifkanModeKonsol();
    srand(static_cast<unsigned int>(time(NULL)));

    // Inisialisasi Kategori dan Karya Seni
    vector<Kategori> semuaKategori = inisialisasiKoleksi();

    // Tampilkan Banner Sambutan Pertama Kali
    tampilkanBannerPembuka();

    while (true) {
        bersihkanLayar();
        headerAplikasi();
        headerHalaman("MENU UTAMA");

        cout << "  Silakan pilih menu yang ingin Anda buka:\n\n";
        cout << "    [1]  Jelajahi Galeri Seni (Berdasarkan Kategori)\n";
        cout << "    [2]  Cari Karya Seni Berdasarkan Nama / Kata Kunci\n";
        cout << "    [3]  Studio Pembuat Gambar ASCII (Buat Karya Sendiri)\n";
        cout << "    [4]  Sorotan Karya Seni Acak (Random Art Spotlight)\n";
        cout << "    [5]  Panduan Penggunaan & Tentang Galeri\n";
        cout << "    [0]  Keluar dari Aplikasi\n";
        cout << "\n";
        batas(80, '-');

        int pilihan = inputAngka(0, 5, "  Silakan ketik angka pilihan Anda [0-5]: ");

        if (pilihan == 1) {
            menuJelajahiKategori(semuaKategori);
        } else if (pilihan == 2) {
            menuPencarian(semuaKategori);
        } else if (pilihan == 3) {
            menuBuatGambar(semuaKategori);
        } else if (pilihan == 4) {
            menuKaryaAcak(semuaKategori);
        } else if (pilihan == 5) {
            menuBantuan();
        } else if (pilihan == 0) {
            if (konfirmasiKeluar()) {
                break;
            }
        }
    }

    return 0;
=======
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// __________________________________________________
void batas(){
    for (int i=0;i<1;i++){
        for (int j=0;j<120;j++){
            cout << "=";
        }
        cout << endl;
    }
}
void tampilkanGambar(const string& folder, const string& file) {
    string z=  folder + "/" + file + ".txt";
    ifstream f(z);
    string garis;
    
        if(f.is_open()) {
            cout << "\n";
            while(getline(f, garis)) {
                cout << garis << endl;
            }
            cout << "\n";
            f.close();
        }else {
            cout << "Comingg Sooonnnn!\n" << endl;
        }
}
void tambahGambar() {
    string nama, kategori, isi, baris;
    char lagi;

    do {
    cout << "=== TAMBAH GAMBAR SIMPLE ===" << endl;
    cout << "*Batal Menggambar (ketik 'B')" << endl;
    batas();
    cout << "Nama file (huruf kecil):";
    cin >> nama;
    if (nama == "B"|| nama=="b") {
        cout << "Program dibatalkan........." << endl;
        return;
    }
    cin.ignore();
    
    cout << "\nMasukkan gambar ASCII :" << endl;
    cout << "Ketik 'END' di baris baru untuk selesai" << endl;
    cout << "Ketik 'BATAL' untuk membatalkan gambar" << endl;

    isi = "";
    bool BATAL = false;

    while(true) {
        getline(cin, baris);
        if(baris == "BATAL") {
            BATAL = true;
            break;
        }
        if(baris == "END"){
            break;
        }
        isi += baris + "\n";
    }

    if (BATAL) {
        cout << "Gambar dibatalkan........." << endl;
        cout << "Mau Coba Lagi? (Y/N): ";
        cin >> lagi;
        cin.ignore();

        if(lagi == 'N' || lagi == 'n') {    
            return;
        }
        continue;
    }

    ofstream file(nama + ".txt");
    if(file.is_open()) {
        file << isi;
        file.close();
        cout << "Berhasil disimpan sebagai " << nama << ".txt\n";
    } else {
        cout << "Gagal menyimpan!\n";
    }

    cout << "Ingin menambahkan gambar lain? (Y/N): ";  
    cin >> lagi;
        if(lagi == 'N' || lagi == 'n') {    
            break;
        }

    batas();
    cin.ignore();
    } while(true);
}
bool cariGambar(const string& nama) {
    do {
    string kategori[] = {"Hewan","BangunDatar","Manusia","Pemandangan","Rumah","Tumbuhan"};
    string daftar[][21] = {
        {"anjing","kelinci","kucing","burung","ikan","kurakura","gajah"},
        {"persegi","segitiga","lingkaran","belah ketupat","segi lima","segi enam","segi delapan"},
        {"manusia","jokowi","elon musk","logoml","ferry irwandi"},
        {"pemandangan","indonesia"},
    };
    
    bool ketemu = false;
    
    for(int k = 0; k < 4; k++) {
        for(int i = 0; i < 10; i++) {
            if(daftar[k][i] == nama) {
                cout << "\n[Ditemukan di kategori " << kategori[k] << "]\n" << endl;
                tampilkanGambar(kategori[k], nama);
                ketemu = true;
                break;
            }
        }
        if(ketemu) break;
    }
    return ketemu;
    } while (false);
}
//_______________________________________________________________________________
int main(){
    string opsi[]={"Pilihan Kategori", "Buat Gambar Sendiri", "Cari Gambar Pakai Nama", "Keluar"};
    string art[] ={"Hewan","Bangun Datar", "Manusia", "Pemandangan","Rumah","Tumbuhan","Kembali" };
    string hewan[] ={"anjing","burung" , "gajah","ikan" ,"kelinci", "kucing","kura kura" };
    string bangunDatar[] ={"belah ketupat", "bintang", "lingkaran", "persegi", "segi enam", "segi lima", "segitiga"};
    string manusia [] ={"manusia", "jokowi", "elon musk","ferry irwandi"};
    string pemandangan[] ={"pemandangan", "indonesia"};
    string rumah[] ={"rumah sederhana", "rumah mewah", "rumah adat"};
    string tumbuhan[] ={"bunga", "pohon"};

    int x = sizeof(opsi)/sizeof(opsi[0]);
    int pilihan;
    char pilihan1;
    int pilihan2;

//__________________________________________________________________________________
    for(int i = 1; i <= 5; i++) {
        for(int ulang = 0; ulang < 11; ulang++) {
            for(int s1 = 1; s1 <= 5 - i; s1++) {
                cout << " ";
            }
            for(int b = 1; b <= (2*i - 1); b++) {
                cout << "*";
            }
            for(int s2 = 1; s2 <= 5 - i + 2; s2++) {
                cout << " ";
            }
        }
        cout << endl;
    }
//__________________________________________________________________________________
cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~SELAMAT DATANG DI GALERI KARYA SENI ASCII~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<< endl;

do {
    batas();
    // _______________________________________________________________________________________________________
        cout << "SISTEM GALERI SEDERHANA ART STYLE ASCII\n" << "*Note: Update Sewaktu-waktu~" << endl;
        for (int i=0;i < x;i++){
            cout << i+1 << ". " << opsi[i] << endl;
        }
        // _________________________________________________________________________________
        while (true) {
        cout << "Silahkan Ketik Angka Untuk Memilih= ";
        if (cin >> pilihan) {
            break;
        } 
        cout << "Input tidak valid! Masukkan angka.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        }
    //_____________________________________________________________________________________________
    batas();
    //_____________________________________________________________________________________________
    switch (pilihan){
        case 1:{
            do{
            cout << "~~KATEGORI~~" << endl;
            int y = sizeof(art)/sizeof(art[0]);
            for (int i=0;i < y;i++){
                cout << i+1 << ". " << art[i] << endl;
            }

            cout << "Ketik angka sesuai kategori : ";
            cin >> pilihan2;
            for (int i=0;i<1;i++){
                for (int j=0;j<120;j++){
                    cout << "=";
                }
                cout << endl;
            }
            //_________________________________________________________________________________________________________________________
            switch (pilihan2){
                case 1:{
                        cout << "~~HEWAN~~" << endl;
                        int y = sizeof(hewan)/sizeof(hewan[0]);
                    for (int i=0;i < y;i++){
                        cout << "#" << hewan [i] << endl;
                        tampilkanGambar("Hewan", hewan[i]);
                    }
                    batas();
                    break;
                }

                case 2:{
                        cout << "~~BANGUN DATAR~~" << endl;
                        int y = sizeof(bangunDatar)/sizeof(bangunDatar[0]);
                    for (int i=0;i < y;i++){
                        cout << "#" << bangunDatar [i] << endl;
                        tampilkanGambar("Bangun Datar", bangunDatar[i]);
                    }
                    batas();
                    break;
                }

                case 3:{
                        cout << "~~MANUSIA~~" << endl;
                        int y = sizeof(manusia)/sizeof(manusia[0]);
                    for (int i=0;i < y;i++){
                        cout << "#" << manusia [i] << endl;
                        tampilkanGambar("Manusia", manusia[i] );
                    }
                    batas();
                    break;
                }

                case 4:{
                        cout << "~~PEMANDANGAN~~" << endl;
                        int y = sizeof(pemandangan)/sizeof(pemandangan[0]);
                    for (int i=0;i < y;i++){
                        cout << "#" << pemandangan[i] << endl;
                        tampilkanGambar("Pemandangan", pemandangan[i]);
                    }
                    batas();
                    break;
                }

                case 5:{
                        cout << "~~RUMAH~~" << endl;
                        int y = sizeof(rumah)/sizeof(rumah[0]);
                    for (int i=0;i < y;i++){    
                        cout << "#" << rumah[i] << endl;
                        tampilkanGambar("Rumah", rumah[i]);
                    }
                    batas();
                    break;
                }

                case 6:{
                        cout << "~~TUMBUHAN~~" << endl;
                        int y = sizeof(tumbuhan)/sizeof(tumbuhan[0]);
                    for (int i=0;i < y;i++){    
                        cout << "#" << tumbuhan[i] << endl;
                        tampilkanGambar("Tumbuhan", tumbuhan[i]);
                    }
                    batas();
                    break;
                }

                case 7:{
                    break;   
                }

                default:
                    cout << "Yang Bener Ngetik Angkanya" << endl;
                    break;
            }
            cout << "Kembali (Menu Utama='K')/(Menu Kategori='C'): ";
            cin >> pilihan1;
                    if (pilihan1 == 'K' || pilihan1 == 'k'){
                        batas();
                        cout <<"\n"<< endl;
                        break;
                    }
                } while (pilihan1 == 'C' || pilihan1 == 'c');
            break;
        }
        //_________________________________________________________________________________________________________________________
        case 2:{
            tambahGambar();
            break;
        }

        case 3:{
            do {
            string namaGambar;
            cout << "Masukkan nama gambar yang ingin anda kagumi(huruf kecil semua): ";
            cin >> namaGambar;
            if(!cariGambar(namaGambar)) {
                cout << "COMING SOONN YEAHHHH" << endl;
            }
            batas();
            cout << "Ingin mencari gambar lain? (Y/N): ";
            char lagi;  
            cin >> lagi;
                if(lagi == 'N' || lagi == 'n') {    
                    return main();
                }

            batas();
            cin.ignore();
            } while(true);
            continue;
        }

        case 4:{
            cout << "=============================================TERIMA KASIH SUDAH BERKUNJUNG===============================================" << endl;
            return 0;
            break;
        }

        default:
            cout << "Yang Bener Ngetik Angkanya" << endl;
            break;
    }
    } while(true);
>>>>>>> 34e3dffe2845d21a431ab0c68ca55a1031bd0e2a
}