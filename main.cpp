#include <iostream>
#include <limits>
#include "QuanLyViettelPost.h"

using namespace std;

// Hàm hỗ trợ dọn dẹp bộ nhớ đệm bàn phím
void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    QuanLyViettelPost heThong;
    
    // Khởi tạo Data mẫu cho hệ thống
    heThong.themBuuCuc(new BuuCuc("BC_HN", "Ha Noi"));
    heThong.themShipper(new Shipper("SP01", "Tran Van B", "0909123456"));
    
    // Tự động load file khi mở app
    heThong.docDuLieuTuFile("database.txt");

    int luaChon;
    do {
        cout << "\n=============================================\n";
        cout << "    HE THONG QUAN LY VIETTEL POST \n";
        cout << "=============================================\n";
        cout << "1. Tao don hang moi\n";
        cout << "2. Tra cuu don hang\n";
        cout << "3. Phan bo don vao Hang Doi \n";
        cout << "4. Buu cuc xu ly Hang Doi \n";
        cout << "5. Thong ke doanh thu & Shipper\n";
        cout << "6. Luu du lieu xuong File \n";
        cout << "0. Thoat chuong trinh\n";
        cout << "=============================================\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;

        if (cin.fail()) { clearBuffer(); luaChon = -1; }

        switch (luaChon) {
            case 1: {
                clearBuffer();
                string loai, ma, ten, dc;
                int64_t tien, phi = 0;

                cout << "Chon loai don (1: Giao tan nha, 2: Tai Buu cuc): ";
                getline(cin, loai);
                cout << "Nhap ma don: "; getline(cin, ma);
                cout << "Nhap ten khach: "; getline(cin, ten);
                cout << "Nhap tien hang (VND): "; cin >> tien;
                clearBuffer();

                try {
                    unique_ptr<DonHang> dh;
                    if (loai == "1") {
                        cout << "Nhap dia chi: "; getline(cin, dc);
                        cout << "Nhap phi giao (VND): "; cin >> phi;
                        dh = make_unique<DonGiaoNha>(ma, ten, tien, dc, phi);
                    } else {
                        dh = make_unique<DonNhanTaiBuuCuc>(ma, ten, tien);
                    }
                    if (heThong.taoDonHangMoi(move(dh))) {
                        cout << "-> Tao don thanh cong!\n";
                    } else {
                        cout << "-> Ma don da ton tai!\n";
                    }
                } catch (const exception& e) {
                    cout << "Loi: " << e.what() << "\n";
                }
                break;
            }
            case 2: {
                clearBuffer();
                string ma;
                cout << "Nhap ma don can tra cuu: ";
                getline(cin, ma);
                heThong.traCuuDonHang(ma);
                break;
            }
            case 3:
                heThong.phanBoDonHangVeBuuCuc();
                break;
            case 4:
                heThong.buuCucXuLyDonHang();
                break;
            case 5:
                cout << "\n--- THONG KE ---\n";
                heThong.thongKeDoanhThu();
                heThong.timShipperXuatSac();
                break;
            case 6:
                heThong.ghiDuLieuXuongFile("database.txt");
                break;
            case 0:
                cout << "Tu dong luu du lieu truoc khi thoat...\n";
                heThong.ghiDuLieuXuongFile("database.txt");
                cout << "Cam on da su dung he thong. Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai.\n";
                break;
        }
    } while (luaChon != 0);

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 0cb9dda85d357fdae662589c31e13a67b6631665
