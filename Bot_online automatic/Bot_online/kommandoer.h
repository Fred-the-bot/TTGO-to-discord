#include "HX711.h"
#include "torta.h"
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

const int LOADCELL_DOUT_PIN = 33;
const int LOADCELL_SCK_PIN = 32;
const char ssid[] = "amfelt";    // Netværks navnet
const char pass[] = "12345678";    // Netværks passwordet
const String discord_webhook = "https://discordapp.com/api/webhooks/813341551782264862/f7Efm9NiinYUNTPekyvl86dS_7ymjbwLj8wr-v23sARUex120yte1ssylaft_Eq4AoK0"; //webhooken til discord "botten"
const String discord_tts = "false"; //TTS= Text To Speech "true" for at tænde det og "false" for at slå det fra
//openssl s_client -showcerts -connect discordapp.com:443 (get last certificate)
HX711 scale;
String drikkelse[] = {"Cocktail", "Sodavand", "Kaffe", "Vand", "Shots"};
int j = 0;
long val = 0;
float count = 0;
int drak;
int val1;
int val2;
bool drik;

float drikketid; //hvor længe man var om at drikke
unsigned long nutid = 0; //bliver brugt til at holde øje med tid
unsigned long datid = 0; //bliver brugt til at holde øje med tid


/*void vaegt() {
  j++;
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  count = count + 1;
  // Use only one of these
  // val = ((count - 1) / count) * val    +  (1 / count) * scale.read(); // take long term average
  //val = 0.2 * val    +   0.8 * scale.read(); // take recent average
  val = scale.read(); // most recent reading
  val = (val - 149230) / 198460.0f * 177;

  if (val > 212.4 && j == 1) {
    val1 = scale.read(); // most recent reading
    val1 = (val1 - 149230) / 198460.0f * 177;
    delay(50);
  } else if (val > 212.4 && j == 2) {
    val2 = scale.read(); // most recent reading
    val2 = (val2 - 149230) / 198460.0f * 177;
    drak = val1 - val2;
    if (drak == 0) {
      error_code(301);
    }
    delay(50);
    j = 0;
  } else {
    error_code(302);

  }
  }
*/
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

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.print("[HTTP] Response: ");
            Serial.println(payload);
          }
        } else {
          error_code(502);
          Serial.println(https.errorToString(httpCode).c_str()); //skal kigges på
        }

        https.end();
      } else {
        error_code(503);

      }

      // End extra scoping block
    }

    delete client;
  } else {
    error_code(504);

  }
}

void start() {
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  while (drik == true) {
    nutid = millis();
    val = scale.read(); // most recent reading
    val = (val - 149230) / 198460.0f * 177;
    val1 = val;
    Serial.print(val1);
    delay(50);
    if (val < 212.4) {
      j = 1;
      datid = nutid;
      while (val < 212.4) {
        //DRIK DRIK DRIK
        nutid = millis();
        val = scale.read(); // most recent reading
        val = (val - 149230) / 198460.0f * 177;
        Serial.println(val);
      }

    }
    if (val > 212.4 && j == 1) {
      drikketid = nutid - datid;
      delay(500);
      val = scale.read(); // most recent reading
      val = (val - 149230) / 198460.0f * 177;
      val2 = val;
      drak = val2 - val1;
      Serial.println(drikketid);
      drikketid = drikketid / 1000;
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
