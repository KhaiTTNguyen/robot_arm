/*
  Stepper Motor Demonstration 1
  StepperMotor.ino
  Demonstrates 28BYJ-48 Unipolar Stepper with ULN2003A Driver
  Uses Arduino Stepper Library

  BluIcedPen 2018
  https://www.linkedin.com/in/blueicedpen/
*/

//Include the Arduino Stepper & servo Library
#include <Stepper.h>
#include <Servo.h>


// Define Constants

// Number of steps per internal motor revolution 
const float STEPS_PER_REVOLUTION = 16; 

//  Amount of Gear Reduction
const float GEAR_REDUCTION = 1;

// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REVOLUTION * GEAR_REDUCTION;

// Define Variables

// Number of Steps Required
int StepsRequired;

Stepper steppermotor(STEPS_PER_REVOLUTION, 2, 4, 3, 5);
Servo myservo;  // create servo object to control a servo

// Motor 1
int switchPin = 7;
int switchPinRev = 6;
//Extra Boolean variables to keep track of button and motor state
boolean current = LOW;
boolean last = LOW;
boolean currentRev = LOW;
boolean lastRev = LOW;

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup()
{
// Nothing  (Stepper Library sets pins as outputs)
  pinMode(switchPin, INPUT);
  pinMode(switchPinRev, INPUT);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}
//Corrects push button bounce (not the best debounce function)
boolean debounce(boolean inLast){
  boolean inCurrent = digitalRead(switchPin);
  if(inLast != current){
    delay(5);
    inCurrent = digitalRead(switchPin);
  }
  return inCurrent;
}

boolean debounceRev(boolean inLastRev){
  boolean inCurrentRev = digitalRead(switchPinRev);
  if(inLastRev != currentRev){
    delay(5);
    inCurrentRev = digitalRead(switchPinRev);
  }
  return inCurrentRev;
}

void garageAction(float factor){
  // Slow - 4-step CW sequence to observe lights on driver board
  
   // Rotate CW 1/2 turn slowly
  StepsRequired  =  STEPS_PER_OUT_REV*factor; 
  steppermotor.setSpeed(1000);   
  steppermotor.step(StepsRequired);
}


void loop()
{
  current = debounce(last);
  currentRev = debounceRev(lastRev);
  if(current == HIGH){
  garageAction(2);
  }
  if(currentRev == HIGH){
  garageAction(-2);
  }

  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
