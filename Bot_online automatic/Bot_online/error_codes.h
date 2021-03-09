#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

/*Denne side er dedikeret til fejl beskeder
   de er lagret som med HTTP

   1xx-2xx bruges ikke

   3xx fejlen ligger hos brugerens udstyr
   4xx fejlen ligger hos brugeren
   5xx fejlen ligger ikke hos brugeren eller deres udstyr


*/

void error_code(int code) {

  switch (code) {
    case 301: //fejl med at læse værdien af den drukkede genstand
      Serial.println("ERROR: ingen værdi kunne blive læst");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 301");
      break;

    case 302: //fejl med at måle glasset
      Serial.println("ERROR: kunne ikke finde glasset");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 302");
      break;

    case 303: //kunne ikke måle den tid det blev drukket på
      Serial.println("ERROR: could not measure time");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 303");
      break;



    case 501:
      Serial.print("[HTTP] Post... failed, error: ");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 501");
      break;

    case 502:
      Serial.printf("[HTTP] Unable to connect\n");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 502");
      break;

    case 503:
      Serial.println("[HTTP] Unable to create client");
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 503");
      break;

    case 504: //error 404

      tft.fillScreen(TFT_BLACK);
      tft.setCursor(13, 50, 2);
      tft.setTextColor(TFT_WHITE, TFT_BLACK);  tft.setTextSize(3);
      tft.println("ERROR: 504");
  }




}
