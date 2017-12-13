    //Thêm thư viện LiquitCrystal - nó có sẵn vì vậy bạn không cần cài thêm gì cả
    #include <LiquidCrystal.h>
     
    //Khởi tạo với các chân
LiquidCrystal lcd(D5, D0, D1, D2, D3, D4);
     
    void setup() {
      //Thông báo đây là LCD 1602
      lcd.begin(16, 2);
      //In ra màn hình lcd dòng chữ Toi yeu Arduino
      lcd.print("Toi yeu Arduino!");
    }
     
    void loop() {
      // đặt con trỏ vào cột 0, dòng 1
      // Lưu ý: dòng 1 là dòng thứ 2, lòng 0 là dòng thứ 1. Nôm na, nó đếm từ 0 từ không phải từ 1
      lcd.setCursor(0, 1);
      // In ra dong chu
      lcd.print("   Arduino.VN");
    }
