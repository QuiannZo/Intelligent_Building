// Photoresistor Code

int ldr = 0;
int ldr_value = 0;


void setup()
{
  Serial.begin (9600);
}

void loop()
{
  ldr_value = analogRead (ldr);
  Serial.println (ldr_value);
  
  delay(1000); // Wait for 1000 millisecond(s)
}
