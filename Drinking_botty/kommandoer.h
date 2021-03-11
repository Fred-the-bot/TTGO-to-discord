#include "HX711.h"
#include "torta.h"
#include "bruger_input.h"
const char ssid[] = wifiname;
const char pass[] = wifipassword;    // Netværks passwordet

const int LOADCELL_DOUT_PIN = 33;
const int LOADCELL_SCK_PIN = 32;
const String discord_webhook = webhook; //webhooken til discord "botten"
const String discord_tts = "false"; //TTS= Text To Speech "true" for at tænde det og "false" for at slå det fra
HX711 scale;
String drikkelse[] = {"Cocktail", "Sodavand", "Kaffe", "Vand", "Shots"};
int j = 0;
long val = 0;
float count = 0;
int drak;
int val1;
int val2;
bool drik;
int glas = 100;
float drikketid; //hvor længe man var om at drikke
unsigned long nutid = 0; //bliver brugt til at holde øje med tid
unsigned long datid = 0; //bliver brugt til at holde øje med tid

void liquid() {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(13, 50, 2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
  tft.println(drikkelse[i]);
}


void wifi() {
  i = -1;
  k = 0;
  j = 0;
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(13, 5, 2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
  tft.println("Searching");
  tft.setCursor(13, 70, 2);
  tft.println("for WIFI");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  tft.pushImage(0, 0,  240, 135, bootlogo);
}

void besked(String content) {
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client) {
    client -> setCACert(discordappCertificate);
    {
      HTTPClient https;
      Serial.println("[HTTP] Connecting to Discord...");
      Serial.println("[HTTP] Message: " + content);
      if (https.begin(*client, discord_webhook)) {  // HTTPS
        // start connection and send HTTP header
        https.addHeader("Content-Type", "application/json");
        int httpCode = https.POST("{\"content\":\"" + content + "\",\"tts\":" + discord_tts + "}"); //her bliver selve besked sendt til discord via en HTTPS POST kommando

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.print("[HTTP] Status code: ");
          Serial.println(httpCode);
          if (httpCode == 404) {
            error_code(504);
          }
        } else {
          error_code(501);
          Serial.println(https.errorToString(httpCode).c_str());
        }
        https.end();
      } else {
        error_code(502);
      }

    }

    delete client;
  } else {
    error_code(503);

  }
}

void start() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  val = scale.read(); // most recent reading
  val = (val - 149230) / 198460.0f * 177; //Her skal din egen kalibrering stå.
  val1 = val;
  if (val1 < glas) {
    error_code(302);
    return;
  }
  while (drik == true) {
    nutid = millis();
    val = scale.read(); // most recent reading
    val = ligning;
    val1 = val;
    delay(50);
    if (val < glas) { //Starter en timer da den bemærker at glasset er løftet
      j = 1;
      datid = nutid;
      while (val < glas) {
        //DRIK DRIK DRIK
        nutid = millis();
        val = scale.read(); // most recent reading
        val =ligning;
      }

    }
    if (val > glas && j == 1) { //Stopper timeren når den bemærker at glasset er på igen
      drikketid = nutid - datid;
      datid = nutid;
      delay(50);
      while (nutid - datid < 1000) {
        val = 0.2 * val    +   0.8 * scale.read(); // take recent average
        val =ligning;
        nutid = millis();
      }
      val2 = val;
      drak = val2 - val1;
      drikketid = drikketid / 1000;
      if (drikketid == 0) {
        error_code(303);
        return;
      } else if (drak == 0) {
        error_code(301);
        return;
      }
      String druk = String(drikketid);
      besked("Frederik har drukket");
      String test = String(drak);
      besked(test);
      besked("mL på");
      besked(druk);
      besked("Sekunder");
      j = 0;
      drik = false;
    }
  }

}
