KhachHang::KhachHang() : Nguoi() {
    maKhachHang = "";
}

KhachHang::KhachHang(string maKhachHang, string hoTen,
                     string soDienThoai, string diaChi)
    : Nguoi(hoTen, soDienThoai, diaChi) {
    this->maKhachHang = maKhachHang;
}

string KhachHang::getMaKhachHang() const {
    return maKhachHang;
}

void KhachHang::setMaKhachHang(string maKhachHang) {
    this->maKhachHang = maKhachHang;
}

void KhachHang::hienThi() const {
    cout << "\nMa khach hang: " << maKhachHang;
    cout << "\nHo ten: " << getHoTen();
    cout << "\nSo dien thoai: " << getSoDienThoai();
    cout << "\nDia chi: " << getDiaChi();
    cout << "\n-----------------------------";
}
