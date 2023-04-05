void setup() 
{
  pinMode(8, OUTPUT);
}

void loop() 
{
  digitalRead(10)? digitalWrite(8, LOW) : digitalWrite(8, HIGH);
}
