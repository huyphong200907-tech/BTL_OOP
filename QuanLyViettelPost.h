#ifndef QUANLYVIETTELPOST_H
#define QUANLYVIETTELPOST_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <limits>

using namespace std;

// ============================================================
// HỆ THỐNG ĐƠN HÀNG (Đã gộp kiến trúc OOP hiện đại)
// ============================================================
class DonHang {
public:
    using Tien = int64_t;

    DonHang(string maDon, string tenKhach, Tien tienHang);
    virtual ~DonHang() = default; // Cho phép unique_ptr hủy đúng class con

    const string& getMaVanDon() const;
    string getTrangThai() const;
    void capNhatTrangThai(string tt);
    
    // Đa hình
    virtual Tien tinhTongTien() const = 0;
    virtual void xuatThongTin() const = 0;
    
    // Hỗ trợ hàm hệ thống cũ
    virtual string getDiaChiNhan() const = 0; 
    virtual Tien tinhPhiVanChuyen() const = 0;

protected:
    Tien getTienHang() const;
    void xuatThongTinChung() const;

private:
    string maDon_;
    string tenKhach_;
    Tien tienHang_;
    string trangThai_;
};

// Đơn giao tận nhà
class DonGiaoNha final : public DonHang {
public:
    DonGiaoNha(string maDon, string tenKhach, Tien tienHang, string diaChi, Tien phiGiaoHang);
    Tien tinhTongTien() const override;
    void xuatThongTin() const override;
    string getDiaChiNhan() const override;
    Tien tinhPhiVanChuyen() const override;

private:
    string diaChi_;
    Tien phiGiaoHang_;
};

// Đơn khách tự ra bưu cục nhận (Chuyển thể từ DonTaiCuaHang)
class DonNhanTaiBuuCuc final : public DonHang {
public:
    using DonHang::DonHang;
    Tien tinhTongTien() const override;
    void xuatThongTin() const override;
    string getDiaChiNhan() const override;
    Tien tinhPhiVanChuyen() const override;
};

// ... (Khai báo các class BuuCuc, Nguoi, KhachHang, Shipper giữ nguyên như cũ) ...

// ============================================================
// HỆ THỐNG QUẢN LÝ CHÍNH
// ============================================================
class QuanLyViettelPost {
private:
    vector<KhachHang*> danhSachKhachHang;
    vector<Shipper*> danhSachShipper;
    vector<BuuCuc*> heThongBuuCuc;
    
    // [UPDATE] Sử dụng unordered_map và unique_ptr để tối ưu O(1) tra cứu
    unordered_map<string, unique_ptr<DonHang>> tongDanhSachDonHang;

public:
    QuanLyViettelPost();
    ~QuanLyViettelPost();

    void themBuuCuc(BuuCuc* bc);
    void themKhachHang(KhachHang* kh);
    void themShipper(Shipper* sp);

    // [UPDATE] Cập nhật tham số nhận unique_ptr
    bool taoDonHangMoi(unique_ptr<DonHang> dh);
    DonHang* traCuuDonHang(const string& maVanDon) const;

    void phanBoDonHangVeBuuCuc();
    void capNhatTrangThaiDon(string maVanDon, string trangThaiMoi);

    int64_t tinhTongDoanhThu() const;
    void thongKeDonHangTheoTrangThai(string trangThai) const;
};

#endif
