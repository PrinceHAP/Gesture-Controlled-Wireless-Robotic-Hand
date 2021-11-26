#include         <Servo.h>
 
 Servo servo_test;      //initialize a servo object for the connected servo  
                
 int angle = 0;    
     // initialize the A0analog pin for potentiometer

 int pin=9;
 void setup() 
 { 
     // attach the signal pin of servo to pin9 of arduino
     servo_test.attach(9);
 } 
 
 void loop() 
 { 
  servo_test.attach(9);
  servo_test.write(angle);                   //command to rotate the servo to the specified angle 
  delay(198);
  servo_test.attach(10);
  delay(4000);
  servo_test.attach(9);
  servo_test.write(187.5);                   //command to rotate the servo to the specified angle 
  delay(200);
  servo_test.attach(10);
  delay(4000);      
  
  
 }  

               
