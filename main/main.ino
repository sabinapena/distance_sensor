#include <Wire.h> // for 12c communication
#include <Adafruit_VL53L0X.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X(); //instance

void setup(){
  Serial.begin(115200); // initiate serial communication
  Wire.begin();
  delay(1000);

  if(!lox.begin()){
    Serial.println("Failed to boot dist sensor");
    while(1);
  }
  Serial.println("Sensor ready\n");
}

void loop(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure);
  if(measure.RangeStatus != 4){
    Serial.print("Distance (mm): ");
    Serial.println(measure.RangeMilliMeter);
  }else{
    Serial.println("Object out of range");
  }
  delay(100);
}