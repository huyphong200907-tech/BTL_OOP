Shipper::Shipper() : Nguoi() {
    maShipper = "";
    bienSoXe = "";
}

Shipper::Shipper(string maShipper, string hoTen,
                 string soDienThoai, string diaChi,
                 string bienSoXe)
    : Nguoi(hoTen, soDienThoai, diaChi) {
    this->maShipper = maShipper;
    this->bienSoXe = bienSoXe;
}

string Shipper::getMaShipper() const {
    return maShipper;
}

string Shipper::getBienSoXe() const {
    return bienSoXe;
}

void Shipper::setMaShipper(string maShipper) {
    this->maShipper = maShipper;
}

void Shipper::setBienSoXe(string bienSoXe) {
    this->bienSoXe = bienSoXe;
}

void Shipper::hienThi() const {
    cout << "\nMa shipper: " << maShipper;
    cout << "\nHo ten: " << getHoTen();
    cout << "\nSo dien thoai: " << getSoDienThoai();
    cout << "\nDia chi: " << getDiaChi();
    cout << "\nBien so xe: " << bienSoXe;
    cout << "\n-----------------------------";
}
