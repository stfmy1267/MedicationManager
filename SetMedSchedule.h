#include <M5StickCPlus.h>
#include "efont.h"
#include "efontM5StickCPlus.h"
#include "efontEnableJa.h"

class SetMedSchedule {
  public:
    int hour = 6;
    int minute = 0;
    int h1,h2,m1,m2;
    int cursorIndex = 1;
    bool timeConfigured = false;

    void showTime();
    void setTime();
    
};

void SetMedSchedule::showTime(){
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(5, 5);
  if (h1 == NULL) M5.Lcd.printf("TIME1");
  else if (h2 == NULL) M5.Lcd.printf("TIME2");
  M5.Lcd.setTextSize(5);
  M5.Lcd.setCursor(50, 35);
  M5.Lcd.printf("%02d:%02d",hour,minute);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(100, 95);
  M5.Lcd.printf("OK?");
}

void SetMedSchedule::setTime() {
  if (cursorIndex == 0) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
    if (h1 == NULL) {
      M5.Lcd.printf("%02d:%02d\n",hour,minute);
      M5.Lcd.setTextSize(1);
      printEfont("にTIME1を設定しました");
      if (M5.BtnA.wasPressed()) {
        h1 = hour; m1 = minute;
        M5.Lcd.fillScreen(BLACK);
        cursorIndex = 1;  
      } else if (M5.BtnB.wasPressed()) {
        M5.Lcd.fillScreen(BLACK);
        cursorIndex = 1;
      }
    } else if  (h2 == NULL && hour == h1 && minute == m1){
      M5.Lcd.setTextSize(2);    
      printEfont("TIME1と同じ時間は設定出来ません");
      delay(3000);
      cursorIndex = 1;
      M5.Lcd.fillScreen(BLACK); 
    } else if (h2 == NULL) {
      M5.Lcd.printf("%02d:%02d\n",hour,minute);
      M5.Lcd.setTextSize(1);
      printEfont("にTIME2を設定しました");
      if (M5.BtnA.wasPressed()) {
        M5.Lcd.fillScreen(BLACK);
          h2 = hour; m2 = minute;
          timeConfigured = true;  
      } else if (M5.BtnB.wasPressed()) {
        M5.Lcd.fillScreen(BLACK);
        cursorIndex = 1;
      }
    }
  } else if (cursorIndex == 1) { 
    showTime();
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(70,10);
    printEfont("▼");
    if(M5.BtnB.wasPressed()) {
      M5.Lcd.fillScreen(BLACK);
      cursorIndex = 2;
    } 
    if(M5.BtnA.wasPressed()) {
      hour++;
      if (hour > 23) hour = 0;
    }
  }else if (cursorIndex == 2) {
    showTime();
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(160,10);
    printEfont("▼");
     if(M5.BtnB.wasPressed()){
      M5.Lcd.fillScreen(BLACK);
      cursorIndex = 3;
    }
    if(M5.BtnA.wasPressed()) {
      minute = minute + 10;
      if (minute > 59) minute = 0;
    }
  } else if (cursorIndex == 3) {
    showTime();
    M5.Lcd.setCursor(75,100);
    M5.Lcd.setTextSize(1);
    printEfont("▶");
    if(M5.BtnB.wasPressed()){
      M5.Lcd.fillScreen(BLACK);
      cursorIndex = 1;
    }
    if(M5.BtnA.wasPressed()){
      cursorIndex = 0;
    }
  }
}
