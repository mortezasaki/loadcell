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
  lcd.print("Hello, world!");
  pinMode(add_btn_pin, INPUT);
  Serial.begin(57600);
  Serial.println("HX711 Demo by Satyam Singh");
  Serial.println("Initializing the scale");
 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
 
  // Serial.println("Before setting up the scale:");
  // Serial.print("read: \t\t");
  // Serial.println(scale.read());      // print a raw reading from the ADC
 
  // Serial.print("read average: \t\t");
  // Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
 
  // Serial.print("get value: \t\t");
  // Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)
 
  // Serial.print("get units: \t\t");
  // Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
  //           // by the SCALE parameter (not set yet)
            
  // scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  // //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  scale.set_scale(31.457);
 
  // Serial.println("After setting up the scale:");
 
  // Serial.print("read: \t\t");
  // Serial.println(scale.read());                 // print a raw reading from the ADC
 
  // Serial.print("read average: \t\t");
  // Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
 
  // Serial.print("get value: \t\t");
  // Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
 
  // Serial.print("get units: \t\t");
  // Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
  //           // by the SCALE parameter set with set_scale
 
  // Serial.println("Readings:");
}
 
void loop() {
  double kilograms;
  kilograms = scale.get_units(20)/1000;
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
