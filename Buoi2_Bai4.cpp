#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

const int MAX_SINH_VIEN = 100;
const int MAX_LOP_HOC = 10;

struct SinhVien {
    char hoTen[50];
    int tuoi;
    float diemToan;
    float diemVan;
    float diemAnh;

    float diemTrungBinh() const {
        return (diemToan + diemVan + diemAnh) / 3;
    }

    const char* xepLoai() const {
        float dtb = diemTrungBinh();
        if (dtb >= 8.5) return "Gioi";
        else if (dtb >= 7.0) return "Kha";
        else if (dtb >= 5.5) return "Trung binh";
        else return "Yeu";
    }
};

struct LopHoc {
    char tenLop[50];
    int siSo;
    SinhVien danhSachSinhVien[MAX_SINH_VIEN];
};
void taoFileDSLop(const LopHoc danhSachLop[], int soLop) {
    std::ofstream file("dslop.txt");
    for (int i = 0; i < soLop; ++i) {
        file << danhSachLop[i].tenLop << '\n';
        file << danhSachLop[i].siSo << '\n';
        for (int j = 0; j < danhSachLop[i].siSo; ++j) {
            file << danhSachLop[i].danhSachSinhVien[j].hoTen << ','
                 << danhSachLop[i].danhSachSinhVien[j].tuoi << ','
                 << danhSachLop[i].danhSachSinhVien[j].diemToan << ','
                 << danhSachLop[i].danhSachSinhVien[j].diemVan << ','
                 << danhSachLop[i].danhSachSinhVien[j].diemAnh << '\n';
        }
    }
    file.close();
}
int docFileDSLop(const char* fileName, LopHoc danhSachLop[]) {
    std::ifstream file(fileName);
    int soLop = 0;
    std::string line;

    while (std::getline(file, line)) {
        strcpy(danhSachLop[soLop].tenLop, line.c_str());
        std::getline(file, line);
        danhSachLop[soLop].siSo = std::stoi(line);

        for (int i = 0; i < danhSachLop[soLop].siSo; ++i) {
            std::getline(file, line);
            std::stringstream ss(line);
            std::string temp;

            std::getline(ss, temp, ',');
            strcpy(danhSachLop[soLop].danhSachSinhVien[i].hoTen, temp.c_str());
            std::getline(ss, temp, ',');
            danhSachLop[soLop].danhSachSinhVien[i].tuoi = std::stoi(temp);
            std::getline(ss, temp, ',');
            danhSachLop[soLop].danhSachSinhVien[i].diemToan = std::stof(temp);
            std::getline(ss, temp, ',');
            danhSachLop[soLop].danhSachSinhVien[i].diemVan = std::stof(temp);
            std::getline(ss, temp, ',');
            danhSachLop[soLop].danhSachSinhVien[i].diemAnh = std::stof(temp);
        }
        ++soLop;
    }
    file.close();
    return soLop;
}
void xuatDanhSachLop(const LopHoc danhSachLop[], int soLop, const char* fileName) {
    std::ofstream file(fileName);
    for (int i = 0; i < soLop; ++i) {
        file << "Lop: " << danhSachLop[i].tenLop << ", Si so: " << danhSachLop[i].siSo << '\n';
        for (int j = 0; j < danhSachLop[i].siSo; ++j) {
            file << "Ho ten: " << danhSachLop[i].danhSachSinhVien[j].hoTen 
                 << ", Tuoi: " << danhSachLop[i].danhSachSinhVien[j].tuoi 
                 << ", Diem Toan: " << danhSachLop[i].danhSachSinhVien[j].diemToan 
                 << ", Diem Van: " << danhSachLop[i].danhSachSinhVien[j].diemVan 
                 << ", Diem Anh: " << danhSachLop[i].danhSachSinhVien[j].diemAnh 
                 << ", Diem TB: " << danhSachLop[i].danhSachSinhVien[j].diemTrungBinh() 
                 << ", Xep loai: " << danhSachLop[i].danhSachSinhVien[j].xepLoai() << '\n';
        }
    }
    file.close();
}
void inLopGioi(const LopHoc danhSachLop[], int soLop, const char* fileName) {
    std::ofstream file(fileName, std::ios::app);
    for (int i = 0; i < soLop; ++i) {
        int soSVGioi = 0;
        for (int j = 0; j < danhSachLop[i].siSo; ++j) {
            if (strcmp(danhSachLop[i].danhSachSinhVien[j].xepLoai(), "Gioi") == 0) {
                ++soSVGioi;
            }
        }
        if (soSVGioi > 5) {
            file << "Lop: " << danhSachLop[i].tenLop << " co " << soSVGioi << " sinh vien gioi\n";
        }
    }
    file.close();
}
void lopNhieuSinhVienNhat(const LopHoc danhSachLop[], int soLop, const char* fileName) {
    std::ofstream file(fileName, std::ios::app);
    int maxSiSo = 0;
    int lopIndex = -1;
    for (int i = 0; i < soLop; ++i) {
        if (danhSachLop[i].siSo > maxSiSo) {
            maxSiSo = danhSachLop[i].siSo;
            lopIndex = i;
        }
    }
    if (lopIndex != -1) {
        file << "Lop co nhieu sinh vien nhat: " << danhSachLop[lopIndex].tenLop << " voi " << maxSiSo << " sinh vien\n";
    }
    file.close();
}
void sinhVienGioiNhat(const LopHoc danhSachLop[], int soLop, const char* fileName) {
    std::ofstream file(fileName, std::ios::app);
    SinhVien* sinhVienGioiNhat = nullptr;
    for (int i = 0; i < soLop; ++i) {
        for (int j = 0; j < danhSachLop[i].siSo; ++j) {
            if (!sinhVienGioiNhat || danhSachLop[i].danhSachSinhVien[j].diemTrungBinh() > sinhVienGioiNhat->diemTrungBinh()) {
                sinhVienGioiNhat = &danhSachLop[i].danhSachSinhVien[j];
            }
        }
    }
    if (sinhVienGioiNhat) {
        file << "Sinh vien co diem trung binh cao nhat: " << sinhVienGioiNhat->hoTen << " voi diem TB: " 
             << sinhVienGioiNhat->diemTrungBinh() << '\n';
    }
    file.close();
}
int main() {
    // Gi? l?p d? li?u
    LopHoc danhSachLop[MAX_LOP_HOC] = {
        {"Lop 1", 3, {{"Nguyen Van A", 20, 9, 8, 7}, {"Tran Thi B", 21, 8, 9, 9}, {"Le Van C", 22, 10, 9, 8}}},
        {"Lop 2", 2, {{"Hoang Thi D", 20, 7, 8, 6}, {"Pham Van E", 21, 5, 6, 7}}},
    };
    int soLop = 2;

    // T?o file
    taoFileDSLop(danhSachLop, soLop);

    // Ð?c file
    LopHoc docDanhSachLop[MAX_LOP_HOC];
    int soLopDoc = docFileDSLop("dslop.txt", docDanhSachLop);

    // Xu?t danh sách l?p
    xuatDanhSachLop(docDanhSachLop, soLopDoc, "output.txt");

    // In danh sách các l?p có trên 5 sinh viên có di?m trung bình lo?i gi?i
    inLopGioi(docDanhSachLop, soLopDoc, "output.txt");

    // Tìm và in thông tin l?p có nhi?u sinh viên nh?t
    lopNhieuSinhVienNhat(docDanhSachLop, soLopDoc, "output.txt");

    // Tìm và in thông tin sinh viên có di?m trung bình cao nh?t trong các l?p
    sinhVienGioiNhat(docDanhSachLop, soLopDoc, "output.txt");

    return 0;
}
