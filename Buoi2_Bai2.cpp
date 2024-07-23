#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int phan_nguyen;
    int tu_so;
    int mau_so;
} HonSo;

typedef struct {
    int tu_so;
    int mau_so;
} PhanSo;

// 1. Tao mang b chua gia tri hon so ngau nhien. Luu y mau khac 0.
void taoMangHonSo(HonSo b[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        b[i].phan_nguyen = rand() % 10; 
        b[i].tu_so = rand() % 10;       
        do {
            b[i].mau_so = rand() % 10;  
        } while (b[i].mau_so == 0);
    }
}

// 2. Xuat danh sach hon so.
void xuatDanhSachHonSo(HonSo b[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d/%d\n", b[i].phan_nguyen, b[i].tu_so, b[i].mau_so);
    }
}

// 3. So sanh 2 hon so
int soSanhHonSo(HonSo a, HonSo b) {
    int tu_so_a = a.phan_nguyen * a.mau_so + a.tu_so;
    int tu_so_b = b.phan_nguyen * b.mau_so + b.tu_so;
    int mau_so_chung = a.mau_so * b.mau_so;
    
    if (tu_so_a * b.mau_so < tu_so_b * a.mau_so)
        return -1;
    else if (tu_so_a * b.mau_so > tu_so_b * a.mau_so)
        return 1;
    else
        return 0;
}

// 4. Chuyen hon so thanh phan so
PhanSo chuyenHonSoThanhPhanSo(HonSo a) {
    PhanSo ketqua;
    ketqua.tu_so = a.phan_nguyen * a.mau_so + a.tu_so;
    ketqua.mau_so = a.mau_so;
    return ketqua;
}

// 5. Chuyen phan so thanh hon so
HonSo chuyenPhanSoThanhHonSo(PhanSo a) {
    HonSo ketqua;
    ketqua.phan_nguyen = a.tu_so / a.mau_so;
    ketqua.tu_so = a.tu_so % a.mau_so;
    ketqua.mau_so = a.mau_so;
    return ketqua;
}

// 6. Tinh tong, hieu, tich, thuong 2 hon so
HonSo tinhTongHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.mau_so + ps_b.tu_so * ps_a.mau_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.mau_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

HonSo tinhHieuHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.mau_so - ps_b.tu_so * ps_a.mau_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.mau_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

HonSo tinhTichHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.tu_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.mau_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

HonSo tinhThuongHonSo(HonSo a, HonSo b) {
    PhanSo ps_a = chuyenHonSoThanhPhanSo(a);
    PhanSo ps_b = chuyenHonSoThanhPhanSo(b);
    PhanSo ketqua;
    
    ketqua.tu_so = ps_a.tu_so * ps_b.mau_so;
    ketqua.mau_so = ps_a.mau_so * ps_b.tu_so;
    
    return chuyenPhanSoThanhHonSo(ketqua);
}

// 7. Sap xep mang b tang/giam theo 3 giai thuat sap xep da hoc


void sapXepNoiBot(HonSo b[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (soSanhHonSo(b[j], b[j+1]) > 0) {
                HonSo temp = b[j];
                b[j] = b[j+1];
                b[j+1] = temp;
            }
        }
    }
}


void sapXepChen(HonSo b[], int n) {
    for (int i = 1; i < n; i++) {
        HonSo key = b[i];
        int j = i - 1;
        while (j >= 0 && soSanhHonSo(b[j], key) > 0) {
            b[j + 1] = b[j];
            j = j - 1;
        }
        b[j + 1] = key;
    }
}


void sapXepChon(HonSo b[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (soSanhHonSo(b[j], b[min_idx]) < 0) {
                min_idx = j;
            }
        }
        HonSo temp = b[min_idx];
        b[min_idx] = b[i];
        b[i] = temp;
    }
}

int main() {
    int n = 10; 
    HonSo a;
    HonSo b[n];
    
    
    taoMangHonSo(b, n);
    printf("Danh sach hon so ban dau:\n");
    xuatDanhSachHonSo(b, n);
    
    
    taoMangHonSo(b,n);
    printf("Chuyen hon so thanh phan so: ",chuyenHonSoThanhPhanSo(a));
    

    sapXepNoiBot(b, n);
    printf("\nDanh sách hon so sau khi sap xep noi bot:\n");
    xuatDanhSachHonSo(b, n);
    

    taoMangHonSo(b, n); 
    sapXepChen(b, n);
    printf("\nDanh sach hon so sau khi sap xep chen:\n");
    xuatDanhSachHonSo(b, n);
    

    taoMangHonSo(b, n); 
    sapXepChon(b, n);
    printf("\nDanh sach hon s sau khi sap xep chen:\n");
    xuatDanhSachHonSo(b, n);
    
    return 0;
}
