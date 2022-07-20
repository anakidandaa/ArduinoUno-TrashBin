/*
  CODE BY: https://github.com/anakidandaa/ArduinoUno-TrashBin
  FOR : AUTOMATIC TRASH BIN 
  BOARD : ARDUINO UNO R3
  SENSOR : ULTRASONIC SENSOR
  TOOLS : ULTASONIC SENSOR & SERVO
  HOW IT WORKS : Ultasonic sensor detect things and thrashbin opens it self
*/

#include <Servo.h>   //include servo library
Servo servo;         // define servo

//define servo & sensor pins
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;
int led = 10;
long duration, dist, average;
long aver[3];   //array for average


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.write(0);         //to close cap
  delay(100);
  servo.detach();
}


//measure distance
void measure() {
  digitalWrite(10, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;  //obtain distance
}

void loop() {
  for (int i = 0; i <= 2; i++) { //average distance
    measure();
    aver[i] = dist;
    delay(10);              //delay between measurements
  }
  dist = (aver[0] + aver[1] + aver[2]) / 3;

  if ( dist < 20 ) { //distance between things and sensor
    //Change distance as per your need
    servo.attach(servoPin);
    delay(1);
    servo.write(0);
    delay(3000);
    servo.write(150);
    delay(1000);
    servo.detach();
  }
  Serial.print(dist);
}
