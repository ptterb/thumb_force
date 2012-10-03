#include <Servo.h> //import servo library through menu
#include "pitches.h" // import pitches

Servo servoMotor; // instance of servo object
int servoPin = 8; // control pin for servo

// notes in the melody:
 int melody[] = {NOTE_FS6, NOTE_F6, NOTE_FS6, NOTE_F6, NOTE_FS6, NOTE_F6, 
 NOTE_FS6, 0, NOTE_GS6, NOTE_G6, NOTE_GS6, NOTE_G6, NOTE_GS6, NOTE_G6, NOTE_GS6,
 0, NOTE_F6, NOTE_E6, NOTE_F6, NOTE_E6, NOTE_F6, NOTE_E6, NOTE_F6, 0,
 NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_F6, NOTE_FS6, NOTE_FS6, NOTE_FS6};
 
 // note durations: 4 = quarter note, 8 = eighth note, etc.:
 int noteDurations[] = {4,4,4,4,4,4,4,8,4,4,4,4,4,4,4,8,4,4,4,4,4,4,4,
 8,4,4,4,4,4,4,4 };
 

void setup(){
  Serial.begin(9600);
  servoMotor.attach(servoPin); // attaches the servo on pin 2
  for (int pin = 2; pin < 8; pin++){
    pinMode(pin, OUTPUT);
  }
  
//  // iterate over the notes of the melody:
//   for (int thisNote = 0; thisNote < 31; thisNote++) {
//
//     // to calculate the note duration, take one second 
//     // divided by the note type.
//     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//     int noteDuration = 1000/noteDurations[thisNote];
//     tone(9, melody[thisNote],noteDuration);
//
//     //pause for the note's duration plus 30 ms:
//     delay(noteDuration +30);
//   }
}

void loop(){
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  
  // print out the value you read:
  Serial.println(sensorValue);

  
  // Delay to smooth out readings
  delay(5);

  //map flex sensor input to servo angle
  int servoAngle = map(sensorValue, 0,450,0,179);

  // Move the servo the desired angle only if above threshold
  if (servoAngle > 10) {
    servoMotor.write(servoAngle);
  } 
  
  // Map flex sensor input to frequency
  float freq = map(sensorValue,0,450,100,1000);
  
  //turn on the LEDs according to how hard the sensor is pressed
  if (sensorValue > 25) {
    for (int pin = 2; pin < 3; pin++){
      digitalWrite(pin, HIGH);
    }
  }
  if (sensorValue > 50) {
    for (int pin = 2; pin < 4; pin++){
      digitalWrite(pin, HIGH);
    }
  }
  if (sensorValue > 100) {
    for (int pin = 2; pin < 5; pin++){
      digitalWrite(pin, HIGH);
    }
  }
  if (sensorValue > 150) {
    for (int pin = 2; pin < 6; pin++){
      digitalWrite(pin, HIGH);
    }
  }
  if (sensorValue > 200) {
    for (int pin = 2; pin < 7; pin++){
      digitalWrite(pin, HIGH);
    }
  }
  if (sensorValue > 250) {
    for (int pin = 2; pin < 8; pin++){
      digitalWrite(pin, HIGH);
    }
    
    // loop through melody if player gets high enough score
   for (int thisNote = 0; thisNote < 31; thisNote++) {

     // to calculate the note duration, take one second 
     // divided by the note type.
     //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     int noteDuration = 1000/noteDurations[thisNote];
     tone(9, melody[thisNote],noteDuration);

     //pause for the note's duration plus 30 ms:
     delay(noteDuration +30);
   }
  }
  if (sensorValue < 25) {
    for (int pin = 2; pin < 8; pin++){
      digitalWrite(pin, LOW);
    }
  }

}
