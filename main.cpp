#include <iostream>
#include "QuanLyViettelPost.h"

using namespace std;

int main() {
    cout << "===========================================\n";
    cout << " HE THONG QUAN LY VIETTEL POST\n";
    cout << "===========================================\n\n";

    // 1. Khởi tạo hệ thống
    QuanLyViettelPost heThong;

    // 2. Thêm Bưu cục vào hệ thống
    BuuCuc* bcHN = new BuuCuc("BC_HN01", "Ha Noi");
    BuuCuc* bcHCM = new BuuCuc("BC_HCM01", "Ho Chi Minh");
    heThong.themBuuCuc(bcHN);
    heThong.themBuuCuc(bcHCM);

    // 3. Thêm Nhân sự (Khách hàng & Shipper)
    KhachHang* kh1 = new KhachHang("KH001", "Nguyen Van A", "0901234567", "Cau Giay, Ha Noi");
    Shipper* sp1 = new Shipper("SP001", "Tran Van B", "0987654321", "Ha Noi", "29A1-12345");
    
    // Giả lập shipper này đã giao thành công 50 đơn trước đó
    for(int i=0; i<50; i++) sp1->tangSoDonDaGiao(); 

    heThong.themKhachHang(kh1);
    heThong.themShipper(sp1);

    // 4. Tạo Đơn hàng mới
    cout << "\n--- TAO DON HANG MOI ---\n";
    DonHang* dh1 = new DonHang("VD1001", "Tay Ho, Ha Noi", 35000);
    DonHang* dh2 = new DonHang("VD1002", "Quan 1, Ho Chi Minh", 45000);
    
    heThong.taoDonHangMoi(dh1);
    heThong.taoDonHangMoi(dh2);

    // 5. Phân bổ Bưu cục
    cout << "\n--- PHAN BO DON HANG ---\n";
    heThong.phanBoDonHangVeBuuCuc();

    // 6. Cập nhật trạng thái
    cout << "\n--- CAP NHAT TRANG THAI ---\n";
    heThong.capNhatTrangThaiDon("VD1001", "Da giao"); // Đơn 1 giao thành công
    sp1->tangSoDonDaGiao(); // Shipper SP001 hoàn thành thêm 1 đơn

    // 7. Thống kê báo cáo (P5)
    cout << "\n--- THONG KE BAO CAO ---\n";
    heThong.thongKeDonHangTheoTrangThai("Da giao");
    cout << "=> TONG DOANH THU: " << heThong.tinhTongDoanhThu() << " VND\n";
    
    heThong.timShipperGiaoNhieuDonNhat();

    // 8. Đọc/Ghi File (P4)
    cout << "\n--- LUU TRU DU LIEU (FILE I/O) ---\n";
    heThong.ghiDuLieuXuongFile("database_viettelpost.txt");
    
    // Test thử đọc lại file (Giả lập khởi động lại phần mềm)
    // heThong.docDuLieuTuFile("database_viettelpost.txt");

    cout << "\n===========================================\n";
    cout << "      CAM ON QUY KHACH HANG\n";
    cout << "===========================================\n";

    return 0;
}
