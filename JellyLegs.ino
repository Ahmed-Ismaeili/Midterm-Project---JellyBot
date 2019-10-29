/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include <Wire.h>

// create servo object to control a servo
Servo servo1;  
Servo servo2;
Servo servo3;
Servo servo4;

bool servo1Dir=true;
bool servo2Dir=true;
bool servo3Dir=true;
bool servo4Dir=true;

// variable to store the servo position. Set distance and distanceValue so that the JellyLegs are at minimum speed when nothing is infront of the sensor
int pos = 0;    // variable to store the servo position
float distance=90.0;
float distanceValue=0.0;

// set servo signal inputs
void setup() {
  servo1.attach(6);  // attaches the servo on pin 9 to the servo object
  servo2.attach(11);
  servo3.attach(9);
  servo4.attach(10);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

}

void loop() {
  distanceValue=map(distance,50.0,90.0,5.0,30.0);
  // original code without adjustments that the new code was based off of. A spin off of the original example
//  for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    servo1.write(pos);              // tell servo to go to position in variable 'pos'
//    servo2.write(pos); 
//    servo3.write(pos); 
//    servo4.write(pos); 
//    delay(15*distanceValue);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 150; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    servo1.write(pos);              // tell servo to go to position in variable 'pos'
//    servo2.write(pos); 
//    servo3.write(pos); 
//    servo4.write(pos);  
//    delay(15*distanceValue);                       // waits 15ms for the servo to reach the position
//  }

// Servo direction function call
  servo1Dir=step(servo1,servo1Dir);
  servo2Dir=step(servo2,servo2Dir);
  servo3Dir=step(servo3,servo3Dir);
  servo4Dir=step(servo4,servo4Dir);
  delay(distanceValue);
  //Serial.println(servo2.read());
  Serial.println(servo2Dir);
}

bool step(Servo s,bool dir){
  // Randomness set to a one percent chance of changing direction per step. 150 steps per rotation with random change print in the serial monitor to monitor change
  long r=random(0,100);
  if(r<=1){
    if(dir==1){
      return 0;
    }else{
      return 1;
    }
    Serial.println("random change");
  }
  if(dir==1){
    s.write(s.read()+1);
  }else{
    s.write(s.read()-1);
  }

  // Directional changes set for when the angle of the motor horn reaches 0 or 150. Coded changes rather than random
  if(s.read()==0){
    //Serial.println(s.read());
    return true;
  }
  else if(s.read()>=150){
    //Serial.println("changing");
    return false;
  }else{
    return dir;
  }
}

// code used to read distance sensor values from another arduino to this one
void receiveEvent(int howMany){
  distance=Wire.read();       // between 50.0 and 90.0
  Serial.println(distance);
}
