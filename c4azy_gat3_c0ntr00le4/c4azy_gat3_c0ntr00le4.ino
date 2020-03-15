//This code is done by c0ld Z3r0 (dev_bides_mega)
//For awesome code check https://github.com/c0ld-z3r0 :)

#include<SoftwareSerial.h> // Getting Serial Data from output
#include<Servo.h> // For controlling Servo's

#define servo1 1 // 1st Servo D3
#define servo2 2 // 2nd Servo D4

#define echo1 3 // ECHO pin of 1st Ultrasonic Sensor D6
#define trig1 4 // TRIGGER pin of 1st Ultrasonic Sensor D7
#define echo2 5 // ECHO pin of 2nd Ultrasonic Sensor D8
#define trig2 6 // TRIGGER pin of 2nd Ultrasonic Sensor D9

#define signal1red 7 // RED Signal LED for 1st Sensor
#define signal1green 8 // GREEN Signal LED for 1st Sensor
#define signal2red 9 // RED Signal for 2nd Sensor
#define signal2green 10 // GREEN Signal LED for 2nd Sensor

Servo gate1;
Servo gate2;

long latency1,distance1,latency2,distance2;
boolean gate_state = false;
int pos = 0;
void light_animation1(int ms)
{
  digitalWrite(signal1red,HIGH);
  delay(ms/4);
  digitalWrite(signal1green,LOW);
  delay(ms/4);
  digitalWrite(signal1red,LOW);
  delay(ms/4);
  digitalWrite(signal1green,HIGH);
  delay(ms/4);
}
void light_animation2(int ms)
{
  digitalWrite(signal2red,HIGH);
  delay(ms/4);
  digitalWrite(signal2green,LOW);
  delay(ms/4);
  digitalWrite(signal2red,LOW);
  delay(ms/4);
  digitalWrite(signal2green,HIGH);
  delay(ms/4);
}
void setup()
{
  Serial.begin(9600);
  pinMode(trig1,OUTPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(echo2,INPUT);

  gate1.attach(servo1);
  gate2.attach(servo2);

  gate1.write(0);
  gate2.write(0);
  
}
void loop()
{
  digitalWrite(signal1red,HIGH);
  digitalWrite(signal1green,LOW);
  digitalWrite(signal2red,HIGH);
  digitalWrite(signal2green,LOW);
  
  digitalWrite(trig1,LOW);
  digitalWrite(trig2,LOW);
  delayMicroseconds(2);
  digitalWrite(trig1,HIGH);
  digitalWrite(trig2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
  digitalWrite(trig2,LOW);
  latency1 = pulseIn(echo1,HIGH);
  latency2 = pulseIn(echo2,HIGH);
  distance1 = ((latency1/2)/29.1); //This distance1 is in cm and from 1st Ultrasonic Sensor
  distance2 = ((latency2/2)/29.1); //This distance2 is in cm and from 2nd Ultrasonic Sensor
  
  if(Serial.available()>0)// This checks for a serial monitor
  {
    Serial.print("The distance from radar1 is : ");
    Serial.print(distance1);// This prints the distance of some object detected in the radar1 in cm
    Serial.print(" cm.");
    Serial.println();
    Serial.print("The distance from radar2 is : ");
    Serial.print(distance2);// This prints the distance of some object detected in the radar1 in cm
    Serial.print(" cm.");
    Serial.println();
    delay(2000); // Waits 2 seconds or else you cannot read the terminal ;)
  }
  if(distance1 <= 10)
  {
    gate_state = true;// It switches the state of gate's
    for (pos = 0;pos <= 90;pos+9)// Raising Gate's to 90 degree
    {
      gate1.write(pos);
      gate2.write(pos);
      light_animation1(100);//Some Signal animation change value for good blink
    }
    digitalWrite(signal1red,LOW);
    digitalWrite(signal1green,HIGH);
    delay(10000);
  }
  else if(distance2 <= 10)
  {
    gate_state = true;// It switches the state of gate's
    for (pos = 0;pos <= 90;pos+9)// Raising Gate's to 90 degree
    {
      gate1.write(pos);
      gate2.write(pos);
      light_animation2(100);//Some Signal animation change value for good blink
    }
    digitalWrite(signal2red,LOW);
    digitalWrite(signal2green,HIGH);
    delay(10000);
  }
  if (gate_state)// This statement checks for gate state if open closes it
  {
    for(pos;pos >= 0; pos-9)
    {
      gate1.write(pos);
      gate2.write(pos);
      light_animation1(50);
      light_animation2(50);
    }
    delay(20000);
    digitalWrite(signal1red,HIGH);
    digitalWrite(signal1green,LOW);
    digitalWrite(signal2red,HIGH);
    digitalWrite(signal2green,LOW);
  }
}
