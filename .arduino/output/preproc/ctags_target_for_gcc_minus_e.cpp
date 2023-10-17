# 1 "C:\\Users\\thoma\\OneDrive\\Skrivebord\\Ingeniørprojekt\\Github\\Tre blinkende Leds\\vanligGjennomsnitt\\vanligGjennomsnitt.ino"
int ledPin = 13;
int sensorPin = A0;
int sensorValue = 0;
int interval = 100;
unsigned long previousMillis = 0; //Forrige millis
int blinkState = 0x0; //Holde styr på led state


void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, 0x0); //sensor input
  pinMode(ledPin, 0x1); //led input
}
void loop() {
    sensorReading();
   blink();
}


void sensorReading(){
  for (int i=0; i < 5; i++) { //Tar inn data fra sensorPin og regner gjennomsnittet.
  sensorValue = sensorValue + analogRead(sensorPin);
 }
  sensorValue = sensorValue/5;
  Serial.println(sensorValue); //Printer gjennomsnittet
}

void blink(){
    unsigned long currentMillis = millis();
    int intervalLong = 1000; //Blinke intervaller
    int intervalShort = 166;
    if (currentMillis - previousMillis >= intervalLong && sensorValue >= 100) { //Sjekker om nok tid har passert og sensorReading
        previousMillis = currentMillis; //Blinker i intervalLong intervallet
        if (blinkState == 0x0) { //Endrer på BlinkState, basert på tidligere state
        digitalWrite(ledPin, 0x1);
        blinkState = 0x1;
        }
    else {
      digitalWrite(ledPin, 0x0);
      blinkState = 0x0;
    }
    }
    if(currentMillis - previousMillis >= intervalShort && sensorValue < 100){ //Sjekker om nok tid har passert og sensorReading
        previousMillis = currentMillis; //Blinker i intervalShort intervallet
        if (blinkState == 0x0) { //Endrer på BlinkState, basert på tidligere state
        digitalWrite(ledPin, 0x1);
        blinkState = 0x1;
        }
    else {
      digitalWrite(ledPin, 0x0);
      blinkState = 0x0;
    }
    }
}
