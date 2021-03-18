#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 33;
const int LOADCELL_SCK_PIN = 32;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

long val = 0;
float count = 0;

void loop() {
  count = count + 1;


  // val = ((count - 1) / count) * val    +  (1 / count) * scale.read(); // tager gennesnittet af alt. alt hvad modulet "vejer" imens den er tændt blive puttet ind i gennemsnittet her.
  val = 0.2 * val    +   0.8 * scale.read(); // tager et mindre gennemsnit hvor man kun bruger 80% af alle målte værdier.
  //val = scale.read(); // Måler hvad den vejer lige nu og her. intet gennesnit eller matematik.
  Serial.println((val)); //her ender din formel til at skulle stå.
  delay(500);


}
