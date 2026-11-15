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

## 🔄 QUY TRÌNH DEMO
Để chứng minh được toàn bộ sức mạnh của 5 Module (OOP, Queue, Map, File I/O, Thống kê), bạn hãy chạy chương trình và làm theo kịch bản nhập liệu từng bước dưới đây:
Bước 1: Tạo đơn hàng Giao Tận Nhà (Test tính Đa hình)
•	Tại Menu, nhập 1 (Tạo đơn hàng mới) -> Enter.
•	Chon loai don: Nhập 1
•	Nhap ma don: Nhập VD01
•	Nhap ten khach: Nhập Nguyen Van A
•	Nhap tien hang: Nhập 500000
•	Nhap dia chi: Nhập Cau Giay, Ha Noi
•	Nhap phi giao: Nhập 35000
Kết quả: Hệ thống báo "Tao don thanh cong!".

Bước 2: Tạo đơn Nhận Tại Bưu Cục (Test loại Class thứ 2)
•	Tại Menu, nhập 1 -> Enter.
•	Chon loai don: Nhập 2
•	Nhap ma don: Nhập VD02
•	Nhap ten khach: Nhập Tran Van B
•	Nhap tien hang: Nhập 150000
Kết quả: Đơn thứ 2 được tạo nhanh chóng, không bị hỏi địa chỉ và phí ship (do tính chất Kế thừa OOP).

Bước 3: Cố tình tạo đơn trùng mã (Test bẫy lỗi của Unordered Map)
•	Tại Menu, nhập 1 -> Enter.
•	Chon loai don: Nhập 2
•	Nhap ma don: Nhập VD01 (Cố tình nhập lại mã cũ)
•	Nhap ten khach: Nhập Hacker
•	Nhap tien hang: Nhập 999
Kết quả: Hệ thống chặn lại và báo "-> Ma don da ton tai!", dữ liệu rác không bị ghi vào hệ thống.

Bước 4: Tra cứu đơn hàng (Test cơ chế gọi hàm Ảo - Virtual)
•	Tại Menu, nhập 2 -> Enter.
•	Nhap ma don can tra cuu: Nhập VD01
Kết quả: In ra đúng [Giao Tan Nha] kèm địa chỉ và phí giao. Tổng tiền tính = Tiền hàng + Phí ship.
•	Tiếp tục nhập 2, tìm mã VD02.
Kết quả: In ra đúng [Tai Buu Cuc] (miễn phí ship). Tổng tiền chỉ = Tiền hàng.

Bước 5: Đưa đơn vào luồng xử lý (Test cấu trúc dữ liệu Queue)
•	Tại Menu, nhập 3 (Phân bổ đơn) -> Enter.
Kết quả: Hệ thống báo "Da day 2 don hang vao Hang Doi (Queue) cua cac Buu cuc."
•	Bạn có thể bấm số 2 tra cứu lại đơn VD01, sẽ thấy trạng thái chuyển thành "Dang xu ly".
Bước 6: Bưu cục giải phóng luồng (Test lấy ra khỏi Queue)
•	Tại Menu, nhập 4 -> Enter.
Kết quả: Bưu cục báo đã xử lý xong 2 đơn hàng. Trạng thái các đơn tự động thành "Da giao". (Nguyên lý Vào trước - Ra trước của Queue).

Bước 7: Xem Báo cáo BTL (Test Thống kê)
•	Tại Menu, nhập 5 -> Enter.
Kết quả:
•	Tổng số đơn đã giao: 2
•	Doanh thu phí vận chuyển: 35000 VND (Vì đơn VD02 khách tự ra lấy nên phí ship = 0, hàm tự biết tính toán thông minh).
•	In ra thông tin Shipper xuất sắc nhất.

Bước 8: Thoát & Khôi phục dữ liệu (Test File I/O)
•	Tại Menu, nhập 0 -> Enter.
Kết quả: Màn hình báo "Luu du lieu thanh cong vao file database.txt". File text sẽ tự động sinh ra trong thư mục code của bạn.
•	Cú chót để lấy điểm A+: Bạn hãy chạy lại (Run) chương trình lần 2. Vừa mở app lên, hệ thống sẽ báo "Da tai 2 don hang tu he thong". Bạn bấm phím 2 tra cứu lại mã VD01 sẽ thấy dữ liệu cũ hôm qua vẫn còn y nguyên, chứng minh module Đọc/Ghi file hoạt động 100%.


