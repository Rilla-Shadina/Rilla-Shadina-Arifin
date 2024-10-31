#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

typedef struct node node;

void tambahAwal(node **head);
void tambahTengah(node **head);
void tambahAkhir(node **head);
void tampilkan(node *head);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);

int main() {
	node *head = NULL;
	char pilihan;

do {
	printf("Masukkan pilihan\n");
	printf("1. Tambah peserta di awal\n");
	printf("2. Tambah peserta di tengah\n");
	printf("3. Tambah peserta di akhir\n");
	printf("4. Hapus peserta awal\n");
	printf("5. Hapus peserta tengah\n");
	printf("6. Hapus peserta akhir\n");
	printf("Masukkan pilihan dengan angka (ketik q untuk keluar): ");
	scanf("%c", &pilihan);
     if (pilihan == '1')
     	tambahAwal(&head);
     else if (pilihan == '2')
		tambahTengah(&head);
	 else if (pilihan == '3')
	 	tambahAkhir(&head);
     else if (pilihan == '4') {
     	tampilkan(head);
     	getch(); 	
	}
	else if (pilihan == '5')
		hapusAwal(&head);
	 else if (pilihan == '6')
	 	hapusTengah(&head);
     else if (pilihan == '7')
     	hapusAkhir(&head);
}while (pilihan != 'q');

return 0;
}
	

void tambahAwal(node **head) {
	int peserta;
    node *pNew;

    printf("Masukkan peserta (nama(L/P)): \n");
    scanf("%d", &peserta);
    system("cls");
    
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Gagal.\n");
        return;
    }
    
    pNew->data = peserta;
    pNew->left = NULL;
    pNew->right = *head;

    if (*head != NULL) {
        (*head)->left = pNew;
    }

    *head = pNew;
}

void tambahTengah(node **head) {
	int peserta;
	int cari;
    node *pNew, *pCur;

    if (*head == NULL) {
        printf("List kosong. Tidak bisa menambahkan peserta.\n");
        return;
    }
	
    printf("Masukkan peserta (nama(L/P)): \n");
    scanf("%d", &peserta);
    printf("Masukkan peserta setelah: ");
    scanf("%d", &cari);
	system ("cls");
	
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Gagal.\n");
        return;
    }
    pNew->data = peserta;

    pCur = *head;
    do {
        if (pCur->data == cari) {
            
            pNew->right = pCur->right; 
            pNew->left = pCur;         
            
            if (pCur->right != *head) {
                pCur->right->left = pNew; 
            }
            pCur->right = pNew;          
            return;
        }
        pCur = pCur->right; 
    } while (pCur != *head); 

    printf("Nilai %d tidak ditemukan. Data tidak ditambahkan.\n", cari);
    free(pNew); 
}

void tambahAkhir(node **head) {
    int peserta;
    node *pNew, *pCur;

    printf("Masukkan peserta (nama(L/P)): \n");
    scanf("%d", &peserta);
	system ("cls");
	
    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal.\n");
        return;
    }

    	pNew->data = peserta;
    	pNew->right = NULL;

    	if (*head == NULL) {
        	pNew->left = NULL;
        	*head = pNew;
    	}else {
       	 	pCur = *head;

        while (pCur->right != NULL) {
            pCur = pCur->right;
        }

        pCur->right = pNew;
        pNew->left = pCur;
    }
}

void tampilkan(node *head) {
    node *pCur;

    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    pCur = head;
    printf("Isi lingkaran: \n");

    while (pCur != NULL) {
    printf("%d", pCur->data);

    pCur = pCur->right;

    if (pCur != NULL) {
        printf(" <-> ");
    }
}
    printf("\n");
}

void hapusAwal(node **head) {
    node *pCur;

    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus.\n");
        return;
    }
    	pCur = *head;
    	*head = pCur->right;

    if (*head != NULL) {
        (*head)->left = NULL;
    }

    free(pCur);
    printf("Peserta awal berhasil dihapus.\n");
}

void hapusTengah(node **head) {
    int posisi, i;
    node *pCur;

    if (*head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    printf("Masukkan posisi peserta yang ingin dihapus: ");
    scanf("%d", &posisi);

    pCur = *head;

    if (posisi == 1) {
        hapusAwal(head);
        return;
    }

    for (i = 1; i < posisi && pCur != NULL; i++) {
        pCur = pCur->right;
    }if (pCur == NULL) {
        printf("Posisi tidak valid.\n");
        return;
    }

    if (pCur->right != NULL) {
        pCur->right->left = pCur->left;
    }

    if (pCur->left != NULL) {
        pCur->left->right = pCur->right;
    }

    free(pCur);
    printf("Peserta pada posisi %d berhasil dihapus.\n", posisi);
}

void hapusAkhir(node **head) {
    node *pCur;

    if (*head == NULL) {
        printf("Lingkaran kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    pCur = *head;

    if (pCur->right == NULL) {
        free(pCur);
        *head = NULL;
        return;
    }

    while (pCur->right != NULL) {
        pCur = pCur->right;
    }

    pCur->left->right = NULL;
    free(pCur);
    printf("Peserta akhir berhasil dihapus.\n");
}
	
	


