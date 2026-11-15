#include "QuanLyViettelPost.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

// --- CÀI ĐẶT ĐƠN HÀNG ---
DonHang::DonHang(string maDon, string tenKhach, Tien tienHang)
    : maDon_(move(maDon)), tenKhach_(move(tenKhach)), tienHang_(tienHang), trangThai_("Cho xu ly") {}

const string& DonHang::getMaVanDon() const { return maDon_; }
string DonHang::getTenKhach() const { return tenKhach_; }
string DonHang::getTrangThai() const { return trangThai_; }
DonHang::Tien DonHang::getTienHang() const { return tienHang_; }
void DonHang::capNhatTrangThai(string tt) { trangThai_ = tt; }

void DonHang::xuatThongTinChung() const {
    cout << "Ma don: " << maDon_ << " | Khach: " << tenKhach_ 
         << " | Tien hang: " << tienHang_ << " | TT: " << trangThai_ << "\n";
}

DonGiaoNha::DonGiaoNha(string ma, string ten, Tien tien, string diaChi, Tien phi)
    : DonHang(move(ma), move(ten), tien), diaChi_(move(diaChi)), phiGiaoHang_(phi) {}
DonHang::Tien DonGiaoNha::tinhTongTien() const { return getTienHang() + phiGiaoHang_; }
void DonGiaoNha::xuatThongTin() const {
    cout << "[Giao Tan Nha] "; xuatThongTinChung();
    cout << "   -> Dia chi: " << diaChi_ << " | Phi ship: " << phiGiaoHang_ << "\n";
}
string DonGiaoNha::getDiaChiNhan() const { return diaChi_; }
DonHang::Tien DonGiaoNha::tinhPhiVanChuyen() const { return phiGiaoHang_; }
int DonGiaoNha::getLoaiDon() const { return 1; }

DonHang::Tien DonNhanTaiBuuCuc::tinhTongTien() const { return getTienHang(); }
void DonNhanTaiBuuCuc::xuatThongTin() const {
    cout << "[Tai Buu Cuc]  "; xuatThongTinChung();
}
string DonNhanTaiBuuCuc::getDiaChiNhan() const { return "Tai Buu Cuc"; }
DonHang::Tien DonNhanTaiBuuCuc::tinhPhiVanChuyen() const { return 0; }
int DonNhanTaiBuuCuc::getLoaiDon() const { return 2; }


// --- CÀI ĐẶT CẤU TRÚC DỮ LIỆU QUEUE (BƯU CỤC) ---
BuuCuc::BuuCuc(string ma, string kv) : maBuuCuc(ma), khuVuc(kv) {}
string BuuCuc::getMaBuuCuc() const { return maBuuCuc; }
string BuuCuc::getKhuVuc() const { return khuVuc; }
int BuuCuc::soDonDangCho() const { return hangDoiDonHang.size(); }

void BuuCuc::nhanDonHangVaoHangDoi(DonHang* dh) {
    hangDoiDonHang.push(dh); // Thêm vào cuối hàng đợi (Enqueue)
}

void BuuCuc::xuLyDonHangTrongHangDoi() {
    int count = 0;
    while (!hangDoiDonHang.empty()) {
        DonHang* dh = hangDoiDonHang.front(); // Lấy phần tử đầu (Peek)
        hangDoiDonHang.pop(); // Xóa khỏi hàng đợi (Dequeue)
        
        dh->capNhatTrangThai("Da giao"); // Xử lý xong
        count++;
    }
    if (count > 0) cout << "-> Buu cuc " << maBuuCuc << " da xu ly xong " << count << " don hang.\n";
}


// --- NHÂN SỰ ---
Nguoi::Nguoi(string ht, string sdt) : hoTen(ht), soDienThoai(sdt) {}
string Nguoi::getHoTen() const { return hoTen; }

Shipper::Shipper(string ma, string ht, string sdt) : Nguoi(ht, sdt), maShipper(ma), soDonDaGiao(0) {}
int Shipper::getSoDonDaGiao() const { return soDonDaGiao; }
void Shipper::tangSoDonDaGiao() { soDonDaGiao++; }
void Shipper::hienThi() const { cout << "Shipper: " << hoTen << " | Da giao: " << soDonDaGiao << " don\n"; }


// --- HỆ THỐNG QUẢN LÝ ---
QuanLyViettelPost::QuanLyViettelPost() {}
QuanLyViettelPost::~QuanLyViettelPost() {
    for (auto sp : danhSachShipper) delete sp;
    for (auto bc : heThongBuuCuc) delete bc;
}

void QuanLyViettelPost::themBuuCuc(BuuCuc* bc) { heThongBuuCuc.push_back(bc); }
void QuanLyViettelPost::themShipper(Shipper* sp) { danhSachShipper.push_back(sp); }

bool QuanLyViettelPost::taoDonHangMoi(unique_ptr<DonHang> dh) {
    if (!dh) return false;
    string ma = dh->getMaVanDon();
    if (tongDanhSachDonHang.try_emplace(ma, move(dh)).second) {
        return true;
    }
    return false;
}

void QuanLyViettelPost::traCuuDonHang(const string& maVanDon) const {
    auto it = tongDanhSachDonHang.find(maVanDon);
    if (it != tongDanhSachDonHang.end()) {
        it->second->xuatThongTin();
        cout << "-> Tong thanh toan: " << it->second->tinhTongTien() << " VND\n";
    } else {
        cout << "[Loi] Khong tim thay ma don: " << maVanDon << "\n";
    }
}

// Chuyển đơn hàng vào Queue của bưu cục
void QuanLyViettelPost::phanBoDonHangVeBuuCuc() {
    if (heThongBuuCuc.empty()) return;
    int dem = 0;
    for (const auto& pair : tongDanhSachDonHang) {
        DonHang* dh = pair.second.get();
        if (dh->getTrangThai() == "Cho xu ly") {
            // Logic đơn giản: Phân bổ luân phiên hoặc bưu cục ít đơn nhất
            BuuCuc* chon = heThongBuuCuc[0];
            for (BuuCuc* bc : heThongBuuCuc) {
                if (bc->soDonDangCho() < chon->soDonDangCho()) chon = bc;
            }
            chon->nhanDonHangVaoHangDoi(dh);
            dh->capNhatTrangThai("Dang xu ly");
            dem++;
        }
    }
    cout << "Da day " << dem << " don hang vao Hang Doi (Queue) cua cac Buu cuc.\n";
}

// Bưu cục lấy Queue ra xử lý
void QuanLyViettelPost::buuCucXuLyDonHang() {
    for (BuuCuc* bc : heThongBuuCuc) {
        bc->xuLyDonHangTrongHangDoi();
    }
}

void QuanLyViettelPost::thongKeDoanhThu() const {
    int64_t tongDoanhThu = 0;
    int soDon = 0;
    for (const auto& pair : tongDanhSachDonHang) {
        if (pair.second->getTrangThai() == "Da giao") {
            tongDoanhThu += pair.second->tinhPhiVanChuyen();
            soDon++;
        }
    }
    cout << "Tong so don da giao: " << soDon << "\n";
    cout << "Doanh thu tu Phi Van Chuyen: " << tongDoanhThu << " VND\n";
}

void QuanLyViettelPost::timShipperXuatSac() const {
    if (danhSachShipper.empty()) return;
    Shipper* best = danhSachShipper[0];
    for (auto sp : danhSachShipper) {
        if (sp->getSoDonDaGiao() > best->getSoDonDaGiao()) best = sp;
    }
    cout << "*** SHIPPER XUAT SAC NHAT ***\n";
    best->hienThi();
}

// --- FILE I/O ĐA HÌNH ---
// Format: LoaiDon(1/2),MaDon,TenKhach,TienHang,TrangThai,DiaChi,PhiGiao
void QuanLyViettelPost::ghiDuLieuXuongFile(const string& tenFile) const {
    ofstream fileOut(tenFile, ios::trunc);
    if (!fileOut.is_open()) return;

    for (const auto& pair : tongDanhSachDonHang) {
        DonHang* dh = pair.second.get();
        fileOut << dh->getLoaiDon() << ","
                << dh->getMaVanDon() << ","
                << dh->getTenKhach() << ","
                << dh->getTienHang() << ","
                << dh->getTrangThai() << ","
                << dh->getDiaChiNhan() << ","
                << dh->tinhPhiVanChuyen() << "\n";
    }
    fileOut.close();
    cout << "Luu du lieu thanh cong vao file " << tenFile << "\n";
}

void QuanLyViettelPost::docDuLieuTuFile(const string& tenFile) {
    ifstream fileIn(tenFile);
    if (!fileIn.is_open()) {
        cout << "[Canh bao] Khong tim thay file " << tenFile << ". Se tao moi khi luu.\n";
        return;
    }

    string line;
    int count = 0;
    while (getline(fileIn, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string loai, ma, ten, tienStr, tt, diaChi, phiStr;
        
        getline(ss, loai, ',');
        getline(ss, ma, ',');
        getline(ss, ten, ',');
        getline(ss, tienStr, ',');
        getline(ss, tt, ',');
        getline(ss, diaChi, ',');
        getline(ss, phiStr, ',');

        if(ma.empty()) continue;

        unique_ptr<DonHang> dh;
        if (loai == "1") {
            dh = make_unique<DonGiaoNha>(ma, ten, stoll(tienStr), diaChi, stoll(phiStr));
        } else {
            dh = make_unique<DonNhanTaiBuuCuc>(ma, ten, stoll(tienStr));
        }
        dh->capNhatTrangThai(tt);
        
        if(taoDonHangMoi(move(dh))) count++;
    }
    fileIn.close();
    cout << "Da tai " << count << " don hang tu he thong.\n";
}