#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "certificate.h"
#include "kommandoer.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
#include "torta.h"
int i = -1;
void setup() {
  Serial.begin(115200);
  wifi();
  pinMode(0, INPUT); //venstre knap if ==0 så den trykket ned
  pinMode(35, INPUT); //Højre knap
  tft.init();
  tft.setRotation(45);

  tft.setSwapBytes(true);
  tft.pushImage(0, 0,  135, 240, bootlogo);
}

void loop() {

  if (digitalRead(35) == 0) {
    vaegt();
    String test = String(val);
    besked("Fred the bot drikker nu");
    besked(drikkelse[i]);
  }


  if (digitalRead(0) == 0) {
    delay(250); //For at undgå at den køre flere gange når der bare skal trykkes
    i++;
    if (i == 5) {
      i = 0;
    }
    
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(13, 50, 2);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
    tft.println(drikkelse[i]);
  }

}
