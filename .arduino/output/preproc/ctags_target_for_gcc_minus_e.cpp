# 1 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
const int redLedPin = 13;
const int yellowLedPin = 12;
const int greenLedPin = 11;
const int buttonPin = 2;
unsigned long previousMillisYellow = 0;
unsigned long previousMillisColor = 0;

bool greenLedOn = false;
bool redLedOn = false;

bool buttonState = 0x0;
bool lastButtonState = 0x0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int current_color = 0;


const long gulBlinkInterval = 850; // Interval in milliseconds (850ms)
const long fargeBlinkInterval = 500;

void setup() {
  pinMode(redLedPin, 0x1);
  pinMode(yellowLedPin, 0x1);
  pinMode(greenLedPin, 0x1);
  pinMode(buttonPin, 0x0);
}

void loop() {
  gulBlink();
  hvilkenFarge();
}



void gulBlink(){
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillisYellow >= gulBlinkInterval) {
    previousMillisYellow = currentMillis;

    if (digitalRead(yellowLedPin) == 0x0) {
      digitalWrite(yellowLedPin, 0x1);
    } else {
      digitalWrite(yellowLedPin, 0x0);
    }
  }
}


void rodBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) {
    previousMillisColor = currentMillis;

    if (digitalRead(redLedPin) == 0x0) {
      digitalWrite(redLedPin, 0x1);
    } else {
      digitalWrite(redLedPin, 0x0);
    }
  }
}

void gronnBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) {
    previousMillisColor = currentMillis;

    if (digitalRead(greenLedPin) == 0x0) {
      digitalWrite(greenLedPin, 0x1);
    } else {
      digitalWrite(greenLedPin, 0x0);
    }
  }
}

void hvilkenFarge() {
  buttonState = digitalRead(buttonPin);
  unsigned long currentMillis = millis();

  if (buttonState != lastButtonState) {
    if (currentMillis - lastDebounceTime >= debounceDelay) {
      if (buttonState == 0x0) {
        current_color = 1 - current_color; // Toggle between 0 and 1
      }
      lastDebounceTime = currentMillis;
    }
  }
  lastButtonState = buttonState;

  if (current_color == 0) {
    rodBlink();
    digitalWrite(greenLedPin, 0x0);
  }
  else if (current_color == 1) {
    gronnBlink();
    digitalWrite(redLedPin, 0x0);
  }
}
