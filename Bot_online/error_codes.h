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
      break;

    case 302: //fejl med at måle glasset
      Serial.println("ERROR: kunne ikke finde glasset");
      break;


    case 502: //ukendt fejl i koden
      Serial.println("ERROR: Unkown error, check line 42 in 'Bot_online'");
      break;


  }


}
