#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include <SPI.h>

#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <Adafruit_GFX.h>

#include "config.h"

#define JST 3600*9

/* LED Matrix settings */
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 5

#define ROW_SIZE 16
#define COLUMN_SIZE 16

void startWiFi(void);
void setPoint(int,int,bool);

const char* ssid = SSID;
const char* password = WIFI_PASSWORD;

MD_Parola parola = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

GFXcanvas1 myCanvas(16,16);

void setup() {
  Serial.begin(115200);
  Serial.print("WiFi is connecting.");

  startWiFi();
  configTime(JST,0,"ntp.nict.jp", "ntp.jst.mfeed.ad.jp");

  mx.begin();

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

  //myCanvas.writeFastHLine(2,2,10,0x01);
  //myCanvas.drawCircle(7,7,5,0x01);

  myCanvas.setTextSize(1);
  myCanvas.drawChar(0,0,'A',0x01,0,1);

  mx.clear();

  for (int i = 0; i < 16; i++){
    for(int j=0; j < 16; j++){
      //Serial.print(myCanvas.getPixel(i,j));
      setPoint(i,j,myCanvas.getPixel(i,j));
    }
    //Serial.println();
  }
  
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

void setPoint(int x, int y, bool state){
  if(0 <= y && y < 8){
    mx.setPoint(7-y, x, state);
  }
  if(8 <= y && y < 16){
    mx.setPoint(15-y, x+16, state);
  }
}