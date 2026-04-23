#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal_I2C.h>  // ← replaces the two OLED includes

VL53L0X sensor;
int cm;

LiquidCrystal_I2C lcd(0x27, 16, 2);  // ← replaces the OLED display object

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // LCD setup
  lcd.init();
  lcd.backlight();

  // Sensor setup
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!");
    while (1) {}
  }
  sensor.startContinuous();
}

void loop()
{
  cm = (sensor.readRangeContinuousMillimeters()) / 10;
  Serial.println(cm);

  lcd.clear();
  lcd.setCursor(0, 0);       // Row 0 = "Distance:"
  lcd.print("Distance:");
  lcd.setCursor(0, 1);       // Row 1 = the actual value
  lcd.print(cm);
  lcd.print(" cm");

  delay(500);

  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
}
