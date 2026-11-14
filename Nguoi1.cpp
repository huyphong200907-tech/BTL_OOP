Nguoi::Nguoi() {
    hoTen = "";
    soDienThoai = "";
    diaChi = "";
}

Nguoi::Nguoi(string hoTen, string soDienThoai, string diaChi) {
    this->hoTen = hoTen;
    this->soDienThoai = soDienThoai;
    this->diaChi = diaChi;
}

Nguoi::~Nguoi() {
}

string Nguoi::getHoTen() const {
    return hoTen;
}

string Nguoi::getSoDienThoai() const {
    return soDienThoai;
}

string Nguoi::getDiaChi() const {
    return diaChi;
}

void Nguoi::setHoTen(string hoTen) {
    this->hoTen = hoTen;
}

void Nguoi::setSoDienThoai(string soDienThoai) {
    this->soDienThoai = soDienThoai;
}

void Nguoi::setDiaChi(string diaChi) {
    this->diaChi = diaChi;
}
