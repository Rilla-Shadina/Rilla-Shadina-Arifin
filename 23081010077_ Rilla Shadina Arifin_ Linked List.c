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

void tambahAwal(node **head){
  int bil;
  node *pNew;

  system("cls");
  fflush(stdin);
  printf("masukkan bilangan : ");
  fflush(stdin);
  scanf("%d", &bil);
  pNew = (node *)malloc(sizeof(node));

  if (pNew != NULL){
  	  pNew->data = bil;
      pNew->next = NULL;
      //add before first logical node or to an empty list
	  pNew -> next = *head;
      *head = pNew;
  }
  else{
      printf("Alokasi memori gagal");
      getch();
  }
}

//========================================================

void tambahData(node **head){
  int pos, bil;
  node *pNew, *pCur;

  system("cls");
  tranverse(*head);
  printf("\nposisi penyisipan setelah data bernilai : ");
  fflush(stdin);
  scanf("%d", &pos);
  printf("\nbilangan : ");
  fflush(stdin);
  scanf("%d", &bil);

  pCur = *head;
  while (pCur != NULL && pCur -> data != pos) {
    pCur = pCur -> next;
  }

  pNew = (node *)malloc(sizeof(node));

  if (pCur == NULL){
     printf("\nnode tidak ditemukan");
     getch();
  }
  else if (pNew == NULL){
     printf("\nalokasi memeori gagal");
     getch();
  }
  else{
     pNew->data = bil;
     pNew->next = NULL;
     pNew -> next = pCur -> next;
     pCur -> next = pNew;
  }
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
        pNew->next = NULL;

        if (*head == NULL) {
            *head = pNew;  // Jika list kosong, node baru jadi head
        } else {
            pCur = *head;
            while (pCur->next != NULL) {
                pCur = pCur->next;
            }
            pCur->next = pNew;  // Tambah node baru di akhir list
        }
    } else {
        printf("Alokasi memori gagal");
        getch();
    }
}

//========================================================

void tranverse(node *head){
   //traverse a linked list
	node *pWalker;

    system("cls");
	pWalker = head;
	while (pWalker != NULL){
   	printf("%d\t", pWalker -> data);
   	pWalker = pWalker -> next;
      printf(" -> ");
	}
   printf("NULL");
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
    } else {
        node *pTemp = *head;
        *head = (*head)->next; 
        free(pTemp); 
        printf("Node di awal telah dihapus\n");
    }
}

//========================================================

void hapusTengah(node **head) {
    int target;

    printf("Masukkan nilai data yang ingin dihapus: ");
    scanf("%d", &target);
    
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus\n");
        return;
    }

    node *pCur = *head;  
    node *pPrev = NULL;  

    // Cek jika node pertama adalah target
    if (pCur->data == target) {
        *head = pCur->next;  
        free(pCur);           
        printf("Node dengan data %d dihapus\n", target);
        return;
    }

    while (pCur != NULL && pCur->data != target) {
        pPrev = pCur;         // Simpan node sebelumnya
        pCur = pCur->next;    // Pindah ke node berikutnya
    }

    if (pCur == NULL) {
        printf("Node dengan data %d tidak ditemukan\n", target);
        return;
    }
    
    
    pPrev->next = pCur->next;
    free(pCur);
    printf("Node dengan data %d dihapus\n", target);
}

//========================================================

void hapusAkhir(node **head) {
    if (*head == NULL) {
        printf("List kosong, tidak ada yang bisa dihapus\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;  
        printf("Node terakhir telah dihapus\n");
        return;
    }

    // Jika ada lebih dari satu node
    node *pCur = *head;
    node *pPrev = NULL;

    while (pCur->next != NULL) {
        pPrev = pCur;         
        pCur = pCur->next;    
    }

    pPrev->next = NULL;  
    free(pCur);        
    printf("Node terakhir telah dihapus\n");
} 

//========================================================

void cariData(node *head) {
    int target;
    node *pCur = head;
    int found = 0;

    system("cls");
    printf("Masukkan data yang ingin dicari: ");
    fflush(stdin);
    scanf("%d", &target);

    while (pCur != NULL) {
        if (pCur->data == target) {
            printf("Data %d ditemukan dalam linked list.\n", target);
            found = 1;
            break;
        }
        pCur = pCur->next;
    }
    if (!found) {
        printf("Data %d tidak ditemukan dalam linked list.\n", target);
    }
    getch();  
}

//========================================================

void hitungData(node *head) {
    int count = 0;
    node *pCur = head;  
    
    while (pCur != NULL) {
        count++;        
        pCur = pCur->next;  
    }
    printf("Jumlah data dalam list: %d\n", count);
}

//========================================================

void hasilJumlah(node *head) {
    int total = 0;
    node *pCur = head;

    if (head == NULL) {
        printf("List kosong, tidak ada yang bisa dijumlah\n");
        return;
    }

    while (pCur != NULL) {
        total += pCur->data;  
        pCur = pCur->next;    
    }

    printf("Hasil penjumlahan data dalam list: %d\n", total);
    
}

//========================================================

