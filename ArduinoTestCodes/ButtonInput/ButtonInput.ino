#define BAUD 9600
#define INPIN 12

void setup() {
  Serial.begin( BAUD );
  pinMode( INPIN, INPUT );
  pinMode( LED_BUILTIN, OUTPUT );
}

int buttonstate = 0;

void loop() {
  buttonstate = digitalRead( INPIN );
  if ( buttonstate == LOW )
  {
    digitalWrite( LED_BUILTIN, LOW );
    Serial.write( 0 );
  }
  else
  {
    digitalWrite( LED_BUILTIN, HIGH );
    Serial.write( 1 );
  }
}
