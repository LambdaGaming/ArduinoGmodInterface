#define BAUD 9600
#define DELAY_TIME 100
#define led LED_BUILTIN

String receivedString;

void setup() {
  Serial.begin( BAUD );
  pinMode( led, OUTPUT );
}

void loop() {
  if ( Serial.available() > 0 )
  {
    receivedString = Serial.readStringUntil( '\n' );
  }
  
  if ( receivedString.equals( "ON" ) )
  {
    digitalWrite( led, HIGH );
  }
  else if ( receivedString.equals( "OFF" ) )
  {
    digitalWrite( led, LOW );
  }
}
