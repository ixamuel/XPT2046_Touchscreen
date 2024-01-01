#include "TFT_eSPI.h"
#include "pins.h" // from https://github.com/Xinyuan-LilyGO/T-HMI/tree/master
#include <XPT2046_Touchscreen.h>
#include <SPI.h>


#define BACKGROUND_COLOR 0x001F // Blue
#define FOREGROUND_COLOR 0xFFFF // White
#define HIGHLIGHT_COLOR  0xFFE0 // Yellow

XPT2046_Touchscreen ts(TOUCHSCREEN_CS_PIN, TOUCHSCREEN_IRQ_PIN);

TFT_eSPI tft = TFT_eSPI();

void setup() {
  pinMode(PWR_EN_PIN, OUTPUT);
  digitalWrite(PWR_EN_PIN, HIGH);
  SPI.begin(TOUCHSCREEN_SCLK_PIN, TOUCHSCREEN_MISO_PIN, TOUCHSCREEN_MOSI_PIN);
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(BACKGROUND_COLOR);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000));
}

boolean wastouched = true;

void loop() {
  boolean istouched = ts.touched();
  if (istouched) {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      tft.fillScreen(BACKGROUND_COLOR);
      tft.setTextColor(HIGHLIGHT_COLOR);
      tft.setTextSize(3);
      tft.setCursor(60, 80);
      tft.print("Touch");
    }
    tft.fillRect(100, 150, 140, 60, BACKGROUND_COLOR);
    tft.setTextColor(HIGHLIGHT_COLOR);
    tft.setTextSize(3);
    tft.setCursor(100, 150);
    tft.print("X = ");
    tft.print(p.x);
    tft.setCursor(100, 180);
    tft.print("Y = ");
    tft.print(p.y);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.println(p.y);
  } else {
    if (wastouched) {
      tft.fillScreen(BACKGROUND_COLOR);
      tft.setTextColor(HIGHLIGHT_COLOR);
      tft.setTextSize(3);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
    }
    Serial.println("no touch");
  }
  wastouched = istouched;
  delay(100);
}
