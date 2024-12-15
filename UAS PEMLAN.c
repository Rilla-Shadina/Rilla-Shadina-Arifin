#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PESANAN 100

typedef struct {
    char nama[50];
    char jenisTiket[20];
    int jumlahTiket;
    float hargaTiket;
    char kodePenerbangan[10];
    char tanggalKeberangkatan[20];
} Pesanan;

Pesanan pesanan[MAX_PESANAN];
int jumlahPesanan = 0;

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error membuka file");
        return;
    }
    for (int i = 0; i < jumlahPesanan; i++) {
        fprintf(file, "%s %s %d %.2f %s %s\n", pesanan[i].nama, pesanan[i].jenisTiket, pesanan[i].jumlahTiket, pesanan[i].hargaTiket, pesanan[i].kodePenerbangan, pesanan[i].tanggalKeberangkatan);
    }
    fclose(file);
}

void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error membuka file");
        return;
    }
    jumlahPesanan = 0;
    while (fscanf(file, "%49s %19s %d %f %9s %19s", pesanan[jumlahPesanan].nama, pesanan[jumlahPesanan].jenisTiket, &pesanan[jumlahPesanan].jumlahTiket, &pesanan[jumlahPesanan].hargaTiket, pesanan[jumlahPesanan].kodePenerbangan, pesanan[jumlahPesanan].tanggalKeberangkatan) == 6) {
        jumlahPesanan++;
    }
    fclose(file);
}

void addPesanan() {
    if (jumlahPesanan >= MAX_PESANAN) {
        printf("Kapasitas Pesanan Penuh!\n");
        return;
    }

    printf("Masukkan nama: ");
    getchar();
    fgets(pesanan[jumlahPesanan].nama, 50, stdin);
    pesanan[jumlahPesanan].nama[strcspn(pesanan[jumlahPesanan].nama, "\n")] = 0;

    printf("Masukkan jenis tiket: ");
    fgets(pesanan[jumlahPesanan].jenisTiket, 20, stdin);
    pesanan[jumlahPesanan].jenisTiket[strcspn(pesanan[jumlahPesanan].jenisTiket, "\n")] = 0;

    printf("Masukkan kode penerbangan: ");
    fgets(pesanan[jumlahPesanan].kodePenerbangan, 10, stdin);
    pesanan[jumlahPesanan].kodePenerbangan[strcspn(pesanan[jumlahPesanan].kodePenerbangan, "\n")] = 0;

    printf("Masukkan tanggal keberangkatan (dd-mm-yyyy): ");
    fgets(pesanan[jumlahPesanan].tanggalKeberangkatan, 20, stdin);
    pesanan[jumlahPesanan].tanggalKeberangkatan[strcspn(pesanan[jumlahPesanan].tanggalKeberangkatan, "\n")] = 0;

    do {
        printf("Masukkan jumlah tiket: ");
        if (scanf("%d", &pesanan[jumlahPesanan].jumlahTiket) != 1 || pesanan[jumlahPesanan].jumlahTiket < 0) {
            printf("Input salah. Masukkan angka bulat positif atau nol ya!\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    do {
        printf("Masukkan Harga Tiket: ");
        if (scanf("%f", &pesanan[jumlahPesanan].hargaTiket) != 1 || pesanan[jumlahPesanan].hargaTiket < 0) {
            printf("Input salah. Masukkan angka bulat positif atau nol ya!\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);

    jumlahPesanan++;
    printf("Pesanan tiket pesawat berhasil ditambahkan!\n");
}

void searchPesanan() {
    char nama[50];
    printf("Masukkan nama untuk pencarian: ");
    getchar();
    fgets(nama, 50, stdin);
    nama[strcspn(nama, "\n")] = 0;

    for (int i = 0; i < jumlahPesanan; i++) {
        if (strcmp(pesanan[i].nama, nama) == 0) {
            printf("Nama: %s\nJenis: %s\nJumlah: %d\nHarga: %.2f\nKode Penerbangan: %s\nTanggal Keberangkatan: %s\n", pesanan[i].nama, pesanan[i].jenisTiket, pesanan[i].jumlahTiket, pesanan[i].hargaTiket, pesanan[i].kodePenerbangan, pesanan[i].tanggalKeberangkatan);
            printf("Press Enter to return to the menu...");
            getchar();
            return;
        }
    }
    printf("Pesanan Tidak Ditemukan.\n");
    printf("Tekan Enter");
    getchar();
}

float calculateRevenue(int index) {
    if (index == jumlahPesanan) return 0;
    return pesanan[index].jumlahTiket * pesanan[index].hargaTiket + calculateRevenue(index + 1);
}

void bubbleSort() {
    for (int i = 0; i < jumlahPesanan - 1; i++) {
        for (int j = 0; j < jumlahPesanan - i - 1; j++) {
            if (pesanan[j].jumlahTiket > pesanan[j + 1].jumlahTiket) 
                Pesanan temp = pesanan[j];
                pesanan[j] = pesanan[j + 1];
                pesanan[j + 1] = temp;
            }
        }
    }
    printf("Pesanan diurutkan berdasarkan jumlah tiket.\n");
}

void displayPesanan() {
    if (jumlahPesanan == 0) {
        printf("Tidak ada pesanan yang ditampilkan\n");
        return;
    }
    printf("\n%-20s %-15s %-10s %-10s %-15s %-20s\n", "Nama", "Jenis","Jumlah","Harga","Kode Penerbangan","Tanggal Keberangkatan");
    printf("---------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlahPesanan; i++) {
        printf("%-20s %-15s %-10d %-10.2f %-15s %-20s\n", pesanan[i].nama, pesanan[i].jenisTiket, pesanan[i].jumlahTiket, pesanan[i].hargaTiket, pesanan[i].kodePenerbangan, pesanan[i].tanggalKeberangkatan);
    }
}

void displayMenu() {
    system("cls");
    printf("\n--- Sistem Pengelolaan Pemesanan Tiket Pesawat ---\n");
    printf("1. Tambahkan Pesanan\n");
    printf("2. Cari Pesanan\n");
    printf("3. Hitung Pendapatan\n");
    printf("4. Urutkan Pesanan\n");
    printf("5. Tampilkan Pesanan\n");
    printf("6. Simpan dan Keluar\n");
    printf("Masukkan pilihanmu: ");
}

int main() {
    int choice;
    char filename[] = "pesanan.txt";
    loadFromFile(filename);

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Input salah. Masukkan angka ya.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addPesanan();
                break;
            case 2:
                searchPesanan();
                break;
            case 3:
                printf("Total Pendapatan: %.2f\n", calculateRevenue(0));
                break;
            case 4:
                bubbleSort();
                break;
            case 5:
                displayPesanan();
                break;
            case 6:
                saveToFile(filename);
                printf("Data berhasil disimpan. Keluar...\n");
                break;
            default:
                printf("Pilihan salah. Coba lagi\n");
        }

        if (choice != 6) {
            printf("Tekan Enter untuk kembali ke menu..");
            getchar();
            getchar();
        }

    } while (choice != 6);

    return 0;
}
