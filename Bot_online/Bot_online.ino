int i = -1;
int k = 0;
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "certificate.h"
#include "kommandoer.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
//TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(45);
  tft.setSwapBytes(true);
  wifi();
  pinMode(0, INPUT); //venstre knap if ==0 så den trykket ned
  pinMode(35, INPUT); //Højre knap
}

void loop() {

if(WiFi.status() != WL_CONNECTED) {
  wifi();
}
  if (digitalRead(35) == 0) {
    delay(250); //For at undgå at den køre flere gange når der bare skal trykkes
    k++;
    vaegt();
    if (k == 1) {
      besked("Frederik drikker nu");
      besked(drikkelse[i]);
    } else if (k == 2 && drak!=0) {
      besked("Frederik har drukket");
      String test = String(drak);
      delay(10);
      besked(test);
      besked("mL");
      k = 0;
    } else {
      k=0;
      j=0;
      Serial.println("ERROR: either no value was detected (see above) or something went wrong, check function at line 34 in 'bot_online'");
    }
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
