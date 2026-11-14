#include "QuanLyViettelPost.h"

// --- CÀI ĐẶT CLASS ĐƠN HÀNG ---
DonHang::DonHang(string maDon, string tenKhach, Tien tienHang)
    : maDon_(move(maDon)), tenKhach_(move(tenKhach)), tienHang_(tienHang), trangThai_("Cho xu ly") {
    if (maDon_.empty() || tenKhach_.empty() || tienHang_ < 0) {
        throw invalid_argument("Thong tin don hang khong hop le.");
    }
}

const string& DonHang::getMaVanDon() const { return maDon_; }
string DonHang::getTrangThai() const { return trangThai_; }
void DonHang::capNhatTrangThai(string tt) { trangThai_ = tt; }
DonHang::Tien DonHang::getTienHang() const { return tienHang_; }

void DonHang::xuatThongTinChung() const {
    cout << "- Ma don: " << maDon_ << " | Khach: " << tenKhach_ 
         << " | Tien hang: " << tienHang_ << " VND | TT: " << trangThai_ << "\n";
}

// Lớp Đơn Giao Nhà
DonGiaoNha::DonGiaoNha(string maDon, string tenKhach, Tien tienHang, string diaChi, Tien phiGiaoHang)
    : DonHang(move(maDon), move(tenKhach), tienHang), diaChi_(move(diaChi)), phiGiaoHang_(phiGiaoHang) {
    if (diaChi_.empty() || phiGiaoHang_ < 0) throw invalid_argument("Dia chi hoac phi giao hang loi.");
}
DonHang::Tien DonGiaoNha::tinhTongTien() const { return getTienHang() + phiGiaoHang_; }
void DonGiaoNha::xuatThongTin() const {
    cout << "[Loai: Giao Tan Nha] "; xuatThongTinChung();
    cout << "  -> Dia chi: " << diaChi_ << " | Phi ship: " << phiGiaoHang_ << " VND\n";
}
string DonGiaoNha::getDiaChiNhan() const { return diaChi_; }
DonHang::Tien DonGiaoNha::tinhPhiVanChuyen() const { return phiGiaoHang_; }

// Lớp Đơn Nhận Tại Bưu Cục
DonHang::Tien DonNhanTaiBuuCuc::tinhTongTien() const { return getTienHang(); }
void DonNhanTaiBuuCuc::xuatThongTin() const {
    cout << "[Loai: Nhan Tai Buu Cuc] "; xuatThongTinChung();
    cout << "  -> Khach hang tu ra buu cuc lay (Mien phi van chuyen).\n";
}
string DonNhanTaiBuuCuc::getDiaChiNhan() const { return "Tai Buu Cuc"; }
DonHang::Tien DonNhanTaiBuuCuc::tinhPhiVanChuyen() const { return 0; }



// Thay vì push_back, dùng try_emplace của unordered_map để chặn trùng mã O(1)
bool QuanLyViettelPost::taoDonHangMoi(unique_ptr<DonHang> dh) {
    if (!dh) return false;
    string ma = dh->getMaVanDon();
    auto result = tongDanhSachDonHang.try_emplace(ma, move(dh));
    if (result.second) {
        cout << "=> Da tao don hang: " << ma << "\n";
        return true;
    }
    cout << "[Loi] Ma don hang " << ma << " da ton tai!\n";
    return false;
}

// Tìm kiếm O(1) bằng khóa Hash
DonHang* QuanLyViettelPost::traCuuDonHang(const string& maVanDon) const {
    auto it = tongDanhSachDonHang.find(maVanDon);
    return it == tongDanhSachDonHang.end() ? nullptr : it->second.get();
}

// Thống kê: Duyệt qua Map thay vì Vector
int64_t QuanLyViettelPost::tinhTongDoanhThu() const {
    int64_t tong = 0;
    // Cặp key-value trong unordered_map: pair.second là unique_ptr<DonHang>
    for (const auto& pair : tongDanhSachDonHang) {
        if (pair.second->getTrangThai() == "Da giao") {
            tong += pair.second->tinhPhiVanChuyen();
        }
    }
    return tong;
}

void QuanLyViettelPost::thongKeDonHangTheoTrangThai(string trangThai) const {
    cout << "\n--- THONG KE DON: " << trangThai << " ---\n";
    for (const auto& pair : tongDanhSachDonHang) {
        if (pair.second->getTrangThai() == trangThai) {
            pair.second->xuatThongTin();
        }
    }
}