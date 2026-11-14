class Nguoi {
private:
    string hoTen;
    string soDienThoai;
    string diaChi;

public:
    Nguoi();
    Nguoi(string hoTen, string soDienThoai, string diaChi);
    virtual ~Nguoi();

    string getHoTen() const;
    string getSoDienThoai() const;
    string getDiaChi() const;

    void setHoTen(string hoTen);
    void setSoDienThoai(string soDienThoai);
    void setDiaChi(string diaChi);
};

class KhachHang : public Nguoi {
private:
    string maKhachHang;

public:
    KhachHang();
    KhachHang(string maKhachHang, string hoTen,
              string soDienThoai, string diaChi);

    string getMaKhachHang() const;
    void setMaKhachHang(string maKhachHang);

    void hienThi() const;
};

class Shipper : public Nguoi {
private:
    string maShipper;
    string bienSoXe;

public:
    Shipper();
    Shipper(string maShipper, string hoTen,
            string soDienThoai, string diaChi,
            string bienSoXe);

    string getMaShipper() const;
    string getBienSoXe() const;

    void setMaShipper(string maShipper);
    void setBienSoXe(string bienSoXe);

    void hienThi() const;
};
