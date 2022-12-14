#include <Arduino.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


LiquidCrystal_I2C lcd(0x20, 16, 2);


 
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const float CALIBRATION_FACTOR = 31.457;

int count;
bool isMaxKG = false;
 
HX711 scale;
 
void setup() {
  count = EEPROM.read(0);
  // If count is not number, set it to 0
  if (count < 0) {
    count = 0;
  }
  lcd.init();
  lcd.backlight();
  lcd.print("Starting...");
 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
 
  scale.tare();               // reset the scale to 0
  scale.set_scale(CALIBRATION_FACTOR);
}
 
void loop() {
  double kilograms;
  kilograms = scale.get_units(20)/1000;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(kilograms, 2);
  lcd.println(" kg");
  lcd.setCursor(0, 1);
  lcd.print(count);

  delay(100);

  if (kilograms >= 2.0 && !isMaxKG) {
    count++;
    EEPROM.write(0, count);
    isMaxKG = true;
  } else if (kilograms == 0.0) {
    isMaxKG = false;
  }
}
