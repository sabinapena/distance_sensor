#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <VL53L0X.h>
#include <array>
#include <cmath>

LiquidCrystal_I2C lcd(0x27, 16, 2);
VL53L0X sensor;

unsigned long previousMillis = 0;
int seconds = 0;

double getAngle(double opp, double adj) {
    double angleRad = atan(opp / adj);   // angle in radians
    double angleDeg = angleRad * 180.0 / M_PI; // convert to degrees
    return angleDeg;
}


void setup() {
  Serial.begin(9600);
  Wire.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hallo Michelle");

  delay(5000);
  // Initialize sensor

  //Serial.println("Initializing sensor...");
  if (!sensor.init()) {
    lcd.clear();
    lcd.print("Failed to detect VL53L0X!");
    while (1);
  }

  sensor.setTimeout(500);
  sensor.startContinuous();

  // Initialize LCD

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Angle:");
  lcd.setCursor(0,1);
  lcd.print("Timer:");

  Serial.println("Setup complete ");
}

void loop() {
  int distance_mm = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.println("Timeout ");
    return;
  }

//timer
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;

      seconds++;
      Serial.print("Timer: ");
      Serial.println(seconds);
    }

  // Convert to cm (like your old code)
  int distance_cm = distance_mm / 17;

  double angle = getAngle(distance_cm, 17);

  if (distance_cm < 1) {
      seconds = 0;
      previousMillis = millis();   // restart timing from now

      Serial.println("Timer reset");
  }

  Serial.print("Height: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.println(" degrees");

  // LCD display
  lcd.setCursor(7,0);
  lcd.print(angle);
  lcd.print(" o ");

  lcd.setCursor(7,1);
  lcd.print(seconds);
  lcd.print("  sec ");

  delay(500);
}