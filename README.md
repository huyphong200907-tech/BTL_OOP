# 📘 Hướng Dẫn Sử Dụng `QuanLyViettelPost.h` Cho Toàn Nhóm

Chào các anh em! Dự án của chúng ta áp dụng mô hình quản lý tập trung thông qua class `QuanLyViettelPost`. File này chính là "bộ não" của toàn hệ thống, nơi lưu trữ mọi dữ liệu (Vector) và điều phối các chức năng. 

Để dự án chạy mượt mà và không bị *conflict* (xung đột code) khi ghép, mọi người vui lòng đọc kỹ hướng dẫn dưới đây trước khi code phần của mình.

---

## ⚠️ NGUYÊN TẮC SỐNG CÒN (BẮT BUỘC ĐỌC)

1. **KHÔNG TỰ Ý SỬA FILE `.h`:** Tuyệt đối không ai được phép sửa đổi file `QuanLyViettelPost.h` (như thêm/xóa biến, đổi tên hàm). Nếu cần thêm chức năng, phải nhắn vào group chốt với Trưởng nhóm trước.
2. **CHỈ CODE PHẦN CỦA MÌNH:** Trong file `QuanLyViettelPost.cpp`, mỗi người chỉ tìm đến đúng cái hàm mình được phân công để viết logic bên trong `{ ... }`. Tuyệt đối không chạm vào thân hàm của người khác.
3. **TEST ĐỘC LẬP:** Đừng đợi người khác làm xong mới test. Hãy tự tạo file `main.cpp` riêng trên máy bạn, *hardcode* dữ liệu giả và chạy thử hàm của mình.

---

## 👨‍💻 HƯỚNG DẪN CODE CHO TỪNG THÀNH VIÊN

Tất cả các bạn đều sẽ code chung vào file `QuanLyViettelPost.cpp`. Dưới đây là phân việc cụ thể:

### 👤 Người 1 & Người 3: Module Đơn Hàng & Bưu Cục
*   **Việc của bạn:** Viết logic cho các hàm `taoDonHangMoi`, `traCuuDonHang`, `capNhatTrangThaiDon`, `phanBoDonHangVeBuuCuc`.
*   **Lưu ý:** Khi dùng vòng lặp tìm kiếm đơn hàng, hãy dùng thuộc tính `maVanDon`. Đừng quên ép kiểu (Casting) hoặc dùng tính Đa hình (Polymorphism) khi gọi hàm `tinhPhiVanChuyen()` vì danh sách lưu dưới dạng con trỏ `DonHang*`.

### 👤 Người 2: Module Nhân Sự & Khách Hàng
*   **Việc của bạn:** Viết logic cho `themKhachHang`, `themShipper`, `timKhachHangTheoSDT`, `timShipperTheoMa`.
*   **Lưu ý:** Trước khi dùng phương thức `push_back` để thêm vào Vector, hãy nhớ viết đoạn logic kiểm tra trùng lặp (Ví dụ: Số điện thoại này đã có khách hàng nào dùng chưa? Mã shipper này đã tồn tại chưa?).

### 👤 Người 4: Module Đọc/Ghi File
*   **Việc của bạn:** Viết logic cho `docDuLieuTuFile` và `ghiDuLieuXuongFile`.
*   **Lưu ý:** Bạn có toàn quyền truy cập vào các `vector` (như `danhSachKhachHang`, `tongDanhSachDonHang`) bên trong class này. Hãy duyệt qua từng vector, lấy các thuộc tính ra và dùng thư viện `<fstream>` để ghi nối tiếp xuống file `.txt` hoặc `.csv`. Khi đọc file, hãy khởi tạo đối tượng bằng từ khóa `new` và `push_back` vào vector tương ứng.

### 👤 Người 5: Giao Diện Console & Thống Kê
*   **Việc của bạn:**
    1. Viết logic thống kê: `tinhTongDoanhThu`, `thongKeDonHangTheoTrangThai`, `timShipperGiaoNhieuDonNhat`.
    2. Viết hàm `main()` tổng của dự án (Chứa Menu Switch-Case).
*   **Lưu ý Menu:** Bạn chỉ cần khởi tạo ĐÚNG MỘT đối tượng `QuanLyViettelPost app;` trong hàm `main()`. Sau đó dùng đối tượng `app` này để gọi các hàm tương ứng do các bạn khác đã viết.

---

## 🧪 VÍ DỤ: CÁCH TEST ĐỘC LẬP DÀNH CHO CÁ NHÂN

Giả sử bạn là **Người 5** và bạn vừa code xong hàm `tinhTongDoanhThu()`. Bạn không cần đợi Người 1 viết xong Menu tạo đơn hàng. Hãy tự test như sau trên máy của bạn:

```cpp
// main_test_nguoi5.cpp
#include <iostream>
#include "QuanLyViettelPost.h"
#include "DonGiaoNhanh.h"
#include "DonHoaToc.h"

using namespace std;

int main() {
    QuanLyViettelPost appTest;

    // 1. Hardcode tạo dữ liệu giả (Mock Data)
    DonHang* dh1 = new DonGiaoNhanh("DH01", KhachHang(), KhachHang(), 2.5, 10, 5000); 
    DonHang* dh2 = new DonHoaToc("DH02", KhachHang(), KhachHang(), 1.0, 5, 2.0);

    // 2. Ép dữ liệu vào hệ thống
    appTest.taoDonHangMoi(dh1);
    appTest.taoDonHangMoi(dh2);

    // 3. Gọi hàm của bạn để xem chạy đúng không
    double doanhThu = appTest.tinhTongDoanhThu();
    cout << "Test Doanh Thu (Mong doi ra khoang X VND): " << doanhThu << endl;

    return 0;
}
```
*Chỉ cần output ra đúng số tiền bạn nhẩm tính là bạn đã hoàn thành 100% nhiệm vụ của mình!*

---

## 🔄 QUY TRÌNH GHÉP CODE VÀO NGÀY CUỐI

1. Người 5 gửi file `main.cpp` (chứa giao diện Menu) lên nhóm.
2. Trưởng nhóm gom tất cả các đoạn logic mọi người đã viết trong file `QuanLyViettelPost.cpp` (và các file Class con) ráp lại thành một bản duy nhất.
3. Vì mọi người đều tuân thủ nguyên tắc "Gọi qua hàm đã khai báo trong file `.h`", khi biên dịch sẽ KHÔNG BÁO LỖI cú pháp.
4. Cả nhóm cùng ngồi chạy kịch bản thật từ Console để bắt lỗi *logic* (nếu có).
