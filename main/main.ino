#include <Wire.h> // for 12c communication
#include <VL53L0X.h>

VL53L0X sensor; //instance

void setup(){
  Serial.begin(9600); // initiate serial communication
  Wire.begin();

  sensor.init();
  sensor.setTimeout(900);

  sensor.startContinuous();
}

void loop()
{
  int distance = sensor.readRangeContinuousMillimeters();
  Serial.print("Distance (mm): ");
  Serial.print(distance);
  Serial.print("\n");
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT\n"); }
  delay(500);
}
