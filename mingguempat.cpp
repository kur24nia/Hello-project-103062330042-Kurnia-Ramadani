#include <iostream>
#include <string>
#include <vector>
//ubah file
//ubah

struct Aset {
    std::string nama;
    std::string jenis;
    int jumlah;
    double harga;

    Aset(std::string nama, std::string jenis, int jumlah, double harga)
        : nama(nama), jenis(jenis), jumlah(jumlah), harga(harga) {}

    virtual void tahunBerikutnya() = 0;
    virtual void tampilkanAset() const = 0;
    virtual ~Aset() = default;  // Menambahkan destructor virtual untuk menghindari kebocoran memori
};

struct Saham : public Aset {
    double dividen;
    double pertumbuhan;

    Saham(std::string nama, int jumlah, double harga, double pertumbuhan, double dividen)
        : Aset(nama, "SAHAM", jumlah, harga), pertumbuhan(pertumbuhan), dividen(dividen) {}

    void tahunBerikutnya() override {
        grow();
        harga *= (1 + pertumbuhan);  // Update harga saham berdasarkan pertumbuhan
        double totalDividen = dividen * jumlah;  // Hitung total dividen
        std::cout << "Dividen yang didapat: " << totalDividen << "\n";
    }

    // Perbaikan fungsi grow agar sesuai dengan tipe double
    void grow() {
        pertumbuhan = pertumbuhan * 0.1; // Pertumbuhan 10% setiap tahun (contoh)
    }

    void tampilkanAset() const override {
        std::cout << "Saham: " << nama << " | Jumlah: " << jumlah << " | Harga: " << harga << std::endl;
    }
};

struct Obligasi : public Aset {
    double bunga;

    Obligasi(std::string nama, int jumlah, double harga, double bunga)
        : Aset(nama, "OBLIGASI", jumlah, harga), bunga(bunga) {}

    void tahunBerikutnya() override {
        double totalBunga = bunga * harga * jumlah;  // Hitung total bunga
        std::cout << "Bunga yang didapat: " << totalBunga << "\n";
    }

    void tampilkanAset() const override {
        std::cout << "Obligasi: " << nama << " | Jumlah: " << jumlah << " | Harga: " << harga << std::endl;
    }
};

struct Node {
    Aset* data;
    Node* next;

    Node(Aset* data) : data(data), next(0) {}
};

class Pacilnomo {
private:
    Node* head;
    double earnings;

    void printSeparator() const {
        std::cout << std::string(64, '=') << std::endl;
    }

    void daftarAset() const {
        printSeparator();
        Node* current = head;
        int count = 0;
        while (current != 0) {
            current->data->tampilkanAset();
            current = current->next;
            count++;
        }
        std::cout << "Kamu memiliki " << count << " total aset:" << std::endl;
        printSeparator();
    }

    void infoPortofolio() const {
        int jumlahSaham = 0, jumlahObligasi = 0;
        double netWorth = 0;
        Node* current = head;

        while (current != 0) {
            if (current->data->jenis == "SAHAM") {
                jumlahSaham++;
            } else if (current->data->jenis == "OBLIGASI") {
                jumlahObligasi++;
            }
            netWorth += current->data->harga * current->data->jumlah;
            current = current->next;
        }

        printSeparator();
        std::cout << "Info Portofolio\n"
                  << "Jumlah Jenis Saham: " << jumlahSaham << "\n"
                  << "Jumlah Jenis Obligasi: " << jumlahObligasi << "\n"
                  << "Total Nilai Portofolio: " << netWorth << std::endl;
        printSeparator();
    }

    void tahunBerikutnya() {
        Node* current = head;
        while (current != 0) {
            current->data->tahunBerikutnya();
            current = current->next;
        }
        std::cout << "Setahun telah berlalu...\n";
        printSeparator();
    }

public:
    Pacilnomo() : head(0), earnings(0) {}

    void addAset(Aset* aset) {
        Node* newNode = new Node(aset);
        newNode->next = head;
        head = newNode;
    }

    void addToEarnings(double jumlah) {
        earnings += jumlah;
    }

    Aset* cariAset(const std::string& namaAset) const {
        Node* current = head;
        while (current != 0) {
            if (current->data->nama == namaAset) {
                return current->data; // Jika ditemukan, kembalikan pointer ke objek Aset
            }
            current = current->next;
        }
        std::cout << "Aset tidak ditemukan!" << std::endl;
        return 0; // Jika tidak ditemukan, kembalikan 0
    }

    void run() {
        int banyakAset;
        std::cout << "Masukkan banyak aset yang tersedia: ";
        std::cin >> banyakAset;
        std::cin.ignore();

        for (int i = 0; i < banyakAset; i++) {
            std::cout << "Aset " << i + 1 << ": ";
            std::string namaAset, jenisAset;
            int jumlah;
            double harga;
            std::cin >> namaAset >> jenisAset >> jumlah >> harga;

            if (jenisAset == "SAHAM") {
                double pertumbuhan, dividen;
                std::cout << "Masukkan pertumbuhan dan dividen: ";
                std::cin >> pertumbuhan >> dividen;
                addAset(new Saham(namaAset, jumlah, harga, pertumbuhan, dividen));
            } else if (jenisAset == "OBLIGASI") {
                double bunga;
                std::cout << "Masukkan bunga: ";
                std::cin >> bunga;
                addAset(new Obligasi(namaAset, jumlah, harga, bunga));
            }
        }

        std::cout << "Selamat datang di...\n"
                  << " /$$$$$$$                     /$$ /$$\n"
                  << "| $$_  $$                   |_/| $$\n"
                  << "| $$  \\ $$ /$$$$$$   /$$$$$$$ /$$| $$ /$$$$$$$   /$$$$$$  /$$$$$$/$$$$   /$$$$$$\n"
                  << "| $$$$$$$/|__  $$ /$$__/| $$| $$| $$_  $$ /$$_  $$| $$  $$_  $$ /$$__  $$\n"
                  << "| $$__/  /$$$$$$$| $$      | $$| $$| $$  \\ $$| $$  \\ $$| $$ \\ $$ \\ $$| $$  \\ $$\n"
                  << "| $$      /$$__  $$| $$      | $$| $$| $$  | $$| $$  | $$| $$ | $$ | $$| $$  | $$\n"
                  << "| $$     |  $$$$$$$|  $$$$$$$| $$| $$| $$  | $$|  $$$$$$/| $$ | $$ | $$|  $$$$$$/\n"
                  << "|_/      \\__/ \\__/|/|/|/  |/ \\__/ |/ |/ |/ \\___/\n\n";

        while (true) {
            std::cout << "Pilih salah satu opsi berikut:\n"
                      << "[1] Daftar aset\n"
                      << "[2] Info portofolio\n"
                      << "[3] Lanjut ke tahun berikutnya\n"
                      << "[4] Cari aset\n"  // Tambahkan opsi untuk mencari aset
                      << "[*] Keluar\n";
            printSeparator();
            std::cout << "Input: ";
            std::string pilihan;
            std::cin >> pilihan;
            if (pilihan == "1") {
                daftarAset();
            } else if (pilihan == "2") {
                infoPortofolio();
            } else if (pilihan == "3") {
                tahunBerikutnya();
            } else if (pilihan == "4") {
                std::cout << "Masukkan nama aset yang ingin dicari: ";
                std::string namaAset;
                std::cin >> namaAset;
                Aset* aset = cariAset(namaAset);
                if (aset != 0) {
                    aset->tampilkanAset();
                }
            } else {
                std::cout << "Terima kasih telah menggunakan layanan Pacilnomo ~ !\n";
                break;
            }
        }
    }
};

int main() {
    Pacilnomo pacilnomo;
    pacilnomo.run();
    return 0;
}