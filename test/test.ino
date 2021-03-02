#include <Arduino.h>
#include "WiFi.h"
#include "AnotherIFTTTWebhook.h"
 
// Set WiFi credentials
#define WIFI_SSID "amfelt"
#define WIFI_PASS "12345678"
 
// Set IFTTT Webhooks event name and key
#define IFTTT_Key "https://discordapp.com/api/webhooks/813341551782264862/f7Efm9NiinYUNTPekyvl86dS_7ymjbwLj8wr-v23sARUex120yte1ssylaft_Eq4AoK0"
#define IFTTT_Event "email"
 
void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
      WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(1000);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
  // Send Webook to IFTTT
  send_webhook(IFTTT_Event,IFTTT_Key,"Hi its Wemos!","value 2","value 3");
}
 
void loop() {
  // put your main code here, to run repeatedly:
 
}
