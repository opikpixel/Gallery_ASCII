#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // Untuk system("cls")

using namespace std;

// 1. FUNGSI KHUSUS UNTUK MEMBACA FILE (Efisiensi & Reusability)
void tampilkanAsciiArt(const string& namaFile) {
    ifstream file(namaFile);
    string baris;

    // 2. PENANGANAN ERROR (Mencegah program crash)
    if (file.is_open()) {
        while (getline(file, baris)) {
            cout << baris << '\n';
        }
        file.close();
    } else {
        cout << "\n[ERROR] Maaf, file '" << namaFile << "' tidak dapat ditemukan atau gagal dibuka.\n";
    }
    
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get(); // Menunggu input pengguna sebelum membersihkan layar
}

int main() {
    int pilihan;
    bool jalan = true;

    // 3. MENU INTERAKTIF DENGAN LOOP (User Friendly)
    do {
        // Membersihkan layar (gunakan "clear" jika di Linux/Mac)
        system("cls"); 

        cout << "========================================\n";
        cout << "          GALERI ASCII ART C++          \n";
        cout << "========================================\n";
        cout << "1. Tampilkan Anjing\n";
        cout << "2. Tampilkan Burung\n";
        cout << "3. Tampilkan Elon Musk\n";
        cout << "4. Tampilkan Pemandangan\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "========================================\n";
        cout << "Pilih menu (0-4): ";
        
        cin >> pilihan;

        system("cls"); // Bersihkan layar sebelum menampilkan gambar

        switch (pilihan) {
            case 1:
                tampilkanAsciiArt("anjing.txt");
                break;
            case 2:
                tampilkanAsciiArt("burung.txt");
                break;
            case 3:
                tampilkanAsciiArt("elon musk.txt");
                break;
            case 4:
                tampilkanAsciiArt("pemandangan.txt");
                break;
            case 0:
                jalan = false;
                cout << "Terima kasih telah mengunjungi Galeri ASCII!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                cin.ignore();
                cin.get();
                break;
        }
    } while (jalan);

    return 0;
}