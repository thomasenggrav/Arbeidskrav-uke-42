# 1 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlinkBonus\\treBlinkBonus.ino"
const int redLedPin = 13; // Pin for rød LED
const int yellowLedPin = 12; // Pin for gul LED
const int greenLedPin = 11; // Pin for grønn LED
const int buttonPin = 2; // Pin for knapp
unsigned long previousMillisYellow = 0; // Variabel for tidssporing gul LED
unsigned long previousMillisColor = 0; // Variabel for tidssporing rød og grønn LED
bool buttonState = 0x0; // Nåværende tilstand til knappen 
bool lastButtonState = 0x0; // Siste kjente tilstand til knappen 
unsigned long lastDebounceTime = 0; // Tidspunkt for forrige debouncing
unsigned long debounceDelay = 50; // Tid i millisekunder for debouncing

int current_color = 0; // Variabel for å holde styr på nåværende LED-farge (0: rød, 1: grønn)
int current_modus = 0;

unsigned long buttonPressTime = 0; // Time when the button was pressed
unsigned long buttonReleaseTime = 0; // Time when the button was released
unsigned long buttonDuration = 0; // Duration the button was presse


const long gulBlinkInterval = 850; // Interval i millisekunder (850ms) for gul LED
const long fargeBlinkInterval = 500; // Interval i millisekunder (500ms) for rød og grønn LED

void setup() {
  pinMode(redLedPin, 0x1); // Setter rød LED-pin til utgang
  pinMode(yellowLedPin, 0x1); // Setter gul LED-pin til utgang
  pinMode(greenLedPin, 0x1); // Setter grønn LED-pin til utgang
  pinMode(buttonPin, 0x2); // Setter knapp-pin til inngang
  Serial.begin(9600);
}

void loop() {
  buttonPress(); // Kall på buttonPress funksjon
  gulBlink(); // Kall funksjonen for å blinke gul LED
  blink(); // Kall på blink funksjon
}


void gulBlink(){
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillisYellow >= gulBlinkInterval) { // Sjekker om gulIntervalBlink har passert og kjører kode.
    previousMillisYellow = currentMillis;

    if (digitalRead(yellowLedPin) == 0x0) { // Skrur av og på yellow led
      digitalWrite(yellowLedPin, 0x1);
    } else {
      digitalWrite(yellowLedPin, 0x0);
    }
  }
}


void rodBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) { // Sjekker om fargeIntervallBlink har passert og kjører kode.
    previousMillisColor = currentMillis;

    if (digitalRead(redLedPin) == 0x0) { // Skrur av og på red led
      digitalWrite(redLedPin, 0x1);
    } else {
      digitalWrite(redLedPin, 0x0);
    }
  }
}

void gronnBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) { // Sjekker om fargeIntervalBlink har passert og kjører kode.
    previousMillisColor = currentMillis;

    if (digitalRead(greenLedPin) == 0x0) { // Skrur av og på green led.
      digitalWrite(greenLedPin, 0x1);
    } else {
      digitalWrite(greenLedPin, 0x0);
    }
  }
}


void buttonPress(){

  unsigned long modusTrykkLengde = 2000; //To sekunder for modus endring
  static int lastButtonState = 0x0; //Forrige buttonState
  static unsigned long buttonPressStartTime = 0; //Start tid på knappetrykk
  int buttonState = digitalRead(buttonPin); //Leser knappe state
  unsigned long buttonPressDuration = millis() - buttonPressStartTime; //Hvor langt knappetrykket er

 if (buttonState == 0x1 && lastButtonState == 0x0) { //Om knappen trykkes kort så endrer current color
    buttonPressStartTime = millis(); //Start av knappetrykk
    Serial.println("Button Pressed");
 current_color = 1 - current_color;
  }

 if (buttonState == 0x1 && buttonPressDuration >= modusTrykkLengde) { //Om knappetrykket er lengre endres modus
    Serial.println("Button Long Pressed");
    current_modus = 1 - current_modus;
    Serial.println(current_modus);
  }

 lastButtonState = buttonState; //Forrige button state
}

void blink(){
  if(current_color == 0 && current_modus == 0){ //Endrer farge og modus i forhold til hva current_color og current_modus er
    rodBlink();
    digitalWrite(greenLedPin, 0x0);
  }
  if(current_color == 0 && current_modus == 1){
    digitalWrite(redLedPin, 0x1);
    digitalWrite(greenLedPin, 0x0);
  }
  if(current_color == 1 && current_modus == 0){
    gronnBlink();
    digitalWrite(redLedPin, 0x0);
  }
  if(current_color == 1 && current_modus == 1){
    digitalWrite(redLedPin, 0x0);
    digitalWrite(greenLedPin, 0x1);
  }
}
