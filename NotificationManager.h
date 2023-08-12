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
