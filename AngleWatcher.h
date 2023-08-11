#include <M5StickCPlus.h>
#include <WiFi.h>

class AngleWatcher {
  public:
    float accX = 0;
    float accY = 0;
    float accZ = 0;

    bool getAngle();
};


bool AngleWatcher::getAngle() {
  M5.Imu.getAccelData(&accX,&accY,&accZ);
  if (accX > 0.7) return true;
  else return false;
}
