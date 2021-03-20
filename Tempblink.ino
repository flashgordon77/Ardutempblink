
void setup()
{
  Serial.begin(9600);
  Serial.println(F("Internal temperature sensor"));
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Serial.println(getTemp(), 2);
  delay(2000);
}

double getTemp(void)
{
  unsigned int wADC;
  int t;
  int p = 0;
  int q = 0;
  int x = 0;

  // The internal temperature has to be used with the internal reference of 1.1V.
  // Channel 8 can not be selected with the analogRead function yet.

  // Set the internal reference and mux.
  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  // wait for voltages to become stable.
  delay(20);

  // Start the ADC
  ADCSRA |= _BV(ADSC);

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA, ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celsius.

  p = t % 100 / 10;
  q = t % 10;


 // Serial.println(p);
// / Serial.println(q);

  while (x < p) {

    digitalWrite(LED_BUILTIN, HIGH);
    delay(700);
    digitalWrite(LED_BUILTIN, LOW);
    delay(400);
    Serial.println("a");
    x++;
  } 
  
  
  delay (1000);
  x = 0;
  Serial.println("a ende");
  
  while (x < q) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(400);
    Serial.println("b");
    x++;
  } 
  
  x = 0;
 Serial.println("b ende");
 delay (1000);
  return (t);
}
