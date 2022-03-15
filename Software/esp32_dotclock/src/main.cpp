#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

#include "config.h"

#define JST 3600*9

void startWiFi(void);

const char* ssid = SSID;
const char* password = WIFI_PASSWORD;

void setup() {
  Serial.begin(115200);
  Serial.print("WiFi is connecting.");

  startWiFi();

  configTime(JST,0,"ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

}

void loop() {
  time_t t;
  struct tm* tm;
  static const char* wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};

  t = time(NULL);
  tm = localtime(&t);

  Serial.printf("%d/%d/%d [%s] \n",tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, wd[tm->tm_wday]);
  Serial.printf("%d:%d:%d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
  delay(1000);
}

void startWiFi(){
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("Done!");

  Serial.print("IP:");
  Serial.println(WiFi.localIP());
}