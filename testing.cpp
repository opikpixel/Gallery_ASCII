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
}