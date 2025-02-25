// 25.02.2025, created by Sergei Znamensky 
// Sketch for Amperka Dragster outputs battery level to Troyka LED Matrix as marquee
#include "TroykaLedMatrix.h" 
TroykaLedMatrix matrix;         // object LED Matrix
char Vbat_str[] = "0.0 ";       // Char array for marquee output in LED Matrix
byte  len = sizeof(Vbat_str);   //  Length of char array
uint16_t shift = 0;             // variable for marquee
float Vbat = 0.0;               // variable flt to be converted to char variable and then presented in LED Matrix
float R1 = 10000;               // CONSTANT DIVIDER
float R2 = 36000;               // CONSTANT DIVIDER

void setup() {
  matrix.begin();                       // initiate LED Matrix
  matrix.selectFont(FONT_8X8_BASIC);    // select font
  pinMode(A1, INPUT);                   // CONFIGURE PIN1 AS ANALOG INPUT
}

void loop() {
  int adcValue = analogRead(A1);        // PICK VALUE FROM A1
  float V = adcValue *5.0/1023.0;       // A1 IN VOLTS AFTER DIVIDER
  Vbat = V * (R1 + R2) / R2;            // CALCULATED BATTERY VOLTS
  dtostrf(Vbat, 3, 1, Vbat_str);        // convert flt number to char string
  Vbat_str[3] = 'V';
// Output as marquee in LED Matrix the battery level in Volts
  delay(150);
  matrix.marqueeText(Vbat_str, len, shift++);
  if (shift == len * 8) {
    shift = 0;
  }
}
