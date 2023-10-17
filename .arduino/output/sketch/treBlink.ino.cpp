#include <Arduino.h>
#line 1 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
const int redLedPin = 13;
const int yellowLedPin = 12;
const int greenLedPin = 11;
const int buttonPin = 2;
unsigned long previousMillisYellow = 0;
unsigned long previousMillisColor = 0;

bool greenLedOn = false;
bool redLedOn = false;

bool buttonState = LOW;
bool lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int current_color = 0;


const long gulBlinkInterval = 850;  // Interval in milliseconds (850ms)
const long fargeBlinkInterval = 500;

#line 22 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void setup();
#line 29 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void loop();
#line 36 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void gulBlink();
#line 51 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void rodBlink();
#line 64 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void gronnBlink();
#line 77 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void hvilkenFarge();
#line 22 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\treBlink\\treBlink.ino"
void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  gulBlink();
  hvilkenFarge();
}



void gulBlink(){
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillisYellow >= gulBlinkInterval) {
    previousMillisYellow = currentMillis;

    if (digitalRead(yellowLedPin) == LOW) {
      digitalWrite(yellowLedPin, HIGH);
    } else {
      digitalWrite(yellowLedPin, LOW);
    }
  }
}


void rodBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) {
    previousMillisColor = currentMillis;

    if (digitalRead(redLedPin) == LOW) {
      digitalWrite(redLedPin, HIGH);
    } else {
      digitalWrite(redLedPin, LOW);
    }
  }
}

void gronnBlink(){
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisColor >= fargeBlinkInterval) {
    previousMillisColor = currentMillis;

    if (digitalRead(greenLedPin) == LOW) {
      digitalWrite(greenLedPin, HIGH);
    } else {
      digitalWrite(greenLedPin, LOW);
    }
  }
}

void hvilkenFarge() {
  buttonState = digitalRead(buttonPin);
  unsigned long currentMillis = millis();

  if (buttonState != lastButtonState) {
    if (currentMillis - lastDebounceTime >= debounceDelay) {
      if (buttonState == LOW) {
        current_color = 1 - current_color;  // Toggle between 0 and 1
      }
      lastDebounceTime = currentMillis;
    }
  }
  lastButtonState = buttonState;

  if (current_color == 0) {
    rodBlink();
    digitalWrite(greenLedPin, LOW);
  } 
  else if (current_color == 1) {
    gronnBlink();
    digitalWrite(redLedPin, LOW);
  }
}
