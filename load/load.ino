#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 33;
const int LOADCELL_SCK_PIN = 32;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("hello");
}

long val = 0;
float count = 0;

void loop() {
  count = count + 1;

  // Use only one of these
 // val = ((count - 1) / count) * val    +  (1 / count) * scale.read(); // take long term average
 val = 0.2 * val    +   0.8 * scale.read(); // take recent average
  //val = scale.read(); // most recent reading
  Serial.println((val-149230)/198460.0f*177);
  //Serial.println( ( 8372000 - val ) / 1020.37f );
  //  Serial.println( val );
  delay(500);

  //kasse 1
//Serial.println((val-18083 )/162980.0f*177);

//kasse 2


}
