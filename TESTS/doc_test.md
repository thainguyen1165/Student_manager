# Tài liệu Kiểm thử Tự động (Automated Testing)

## 1. Mục tiêu và Chiến lược Kiểm thử
Tài liệu này trình bày quy trình kiểm thử đơn vị (Unit Test) cho dự án Quản lý Sinh viên. Mục tiêu là đảm bảo các module xử lý logic nghiệp vụ và dữ liệu cốt lõi hoạt động đúng trước khi tích hợp vào giao diện.

**Chiến lược:**
- **Unit Testing:** Kiểm thử độc lập từng hàm trong các module utils.c, grade.c và data.c.
- **Framework:** Do đây là dự án C độc lập, chúng tôi sử dụng một custom minimal framework (test_framework.h) dựa trên cơ chế Macro ASSERT để dễ dàng tích hợp mà không phụ thuộc thư viện bên ngoài.
- **Tự động hoá:** Quá trình biên dịch và chạy test được tự động hóa qua script run_tests.bat.

## 2. Phạm vi và Chi tiết Logic Kiểm thử

Phần này mô tả chi tiết logic kiểm thử (Test Logic) được áp dụng cho từng module cụ thể nhằm đảm bảo tính đúng đắn của dữ liệu và luồng thực thi.

### 2.1. Module Utils (test_utils.c)
Module tiện ích chứa các hàm xử lý chuỗi cơ bản. Logic kiểm thử tập trung vào việc xử lý các trường hợp đầu vào hợp lệ và không hợp lệ:
- **trim_spaces:**
  - *Logic kiểm thử:* Khởi tạo các chuỗi có chứa nhiều khoảng trắng ở đầu, cuối và giữa chuỗi (VD: "  Hello   World  ").
  - *Kỳ vọng:* Hàm phải loại bỏ chính xác các khoảng trắng ở đầu và cuối chuỗi, giữ nguyên khoảng trắng ở giữa (VD: "Hello   World"). Kiểm tra thêm với chuỗi không có khoảng trắng thừa (VD: "Normal") để đảm bảo hàm không làm thay đổi sai chuỗi.
- **string_equals_ignore_case:**
  - *Logic kiểm thử:* So sánh hai chuỗi giống nhau về mặt ký tự nhưng khác nhau về chữ hoa/chữ thường (VD: "aBcD" và "AbCd").
  - *Kỳ vọng:* Hàm trả về 1 (true). Kiểm tra trường hợp hai chuỗi hoàn toàn khác nhau (VD: "abc" và "abd") thì kỳ vọng trả về 0 (false).
- **string_contains_ignore_case:**
  - *Logic kiểm thử:* Truyền vào chuỗi gốc và một từ khóa cần tìm (VD: chuỗi gốc "Nguyen Van An", từ khóa "van").
  - *Kỳ vọng:* Hàm trả về kết quả true (!= 0). Ngược lại, truyền từ khóa không tồn tại (VD: "tran") thì trả về 0 (false).

### 2.2. Module Grade (test_grade.c)
Module này xử lý logic chuyển đổi điểm hệ 10 sang hệ 4, xếp loại điểm chữ và xếp loại học lực. Logic kiểm thử xoay quanh các giá trị biên (edge cases).
- **convert_10_to_4:**
  - *Logic kiểm thử:* Truyền vào các mốc điểm hệ 10 tiêu biểu như 8.5, 7.0, 3.0.
  - *Kỳ vọng:* Hàm ánh xạ chính xác sang thang hệ 4 tương ứng (4.0, 3.0, 0.0).
- **get_letter_grade:**
  - *Logic kiểm thử:* Cung cấp điểm hệ 10 và kiểm tra kết quả mảng ký tự chứa điểm chữ đầu ra.
  - *Kỳ vọng:* Điểm 8.5 ánh xạ thành "A", điểm 3.9 ánh xạ thành "F". Điều này đảm bảo logic phân loại theo các dải điểm [8.5 - 10], [0 - 3.9], v.v hoạt động ổn định.
- **classify_by_gpa4:**
  - *Logic kiểm thử:* Truyền vào một giá trị GPA hệ 4 cụ thể.
  - *Kỳ vọng:* Ánh xạ thành công trả về chuỗi mô tả xếp loại học lực (VD: GPA 3.8 phải trả về "Xuat sac").

### 2.3. Module Data (test_data.c)
Module dữ liệu quản lý các thao tác liên quan tới bộ nhớ trung tâm (StudentSystem).
- **find_student_index:**
  - *Logic kiểm thử:* Khởi tạo một struct StudentSystem giả lập. Thêm thủ công một sinh viên với mã "SV001" vào mảng students tại vị trí index 0. Thiết lập biến đếm student_count bằng 1.
  - *Kỳ vọng:*
    - Khi tìm kiếm mã "SV001", hàm trả về đúng index là 0.
    - Khi tìm kiếm một mã không tồn tại "SV002", hàm phải xử lý an toàn và trả về -1.

## 3. Cơ chế Hoạt động của Framework Kiểm thử

Để giữ cho dự án gọn nhẹ và không phụ thuộc vào thư viện bên ngoài (như CUnit, Unity), chúng tôi sử dụng một custom framework kiểm thử tự xây dựng dựa trên cơ chế Macro. Dưới đây là cách mã nguồn kiểm thử thực sự hoạt động:

### 3.1. Macro `ASSERT` (test_framework.h)
Trái tim của hệ thống kiểm thử là macro `ASSERT(message, test)`. Khi một test case được chạy:
- Nó tăng biến toàn cục `tests_run` lên 1.
- Nó đánh giá biểu thức điều kiện `test` (ví dụ: `strcmp(a, b) == 0`).
- **Nếu đúng (True):** Tăng biến `tests_passed` lên 1 và in ra [PASS] kèm thông điệp.
- **Nếu sai (False):** Nó sử dụng các macro tiền biên dịch của C là `__FILE__` và `__LINE__` để tự động in ra tên file và dòng code đang bị lỗi cùng với chữ [FAIL]. Điều này giúp lập trình viên xác định chính xác vị trí lỗi chỉ trong vài giây.

### 3.2. Entry Point và Điều phối (test_main.c)
File `test_main.c` chứa hàm `main()` của chương trình test (độc lập hoàn toàn với `main.c` của dự án thật).
- Hàm này đóng vai trò như một **Test Runner**.
- Nó lần lượt gọi các hàm kiểm thử tổng hợp từ các file khác bằng từ khóa `extern` (ví dụ: `extern void test_utils(void);`).
- Ở cuối chương trình, nó so sánh `tests_run` và `tests_passed` để in ra báo cáo tổng kết (Pass bao nhiêu, Fail bao nhiêu).
- Đặc biệt, nó trả về mã lỗi (`return 1;`) cho Hệ điều hành nếu có bất kỳ test nào fail. Điều này cực kỳ quan trọng để tích hợp với các hệ thống CI/CD sau này (script `run_tests.bat` có thể bắt được lỗi này).

### 3.3. Isolation (Tính Độc lập)
Khi biên dịch bằng `run_tests.bat`, file thực thi `test_runner.exe` được tạo ra bằng cách gộp các file `test_*.c` cùng với các module nguồn thật (như `utils.c`, `grade.c`). Tuy nhiên, file `main.c` thật của chương trình bị loại bỏ.
Nhờ vậy, môi trường kiểm thử hoàn toàn bị cô lập khỏi luồng chạy giao diện Console thông thường của người dùng, đảm bảo các hàm được test thuần túy về mặt logic.

## 4. Cấu trúc Thư mục Kiểm thử
```text
TESTS/
├── doc_test.md           # Tài liệu chi tiết về kiểm thử
├── run_tests.bat         # Script thực thi build và run test tự động
├── build/                # Nơi chứa file thực thi test (.exe)
└── src/                  # Mã nguồn của các kịch bản test
    ├── test_framework.h  # Lõi framework kiểm thử (Macro ASSERT)
    ├── test_main.c       # File entry point chạy toàn bộ test
    ├── test_utils.c      # Test cases cho thư viện utils
    ├── test_grade.c      # Test cases cho nghiệp vụ tính điểm
    └── test_data.c       # Test cases cho nghiệp vụ dữ liệu
```

## 5. Hướng dẫn Chạy Kiểm thử
- Môi trường: Đảm bảo gcc (MinGW) đã được thêm vào biến môi trường PATH.
- Thực thi: Mở Command Prompt / PowerShell, di chuyển vào thư mục TESTS và chạy run_tests.bat.
- Đầu ra: Chương trình sẽ in ra danh sách các bài test [PASS] hoặc [FAIL] và tổng kết trạng thái.
