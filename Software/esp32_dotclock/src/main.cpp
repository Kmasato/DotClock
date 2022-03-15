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

  Serial.println(tm->tm_year + 1900);
  Serial.println(tm->tm_mon + 1);
  Serial.println(tm->tm_mday);
  Serial.println(wd[tm->tm_wday]);
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