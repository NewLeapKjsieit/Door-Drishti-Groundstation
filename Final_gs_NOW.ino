
/*
  ROTATOR CONTROL FOR GROUND STATION OF
  NEW LEAP INITIATIVE TEAM BY GROUND STATION SUBSYSTEM.

  THIS PROGRAM USES SERIAL VALUES SENT BY PREDICT(KD2BD) SOFTWARE 
  ON THE LINUX MACHINE.
  
  THIS PROGRAM ALSO USES A 180deg SERVO AND A 360deg SERVO
  FOR ELEVATION AND AZIMUTH CONTROL RESPECTIVELY.
  
  AZIMUTH SERVO IS CONNECTED TO PIN 5 AND
  ELEVATION SERVO IS CONNECTED TO PIN 6 OF ARDUINO.

  AUTHOR: GROUND STATION TEAM

  MODIFIED ON 5 JAN, 2019.
*/
#include<Servo.h>

Servo azServo;
Servo elServo;


String az = "";
String el = "";
float el1;
float az1;
float temp_az,temp_az1, temp_el,temp_el1;

void setup() {
  Serial.begin(9600);
  azServo.attach(5);
  elServo.attach(6);
}

void loop() {
  if(Serial.available()!=0){
      char val = Serial.peek();
      if (val == 'A' or val == 'Z' or val == 'E' or val == 'L' )
      {       
        if (val == 'A' or val == 'Z')
        {
          if(val == 'A'){
            Serial.readStringUntil('Z');
            az = Serial.readStringUntil(' ');
            az1 = az.toFloat();
            //while(azServo.read()!= az1){    
              //azServo.write(az1);
            //}
          }
          else{
            Serial.readStringUntil(' ');
            az = Serial.readStringUntil(' ');
            az1 = az.toFloat();
            /*while(azServo.read()!= az1){    
              azServo.write(az1);
            }*/
          }   
        }
        if (val == 'E' or val == 'L')
        {
          if(val == 'E'){
            Serial.readStringUntil('L');
            el = Serial.readStringUntil(' ');
            el1 = el.toFloat();
            //while(elServo.read()!= el1){    
             // elServo.write(el1);
            //}
          }
          else{
            Serial.readStringUntil(' ');
            el = Serial.readStringUntil(' ');
            el1 = el.toFloat();
           // while(elServo.read()!= el1){    
             // elServo.write(el1);
            //}
          }
        }
        Serial.println(az1);
        Serial.println(el1);

        //code for movement
        if(az1 > 180)
        {
          temp_az = az1-180.0;
          temp_az1= map(temp_az,0,180,550,2025);
          azServo.write(temp_az1);
          temp_el = 180.0 - el1;
          temp_el1= map(temp_el,0,180,550,2025);
          elServo.write(temp_el1);
          }
         else{
          temp_az1 = map(az1,0,180,550,2025);
          azServo.write(temp_az1);
          temp_el1 = map(el1,0,180,550,2025);
          elServo.write(temp_el1);
          }
    }  
    else
    {
      Serial.read();
      }
 }  
}








  
