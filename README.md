# ESP32-S3 MPU6050 + SX1278 LoRa TX

> Dự án phát triển hệ thống thu thập dữ liệu cảm biến và truyền qua LoRa theo chế độ Tx.

## 🎯 Mục tiêu
- Đọc dữ liệu gia tốc và gyroscope từ MPU6050
- Tính toán góc Roll và Pitch bằng bộ lọc Kalman
- Gửi gói dữ liệu hoàn chỉnh qua module SX1278 mỗi lần đọc dữ liệu

## 🧩 Thông tin phần cứng
- Board: ESP32-S3 DevKitM-1
- Cảm biến: MPU6050
- Module truyền: SX1278 LoRa

## 📁 Cấu trúc thư mục
- [src](src): mã chương trình chính
- [include](include): header dùng chung và cấu hình chân
- [lib/MPU](lib/MPU): thư viện điều khiển MPU6050
- [lib/LoRaa](lib/LoRaa): thư viện điều khiển SX1278 và đóng gói dữ liệu gửi

## ⚙️ Cài đặt và build
1. Cài đặt PlatformIO
2. Mở thư mục dự án trong VS Code
3. Build firmware:
   - `platformio run`
4. Nạp firmware lên board:
   - `platformio run --target upload`

## 🔌 Cấu hình chân kết nối
Các chân GPIO được định nghĩa trong [include/PinConfig.h](include/PinConfig.h). Hãy thay đổi thành chân thật của bạn trước khi chạy trên hardware.

## 🔄 Luồng hoạt động
1. ESP32-S3 khởi tạo giao tiếp I2C với MPU6050
2. Thực hiện calibration ban đầu
3. Đọc dữ liệu và xử lý bằng Kalman
4. Tạo payload LoRa và gửi qua SX1278

## ⚠️ Lưu ý
- Kiểm tra lại chân SDA/SCL cho MPU6050
- Kiểm tra lại chân SPI/CS/RST/DIO cho SX1278
- Dữ liệu LoRa có thể được nhận bởi một board Rx khác để phân tích
