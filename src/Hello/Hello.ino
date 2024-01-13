#include <TFT_eSPI.h>
#include <SPI.h>
#include "WiFi.h"
#include "homer.h"


#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define LEFT 0
#define RIGHT 47

TFT_eSPI tft = TFT_eSPI();

void blink() {
  tft.drawString("   = _ =   ", 30, 30, 2);
  delay(200);
  tft.drawString("   - _ -   ", 30, 30, 2);
  delay(200);
  tft.drawString("   = _ =   ", 30, 30, 2);
  delay(1000 + random(1000));
  tft.fillScreen(TFT_BLACK);
  tft.drawString("   = _ =   ", 30, 30, 2);
}

void speak(const char *str, int y = 80) {
  int x = 10;
  
  while(*str) {
    if(x > 120) {
      x = 10;
      y += 15;
    }
    tft.drawString("   = .. =   ", 30, 30, 2);
    x += tft.drawChar(*str++, x, y);
    delay(40);
    tft.drawString("   = _ =   ", 30, 30, 2);
    delay(40 + random(40));
  }
  delay(300);
}

void listWifi(){
  speak("scaning ........");
  int n = MIN(WiFi.scanNetworks(), 4);
  blink();
  for (int i = 0; i < n; ++i) {
    speak(WiFi.SSID(i).c_str());
    blink();
  }
}

void gif() {
  delay(1500);
  for(int i=0;i<frames;i++) {
    tft.pushImage(0, 0,128, 128, animation[i]);
    delay(60);
  }
  delay(1500);
  for(int i=0;i<frames;i++) {
    tft.pushImage(0, 0,128, 128, animation[frames - i - 1]);
    delay(60);
  }
}

int screen = 0;

void leftPressed() {
 screen = 1; 
}

void rightPressed() {
 screen = 2; 
}

void hello() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  blink();
  speak("Hello there");
  blink();
  speak("I'm a little board based on the esp32");
  blink();
  speak("I can do wifi");
  blink();
  listWifi();
  blink();
  speak("I also can do blue tooth and much more");
  blink();
  speak("let's do awesome   things together");
  screen = 0;
}

void intro() {
  tft.fillScreen(TFT_BLACK);
  blink();
  speak("Press a button now");
}

void setup(void) {
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(2);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  pinMode(LEFT, INPUT_PULLUP);
	attachInterrupt(LEFT, leftPressed, FALLING);
  pinMode(RIGHT, INPUT_PULLUP);
	attachInterrupt(RIGHT, rightPressed, FALLING);
}

void loop() {
  if (screen == 1) {
    hello();
  } else if(screen == 2){
    gif();
  } else {
    intro();
  }
}

