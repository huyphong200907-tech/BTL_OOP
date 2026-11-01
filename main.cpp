#include <iostream>
#include "QuanLyViettelPost.h"
#include "DonGiaoNhanh.h"
// ... include các file khác

using namespace std;

int main() {
    // 1. Khởi tạo kho quản lý chung
    QuanLyViettelPost appManager;
    
    // 2. Load dữ liệu cũ (Người 4 viết logic trong QuanLyViettelPost.cpp)
    appManager.docDuLieuTuFile("data.txt");

    int luaChon;
    do {
        cout << "\n===== HE THONG VIETTEL POST =====";
        cout << "\n1. Tao don hang moi";
        cout << "\n2. Tra cuu don hang";
        cout << "\n3. Thong ke doanh thu";
        cout << "\n0. Thoat";
        cout << "\nNhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1: {
                // ... Xử lý nhập thông tin giao diện ...
                // Giả sử tạo xong đối tượng DonGiaoNhanh mới
                DonHang* donMoi = new DonGiaoNhanh(/* truyền tham số */);
                
                // Gọi hàm của Người 1 & 3 để xử lý logic
                appManager.taoDonHangMoi(donMoi); 
                break;
            }
            case 3:
                // Gọi hàm của Người 5
                cout << "Tong doanh thu: " << appManager.tinhTongDoanhThu();
                break;
            case 0:
                // Lưu dữ liệu trước khi thoát (Người 4)
                appManager.ghiDuLieuXuongFile("data.txt");
                break;
        }
    } while (luaChon != 0);

    return 0;
}
