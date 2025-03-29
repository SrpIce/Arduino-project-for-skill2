#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trig = 11; //ประกาศขา trig
const int echo = 12; //ประกาศขา echo
const int led = 3; //ประกาศขา led
int Buzz = 10; //กำหนดขา D10 ต่อ Buzzer/Piezo
long duration, distance; //ประกาศตัวแปรเก็บค่าระยะ

void setup() {
  Serial.begin(9600);
  lcd.begin();
  pinMode(echo, INPUT); //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT); //สั่งให้ขา trig ใช้งานเป็น output
  pinMode(led, OUTPUT);
  pinMode(Buzz, OUTPUT);
}
void loop() {
 digitalWrite(trig, LOW); 
 delayMicroseconds(5); 
 digitalWrite(trig, HIGH); 
 delayMicroseconds(5); 
 digitalWrite(trig, LOW); //ใช้งานขา trig
 
 duration = pulseIn(echo, HIGH); //อ่านค่าของ echo
 distance = (duration/2) / 29.1; //คำนวณเป็น centimeters
 	lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Dist = cm");        // print message at (0, 0)
 Serial.print(distance); 
 Serial.print(" cm\n");
 if(distance <= 7){ //ระยะการใช้งาน
  digitalWrite(led, HIGH);
  tone(Buzz, 50, 500); 
 } //เงื่อนไข ถ้าระยะน้อยกว่า 5cm ให้ led ติด
 else{
  digitalWrite(led, LOW);
 }
 delay(300);
}