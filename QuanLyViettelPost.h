#ifndef QUANLYVIETTELPOST_H
#define QUANLYVIETTELPOST_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>
#include <stdexcept>
#include <limits>

using namespace std;

// ============================================================
// MODULE ĐỊNH DANH & ĐÓNG GÓI (OOP)
// ============================================================
class DonHang {
public:
    using Tien = int64_t;

    DonHang(string maDon, string tenKhach, Tien tienHang);
    virtual ~DonHang() = default;

    const string& getMaVanDon() const;
    string getTenKhach() const;
    string getTrangThai() const;
    Tien getTienHang() const;
    
    void capNhatTrangThai(string tt);
    
    virtual Tien tinhTongTien() const = 0;
    virtual void xuatThongTin() const = 0;
    virtual string getDiaChiNhan() const = 0; 
    virtual Tien tinhPhiVanChuyen() const = 0;
    
    // Phục vụ File I/O
    virtual int getLoaiDon() const = 0; 

protected:
    void xuatThongTinChung() const;

private:
    string maDon_;
    string tenKhach_;
    Tien tienHang_;
    string trangThai_;
};

class DonGiaoNha final : public DonHang {
public:
    DonGiaoNha(string maDon, string tenKhach, Tien tienHang, string diaChi, Tien phiGiaoHang);
    Tien tinhTongTien() const override;
    void xuatThongTin() const override;
    string getDiaChiNhan() const override;
    Tien tinhPhiVanChuyen() const override;
    int getLoaiDon() const override;

private:
    string diaChi_;
    Tien phiGiaoHang_;
};

class DonNhanTaiBuuCuc final : public DonHang {
public:
    using DonHang::DonHang;
    Tien tinhTongTien() const override;
    void xuatThongTin() const override;
    string getDiaChiNhan() const override;
    Tien tinhPhiVanChuyen() const override;
    int getLoaiDon() const override;
};

// ============================================================
// MODULE CẤU TRÚC DỮ LIỆU (QUEUE)
// ============================================================
class BuuCuc {
private:
    string maBuuCuc;
    string khuVuc;
    queue<DonHang*> hangDoiDonHang; // Sử dụng Queue (FIFO)
public:
    BuuCuc(string ma, string kv);
    string getMaBuuCuc() const;
    string getKhuVuc() const;
    int soDonDangCho() const;
    void nhanDonHangVaoHangDoi(DonHang* dh);
    void xuLyDonHangTrongHangDoi(); // Lấy từ Queue ra để xử lý
};

// --- HỆ THỐNG NHÂN SỰ ---
class Nguoi {
protected:
    string hoTen;
    string soDienThoai;
public:
    Nguoi(string ht, string sdt);
    virtual ~Nguoi() = default;
    string getHoTen() const;
    virtual void hienThi() const = 0;
};

class Shipper : public Nguoi {
private:
    string maShipper;
    int soDonDaGiao;
public:
    Shipper(string ma, string ht, string sdt);
    int getSoDonDaGiao() const;
    void tangSoDonDaGiao();
    void hienThi() const override;
};

// ============================================================
// HỆ THỐNG QUẢN LÝ CHÍNH
// ============================================================
class QuanLyViettelPost {
private:
    vector<Shipper*> danhSachShipper;
    vector<BuuCuc*> heThongBuuCuc;
    unordered_map<string, unique_ptr<DonHang>> tongDanhSachDonHang;

public:
    QuanLyViettelPost();
    ~QuanLyViettelPost();

    void themBuuCuc(BuuCuc* bc);
    void themShipper(Shipper* sp);

    bool taoDonHangMoi(unique_ptr<DonHang> dh);
    void traCuuDonHang(const string& maVanDon) const;

    // Luồng xử lý
    void phanBoDonHangVeBuuCuc();
    void buuCucXuLyDonHang();
    
    // Thống kê
    void thongKeDoanhThu() const;
    void timShipperXuatSac() const;

    // File I/O
    void ghiDuLieuXuongFile(const string& tenFile) const;
    void docDuLieuTuFile(const string& tenFile);
};

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 0cb9dda85d357fdae662589c31e13a67b6631665
