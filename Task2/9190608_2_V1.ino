#define interruptPin 2

unsigned long prevMillis = 0;
int currentLed = 0;
int leds[12] = {0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int state = 0;


void handler()
{
  if (state != 2)
  {
    state++;
  }
  else
  {
    state--;
  }
  digitalWrite(leds[currentLed], LOW);
}

void setup() 
{
  attachInterrupt(digitalPinToInterrupt(interruptPin), handler, RISING);

  for (int i = 0; i < 12; i++)
  {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
    
}

void loop() 
{
  if (state != 0)
  {
      currentLed = 0;
      if (state == 1)
      {
         while (state == 1)
         {
           digitalWrite(leds[currentLed], HIGH);
           prevMillis = millis();
           while(state == 1 && (unsigned long)(millis() - prevMillis) < 3000);
           digitalWrite(leds[currentLed], LOW);
           currentLed = (currentLed + 1) % 12;
         }
      }
      else
      {
         while (state == 2)
         {
            digitalWrite(leds[currentLed], HIGH);
            prevMillis = millis();
            while(state == 2 && (unsigned long)(millis() - prevMillis) < 1000);
            digitalWrite(leds[currentLed], LOW);
            if (currentLed == 0)
            {
             currentLed = 11;
            }
            else
            {
              currentLed--;
            }
         }
      }
  }
}
