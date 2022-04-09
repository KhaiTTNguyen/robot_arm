
#include <Servo.h>

// declare servo object
Servo claw;

// declare functions
void runStepper(int, float);
void runStepperR(int, float);
int stepCounter(float);

void setup()
{
 Serial.begin(9600);

  // Designate pin 13 for servo
 claw.attach(13);

 // Set pints for output
 for(int i=0;i<13;i++)
  {
    pinMode(i,OUTPUT);
  }
}

void loop()
{
  runStepperR(1, 90);
  delay(500);
  runStepperR(2, 90);
  delay(500);
  runStepperR(3,90);

  delay(500);
    claw.write(0);
    delay(500);
    claw.write(90);
    delay(500);
    claw.write(180);
    delay(500);
    claw.write(90);
}

// Turns an angle into a number of steps
int stepCounter(float degr){
  int steps = 512*(degr/360);
  return steps;
}

// Runs the correct pins for a motor (1 to 30) and moves it forward an angle.
void runStepper(int motor, float angle)
{
  int a = stepCounter(angle);
  int c = ((motor-1)*4) + 2;

  if(motor = 3){
    c = c-1;
  }
  
  for(int b = a; b > 0; b--)
  {
   for(int i=c;i<c+4;i++)
   {
    digitalWrite(i,1);
    delay(10);
    digitalWrite(i,0);
   }
  }
  
}

// Runs the correct pins for a motor (1 to 30) and moves it backwards an angle.
void runStepperR(int motor, float angle)
{
  int a = stepCounter(angle);
  int c = ((motor-1)*4) + 2;

  if(motor == 3){
    c = c-1;
    for(int b = a; b > 0; b--)
    {
     for(int i=c+3;i>=c;i--)
     {
        digitalWrite(i,1);
        delay(10);
        digitalWrite(i,0);
     }
    }
  }
  else{
  for(int b = a; b > 0; b--)
    {
       for(int i=c+4;i>c;i--)
       {
        digitalWrite(i,1);
        delay(10);
        digitalWrite(i,0);
       }
     }
  }
}

  
