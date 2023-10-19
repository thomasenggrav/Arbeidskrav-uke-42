#include <Arduino.h>
#line 1 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
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
int current_modus = 0;

unsigned long buttonPressTime = 0; // Time when the button was pressed
unsigned long buttonReleaseTime = 0; // Time when the button was released
unsigned long buttonDuration = 0;    // Duration the button was presse


const long gulBlinkInterval = 850;   // Interval i millisekunder (850ms) for gul LED
const long fargeBlinkInterval = 500;  // Interval i millisekunder (500ms) for rød og grønn LED

#line 23 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void setup();
#line 31 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void loop();
#line 38 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void gulBlink();
#line 53 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void rodBlink();
#line 66 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void gronnBlink();
#line 80 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void buttonPress();
#line 103 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void blink();
#line 23 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
void setup() {
  pinMode(redLedPin, OUTPUT);      // Setter rød LED-pin til utgang
  pinMode(yellowLedPin, OUTPUT);   // Setter gul LED-pin til utgang
  pinMode(greenLedPin, OUTPUT);    // Setter grønn LED-pin til utgang
  pinMode(buttonPin, INPUT_PULLUP);      // Setter knapp-pin til inngang
  Serial.begin(9600);
}

void loop() {
  buttonPress(); // Kall på buttonPress funksjon
  gulBlink();  // Kall funksjonen for å blinke gul LED
  blink();     // Kall på blink funksjon
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


void buttonPress(){
  
  unsigned long modusTrykkLengde = 2000;    //To sekunder for modus endring
  static int lastButtonState = LOW;         //Forrige buttonState
  static unsigned long buttonPressStartTime = 0;    //Start tid på knappetrykk
  int buttonState = digitalRead(buttonPin);         //Leser knappe state
  unsigned long buttonPressDuration = millis() - buttonPressStartTime;  //Hvor langt knappetrykket er

 if (buttonState == HIGH && lastButtonState == LOW) {       //Om knappen trykkes kort så endrer current color
    buttonPressStartTime = millis();                        //Start av knappetrykk
    Serial.println("Button Pressed");
	current_color = 1 - current_color;
  }

 if (buttonState == HIGH && buttonPressDuration >= modusTrykkLengde) {      //Om knappetrykket er lengre endres modus
    Serial.println("Button Long Pressed");
    current_modus = 1 - current_modus;
    Serial.println(current_modus);
  }

 lastButtonState = buttonState;     //Forrige button state
}

void blink(){
  if(current_color == 0 && current_modus == 0){     //Endrer farge og modus i forhold til hva current_color og current_modus er
    rodBlink();
    digitalWrite(greenLedPin, LOW);
  }
  if(current_color == 0 && current_modus == 1){
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  }
  if(current_color == 1 && current_modus == 0){
    gronnBlink();
    digitalWrite(redLedPin, LOW);
  }
  if(current_color == 1 && current_modus == 1){
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
  }
}
