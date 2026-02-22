#define BAUD 9600
#define led LED_BUILTIN

String receivedString;

void setup() {
  Serial.begin( BAUD );
  pinMode( led, OUTPUT );
}

void loop() {
  if ( Serial.available() > 0 )
  {
    receivedString = Serial.readString();
    if ( receivedString.equals( "1" ) )
    {
      digitalWrite( led, HIGH );
    }
    else if ( receivedString.equals( "0" ) )
    {
      digitalWrite( led, LOW );
    }
  }
  delay(100);
}
