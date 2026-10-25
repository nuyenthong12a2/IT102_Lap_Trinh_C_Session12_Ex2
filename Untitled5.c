#include <stdio.h>
#include <string.h>

#define MAX_NV 50
#define TIEN_PHAT_DI_MUON 50000.0f
#define NGUONG_DI_MUON 15

typedef struct {
    int maNV;
    char hoTen[50];
    int soPhutDiMuon;
    float luongCoBan;
} NhanVien;

void xoaBoDem();
void xoaXuongDong(char str[]);
int timTheoMaNV(NhanVien ds[], int soLuong, int maNV);
int themNhanVien(NhanVien ds[], int soLuong);
void hienThiDanhSach(NhanVien ds[], int soLuong);
void capNhatPhutDiMuon(NhanVien ds[], int soLuong);
void timKiemNhanVien(NhanVien ds[], int soLuong);

int main() {
    NhanVien ds[MAX_NV];
    int soLuong = 0;
    int luaChon;

    do {
        printf("\n===== HE THONG QUAN LY CHAM CONG HRM =====\n");
        printf("1. Them nhan vien moi\n");
        printf("2. Hien thi danh sach va tinh luong\n");
        printf("3. Cap nhat so phut di muon\n");
        printf("4. Tim kiem nhan vien theo ma\n");
        printf("0. Thoat\n");
        printf("==========================================\n");
        printf("Nhap lua chon: ");

        if (scanf("%d", &luaChon) != 1) {
            printf("=> Lua chon khong hop le! Vui long nhap so.\n");
            xoaBoDem();
            continue;
        }

        switch (luaChon) {
            case 1:
                soLuong = themNhanVien(ds, soLuong);
                break;
            case 2:
                hienThiDanhSach(ds, soLuong);
                break;
            case 3:
                capNhatPhutDiMuon(ds, soLuong);
                break;
            case 4:
                timKiemNhanVien(ds, soLuong);
                break;
            case 0:
                printf("=> Da thoat chuong trinh thanh cong!\n");
                break;
            default:
                printf("=> Chuc nang khong ton tai. Vui long chon lai!\n");
                break;
        }
    } while (luaChon != 0);

    return 0;
}

void xoaBoDem() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void xoaXuongDong(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int timTheoMaNV(NhanVien ds[], int soLuong, int maNV) {
    for (int i = 0; i < soLuong; i++) {
        if (ds[i].maNV == maNV) {
            return i;
        }
    }
    return -1;
}

int themNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong >= MAX_NV) {
        printf("=> Danh sach da day (Toi da %d nhan vien)!\n", MAX_NV);
        return soLuong;
    }

    NhanVien nvMoi;
    printf("\n--- THEM NHAN VIEN MOI ---\n");

    printf("Nhap ma nhan vien: ");
    if (scanf("%d", &nvMoi.maNV) != 1) {
        printf("=> Ma nhan vien khong hop le!\n");
        xoaBoDem();
        return soLuong;
    }

    if (timTheoMaNV(ds, soLuong, nvMoi.maNV) != -1) {
        printf("=> Loi: Ma nhan vien %d da ton tai trong he thong!\n", nvMoi.maNV);
        xoaBoDem();
        return soLuong;
    }

    xoaBoDem();

    printf("Nhap ho va ten: ");
    if (fgets(nvMoi.hoTen, sizeof(nvMoi.hoTen), stdin) != NULL) {
        xoaXuongDong(nvMoi.hoTen);
    }

    do {
        printf("Nhap so phut di muon (>= 0): ");
        if (scanf("%d", &nvMoi.soPhutDiMuon) != 1) {
            printf("=> Du lieu phai la so nguyen!\n");
            xoaBoDem();
            nvMoi.soPhutDiMuon = -1;
            continue;
        }
        if (nvMoi.soPhutDiMuon < 0) {
            printf("=> So phut di muon khong duoc am!\n");
        }
    } while (nvMoi.soPhutDiMuon < 0);

    do {
        printf("Nhap luong co ban (>= 0): ");
        if (scanf("%f", &nvMoi.luongCoBan) != 1) {
            printf("=> Du lieu phai la so thuc!\n");
            xoaBoDem();
            nvMoi.luongCoBan = -1.0f;
            continue;
        }
        if (nvMoi.luongCoBan < 0) {
            printf("=> Luong co ban khong duoc am!\n");
        }
    } while (nvMoi.luongCoBan < 0);

    ds[soLuong] = nvMoi;
    soLuong++;
    printf("=> Them nhan vien thanh cong!\n");

    return soLuong;
}

void hienThiDanhSach(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("=> Danh sach nhan vien hien dang rong!\n");
        return;
    }

    printf("\n------------------------------- DANH SACH NHAN VIEN -------------------------------\n");
    printf("%-8s | %-25s | %-12s | %-15s\n", "Ma NV", "Ho ten", "Phut muon", "Luong thuc nhan");
    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < soLuong; i++) {
        float tienPhat = (ds[i].soPhutDiMuon > NGUONG_DI_MUON) ? TIEN_PHAT_DI_MUON : 0.0f;
        float luongThucNhan = ds[i].luongCoBan - tienPhat;
        if (luongThucNhan < 0) {
            luongThucNhan = 0.0f;
        }

        printf("%-8d | %-25s | %-12d | %-15.0f\n", 
               ds[i].maNV, 
               ds[i].hoTen, 
               ds[i].soPhutDiMuon, 
               luongThucNhan);
    }
    printf("------------------------------------------------------------------------------------\n");
}

void capNhatPhutDiMuon(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("=> Danh sach nhan vien hien dang rong!\n");
        return;
    }

    int maNV;
    printf("\nNhap ma NV can cap nhat: ");
    if (scanf("%d", &maNV) != 1) {
        printf("=> Du lieu khong hop le!\n");
        xoaBoDem();
        return;
    }

    int viTri = timTheoMaNV(ds, soLuong, maNV);
    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien!\n");
        return;
    }

    int phutMoi;
    do {
        printf("Nhap so phut di muon moi (>= 0): ");
        if (scanf("%d", &phutMoi) != 1) {
            printf("=> Du lieu phai la so nguyen!\n");
            xoaBoDem();
            phutMoi = -1;
            continue;
        }
        if (phutMoi < 0) {
            printf("=> So phut di muon khong duoc am!\n");
        }
    } while (phutMoi < 0);

    ds[viTri].soPhutDiMuon = phutMoi;
    printf("=> Cap nhat thanh cong!\n");
}

void timKiemNhanVien(NhanVien ds[], int soLuong) {
    if (soLuong == 0) {
        printf("=> Danh sach nhan vien hien dang rong!\n");
        return;
    }

    int maNV;
    printf("\nNhap ma NV can tim: ");
    if (scanf("%d", &maNV) != 1) {
        printf("=> Du lieu khong hop le!\n");
        xoaBoDem();
        return;
    }

    int viTri = timTheoMaNV(ds, soLuong, maNV);
    if (viTri == -1) {
        printf("=> Khong tim thay nhan vien co ma %d!\n", maNV);
        return;
    }

    float tienPhat = (ds[viTri].soPhutDiMuon > NGUONG_DI_MUON) ? TIEN_PHAT_DI_MUON : 0.0f;
    float luongThucNhan = ds[viTri].luongCoBan - tienPhat;
    if (luongThucNhan < 0) {
        luongThucNhan = 0.0f;
    }

    printf("\n--- THONG TIN NHAN VIEN ---\n");
    printf("Ma NV           : %d\n", ds[viTri].maNV);
    printf("Ho va ten       : %s\n", ds[viTri].hoTen);
    printf("So phut di muon : %d phut\n", ds[viTri].soPhutDiMuon);
    printf("Luong co ban    : %.0f VND\n", ds[viTri].luongCoBan);
    printf("Tien phat muon  : %.0f VND\n", tienPhat);
    printf("Luong thuc nhan : %.0f VND\n", luongThucNhan);
}
