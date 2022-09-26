#include <Arduino.h>
#include <HX711.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>


LiquidCrystal_I2C lcd(0x20, 16, 2);


 
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int add_btn_pin = 4;
float calibration_factor = -100000; // This value is obtained using the SparkFun_HX711_Calibration sketch
int count;
 
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
  scale.set_scale(31.457);
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

  if (kilograms >= 2.0)
  {
    count++;
    EEPROM.write(0, count);
  }
  delay(100);
}
