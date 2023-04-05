#include <LiquidCrystal.h>
const int rs = 0, en = 1, d4 = 3, d5 = 4, d6 = 5, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define smokePin 2
int smoke_state = 0;


#define potentiometerPin 5
int temperature;
int prevTemp = 200;


#define motorSteps 32
int motor_pins[4] = {9, 10, 11, 12};
int currentStep = 0;
int motorDirection = 0;
unsigned long motorSpeed;
unsigned long lastMilliStep;


void setup() 
{
  attachInterrupt(digitalPinToInterrupt(smokePin), smokeHandler, CHANGE);

  for (int i = 0; i < 4; i++)
  {
    pinMode(motor_pins[i], OUTPUT);
  }
  lcd.begin(16, 2);
  lcd.print("Temperature is");
}

void loop() 
{
  setMotorSpeed(2);
  motorDirection = 0;
  while (smoke_state == 0 && calcTemp() && temperature > 25)  //no smoke and temp > 25
  {
    Step(); 
  }
  while (smoke_state == 1 && calcTemp())
  {
    Step();
  }
  if (smoke_state == 2)
  {
    unsigned long currentTime = millis();
    while (millis() - currentTime < 3000 && calcTemp())
    {
      Step();
    }
    smoke_state = 0;
  }
}

bool calcTemp()
{
  temperature = (((float)(210) / (float)(1023)) * (analogRead(potentiometerPin) - 1023)) + 155;
  if (prevTemp != temperature)
  {
    prevTemp = temperature;
    lcd.setCursor(0, 1);
    lcd.print("   ");
    lcd.setCursor(0, 1);
    lcd.print(temperature);
  }
  return true;
}

void smokeHandler()
{
  if (smoke_state != 2)
  {
    smoke_state++;
    setMotorSpeed(4); 
    motorDirection = 1;
  }
}

void setMotorSpeed(int rpm)
{
  motorSpeed = ((60l * 1000l) / motorSteps) / rpm;
}

void Step()
{
    unsigned long currentMillis = millis();
    if (lastMilliStep == 0 || (unsigned long)(currentMillis - lastMilliStep) >= motorSpeed)
    {
      lastMilliStep = currentMillis;
      if (currentStep == 0)
      {
        if (motorDirection == 0)
        {
          currentStep++;
        }
        else
        {
          currentStep = motorSteps;
        }
      }
      else if (currentStep == motorSteps)
      {
        if (motorDirection == 0)
        {
          currentStep = 0;
        }
        else
        {
          currentStep--;
        }
      }
      else
      {
        if (motorDirection == 0)
        {
          currentStep++;
        }
        else
        {
          currentStep--;
        }
      }
      Run(currentStep % 4);
   } 
}
    

void Run(int currentstep)
{
  switch (currentstep)
  {
    case 0:
      digitalWrite(motor_pins[0], 1);
      digitalWrite(motor_pins[1], 0);
      digitalWrite(motor_pins[2], 1);
      digitalWrite(motor_pins[3], 0);
      break;

      case 1:
      digitalWrite(motor_pins[0], 0);
      digitalWrite(motor_pins[1], 1);
      digitalWrite(motor_pins[2], 1);
      digitalWrite(motor_pins[3], 0);
      break;
      
    case 2:
      digitalWrite(motor_pins[0], 0);
      digitalWrite(motor_pins[1], 1);
      digitalWrite(motor_pins[2], 0);
      digitalWrite(motor_pins[3], 1);
      break;
    
    case 3:
      digitalWrite(motor_pins[0], 1);
      digitalWrite(motor_pins[1], 0);
      digitalWrite(motor_pins[2], 0);
      digitalWrite(motor_pins[3], 1);
      break;  
  }
}
