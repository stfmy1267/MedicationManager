#include <M5StickCPlus.h>


class NotificationManager {
  public:
    void LineNotify(String msg);

  private:
    const char* host = "notify-api.line.me";
    const char* token = "Bv3z6j1MAMNkgsdd5jBzpz75mZAgHdCEs12wPPlwAXU"; // トークン
};




void NotificationManager::LineNotify(String msg) {
  WiFiClientSecure client; // https接続
  client.setInsecure();
  if (!client.connect(host, 443)) {
    delay(2000);
    M5.Lcd.print("Line Notify disconnect");
    return;
  }

  String query = String("message=") + msg;
  String request = String("") + //空の文字列を生成
               "POST /api/notify HTTP/1.1\r\n" + 
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + token + "\r\n" +
               "Content-Length: " + String(query.length()) +  "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                query + "\r\n";
  client.print(request);
  client.stop();
  
  delay(2000);
}


//// LINE Notify処理関数
//void Line_Notify(String msg) {
//  client.setInsecure();
//  if (!client.connect(host, 443)) {
//    delay(2000);
//    M5.Lcd.print("Line Notify disconnect");
//    return;
//  }
//
//  String query = String("message=") + msg;
//  String request = String("") +
//               "POST /api/notify HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" +
//               "Authorization: Bearer " + token + "\r\n" +
//               "Content-Length: " + String(query.length()) +  "\r\n" + 
//               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
//                query + "\r\n";
//  client.print(request);
//  client.stop();
//
//  delay(2000);
//}
//
//// このコマンドを実行すると、デジタルピン 36 は入力に設定され、プルアップ抵抗が有効になります。プルアップ抵抗とは、デジタルピンに電圧を供給する抵抗です。
//// プルアップ抵抗を有効にすることで、デジタルピンが HIGH 状態になるようにすることができます。
//// プルアップ抵抗は、デジタルピンをスイッチとして使用する場合などに役立ちます。
//// たとえば、デジタルピンをスイッチとして使用する場合、スイッチがオフのときにデジタルピンが LOW 状態になるようにする必要があります。
//// プルアップ抵抗を有効にすることで、スイッチがオフのときにデジタルピンが LOW 状態になるようにすることができます。
//  // pinMode(GPIO_NUM_36,INPUT_PULLUP); // PIR
//  // デジタルピン 10 に電圧を送り出すことができます。
//  // デジタルピン 10 に電圧を送り出すことで、LED を点灯したり、モーターを動かしたりすることができます。
//  // pinMode(GPIO_NUM_10, OUTPUT); // 内蔵LED
//  // たとえば、LED を点灯したり、モーターを動かしたりするのに使用できます。
//  // digitalWrite(GPIO_NUM_10, HIGH);
//
//
//
////アラームを鳴らす&通知処理
//void NotificationManager::alert(){
//  M5.Beep.tone(3000, 1000);  // アラームを鳴らす。カッコ内は調整可
//  delay(15);    //１５秒間鳴るように、括弧内に追記
//  M5.Beep.update();  //アラームが止まる。
//  //メッセージをラインに送信 
//  if (isActive) {
//    Line_Notify("薬を飲んでいません！");
//  }
//}
