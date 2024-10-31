#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//========================================================

struct node {
	int data;
    struct node *next;
};
typedef struct node node;

//node *createNode(void);
void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void tranverse(node *head);
void insertNode(node **head, node *pPre, node *pNew);
void hapusAwal(node **head);
void hapusTengah(node **head);
void hapusAkhir(node **head);
void cariData(node *head);
void hitungData(node *head);
void hasilJumlah(node *head);

//========================================================

int main()
{
  node *head;
  char pilih;

  head = NULL;
  do{
     system("cls");
     printf("masukkan pilihan\n");
     printf("1. tambah data di awal\n");
     printf("2. tambah data di tengah list\n");
     printf("3. tambah data di akhir list\n");
     printf("4. cetak isi list\n");
     printf("5. Hapus data awal\n");
     printf("6. Hapus data tengah\n");
     printf("7. Hapus data akhir\n");
     printf("8. Cari data dalam list\n");
     printf("9. Jumlah data dalam list\n");
     printf("10. Hasil penjumlahan data\n");
     printf("MASUKKAN PILIHAN (tekan q untuk keluar) : ");
     fflush(stdin);
     scanf("%c", &pilih);
     if (pilih == '1')
     	tambahAwal(&head);
     else if (pilih == '2')
		tambahData(&head);
	 else if (pilih == '3')
	 	tambahAkhir(&head);
     else if (pilih == '4'){
     	tranverse(head);
     	 getch();
	 }
     else if (pilih == '5')
     	hapusAwal(&head);
     else if (pilih == '6')
     	hapusTengah(&head);
     else if (pilih == '7')
     	hapusAkhir(&head);
     else if (pilih == '8'){
     	cariData(head);
        getch();
	 }
	 else if (pilih == '9'){
     	hitungData(head);
        getch();
	 }
	 else if (pilih == 10) {
     		hasilJumlah(head);
     		getch();
	 }

  } while (pilih != 'q');
  
  return 0;
}

//========================================================

/*node *createNode(void){
  node *ptr;

  ptr = (node *)malloc(sizeof(node));
  return(ptr);
}*/

//========================================================

void tambahAwal(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    fflush(stdin);
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);
    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = pNew; 
        } else {
            pCur = *head;
            while (pCur->next != *head) { 
                pCur = pCur->next;
            }

            pNew->next = *head; 
            pCur->next = pNew;  
            *head = pNew;     
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}


//========================================================

void tambahData(node **head) {
    int pos, bil;
    node *pNew, *pCur;

    system("cls");
    if (*head == NULL) {
        printf("List kosong. Tidak ada node untuk disisipkan di tengah.\n");
        return;
    }

    tranverse(*head);  
    printf("\nposisi penyisipan setelah data bernilai: ");
    fflush(stdin);
    scanf("%d", &pos);
    printf("\nmasukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));
    if (pNew == NULL) {
        printf("Alokasi memori gagal\n");
        return;
    }

    pNew->data = bil;

    pCur = *head;
    do {
        if (pCur->data == pos) {
            pNew->next = pCur->next; 
            pCur->next = pNew;       
            printf("Node dengan data %d berhasil disisipkan\n", bil);
            return;
        }
        pCur = pCur->next;
    } while (pCur != *head);

    printf("Node dengan data %d tidak ditemukan\n", pos); 
}


//========================================================

void tambahAkhir(node **head) {
    int bil;
    node *pNew, *pCur;

    system("cls");
    printf("Masukkan bilangan: ");
    fflush(stdin);
    scanf("%d", &bil);

    pNew = (node *)malloc(sizeof(node));

    if (pNew != NULL) {
        pNew->data = bil;

        if (*head == NULL) {
            *head = pNew;
            pNew->next = pNew;
        } else {
            pCur = *head;
            while (pCur->next != *head) { 
                pCur = pCur->next;
            }
            pCur->next = pNew; 
            pNew->next = *head; 
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}


//========================================================

void tranverse(node *head) {
    node *pWalker;

    system("cls");
    if (head == NULL) {
        printf("List kosong\n");
        return;
    }

    pWalker = head;
    do {
        printf("%d -> ", pWalker->data);
        pWalker = pWalker->next;
    } while (pWalker != head); // Berhenti jika sudah kembali ke head
    printf(" kembali ke head\n");
}


//========================================================

void insertNode(node **head, node *pPre, node *pNew){
    if (pPre == NULL){
       //add before first logical node or to an empty list
	    pNew -> next = *head;
       *head = pNew;
    }
    else {
       //add in the middle or at the end
       pNew -> next = pPre -> next;
       pPre -> next = pNew;
   }
}

//========================================================

void hapusAwal(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus\n");
        return;
    }

    node *pCur = *head;
    if (pCur->next == *head) {
        free(pCur);
        *head = NULL;
    } else {
        node *pLast = *head;
        while (pLast->next != *head) { 
            pLast = pLast->next;
        }

        pLast->next = (*head)->next; 
        *head = (*head)->next;      
        free(pCur);            
    }
}


//========================================================

void hapusTengah(node **head) {
    int target;
    node *pCur, *pPrev;

    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus\n");
        return;
    }

    printf("Masukkan nilai data yang ingin dihapus: ");
    fflush(stdin);
    scanf("%d", &target);

    pCur = *head;
    pPrev = NULL;

    if (pCur->next == *head && pCur->data == target) {
        free(pCur);
        *head = NULL;
        printf("Node dengan data %d telah dihapus. List sekarang kosong.\n", target);
        return;
    }

    do {
        if (pCur->data == target) {
            if (pPrev == NULL) {
                
                node *pLast = *head;
                while (pLast->next != *head) {  
                    pLast = pLast->next;
                }

                *head = pCur->next;   
                pLast->next = *head; 
            } else {
                
                pPrev->next = pCur->next;  
            }

            free(pCur);  
            printf("Node dengan data %d telah dihapus\n", target);
            return;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);  

    printf("Node dengan data %d tidak ditemukan\n", target);
}


//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus\n");
        return;
    }

    node *pCur = *head, *pPrev = NULL;

    if (pCur->next == *head) {
        
        free(pCur);
        *head = NULL;
    } else {
        while (pCur->next != *head) {
            pPrev = pCur;
            pCur = pCur->next;
        }
        pPrev->next = *head; 
        free(pCur);         
    }
}

//========================================================

void cariData(node *head) {
    int target;
    node *pCur = head;
    int found = 0;

    if (head == NULL) {
        printf("List kosong, tidak ada data yang bisa dicari.\n");
        return;
    }

    system("cls");
    printf("Masukkan data yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &target);

    do {
        if (pCur->data == target) {
            printf("Data %d ditemukan dalam circular linked list.\n", target);
            found = 1;
            break;
        }
        pCur = pCur->next;
    } while (pCur != head);  // Berhenti jika kembali ke head

    if (!found) {
        printf("Data %d tidak ditemukan dalam circular linked list.\n", target);
    }
    getch();  
}


//========================================================

void hitungData(node *head) {
    int count = 0;
    node *pCur = head;  

    if (head == NULL) {
        printf("List kosong, tidak ada data yang bisa dihitung.\n");
        return;
    }

    do {
        count++;        
        pCur = pCur->next;  
    } while (pCur != head);  // Berhenti jika kembali ke head

    printf("Jumlah data dalam circular linked list: %d\n", count);
}


//========================================================

void hasilJumlah(node *head) {
    int total = 0;
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong, tidak ada data yang bisa dijumlahkan.\n");
        return;
    }

    do {
        total += pCur->data;  
        pCur = pCur->next;    
    } while (pCur != head);  // Berhenti jika kembali ke head

    printf("Hasil penjumlahan data dalam circular linked list: %d\n", total);
}


//========================================================

