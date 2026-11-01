#ifndef QUANLYVIETTELPOST_H
#define QUANLYVIETTELPOST_H

#include <vector>
#include <string>
#include "KhachHang.h"
#include "Shipper.h"
#include "DonHang.h"
#include "BuuCuc.h"

using namespace std;

class QuanLyViettelPost {
private:
    // Cấu trúc dữ liệu lưu trữ toàn cục (Central Data Storage)
    vector<KhachHang*> danhSachKhachHang;
    vector<Shipper*> danhSachShipper;
    vector<DonHang*> tongDanhSachDonHang; // Lưu tất cả đơn hàng (Giao nhanh, Hỏa tốc...)
    vector<BuuCuc*> heThongBuuCuc;

    // Singleton pattern (Tùy chọn nâng cao - Đảm bảo chỉ có 1 instance quản lý duy nhất)
    // Nếu dùng Singleton, chuyển constructor vào private. Ở đây để public cho dễ hiểu với OOP cơ bản.

public:
    QuanLyViettelPost();
    ~QuanLyViettelPost();

    // ---------------- MODULE QUẢN LÝ NHÂN SỰ & KHÁCH HÀNG (Người 2) ----------------
    void themKhachHang(KhachHang* kh);
    void themShipper(Shipper* sp);
    KhachHang* timKhachHangTheoSDT(string sdt);
    Shipper* timShipperTheoMa(string ma);
    void hienThiDanhSachShipper() const;

    // ---------------- MODULE QUẢN LÝ ĐƠN HÀNG (Người 1 & Người 3) ----------------
    void taoDonHangMoi(DonHang* dh);
    DonHang* traCuuDonHang(string maVanDon);
    void capNhatTrangThaiDon(string maVanDon, string trangThaiMoi);
    void hienThiTatCaDonHang() const;

    // ---------------- MODULE QUẢN LÝ BƯU CỤC (Người 3) ----------------
    void themBuuCuc(BuuCuc* bc);
    void hienThiHeThongBuuCuc() const;
    // Hàm này sẽ lấy các đơn "Chờ xử lý" đẩy vào hàng đợi của Bưu cục gần nhất
    void phanBoDonHangVeBuuCuc(); 

    // ---------------- MODULE THỐNG KÊ (Người 5) ----------------
    double tinhTongDoanhThu() const;
    void thongKeDonHangTheoTrangThai(string trangThai) const;
    void timShipperGiaoNhieuDonNhat() const;

    // ---------------- MODULE LƯU TRỮ DỮ LIỆU (Người 4) ----------------
    // Gọi các hàm này khi mở app (tải dữ liệu) và khi tắt app (lưu dữ liệu)
    void docDuLieuTuFile(string tenFile);
    void ghiDuLieuXuongFile(string tenFile) const;
};

#endif
