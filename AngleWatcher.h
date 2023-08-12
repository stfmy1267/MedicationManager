#include <M5StickCPlus.h>
#include <WiFi.h>

class AngleWatcher {
  public:
    bool getAngle();

  private:
    float accX = 0;
    float accY = 0;
    float accZ = 0;
//
//    float gyroX = 0;
//    float gyroY = 0;
//    float gyroZ = 0;
};


bool AngleWatcher::getAngle() {
  M5.Imu.getAccelData(&accX,&accY,&accZ);
//  M5.Imu.getGyroData(&gyroX,&gyroY,&gyroZ);
  Serial.print("    X:");
  Serial.println(accX);
  if (accX > 0.7 || accX < -0.7) return true;
  
  else return false;
}
