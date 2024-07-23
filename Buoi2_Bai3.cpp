#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXSIZE 100
const char fNameIn_DSSV[] = "input_DSSV.txt";
const char fNameOut_DSSV[] = "output_DSSV.txt";

struct SinhVien {
    char mssv[11];
    char ho[8], hoLot[20], ten[8];
    double diemTB;
    char xepLoai[10];
};

typedef SinhVien ItemType;

void xepLoaiSV(ItemType &x) {
    if (x.diemTB >= 8)
        strcpy(x.xepLoai, "Gioi");
    else if (x.diemTB >= 6.5)
        strcpy(x.xepLoai, "Kha");
    else if (x.diemTB >= 5.0)
        strcpy(x.xepLoai, "Trung binh");
    else
        strcpy(x.xepLoai, "Yeu");
}

void xuatTTSV(const ItemType &x) {
    cout << x.mssv << "\t" << x.ho << "\t" << x.hoLot << "\t" << x.ten << "\t" 
         << x.diemTB << "\t" << x.xepLoai << endl;
}

void docTTSV(FILE *fi, ItemType &x) {
    fscanf(fi, "%[^#]%*c%[^#]%*c%[^#]%*c%[^#]%*c%lf\n", x.mssv, x.ho, x.hoLot, x.ten, &x.diemTB);
    xepLoaiSV(x);
}

void ghiTTSV(FILE *fo, const ItemType &x) {
    fprintf(fo, "%-15s%-10s%-20s%-10s%5.2lf%-10s\n", x.mssv, x.ho, x.hoLot, x.ten, x.diemTB, x.xepLoai);
}

void docDSSV(const char fNameIn[], ItemType ds[], int &n) {
    FILE *fi = fopen(fNameIn, "rt");
    if (fi == NULL) {
        cout << "Loi: mo file de doc du lieu." << endl;
        return;
    }
    fscanf(fi, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        ItemType x;
        docTTSV(fi, x);
        ds[i] = x;
    }
    fclose(fi);
}

void ghiDSSV(const char fNameOut[], const ItemType ds[], int n) {
    FILE *fo = fopen(fNameOut, "wt");
    if (fo == NULL) {
        cout << "Loi: mo file de ghi du lieu." << endl;
        return;
    }
    fprintf(fo, "%-5s%-15s%-40s%-10s%-10s\n", "STT", "MSSV", "HO VA TEN SINH VIEN", "DIEM TB", "XEP LOAI");
    for (int i = 0; i < n; i++) {
        fprintf(fo, "%-5d", i + 1);
        ghiTTSV(fo, ds[i]);
    }
    fclose(fo);
}

void xuatDSSV(const ItemType ds[], int n) {
    cout << "STT" << "\t" << "MSSV" << "\t" << "HO VA TEN SINH VIEN" << "\t" << "DIEM TB" << "\t" << "XEP LOAI" << endl;
    for (int i = 0; i < n; i++) {
        cout << (i + 1) << "\t";
        xuatTTSV(ds[i]);
    }
}

bool compareAsc(const ItemType &a, const ItemType &b) {
    return a.diemTB < b.diemTB;
}

bool compareDesc(const ItemType &a, const ItemType &b) {
    return a.diemTB > b.diemTB;
}

void sapXepDSSV(ItemType ds[], int n, bool tangDan) {
    if (tangDan) {
        sort(ds, ds + n, compareAsc);
    } else {
        sort(ds, ds + n, compareDesc);
    }
}

void timSVMaxMin(ItemType ds[], int n) {
    if (n == 0) return;
    ItemType maxSV = ds[0], minSV = ds[0];
    for (int i = 1; i < n; i++) {
        if (ds[i].diemTB > maxSV.diemTB) maxSV = ds[i];
        if (ds[i].diemTB < minSV.diemTB) minSV = ds[i];
    }
    cout << "Sinh vien co diem trung binh cao nhat:\n";
    xuatTTSV(maxSV);
    cout << "Sinh vien co diem trung binh thap nhat:\n";
    xuatTTSV(minSV);
}

void xuatSVGioiKha(ItemType ds[], int n) {
    cout << "Danh sach sinh vien xep loai Gioi va Kha:\n";
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].xepLoai, "Gioi") == 0 || strcmp(ds[i].xepLoai, "Kha") == 0) {
            xuatTTSV(ds[i]);
        }
    }
}

int demSVHoNguyen(ItemType ds[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].ho, "Nguyen") == 0) {
            count++;
        }
    }
    return count;
}

void showMenu() {
    cout << "\n***********************************************";
    cout << "\n* MENU *";
    cout << "\n***********************************************";
    cout << "\n* 1. Doc danh sach sinh vien tu file *";
    cout << "\n* 2. Xuat danh sach ra man hinh *";
    cout << "\n* 3. Ghi danh sach sinh vien xuong file *";
    cout << "\n* 4. Sap xep danh sach sinh vien tang dan theo diem TB *";
    cout << "\n* 5. Sap xep danh sach sinh vien giam dan theo diem TB *";
    cout << "\n* 6. Tim sinh vien co diem TB cao nhat va thap nhat *";
    cout << "\n* 7. Xuat danh sach sinh vien co xep loai Gioi va Kha *";
    cout << "\n* 8. Dem so luong sinh vien co ho Nguyen *";
    cout << "\n* 0. Thoat chuong trinh *";
    cout << "\n***********************************************";
}

void process() {
    ItemType DS[MAXSIZE];
    int N = 0;
    int chonChucNang;
    do {
        showMenu();
        cout << "\nBan hay chon mot chuc nang bat ky: ";
        cin >> chonChucNang;
        switch (chonChucNang) {
            case 1:
                docDSSV(fNameIn_DSSV, DS, N);
                cout << "Danh sach sinh vien doc tu file:\n";
                xuatDSSV(DS, N);
                break;
            case 2:
                cout << "Danh sach sinh vien la:\n";
                xuatDSSV(DS, N);
                break;
            case 3:
                cout << "Ghi danh sach sinh vien xuong file\n";
                ghiDSSV(fNameOut_DSSV, DS, N);
                break;
            case 4:
                cout << "Sap xep danh sach sinh vien tang dan theo diem TB\n";
                sapXepDSSV(DS, N, true);
                xuatDSSV(DS, N);
                break;
            case 5:
                cout << "Sap xep danh sach sinh vien giam dan theo diem TB\n";
                sapXepDSSV(DS, N, false);
                xuatDSSV(DS, N);
                break;
            case 6:
                timSVMaxMin(DS, N);
                break;
            case 7:
                xuatSVGioiKha(DS, N);
                break;
            case 8:
                cout << "So luong sinh vien co ho Nguyen: " << demSVHoNguyen(DS, N) << endl;
                break;
        }
    } while (chonChucNang != 0);
}

int main() {
    process();
    return 0;
}
