#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
//ubah fie
using namespace std;

struct Matkul {
    string nama;
    int start_time;
    int end_time;
};

struct Node {
    Matkul data;
    Node* next;
};

Node* head = NULL;

string getNamaHari(int hari) {
    switch (hari) {
        case 0: return "Senin";
        case 1: return "Selasa";
        case 2: return "Rabu";
        case 3: return "Kamis";
        case 4: return "Jumat";
        case 5: return "Sabtu";
        case 6: return "Minggu";
        default: return "Tidak diketahui";
    }
}

void tambahMatkul(const Matkul& matkul) {
    Node* newNode = new Node;
    newNode->data = matkul;
    newNode->next = NULL;

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

bool cekBentrok(const Matkul& matkul) {
    Node* temp = head;
    while (temp) {
        if ((matkul.start_time < temp->data.end_time && matkul.end_time > temp->data.start_time)) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void printJadwal() {
    if (!head) {
        cout << "Tidak ada mata kuliah yang diambil.\n";
        return;
    }
    Node* temp = head;
    cout << "Daftar mata kuliah yang diambil:\n";
    while (temp) {
        int hariMulai = temp->data.start_time / (24 * 60);
        int jamMulai = (temp->data.start_time % (24 * 60)) / 60;
        int menitMulai = temp->data.start_time % 60;
        int hariSelesai = temp->data.end_time / (24 * 60);
        int jamSelesai = (temp->data.end_time % (24 * 60)) / 60;
        int menitSelesai = temp->data.end_time % 60;

        // Format hari, jam, dan menit
        string namaHariMulai = getNamaHari(hariMulai);
        string namaHariSelesai = getNamaHari(hariSelesai);

        cout << temp->data.nama << " - Hari: " << namaHariMulai << ", Jam: "
             << setw(2) << setfill('0') << jamMulai << ":"
             << setw(2) << setfill('0') << menitMulai
             << " s/d Hari: " << namaHariSelesai << ", Jam: "
             << setw(2) << setfill('0') << jamSelesai << ":"
             << setw(2) << setfill('0') << menitSelesai << "\n";
        temp = temp->next;
    }
}

void cekRingkasan() {
    Node* temp = head;
    bool adaBentrok = false;
    
    while (temp) {
        Node* compare = head;
        while (compare) {
            if (temp != compare && (temp->data.start_time < compare->data.end_time && temp->data.end_time > compare->data.start_time)) {
                cout << "Mata kuliah " << temp->data.nama << " bentrok dengan " << compare->data.nama << "\n";
                adaBentrok = true;
            }
            compare = compare->next;
        }
        temp = temp->next;
    }
    if (!adaBentrok) {
        cout << "Tidak ada mata kuliah yang bermasalah.\n";
    }
}

void dropMatkul() {
    if (!head) {
        cout << "Tidak ada mata kuliah yang diambil.\n";
        return;
    }

    Node* temp = head;
    cout << "Mata kuliah yang diambil:\n";
    while (temp) {
        cout << "- " << temp->data.nama << "\n";
        temp = temp->next;
    }

    string namaMatkul;
    cout << "Masukkan nama mata kuliah yang ingin di-drop: ";
    cin.ignore(); 
    getline(cin, namaMatkul);

    temp = head;
    Node* prev = NULL;
    bool ditemukan = false;

    while (temp) {
        if (temp->data.nama == namaMatkul) {
            ditemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Mata kuliah tidak ditemukan.\n";
        return;
    }

    // Hapus mata kuliah yang sesuai
    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    cout << "Mata kuliah " << temp->data.nama << " berhasil di-drop.\n";
    delete temp;
}


int main() {
    // Menghitung start_time dan end_time sesuai dengan hari dan jam dari gambar
    const int MENIT_DALAM_JAM = 60;
    const int MENIT_DALAM_HARI = MENIT_DALAM_JAM * 24;

    const int HARI[] = {0 * MENIT_DALAM_HARI, 1 * MENIT_DALAM_HARI, 2 * MENIT_DALAM_HARI, 3 * MENIT_DALAM_HARI, 4 * MENIT_DALAM_HARI, 5 * MENIT_DALAM_HARI};
    const int JAM[] = {0, 1 * MENIT_DALAM_JAM, 2 * MENIT_DALAM_JAM, 3 * MENIT_DALAM_JAM, 4 * MENIT_DALAM_JAM, 5 * MENIT_DALAM_JAM,
                       6 * MENIT_DALAM_JAM, 7 * MENIT_DALAM_JAM, 8 * MENIT_DALAM_JAM, 9 * MENIT_DALAM_JAM, 10 * MENIT_DALAM_JAM, 11 * MENIT_DALAM_JAM,
                       12 * MENIT_DALAM_JAM, 13 * MENIT_DALAM_JAM, 14 * MENIT_DALAM_JAM, 15 * MENIT_DALAM_JAM, 16 * MENIT_DALAM_JAM, 17 * MENIT_DALAM_JAM};

	Matkul MATKUL_TERSEDIA[] = {
	    {"Struktur Data", HARI[0] + JAM[8], HARI[0] + JAM[9] + 40},     // Senin 08:00 - 09:40
	    {"Linear Matriks", HARI[2] + JAM[8], HARI[2] + JAM[9] + 40},    // Rabu 08:00 - 09:40
	    {"Alpro", HARI[1] + JAM[8], HARI[1] + JAM[9] + 40},             // Selasa 08:00 - 09:40
	    {"Manbis", HARI[0] + JAM[9], HARI[0] + JAM[10] + 40},           // Senin 09:00 - 10:40
	    {"Matdis 1 a", HARI[2] + JAM[9], HARI[2] + JAM[10] + 40},       // Rabu 09:00 - 10:40
	    {"Matdis 1 b", HARI[0] + JAM[9], HARI[0] + JAM[10] + 40},       // Senin 09:00 - 10:40
	    {"Kalkulus 1 c", HARI[2] + JAM[10], HARI[2] + JAM[12] + 0}      // Rabu 10:00 - 12:00
	};

    int pilihan;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Add Matkul\n";
        cout << "2. Drop Matkul\n";
        cout << "3. Cek Ringkasan\n";
        cout << "4. Lihat Daftar Matkul\n";
        cout << "5. Selesai\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Mata kuliah yang tersedia:\n";
		    for (int i = 0; i < 7; ++i) {
		        cout << "- " << MATKUL_TERSEDIA[i].nama << "\n";
		    }
		
		    string namaMatkul;
		    cout << "Masukkan nama mata kuliah: ";
		    cin.ignore(); 
		    getline(cin, namaMatkul);
		
		    bool ditemukan = false;
		    for (int i = 0; i < 7; ++i) {
		        if (MATKUL_TERSEDIA[i].nama == namaMatkul) {
		            Matkul matkulBaru = MATKUL_TERSEDIA[i];
		            tambahMatkul(matkulBaru);
		            cout << "Mata kuliah " << matkulBaru.nama << " berhasil ditambahkan.\n";
		            ditemukan = true;
		            break;
		        }
		    }
		
		    if (!ditemukan) {
		        cout << "Mata kuliah tidak ditemukan.\n";
		    }
        } else if (pilihan == 2) {
            dropMatkul();
        } else if (pilihan == 3) {
            cekRingkasan();
        } else if (pilihan == 4) {
            printJadwal();
        }

    } while (pilihan != 5);

    cout << "Terima kasih!\n";
    return 0;
}