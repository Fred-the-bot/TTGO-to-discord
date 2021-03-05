#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "certificate.h"
#include "kommandoer.h"


void setup() {
  Serial.begin(115200);
  wifi();
  pinMode(0, INPUT); //venstre knap if ==0 så den trykket ned
  pinMode(35, INPUT); //Højre knap
}

void loop() {

  if (digitalRead(35) == 0){
      besked("!random");
  }


  if (digitalRead(0)==0){
    besked("!ping");
  }

}
