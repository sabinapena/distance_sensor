#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <array>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 7;
const int echoPin = 8;
constexpr std::array<int, 14> lookup = {0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25};

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // initialize display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Team Michelle");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);  //Set LCD cursor to upper left corner, column 0, row 0
  lcd.print("Distance:");//Print Message on First Row
  lcd.setCursor(0,1);  //Set LCD cursor to upper left corner, column 0, row 0
  lcd.print("Height:");//Print Message on First Row
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm, height;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  height = lookup[cm]; 


  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.print(height);
  Serial.print("cm");
  Serial.println();

  lcd.setCursor(9,0);   
  lcd.print("                         ");  
  lcd.setCursor(9,0);    
  lcd.print(                cm); //Print measured distance
  lcd.print(" cm");  //Print your units.

  lcd.setCursor(9,1);   
  lcd.print("                         ");  
  lcd.setCursor(9,1);    
  lcd.print(                height); //Print measured height
  lcd.print(" cm");  //Print your units.

  delay(1000);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

