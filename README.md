# Student_manager

## Directory Structure

```text
BTL/
├── README.md               # Tài liệu của dự án
├── run.bat                 # Script để chạy chương trình chính
├── .git/                   # Thư mục quản lý phiên bản Git
├── BUILD/                  # Chứa các file kết quả sau khi build
│   ├── input.txt           # File dữ liệu đầu vào mẫu
│   ├── output.txt          # File kết quả đầu ra
│   └── StudentManager.exe  # File thực thi chính của chương trình
├── SRC/                    # Mã nguồn chính của chương trình
│   ├── common.h            # Định nghĩa các macro và cấu trúc chung
│   ├── data.c              # Cài đặt cấu trúc dữ liệu (vd: Student)
│   ├── data.h              # Khai báo cấu trúc dữ liệu
│   ├── display.c           # Hàm xử lý in/hiển thị thông tin ra màn hình
│   ├── display.h           # Khai báo các hàm hiển thị
│   ├── file_io.c           # Xử lý đọc/ghi file
│   ├── file_io.h           # Khai báo các hàm đọc/ghi file
│   ├── grade.c             # Logic xử lý điểm số và xếp loại
│   ├── grade.h             # Khai báo hàm xử lý điểm
│   ├── main.c              # Điểm bắt đầu (entry point) của chương trình
│   ├── menu.c              # Logic hiển thị và xử lý menu giao diện
│   ├── menu.h              # Khai báo các hàm menu
│   ├── operations.c        # Các thao tác chính (thêm, sửa, xóa, tìm kiếm...)
│   ├── operations.h        # Khai báo các hàm thao tác chính
│   ├── utils.c             # Các hàm tiện ích hỗ trợ (xử lý chuỗi, v.v.)
│   └── utils.h             # Khai báo các hàm tiện ích
└── TESTS/                  # Thư mục chứa các bài kiểm thử (Unit tests)
    ├── run_tests.bat       # Script để chạy tự động các bài kiểm thử
    ├── build/              # Chứa file thực thi của phần kiểm thử
    │   └── test_runner.exe # File thực thi để chạy test
    └── src/                # Mã nguồn của các bài kiểm thử
        ├── test_data.c     # Test cho cấu trúc dữ liệu
        ├── test_framework.h# Framework/Macro đơn giản hỗ trợ viết test
        ├── test_grade.c    # Test cho logic xử lý điểm
        ├── test_main.c     # Điểm bắt đầu của chương trình chạy test
        └── test_utils.c    # Test cho các hàm tiện ích
```
