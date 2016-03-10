#include <Wire.h>

#include<stdio.h>

unsigned int val = 0;
unsigned char PIN = A0;

void setup() {
  Serial.begin(115200);
  pinMode(PIN,INPUT);
   Serial.println("inizio ricezione");
   
   delay(100);
}

void loop() {

 
  val = analogRead(PIN);
   delay(100);
  
  Serial.println(val);
   delay(1000);
 
}
