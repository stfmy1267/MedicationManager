#include <M5StickCPlus.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include "efont.h"
#include "efontM5StickCPlus.h"
#include "efontEnableJa.h"
#include "SetMedSchedule.h"
#include "DateTime.h"
#include "AngleWatcher.h"
#include "NotificationManager.h"

SetMedSchedule setMedSchedule = SetMedSchedule();
DateTime dateTime = DateTime();
AngleWatcher angleWatcher = AngleWatcher();
NotificationManager notificationManager = NotificationManager();


bool isActive = false;
bool isTaken = false;
const char* ssid     = "XXXXXXXXXXXXXXXX";
const char* password = "XXXXXXXXXXXXXXXXXXXX";

const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* ntpServer =  "ntp.jst.mfeed.ad.jp"; //  GMT+9(日本時間)
const long gmtOffset_sec = 9 * 3600; // サマータイム時差(無し)
const int  daylightOffset_sec = 0; 

void connectToWiFi() {
  WiFi.begin(ssid, password);
  // Wifi接続を一分間の間試みる。500ms*120回なので、1分でタイムアウト
  for (int i = 0; i < 120 && WiFi.status() != WL_CONNECTED; i++) {
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED) {
    // Wifi接続エラー
//    printEfont("Wifiに接続できませんでした。");
  }
  //  Wifi接続成功
  if (WiFi.status() == WL_CONNECTED) {
    configTime(gmtOffset_sec,daylightOffset_sec,ntpServer);
    struct tm t;
    if (!getLocalTime(&t)) {
      // NTPサーバ接続エラー
//      connectToWiFi();
    }
  }
//  WiFi.disconnect(true);
//  WiFi.mode(WIFI_OFF);
}

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Imu.Init();
  connectToWiFi();
  M5.Axp.ScreenBreath(3);
}

void loop() {
  M5.update();
    if (isActive) {
    pinMode(10, OUTPUT);
    analogWrite(10, 30);
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
    delay(1000); 
    struct tm t;
    if (getLocalTime(&t)) {
      M5.Lcd.setTextSize(5);
      M5.Lcd.setCursor(50, 25);
      M5.Lcd.printf("%02d:%02d", t.tm_hour, t.tm_min);
      M5.Lcd.setTextSize(1);
      M5.Lcd.setCursor(40, 100);
//      M5.Lcd.setTextSize(2);
      printEfont("お薬を飲む時間帯です。");
      if (t.tm_hour == setMedSchedule.h2 && t.tm_min == setMedSchedule.m2 && !isTaken){
        pinMode(10, INPUT);
        M5.Lcd.fillScreen(BLACK);
        isActive = false;
//        notificationManager.LineNotify("お薬を飲みました");
        M5.Beep.tone(3000, 1000);
        delay(5000);
        M5.Beep.update();
        setMedSchedule.timeConfigured = false;
        setMedSchedule.h1 = NULL;
        setMedSchedule.h2 = NULL;
        setMedSchedule.m1 = NULL;
        setMedSchedule.m2 = NULL;
        setMedSchedule.hour = 6;
        setMedSchedule.minute = 0;
        setMedSchedule.cursorIndex = 1;
      }
    }
     if(angleWatcher.getAngle()){
        pinMode(10, INPUT);
        isTaken = true;
        isActive = false;
        setMedSchedule.timeConfigured = false;
        setMedSchedule.h1 = NULL;
        setMedSchedule.h2 = NULL;
        setMedSchedule.m1 = NULL;
        setMedSchedule.m2 = NULL;
        setMedSchedule.hour = 6;
        setMedSchedule.minute = 0;
        setMedSchedule.cursorIndex = 1;
        M5.Lcd.fillScreen(BLACK);
    }
  } else {
    if(!setMedSchedule.timeConfigured){
      setMedSchedule.setTime();
    } else if (setMedSchedule.timeConfigured){
//      dateTime.showDateTime();
      M5.Lcd.setCursor(10, 20);
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("%02d:%02d", setMedSchedule.h1, setMedSchedule.m1);
      M5.Lcd.setTextSize(2);
      printEfont("〜");
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("%02d:%02d", setMedSchedule.h2, setMedSchedule.m2);
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(10, 50);
      printEfont("の間にお薬を\n飲んでください");
      struct tm t;
      if (getLocalTime(&t)) {
          if (t.tm_hour == setMedSchedule.h1 && t.tm_min == setMedSchedule.m1) {
            isActive = true;
            M5.Lcd.fillScreen(BLACK);
//            notificationManager.LineNotify("お薬を飲む時間帯です");
          }
      }
      
    }
  }

//  delay(100);
}
