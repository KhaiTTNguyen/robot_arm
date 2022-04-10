/*
  Stepper Motor Demonstration 1
  StepperMotor.ino
  Demonstrates 28BYJ-48 Unipolar Stepper with ULN2003A Driver
  Uses Arduino Stepper Library

  BluIcedPen 2018
  https://www.linkedin.com/in/blueicedpen/
*/

//Include the Arduino Stepper Library
#include <Stepper.h>

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
int StepsRequired2;

// Motor 1
int switchPin = 7;
int switchPinRev = 6;
//Extra Boolean variables to keep track of button and motor state
boolean current = LOW;
boolean last = LOW;
boolean currentRev = LOW;
boolean lastRev = LOW;

// Motor 2
int switchPin2 = 13;
int switchPinRev2 = 12;
//Extra Boolean variables to keep track of button and motor state
boolean current2 = LOW;
boolean last2 = LOW;
boolean currentRev2 = LOW;
boolean lastRev2 = LOW;

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing

Stepper steppermotor2(STEPS_PER_REVOLUTION, 8, 10, 9, 11);
Stepper steppermotor(STEPS_PER_REVOLUTION, 2, 4, 3, 5);

void setup()
{
// Nothing  (Stepper Library sets pins as outputs)
  pinMode(switchPin, INPUT);
  pinMode(switchPinRev, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPinRev2, INPUT);
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

boolean debounce2(boolean inLast2){
  boolean inCurrent2 = digitalRead(switchPin2);
  if(inLast2 != current2){
    delay(5);
    inCurrent2 = digitalRead(switchPin2);
  }
  return inCurrent2;
}

boolean debounceRev2(boolean inLastRev2){
  boolean inCurrentRev2 = digitalRead(switchPinRev2);
  if(inLastRev2 != currentRev2){
    delay(5);
    inCurrentRev2 = digitalRead(switchPinRev2);
  }
  return inCurrentRev2;
}

void robotAction(Stepper steppermotor, float factor){
  // Slow - 4-step CW sequence to observe lights on driver board
  
   // Rotate CW 1/2 turn slowly
  StepsRequired  =  STEPS_PER_OUT_REV*factor; 
  steppermotor.setSpeed(1000);   
  steppermotor.step(StepsRequired);
}


void loop()
{
  current2 = debounce2(last2);
  currentRev2 = debounceRev2(lastRev2);
  if(current2 == HIGH){
    robotAction(steppermotor2, 2);
  }
  if(currentRev2 == HIGH){
    robotAction(steppermotor2, -2);
  }
  
  current = debounce(last);
  currentRev = debounceRev(lastRev);
  if(current == HIGH){
    robotAction(steppermotor, 2);
  }
  if(currentRev == HIGH){
    robotAction(steppermotor, -2);
  }
}
