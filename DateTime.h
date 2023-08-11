#include <M5StickCPlus.h>
#include <WiFi.h>

class DateTime {
  public:
    const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    
    void showDateTime();
    String getTime();
};

// 現在時刻の表示
void DateTime::showDateTime() {
  struct tm t;
  if (getLocalTime(&t)) {
    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(20, 25);
    M5.Lcd.printf("%02d:%02d", t.tm_hour, t.tm_min);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(175, 38);
    M5.Lcd.printf(":%02d", t.tm_sec);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(10, 90);
    M5.Lcd.printf("%04d/%02d/%02d", (1900 + t.tm_year), (t.tm_mon + 1), t.tm_mday);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(197, 97);
    M5.Lcd.printf("%s", wd[t.tm_wday]);
  }
}

// 現在時刻を返す
String DateTime::getTime(){
  struct tm t;
  if (getLocalTime(&t)) {
    String time = String(t.tm_hour) + String(t.tm_min);
    return time;
  }
}
