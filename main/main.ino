#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <VL53L0X.h>
#include <array>
#include <cmath>

LiquidCrystal_I2C lcd(0x27, 16, 2);
VL53L0X sensor;


double getAngle(double opp, double adj) {
    double angleRad = atan(opp / adj);   // angle in radians
    double angleDeg = angleRad * 180.0 / M_PI; // convert to degrees
    return angleDeg;
}


void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize sensor
  Serial.println("Initializing sensor...");
  if (!sensor.init()) {
    Serial.println("Failed to detect VL53L0X!");
    while (1);
  }

  sensor.setTimeout(500);
  sensor.startContinuous();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Team Michelle");
  delay(5000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.setCursor(0,1);
  lcd.print("Height:");

  Serial.println("Setup complete ");
}

void loop() {
  int distance_mm = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.println("Timeout ");
    return;
  }

  // Convert to cm (like your old code)
  int distance_cm = distance_mm / 10;

// chnage 10 to real distance 

  double angle = getAngle(distance_cm, 10);


  // Serial output (same style as before)
  Serial.print(cm);
  Serial.print(" cm");
  Serial.println();

  Serial.print("Height: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // LCD display
  lcd.setCursor(9,0);
  lcd.print("      ");  // clear old value
  lcd.setCursor(9,0);
  lcd.print(cm);
  lcd.print(" cm");

  lcd.setCursor(9,1);
  lcd.print("      ");
  lcd.setCursor(9,1);
  lcd.print(angle);
  lcd.print(" degrees");

  delay(500);
}