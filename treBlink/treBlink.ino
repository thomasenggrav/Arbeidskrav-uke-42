const int redLedPin = 13;          // Pin for rød LED
const int yellowLedPin = 12;      // Pin for gul LED
const int greenLedPin = 11;       // Pin for grønn LED
const int buttonPin = 2;          // Pin for knapp
unsigned long previousMillisYellow = 0;  // Variabel for tidssporing gul LED
unsigned long previousMillisColor = 0;   // Variabel for tidssporing rød og grønn LED
bool buttonState = LOW;            // Nåværende tilstand til knappen 
bool lastButtonState = LOW;        // Siste kjente tilstand til knappen 
unsigned long lastDebounceTime = 0;   // Tidspunkt for forrige debouncing
unsigned long debounceDelay = 50;  // Tid i millisekunder for debouncing

int current_color = 0;  // Variabel for å holde styr på nåværende LED-farge (0: rød, 1: grønn)

const long gulBlinkInterval = 850;   // Interval i millisekunder (850ms) for gul LED
const long fargeBlinkInterval = 500;  // Interval i millisekunder (500ms) for rød og grønn LED

void setup() {
  pinMode(redLedPin, OUTPUT);      // Setter rød LED-pin til utgang
  pinMode(yellowLedPin, OUTPUT);   // Setter gul LED-pin til utgang
  pinMode(greenLedPin, OUTPUT);    // Setter grønn LED-pin til utgang
  pinMode(buttonPin, INPUT);       // Setter knapp-pin til inngang
}

void loop() {
  gulBlink();       // Kall funksjonen for å blinke gul LED
  hvilkenFarge();   // Kall funksjonen for å velge rød eller grønn LED basert på knapptrykk
}



void gulBlink(){
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillisYellow >= gulBlinkInterval) {   // Sjekker om gulIntervalBlink har passert og kjører kode.
    previousMillisYellow = currentMillis;

    if (digitalRead(yellowLedPin) == LOW) {    // Skrur av og på yellow led
      digitalWrite(yellowLedPin, HIGH);
    } else {
      digitalWrite(yellowLedPin, LOW);
    }
  }
}


void rodBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) {   // Sjekker om fargeIntervallBlink har passert og kjører kode.
    previousMillisColor = currentMillis;

    if (digitalRead(redLedPin) == LOW) {     // Skrur av og på red led
      digitalWrite(redLedPin, HIGH);  
    } else {
      digitalWrite(redLedPin, LOW);
    }
  }
}

void gronnBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) {   // Sjekker om fargeIntervalBlink har passert og kjører kode.
    previousMillisColor = currentMillis;

    if (digitalRead(greenLedPin) == LOW) {     // Skrur av og på green led.
      digitalWrite(greenLedPin, HIGH);
    } else {
      digitalWrite(greenLedPin, LOW);
    }
  }
}

void hvilkenFarge() {
  buttonState = digitalRead(buttonPin);   // Leser button state
  unsigned long currentMillis = millis();

  if (buttonState != lastButtonState) {   // Om button state har endret seg.
    if (currentMillis - lastDebounceTime >= debounceDelay) {  // Debounce delay for ordentlig knappetrykk
      if (buttonState == LOW) {
        current_color = 1 - current_color;  // Endrer verdi på current color mellom 0 og 1
      }
      lastDebounceTime = currentMillis;
    }
  }
  lastButtonState = buttonState;

  if (current_color == 0) {     // Om current color er 0, blink red.
    rodBlink();
    digitalWrite(greenLedPin, LOW);
  } 
  else if (current_color == 1) {    // Om current color er 1, blink green.
    gronnBlink();
    digitalWrite(redLedPin, LOW);
  }
}