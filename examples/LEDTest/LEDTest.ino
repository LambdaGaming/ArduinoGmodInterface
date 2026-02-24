// Turn on the built-in LED when receiving a 1 as an input
// Can be used with something like a Wiremod switch to toggle an IRL light from in-game

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
