# 🏢 Supplier Management System (BST in C++)

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg?style=flat-square&logo=c%2B%2B)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg?style=flat-square&logo=windows)](https://microsoft.com/windows)
[![Topic](https://img.shields.io/badge/Data%20Structure-Binary%20Search%20Tree-orange.svg?style=flat-square)](https://en.wikipedia.org/wiki/Binary_search_tree)

Hệ thống Quản lý Nhà cung cấp viết bằng ngôn ngữ **C++** sử dụng cấu trúc dữ liệu **Cây nhị phân tìm kiếm (Binary Search Tree - BST)**. Dự án được phát triển dưới dạng ứng dụng Console trực quan với giao diện màu sắc phân cấp và các thuật toán CRUD/Thống kê được chuẩn hóa.

---

## 🌟 Tính năng nổi bật

- **⚡ Cấu trúc BST cốt lõi**: Định vị, chèn mới và xóa các node đạt hiệu năng trung bình $O(\log n)$.
- **📂 Đọc/Ghi File tự động**: Đồng bộ dữ liệu runtime từ cây BST xuống cơ sở dữ liệu giả lập `database.txt` dạng dòng phẳng (flat-file) phân tách bằng ký tự `|`.
- **🎨 Giao diện Console UI/UX**: Tích hợp đổi màu hiển thị tự động (`windows.h`), hiệu ứng thanh tải (`loading bar`) và menu dạng danh sách có tổ chức.
- **🛡️ Cơ chế chống xung đột**: Tự động phát hiện trùng khóa chính (Mã nhà cung cấp) và xử lý bằng cách thêm hậu tố số đếm (Ví dụ: `NCC01#2`, `NCC01#3`).
- **🔍 Lọc & Tìm kiếm đa điều kiện**: Hỗ trợ tìm kiếm không tuần tự chứa từ khóa (so khớp chuỗi không phân biệt hoa thường) theo tên, số điện thoại, và địa chỉ.
- **📊 Thống kê & Phân tích cây đệ quy**:
  - Tính tổng số vốn đầu tư.
  - Đếm tổng số node và số lượng node lá (Leaf nodes).
  - Tìm nhà cung cấp có vốn lớn nhất/nhỏ nhất.
  - Tính toán chiều cao hình học của cây (Tree Height).

---

## 🏗️ Cấu trúc dữ liệu (Data Structure)

### 1. Thực thể Nhà cung cấp (`NhaCungCap`)
```cpp
struct NhaCungCap {
    string maNCC;   // Khóa chính (Key) để phân nhánh BST
    string ten;     // Tên nhà cung cấp
    string diaChi;  // Địa chỉ doanh nghiệp
    string sdt;     // Số điện thoại liên lạc
    string email;   // Địa chỉ email thư điện tử
    double tienVon; // Số vốn đầu tư (VND)
};
```

### 2. Cấu trúc Node Cây BST (`Node`)
```cpp
struct Node {
    NhaCungCap data;
    Node* left;     // Con trỏ tới cây con bên trái (Mã NCC nhỏ hơn)
    Node* right;    // Con trỏ tới cây con bên phải (Mã NCC lớn hơn)
};
typedef Node* Tree;
```

---

## 🖥️ Hướng dẫn cài đặt & Thực thi

### Yêu cầu hệ thống
- **Hệ điều hành**: Microsoft Windows (sử dụng thư viện hệ thống `<windows.h>`).
- **Trình biên dịch**: GCC/G++ hỗ trợ chuẩn **C++11** trở lên.

### Các bước chạy dự án
1. Bản sao mã nguồn về máy hoặc truy cập thư mục chứa file:
   ```bash
   cd "C:\Users\Admin\Desktop\Kì 3\CTDL&GT\btl"
   ```
2. Biên dịch mã nguồn `quanlyncc.cpp`:
   ```bash
   g++ -std=c++11 quanlyncc.cpp -o quanlyncc.exe
   ```
3. Khởi chạy chương trình:
   ```bash
   ./quanlyncc.exe
   ```

---

## 📖 Sơ đồ Phân chia Phân hệ Mã nguồn

Hệ thống được thiết kế theo dạng Module hóa (Clean Code) gồm **9 phần chính** rõ rệt:

| Phân hệ | File & Vị trí | Chức năng |
| :--- | :--- | :--- |
| **Phần 1** | Dòng `1 - 22` | Thư viện & Định nghĩa cấu trúc dữ liệu (`NhaCungCap`, `Node`, `Tree`) |
| **Phần 2** | Dòng `23 - 68` | Các hàm bổ trợ, chuẩn hóa chuỗi và định dạng tiền tệ |
| **Phần 3** | Dòng `69 - 104` & `286 - 311` | Các hiệu ứng loading, giao diện màn hình và hiển thị Menu |
| **Phần 4** | Dòng `105 - 125` & `204 - 236` | Các thao tác BST cơ bản (Khởi tạo, chèn Node, xóa Node, tìm thế mạng) |
| **Phần 5** | Dòng `126 - 149` | Tiêu đề bảng biểu và duyệt cây theo thứ tự tăng dần (`LNR`) |
| **Phần 6** | Dòng `181 - 203` | Lọc và tìm kiếm nhà cung cấp theo các thuộc tính vệ tinh |
| **Phần 7** | Dòng `150 - 180` | Hàm đệ quy tính toán chiều cao, đếm lá, cực trị vốn đầu tư |
| **Phần 8** | Dòng `237 - 285` | Cơ chế lưu trữ bền vững đọc/ghi file `database.txt` |
| **Phần 9** | Dòng `312 - 580` | Hàm điều khiển chính `main()` chứa luồng xử lý và vòng lặp tương tác |

---

## 🗃️ Cơ sở dữ liệu mẫu (`database.txt`)
Dữ liệu được tổ chức dưới dạng văn bản thuần túy phẳng, phân tách bằng dấu gạch đứng `|`:
```text
NCC01|CONG TY TNHH PHAT TRIEN CONG NGHE AN PHAT|HA NOI|0987654321|anphat@gmail.com|1500000000
NCC02|TAP DOAN DA QUOC GIA HOA PHAT|HUNG YEN|0912345678|hoaphat@hoaphat.com.vn|8500000000
NCC03|NHA PHAN PHOI THUC PHAM SACH VIET NAM|TP HO CHI MINH|0909998888|vietnamfoods@gmail.com|750000000
```

---

## 👥 Thành viên thực hiện BTL
- **Lê Văn Đạt**
- **Phạm Ngọc Bảo**
- **Giảng viên hướng dẫn**: ThS. Trần Thu Trang (Khoa CNTT - Trường Đại học Đại Nam)
