#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>

struct SinhVien{
    char ten[30];
    char gt[5];
    int age;
    float dT, dL, dH;
    float dtb;
};
typedef struct SinhVien SV;

struct LinkedList {
    SinhVien data;
    struct LinkedList *next;
};
typedef struct LinkedList *node;

node CreateNode(SinhVien sinhVien) {
    node temp;
    temp = (node)malloc(sizeof(struct LinkedList));
    temp->next = NULL;
    temp->data = sinhVien;
    return temp;
}

node AddTail(node head, SinhVien sinhVien) {
    node temp,p;
    temp = CreateNode(sinhVien);
    if (head == NULL) {
        head = temp;
    } else {
        p = head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next=temp;
    }
    return head;
}

SinhVien get(node head, int index) {
    int k = 0;
    node p = head;
    while (p != NULL && k != index) {
        p = p->next;
        k++;
    }
    return p->data;
}

void xuat(SV sv){
    printf("\nHo ten SV: %s", sv.ten);
    printf("\nGioi tinh: %s", sv.gt);
    printf("\nTuoi SV  : %d", sv.age);
    printf("\nDiem Toan - Ly - Hoa: %.2f - %.2f - %.2f", sv.dT, sv.dL, sv.dH);
    printf("\nDiem TB: %.2f", sv.dtb);
}

void Traverser(node head) {
    printf("\n");
    for (node p = head; p != NULL; p = p->next) {
        xuat(p->data);
    }
}

node InitHead() {
    node head;
    head = NULL;
    return head;
}

int Length(node head) {
    int length = 0;
    for (node p = head; p != NULL; p = p->next) {
        ++length;
    }
    return length;
}

void sort(node head){

    int i, j, k;
    SinhVien tempData;
    node current;
    node next;

    int size = Length(head);
    k = size ;

    for ( i = 0 ; i < size - 1 ; i++, k-- ) {
        current = head ;
        next = head->next ;

        for ( j = 1 ; j < k ; j++ ) {

            if ( current->data.dtb > next->data.dtb ) {
                tempData = current->data ;
                current->data = next->data;
                next->data = tempData ;
            }

            current = current->next;
            next = next->next;
        }
    }
}

SinhVien nhap();
node nhapN(int n);
void xuat(SV sv);
void xeploai(SV a);
void xeploaiN(node head, int n);
void xuatFile(node head, int n, char fileName1[]);
char fileName[] = "export.txt";

int main(){
    int key;
    int n;
    bool daNhap = false;
    node head = NULL;
    do{
        printf("\n[?] Nhap vao so luong sinh vien: "); scanf("%d", &n);
    }while(n <= 0);
    while(true){
        system("cls");
        printf("==================================================================\n");
        printf("1. Nhap du lieu\n");
        printf("2. In danh sach sinh vien\n");
        printf("3. Sap xep sinh vien theo DTB\n");
        printf("4. Xep loai sinh vien\n");
        printf("5. Xuat DS sinh vien\n");
        printf("**\n");
        printf(" Nhap lua chon cua ban          **\n");
        scanf("%d",&key);

        switch(key){
            case 1:
                printf("\nBan da chon nhap DS sinh vien!");
                head = nhapN(n);
                printf("\nBan da nhap thanh cong!");
                daNhap = true;
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
            case 2:
                if(daNhap){
                    printf("\nBan da chon xuat DS sinh vien!");
                    Traverser(head);
                }else{
                    printf("\nNhap DS SV truoc!!!!");
                }
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
            case 3:
                if(daNhap){
                    printf("\nBan da chon sap xep SV theo DTB!");
                    sort(head);
                    Traverser(head);
                }else{
                    printf("\nNhap DS SV truoc!!!!");
                }
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
            case 4:
                if(daNhap){
                    printf("\nBan da chon xep loai SV!");
                    xeploaiN(head, n);
                }else{
                    printf("\nNhap DS SV truoc!!!!");
                }
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
            case 5:
                if(daNhap){
                    printf("\nBan da chon xuat DS SV!");
                    xuatFile(head, n, fileName);
                }else{
                    printf("\nNhap DS SV truoc!!!!");
                }
                printf("\nXuat DSSV thanh cong vao file %s!", fileName);
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
            case 0:
                printf("\nBan da chon thoat chuong trinh!");
                getch();
                return 0;
            default:
                printf("\nKhong co chuc nang nay!");
                printf("\nBam phim bat ky de tiep tuc!");
                getch();
                break;
        }
    }
}

node nhapN(int n){
    node head = InitHead();
    printf("\n____________________________________\n");
    for(int i = 0; i< n; ++i){
        printf("\nNhap SV thu %d:", i+1);
        SinhVien sv = nhap();
        head = AddTail(head, sv);
    }
    printf("\n____________________________________\n");
    return head;
}


SinhVien nhap(){
    SinhVien sv;
    printf("\nNhap ten: "); fflush(stdin); gets(sv.ten);
    printf("\nNhap gioi tinh: "); gets(sv.gt);
    printf("\nNhap tuoi: "); scanf("%d", &sv.age);
    printf("\nNhap diem 3 mon: "); scanf("%f%f%f", &sv.dT, &sv.dL, &sv.dH);
    sv.dtb = (sv.dH + sv.dL + sv.dT)/3;
    return sv;
}

void xeploaiN(node head, int n){
    printf("\n____________________________________\n");
    for(int i = 0;i < n;++i){
        printf("\nXep loai cua SV thu %d la: ", i+1);
        xeploai(get(head, i));
    }
    printf("\n____________________________________\n");
}

void xeploai(SV sv){
    if(sv.dtb >= 8) printf("Gioi");
    else if(sv.dtb >= 6.5) printf("Kha");
    else if(sv.dtb >= 4) printf("Trung binh");
    else printf("Yeu");
}

void xuatFile(node head, int n, char fileName1[]){
    FILE * fp;
    fp = fopen (fileName1,"w");
    fprintf(fp, "%20s%5s%5s%10s%10s%10s%10s\n", "Ho Ten","GT", "Tuoi", "DT", "DL", "DH", "DTB");
    for(int i = 0;i < n;i++){
        SinhVien sv = get(head, i);
        fprintf(fp, "%20s%5s%5d%10f%10f%10f%10f\n", sv.ten,sv.gt, sv.age, sv.dT, sv.dL, sv.dH, sv.dtb);
    }
    fclose (fp);
}