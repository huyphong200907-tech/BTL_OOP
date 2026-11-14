// ============================================================
// BuuCuc.cpp  -  Module Luong xu ly & Cau truc du lieu (Queue)
// Phu trach: Duc
// Ham: QuanLyViettelPost::phanBoDonHangVeBuuCuc()
//      QuanLyViettelPost::capNhatTrangThaiDon()
// ------------------------------------------------------------
// GIA DINH ve cac file .h khac (doi chieu, chi sua TEN cho khop):
//   DonHang : getMaVanDon(), getTrangThai(), setTrangThai(string),
//             getDiaChiNhan()
//   BuuCuc  : nhanDon(DonHang*)  -> push vao queue<DonHang*>
//             soDonDangCho()     -> so don trong queue
//             getKhuVuc(), getMaBuuCuc()
// ============================================================

#include <iostream>
#include <string>
#include <algorithm>
#include "QuanLyViettelPost.h"

using namespace std;

// ---------- Trang thai chuan: THONG NHAT VOI CA NHOM ----------
static const string TT_CHO_XU_LY  = "Chờ xử lý";
static const string TT_DA_PHAN_BO = "Đã phân bổ";
static const string TT_DANG_GIAO  = "Đang giao";
static const string TT_DA_GIAO    = "Đã giao";
static const string TT_DA_HUY     = "Đã hủy";

// ---------- Ham phu (chi dung trong file nay) ----------
static string chuThuong(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

static bool diaChiThuocKhuVuc(const string& diaChi, const string& khuVuc) {
    if (khuVuc.empty()) return false;
    return chuThuong(diaChi).find(chuThuong(khuVuc)) != string::npos;
}

// Cap cua trang thai: chi cho tien len, khong lui
static int capTrangThai(const string& tt) {
    if (tt == TT_CHO_XU_LY)  return 0;
    if (tt == TT_DA_PHAN_BO) return 1;
    if (tt == TT_DANG_GIAO)  return 2;
    if (tt == TT_DA_GIAO)    return 3;
    if (tt == TT_DA_HUY)     return 4;
    return -1;
}

// ============================================================
// phanBoDonHangVeBuuCuc
// Don "Cho xu ly" -> buu cuc cung khu vuc (it don cho nhat)
// -> push vao queue cua buu cuc -> doi thanh "Da phan bo".
// ============================================================
void QuanLyViettelPost::phanBoDonHangVeBuuCuc() {
    if (heThongBuuCuc.empty()) {
        cout << "[Loi] Chua co buu cuc nao trong he thong.\n";
        return;
    }

    int soPhanBo = 0, soKhongTim = 0;

    for (DonHang* dh : tongDanhSachDonHang) {
        if (dh == nullptr || dh->getTrangThai() != TT_CHO_XU_LY) continue;

        BuuCuc* chon = nullptr;
        for (BuuCuc* bc : heThongBuuCuc) {
            if (bc == nullptr) continue;
            if (!diaChiThuocKhuVuc(dh->getDiaChiNhan(), bc->getKhuVuc())) continue;
            if (chon == nullptr || bc->soDonDangCho() < chon->soDonDangCho())
                chon = bc;
        }

        if (chon == nullptr) {
            cout << "[Canh bao] Don " << dh->getMaVanDon()
                 << ": khong co buu cuc cung khu vuc.\n";
            ++soKhongTim;
            continue;
        }

        chon->nhanDon(dh);
        dh->setTrangThai(TT_DA_PHAN_BO);
        ++soPhanBo;
        cout << "Don " << dh->getMaVanDon() << " -> buu cuc "
             << chon->getMaBuuCuc() << "\n";
    }

    cout << "Ket qua: phan bo " << soPhanBo << " don, "
         << soKhongTim << " don chua tim duoc buu cuc.\n";
}

// ============================================================
// capNhatTrangThaiDon
// Tim don theo maVanDon, kiem tra hop le roi cap nhat.
// ============================================================
void QuanLyViettelPost::capNhatTrangThaiDon(string maVanDon, string trangThaiMoi) {
    int capMoi = capTrangThai(trangThaiMoi);
    if (capMoi < 0) {
        cout << "[Loi] Trang thai \"" << trangThaiMoi << "\" khong hop le.\n";
        return;
    }

    for (DonHang* dh : tongDanhSachDonHang) {
        if (dh == nullptr || dh->getMaVanDon() != maVanDon) continue;

        const string ttCu = dh->getTrangThai();
        int capCu = capTrangThai(ttCu);

        if (ttCu == TT_DA_GIAO || ttCu == TT_DA_HUY) {
            cout << "[Loi] Don " << maVanDon << " da ket thuc (" << ttCu
                 << "), khong the cap nhat.\n";
            return;
        }
        if (trangThaiMoi != TT_DA_HUY && capMoi <= capCu) {
            cout << "[Loi] Khong the chuyen tu \"" << ttCu << "\" ve \""
                 << trangThaiMoi << "\".\n";
            return;
        }

        dh->setTrangThai(trangThaiMoi);
        cout << "Don " << maVanDon << ": " << ttCu << " -> "
             << trangThaiMoi << "\n";
        return;
    }

    cout << "[Loi] Khong tim thay don co ma van don " << maVanDon << ".\n";
}
